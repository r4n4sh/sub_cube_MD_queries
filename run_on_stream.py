#!/usr/bin/python
import subprocess
import random
import math
import matplotlib as mpl
from matplotlib import pyplot as plt
from matplotlib import ticker
import numpy as np
import re
import cPickle
import numpy
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


target_file = sys.argv[1] + "_test_add.txt"
f = open(target_file, "w+")
data_set = "dataset.txt"
fn = "./out"
d = 2


#############################################################################
#
#           Run On epsilon
#
#############################################################################

RUNS = 1
efirst = 2
elast = 4
e_range = range(efirst, elast)
epsilons = [2**x for x in e_range]
d = 2
n = 2**10
range = 0

for e in epsilons:
        timing_list = []
        os.system('python generate_dataset.py %s %s' %(str(n), str(d)))
        for run in xrange(RUNS):
            command = [fn,"-e", str(e)]
            if target_file:
                    command += ["-f", data_set, "-n", str(n), "-d", str(d)]
            print " ".join(command)

            out = subprocess.check_output(command)

            if (range == 0):
                timing = re.search("\s(\d+\.\d+)s\s", out).groups()[0]
                timing_list.append(float(timing))
            else:
                f.write(out)
                print out

        if (range == 0):
                lst = timing_list
                mean = sum(lst) / len(lst)
                result = out.split();
                result[6] = str(mean) +"s"
                output = ' '.join(map(str, result))
                f.write(output)
                f.write('\n')

