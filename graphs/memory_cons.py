#!/usr/bin/python
import subprocess
import matplotlib as mpl
from matplotlib import pyplot as plt
from matplotlib import ticker
import numpy as np
import re
import cPickle
import numpy
from math import log
from math import sqrt


FIRST_PHINDEX = 3
LAST_PHINDEX = 14
window_size = 65536
epsilonsrange = range(FIRST_PHINDEX,LAST_PHINDEX)
epsilons = [2**(-x) for x in epsilonsrange] #actually its counters parameters (counters = 1/epsilon)



def plot_memory(memory):
    average_memory= memory
    phis = [2**(-x) for x in epsilonsrange]
    MS = 12
    LW = 4

    plt.plot(phis, average_memory["PAPA"],"-.8"	,label="$PAPA$",markersize=MS, linewidth=LW, c="blue")
    plt.plot(phis, average_memory["NAPA"],":*"	,label="$NAPA$" , ms=MS,markersize=MS, linewidth=LW, c="red")


    ##for algorithm in speed:
    ##    plt.plot(phis, speed[algorithm],label=algorithm)
    plt.xscale("log",basex=2)
    plt.yscale("log",basex=2)

    #ticks,labels = plt.xticks()
    #plt.xticks(ticks[::2],labels[::2])
    plt.gca().xaxis.set_major_locator(ticker.LogLocator(base=2))

    plt.xlabel("Accuracy Guarantee ($\epsilon$)", fontsize=36)
    ylabel_str = "Memory [MB]"
    plt.ylabel(ylabel_str, fontsize=24)
    plt.tick_params(labelsize=20)
    plt.xlim(left = 2**-(LAST_PHINDEX-1), right=2**-FIRST_PHINDEX)
    plt.ylim(0, 80000000)


    #plt.legend(loc="best") # keys of the graphs
    #plt.legend(loc="best",prop={'size':13},ncol=14) # keys of the graphs
    #plt.legend(prop={'size':9},ncol=13) # keys of the graphs

    plt.tight_layout()
    plt.savefig('memory.png')
    plt.clf()

def calc_memory(eps):
    RSS_WCSS = 108 * (4/eps)
    RSS_HIT = 108 * (5/eps)
    RSS_ACC1 = 108 * (5/eps)

    B_WCSS = (4/eps) * (4 + ((log((4/eps), 2))/8))

    b_WCSS = 4 * (4/eps)

    ACC1 = (5/eps) * (5/eps) * (4 + log(5/eps, 2)/8)
    ACC2 = (5/eps) * 2 * sqrt((5/eps)) * (4 + log(5/eps, 2)/8)
    acc = []
    for i in range(1, 32):
        acc.append((5/eps)**(1 + (1.0/ i)) * i  * (4 + log(5/eps, 2)/8) + RSS_ACC1)
    HIT = (5/eps) * log(5/eps, 2) * (4 + log(5/eps, 2)/8)

    WCSS = RSS_WCSS + B_WCSS + b_WCSS
    ACC1 = RSS_ACC1 + ACC1
    ACC2 = RSS_ACC1 + ACC2
    HIT = RSS_ACC1  + HIT
    RAW = (4/eps) * WCSS

    memory["RAW"].append((RAW/ 1e6))
    memory["hhh2RSS"].append((HIT/ 1e6))
    memory["baseWRSS"].append((WCSS/ 1e6))
    memory["acc"].append((ACC1 / 1e6))
    memory["acc1"].append((ACC2/ 1e6))
    memory["acc4"].append((acc[4])/ 1e6)
    memory["acc8"].append((acc[8])/ 1e6)

    delta = 0.0001 #0.0.1%
    oneOverDelta = 1/(delta);
    logOneOverDelta = log(oneOverDelta,2);

    print "ECM"
    print eps
    print (logOneOverDelta * eps**(-2) * 32)/ 1e6
    memory["ECM"].append((logOneOverDelta * eps**(-2) * 32)/ 1e6)


memory = dict()
memory["PAPA"]=[]
memory["NAPA"]=[]

for epsilon in epsilons:
	out = calc_memory(epsilon)

print "memory of y PAPA", memory["PAPA"]
print "memory of y NAPA", memory["nAPA"]

plot_memory(memory)
