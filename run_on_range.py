#!/usr/bin/python
import subprocess
import random
import math
import re
import cPickle
import sys
import os



def median(lst):
    lst = sorted(lst)
    if len(lst) < 1:
            return None
    if len(lst) %2 == 1:
            return lst[((len(lst)+1)/2)-1]
    else:
            return float(sum(lst[(len(lst)/2)-1:(len(lst)/2)+1]))/2.0


target_file = sys.argv[1] + "_test.txt"
f = open(target_file, "w+")
#data_set = "facebook_dataset2d.txt"
#data_set = "dfacebookdataset2d.txt"
#data_set = "dataset.txt"
data_set = "cmdataset.txt"
fn = "./out"
d = 2


#############################################################################
#
#           Run On epsilon
#
#############################################################################

RUNS = 1
efirst = 8
elast = 14
m_range = range(efirst, elast)
mranges = [2**x for x in m_range]
d = 2
#n = 500000
n = 32768
ndata = 2**10
range = 1
e = 2**3

for m in mranges:
        timing_list = []
        #os.system('python generate_dataset.py %s %s' %(str(ndata), str(d)))
        for run in xrange(RUNS):
            command = [fn,"-r", str(m)]
            if target_file:
                    command += ["-f", data_set, "-n", str(n), "-d", str(d), "-e", str(e)]
            print " ".join(command)

            out = subprocess.check_output(command)

            if (range == 0):
                print out
                timing = re.search("\s(\d+\.\d+)s\s", out).groups()[0]
                timing_list.append(float(timing))
            else:
                f.write(out)
                print out

        if (range == 0):
                lst = timing_list
                mean = sum(lst) / len(lst)
                result = out.split();
                result[4] = str(mean) +"s"
                output = ' '.join(map(str, result))
                f.write(output)
                f.write('\n')

