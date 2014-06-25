#!/usr/bin/env python

from subprocess import call
import os


def write_script(name):
    myfile = open('test/split_script_'+name+'.sh','w')
    
    myfile.write(
    """#!/bin/zsh
#
#$ -M daniel.gonzalez@desy.de
# This is a simple example of a SGE batch script
   
sframe_main test/"""+name+"""_${SGE_TASK_ID}.xml
if[$?==0] && echo "success "${SGE_TASK_ID}
""")
    
    myfile.close()


def resub_script(name):
    myfile = open('test/split_script_'+name+'.sh','w')
    
    myfile.write(
    """#!/bin/zsh
#
#$ -M daniel.gonzalez@desy.de
# This is a simple example of a SGE batch script
   
sframe_main test/"""+name+""".xml
if[$?==0] && echo "success "
""")
    
    myfile.close()



def submitt_qsub(NFiles,Stream,name):
    #print '-t 1-'+str(int(NFiles))
    #call(['ls','-l'], shell=True)

    if not os.path.exists(Stream):
        os.makedirs(Stream)
        print Stream+' has been created'
 
    print call(['qsub'+' -V'+' -l os=sld6'+' -cwd'+' -l site=hh'+' -t 1-'+str(NFiles)+' -o '+Stream+'/'+' -e '+Stream+'/'+' test/split_script_'+name+'.sh'], shell=True)

def resubmit(Stream,name):
    #print Stream ,name
    resub_script(name)	
    if not os.path.exists(Stream):
        os.makedirs(Stream)
        print Stream+' has been created'
 
    print call(['qsub'+' -V'+' -l os=sld6'+' -cwd'+' -l site=hh'+' -o '+Stream+'/'+' -e '+Stream+'/'+' test/split_script_'+name+'.sh'], shell=True)


def add_histos(directory, name, NFiles) :

    print call(['rm '+directory+name+'.root'], shell=True)
    string =" "

    for i in range(NFiles):
        string += directory+'test/'+name+'_'+str(i)+'.root'
        string += " "

    #print string
    call(['hadd '+directory+name+'.root'+string], shell=True)

    
