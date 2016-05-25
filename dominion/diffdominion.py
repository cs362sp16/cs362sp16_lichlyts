#!/usr/bin/python

import subprocess
import os
import sys

devnull = open(os.devnull, 'w')

## check if usage is correct
if (len(sys.argv) != 3):
    print "Usage: diffdominion.py <dominion directory 1> <dominion directory 2>"
    exit(1)

## get dominion directories and put them into an array
domdir1 = sys.argv[1]
domdir2 = sys.argv[2]
doms = [domdir1, domdir2]

home = os.getcwd()
executable = "slltestdom"

## loop through and compile respective dominions
for (d) in doms:
    ##change directories
    print "****** Moving to " + d + " ******"
    cd_compile_command = "cd " + d + "; make clean; make all;"
    subprocess.call([cd_compile_command], shell = True)
    compile_test_command = "gcc " + d + "/dominion.o interface.o rngs.o ./testdominion.c -o " + executable + " -Wall -fpic -coverage -lm"
    print compile_test_command
    subprocess.call([compile_test_command], shell = True)

MAX_TESTS = 35

for test in xrange(1, MAX_TESTS + 1):
    print "Test: " + str(test)
    seed = test
    outfiles = []
    for x in xrange(0, 2):
        outfile = open(str(x) + "_" + str(test) + ".out", 'w')
        subprocess.call(["./" + executable + " " + str(seed)], shell = True, stdout = outfile, stderr = devnull)
        outfile.close()
        outfiles.append(str(x) + "_" + str(test) + ".out")

    result = subprocess.call(["diff " + outfiles[0] + " " + outfiles[1]], shell = True, stdout = devnull, stderr = devnull)
    if (result != 0):
        print "DIFF DETECTED"
        subprocess.call(["diff " + outfiles[0] + " " + outfiles[1]], shell = True)
        break