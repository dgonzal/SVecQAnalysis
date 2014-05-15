#!/usr/bin/env python

#python classes
#import xml.dom.minidom

import os

from xml.dom.minidom import parse, parseString
from xml.dom.minidom import Document
import xml.sax

from subprocess import call


#my classes
from Inf_Classes import *

def write_job(Job,Version=-1,SkipEvents=0,MaxEvents=-1):
    doc = Document()
    root = doc.createElement("JobConfig")
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
        tempChild.setAttribute('OutputDirectory', cycle.OutputDirectory)
        tempChild.setAttribute('PostFix', cycle.PostFix)
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

            ConfigGrandGrandchild.setAttribute( item.Name,item.Value )

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
    
    Version = header.Version
    if Version[0] =='-1':Version =-1

    if NEventsBreak!=0 and LastBreak!=0:
        for i in range(LastBreak/NEventsBreak+1):
            outfile = open(path+'_'+str(i)+'.xml','w')
            for line in header.header:
                outfile.write(line)
                print line

            if(i*NEventsBreak < LastBreak):
                outfile.write(write_job(Job,Version,i*NEventsBreak,(i+1)*NEventsBreak))
                print write_job(Job,Version,i*NEventsBreak,(i+1)*NEventsBreak)
            if(i*NEventsBreak >= LastBreak):
                outfile.write(write_job(Job,Version,LastBreak))
                print write_job(Job,Version,LastBreak)
            outfile.close()
    
    else:
        outfile = open(path+'_OneCore'+'.xml','w')
        for line in header.header:
            outfile.write(line)
            print line
        print write_job(Job,Version)
        outfile.write(write_job(Job,Version))
        outfile.close()



xmlfile = "parser_test.xml"

sax_parser = xml.sax.make_parser()
xmlparsed = parse(xmlfile,sax_parser)

header = header(xmlfile)

node = xmlparsed.getElementsByTagName('JobConfiguration')[0]
Job = JobConfig(node)

Job.Job_Cylce[0].Cycle_InputData[0].split_NEvents(10000,20000)



NEventsBreak =Job.Job_Cylce[0].Cycle_InputData[0].NEventsBreak
LastBreak = Job.Job_Cylce[0].Cycle_InputData[0].LastBreak

#print write_job(Job,['TTbar'])

if not os.path.exists('test/'):
    os.makedirs('test/')

write_all_xml('test/test',header)

list_name = call(["ls", "-l"])

print list_name
