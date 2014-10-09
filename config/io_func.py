#!/usr/bin/env python

#python classes
#import xml.dom.minidom

import os
import glob
import getopt
import sys

from xml.dom.minidom import parse, parseString
from xml.dom.minidom import Document
import xml.sax

import math
import time

#my classes
from Inf_Classes import *
from batch_classes import *
"""
options, remainder = getopt.getopt(sys.argv[1:], 'i:v', ['input=', 
                                                         'verbose',
                                                         'version=',
                                                         ])

print 'OPTIONS   :', options

sys.exit(0)
#return 0
"""
def write_job(Job,Version=-1,SkipEvents=0,MaxEvents=-1,NFile =None, FileSplit=-1):
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
        tempChild.setAttribute('PostFix', cycle.PostFix+'_'+str(NFile))
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
            if FileSplit!=-1 and 1 == 1:
                InputGrandchild.setAttribute('Cacheable', 'False')
            else:
                InputGrandchild.setAttribute('Cacheable', cycle.Cycle_InputData[p].Cacheable)
                InputGrandchild.setAttribute('NEventsSkip', str(SkipEvents))
                InputGrandchild.setAttribute('NEventsMax', str(MaxEvents))
        
            count_i =-1
           


            for entry in cycle.Cycle_InputData[p].io_list:
                count_i +=1
               
                if FileSplit==-1 :
                    Datachild= doc.createElement(entry[0])
                    InputGrandchild.appendChild(Datachild)
                    #print entry
                    for it in range(1,(len(entry)-1), 2):
                        #print entry[it],entry[it+1]
                        Datachild.setAttribute(entry[it],entry[it+1])
                       
                elif count_i<(NFile+1)*FileSplit and count_i>= NFile*FileSplit and FileSplit!=-1 and count_i < len(cycle.Cycle_InputData[p].io_list)-2:
                    Datachild= doc.createElement(entry[0])
                    InputGrandchild.appendChild(Datachild)
                                        
                    for it in range(1,(len(entry)), 2):
                        #print entry[it],entry[it+1]
                        Datachild.setAttribute(entry[it],entry[it+1])



            if FileSplit!=-1:
                InputTreePos = len(cycle.Cycle_InputData[p].io_list)-2
                InputTree = doc.createElement(cycle.Cycle_InputData[p].io_list[InputTreePos][0])
                InputGrandchild.appendChild(InputTree)
                InputTree.setAttribute(cycle.Cycle_InputData[p].io_list[InputTreePos][1],cycle.Cycle_InputData[p].io_list[InputTreePos][2])
                
                OutputTreePos = len(cycle.Cycle_InputData[p].io_list)-1
                OutputTree = doc.createElement(cycle.Cycle_InputData[p].io_list[OutputTreePos][0])
                InputGrandchild.appendChild(OutputTree)
                OutputTree.setAttribute(cycle.Cycle_InputData[p].io_list[OutputTreePos][1],cycle.Cycle_InputData[p].io_list[OutputTreePos][2])


        #InGrandGrandchild= doc.createElement('In')

        ConfigGrandchild  = doc.createElement('UserConfig')
        tempChild.appendChild(ConfigGrandchild)

        for item in cycle.Cycle_UserConf:
            ConfigGrandGrandchild = doc.createElement('Item')
            ConfigGrandchild.appendChild(ConfigGrandGrandchild)
            ConfigGrandGrandchild.setAttribute('Name',item.Name)
            ConfigGrandGrandchild.setAttribute('Value',item.Value)

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
                self.FileSplit = int(self.ConfigParse.attributes['FileSplit'].value)

            if 'ConfigSGE' in line : 
                self.ConfigSGE = parseString(line)
            
        f.close()   



