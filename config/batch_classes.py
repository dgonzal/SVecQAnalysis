#!/usr/bin/env python

from subprocess import call


def write_script():
    myfile = open('test/split_script.sh','w')
    
    myfile.write(
    """#!/bin/zsh
#
#
# This is a simple example of a SGE batch script
   
sframe_main test/test_${SGE_TASK_ID}.xml
""")
    
    myfile.close()



def submitt_qsub(NFiles):
    print '-t 1-'+str(int(NFiles))
    #call(['qsub' , '-V', '-l os=sld6', '-cwd', '-l site=hh', '-t 1-'+str(NFiles), 'test/split_script.sh'], shell=True)
