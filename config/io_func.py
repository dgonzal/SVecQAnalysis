#!/usr/bin/env python

#python classes
#import xml.dom.minidom

import os

from xml.dom.minidom import parse, parseString
from xml.dom.minidom import Document
import xml.sax

import math




#my classes
from Inf_Classes import *
from batch_classes import *


def write_job(Job,Version=-1,SkipEvents=0,MaxEvents=-1,NFile =""):
    doc = Document()
    root = doc.createElement("JobConfiguration")
    root.setAttribute( 'JobName', Job.JobName)
    root.setAttribute( 'OutputLevel', Job.OutputLevel)
    
    for lib in Job.Libs:
        # Create Element
        tempChild = doc.createElement('Library')
        root.appendChild(tempChild)
        
        # Set Attr.
        tempChild.setAttribute( 'Name', lib)
        
    
    for pack in Job.Packs:
        # Create Element
        tempChild = doc.createElement('Package')
        root.appendChild(tempChild)
        
        # Set Attr.
        tempChild.setAttribute( 'Name', pack)
        
    for cycle in Job.Job_Cylce:
        # Create Element
        tempChild = doc.createElement('Cycle')
        root.appendChild(tempChild)
        
        # Set Attr.
        tempChild.setAttribute( 'Name', cycle.Cyclename)
        if not os.path.exists(cycle.OutputDirectory+'test/'):
            os.makedirs(cycle.OutputDirectory+'test/')
        tempChild.setAttribute('OutputDirectory', cycle.OutputDirectory+'test/')
        tempChild.setAttribute('PostFix', cycle.PostFix+str(NFile))
        tempChild.setAttribute('TargetLumi', cycle.TargetLumi)
        
        for p in range(len(cycle.Cycle_InputData)):
            version_check = True
            if(Version!=-1): 
                version_check = False
                for entry in Version:
                    if(cycle.Cycle_InputData[p].Version==entry):
                        version_check = True

            if not version_check: continue;
            # Create Element
            InputGrandchild= doc.createElement('InputData')
            tempChild.appendChild(InputGrandchild)
            
            #tempChild.appendChild(cycle.Cycle_InputData[0].node)
            #cycle.Cycle_InputData[0].node.attributes['NEventsMax'].value = str(MaxEvents)
            #cycle.Cycle_InputData[0].node.attributes['NEventsSkip'].value = str(SkipEvents)
        
            InputGrandchild.setAttribute('Lumi', cycle.Cycle_InputData[p].Lumi)
            InputGrandchild.setAttribute('Type', cycle.Cycle_InputData[p].Type)
            InputGrandchild.setAttribute('Version', cycle.Cycle_InputData[p].Version)
            InputGrandchild.setAttribute('Cacheable', cycle.Cycle_InputData[p].Cacheable)
            InputGrandchild.setAttribute('NEventsSkip', str(SkipEvents))
            InputGrandchild.setAttribute('NEventsMax', str(MaxEvents))
        
            for entry in cycle.Cycle_InputData[p].io_list:
                Datachild= doc.createElement(entry[0])
                InputGrandchild.appendChild(Datachild)
                
                for it in range(1,(len(entry)-1), 2):
                    Datachild.setAttribute(entry[it],entry[it+1])
               
                



        #InGrandGrandchild= doc.createElement('In')

        ConfigGrandchild  = doc.createElement('UserConfig')
        tempChild.appendChild(ConfigGrandchild)

        for item in cycle.Cycle_UserConf:
            ConfigGrandGrandchild = doc.createElement('Item')
            ConfigGrandchild.appendChild(ConfigGrandGrandchild)
            ConfigGrandGrandchild.setAttribute('Name',item.Name)
            ConfigGrandGrandchild.setAttribute('Value',item.Value)
    #print Job.Job_Cylce[0].Cyclename

    return root.toprettyxml()


class header(object):
    
    def __init__(self,xmlfile):
        f = open(xmlfile)
        line = f.readline()
        self.header = []
        self.Version = []
        while '<JobConfiguration' not in line:
            self.header.append(line)
            line = f.readline()
            if 'ConfigParse' in line:
                self.ConfigParse = parseString(line).getElementsByTagName('ConfigParse')[0]
                self.Version = self.ConfigParse.attributes['Version'].value.split(',')
                self.NEventsBreak = int(self.ConfigParse.attributes['NEventsBreak'].value)
                self.LastBreak = int(self.ConfigParse.attributes['LastBreak'].value)

            if 'ConfigSGE' in line : 
                self.ConfigSGE = parseString(line)
            
        f.close()   



def write_all_xml(path,header):
    NEventsBreak= header.NEventsBreak
    LastBreak = header.LastBreak
    #print LastBreak,

    Version = header.Version
    if Version[0] =='-1':Version =-1

    #print LastBreak/NEventsBreak

    if NEventsBreak!=0 and LastBreak!=0:
        for i in range(int(math.ceil(LastBreak/NEventsBreak)+1)):
            outfile = open(path+'_'+str(i+1)+'.xml','w+')
            for line in header.header:
                outfile.write(line)
                #print line
            #print i
            if((i+1)*NEventsBreak < LastBreak):
                outfile.write(write_job(Job,Version,i*NEventsBreak,NEventsBreak,i))
                #print write_job(Job,Version,i*NEventsBreak,(i+1)*NEventsBreak)
            if((i+1)*NEventsBreak >= LastBreak):
                outfile.write(write_job(Job,Version,i*NEventsBreak,NEventsBreak-(i+1)*NEventsBreak+LastBreak,i))
                #print write_job(Job,Version,LastBreak)
            outfile.close()
    
    else:
        outfile = open(path+'_OneCore'+'.xml','w+')
        for line in header.header:
            outfile.write(line)
            #print line
        #print write_job(Job,Version)
        outfile.write(write_job(Job,Version))
        outfile.close()



xmlfile = 'par_SVecQ_PreSelection_config.xml'#"parser_test.xml"

sax_parser = xml.sax.make_parser()
xmlparsed = parse(xmlfile,sax_parser)

header = header(xmlfile)

node = xmlparsed.getElementsByTagName('JobConfiguration')[0]
Job = JobConfig(node)

if not os.path.exists('test/'):
    os.makedirs('test/')

write_all_xml('test/test',header)

write_script()


submitt_qsub(math.ceil(header.LastBreak/header.NEventsBreak)+1)