def write_all_xml(path,header,Job):
    NEventsBreak= header.NEventsBreak
    LastBreak = header.LastBreak
    FileSplit=header.FileSplit

    NFiles=0

    Version = header.Version
    if Version[0] =='-1':Version =-1

    if NEventsBreak!=0 and LastBreak!=0:
        NFiles=int(math.ceil(LastBreak/NEventsBreak)+1)
        for i in range(int(math.ceil(LastBreak/NEventsBreak)+1)):
            outfile = open(path+'_'+str(i+1)+'.xml','w+')
            for line in header.header:
                outfile.write(line)
            if((i+1)*NEventsBreak < LastBreak):
                outfile.write(write_job(Job,Version,i*NEventsBreak,NEventsBreak,i))
            if((i+1)*NEventsBreak >= LastBreak):
                outfile.write(write_job(Job,Version,i*NEventsBreak,NEventsBreak-(i+1)*NEventsBreak+LastBreak,i))
            outfile.close()
 
    elif FileSplit!=0:
        for entry in Version:
            print 'Going to split job by files:', entry
            for cycle in Job.Job_Cylce:
                for p in range(len(cycle.Cycle_InputData)):
                    if(cycle.Cycle_InputData[p].Version==entry) or Version ==-1:
                        for it in range(int(math.ceil(float(len(cycle.Cycle_InputData[p].io_list)-2)/FileSplit))):
                            outfile = open(path+'_'+str(it+1)+'.xml','w+')
                            for line in header.header:
                                outfile.write(line)
                            outfile.write(write_job(Job,Version,0,-1,it,FileSplit))
                            outfile.close()
                            NFiles+=1
 

    else:
        NFiles+=1
        outfile = open(path+'_OneCore'+'.xml','w+')
        for line in header.header:
            outfile.write(line)
        outfile.write(write_job(Job,Version,0,-1,"",0))
        outfile.close()

    return NFiles



xmlfile = 'par_SVecQ_PreSelection_config0.xml'#"parser_test.xml"

sax_parser = xml.sax.make_parser()
xmlparsed = parse(xmlfile,sax_parser)

header = header(xmlfile)

node = xmlparsed.getElementsByTagName('JobConfiguration')[0]
Job = JobConfig(node)

if not os.path.exists('test/'):
    os.makedirs('test/')
    print 'test/ has been created'


if header.Version[0] == "-1":
    names =[]
    data_type =[]
    NFiles = []
    
    loop_check = True

    for cycle in Job.Job_Cylce:
        for process in range(len(cycle.Cycle_InputData)):
            header.Version = ([cycle.Cycle_InputData[process].Version])
            names.append(cycle.Cycle_InputData[process].Version)
            data_type.append(cycle.Cycle_InputData[process].Type)
            NFiles.append(write_all_xml('test/'+header.Version[0],header,Job))
            write_script(header.Version[0])
            #submitt_qsub(NFiles[len(NFiles)-1],'test/Stream_'+str(header.Version[0]),str(header.Version[0]))

   	resubmit_flag =1 

        while loop_check==True:   
            if len(names)==0: 
                loop_check = False 
                
            del_list =[]    
            tot_prog = 0

            missing = open('missing_files.txt','w+')

  	    i =0

	    	
            for name in names:
                
                rootCounter = 0                
                #print len(names),names[i]#,cycle.OutputDirectory
                for it in range(NFiles[i]):
                    #print cycle.OutputDirectory+'test/'+cycle.Cyclename+'.'+data_type[i]+'.'+names[i]+'_'+str(it)+'.root'
                    if os.path.exists(cycle.OutputDirectory+'test/'+cycle.Cyclename+'.'+data_type[i]+'.'+names[i]+'_'+str(it)+'.root'):
                        rootCounter +=1 
                    else:
                         missing.write(cycle.OutputDirectory+'test/'+cycle.Cyclename+'.'+data_type[i]+'.'+names[i]+'_'+str(it)+'.root\n')
			 if resubmit_flag: resubmit('test/Stream_'+names[i],names[i]+'_'+str(it+1))
                

                tot_prog += rootCounter
                print names[i]+': ', rootCounter, NFiles[i], round(float(rootCounter)/float(NFiles[i]),3)
                if NFiles[i] == rootCounter: 
                   del_list.append(i)
                i+=1


            missing.close()
  	    resubmit_flag = 0

	    del_list.sort(reverse=True)		
            
            for m in del_list:
		add_histos(cycle.OutputDirectory,cycle.Cyclename+'.'+data_type[m]+'.'+names[m],NFiles[m])
                del NFiles[m]
                del names[m]
                del data_type[m]


            #print 'Total progress', tot_prog
            print '------------------------------------------------------'
            time.sleep(45)
            if len(NFiles)==0: loop_check = False 

"""
#else: 
# NFiles = write_all_xml('test/test',header,Job)
# write_script()
# submitt_qsub(NFiles,'test/Stream_'+str(header.Version[0]))
"""
