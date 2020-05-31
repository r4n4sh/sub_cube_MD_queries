#!/usr/bin/python
import subprocess
import matplotlib as mpl
from matplotlib import pyplot as plt
from matplotlib import ticker
import numpy as np
import re
import cPickle
import numpy
import math
from math import log
from math import sqrt


FIRST_PHINDEX = 1
LAST_PHINDEX = 5
drange = range(FIRST_PHINDEX,LAST_PHINDEX)


N = 1000000
delta_1 = 100
eps = 2**(-3)
limit = 512

def log2(x):
    return math.log(x) / math.log(2)


def plot_memory(memory):
    average_memory= memory
    MS = 12
    LW = 6
    x_range = [1,2,3,4]
    plt.plot(x_range, average_memory["PAPA"],"-.8" ,label="$PAPA$",markersize=MS, linewidth=LW, c="blue")
    plt.plot(x_range, average_memory["NAPATREES"],":*" ,label="$NAPA_{trees}$" , ms=MS,markersize=MS, linewidth=LW, c="red")
    plt.plot(x_range, average_memory["NAPANAIVE"],"--^"   ,label="$NAPA_{naive}$" , ms=MS,markersize=MS, linewidth=LW, c="purple")
    plt.plot(x_range, average_memory["MDSketch"],"--v"  ,label="$MDSketch$" , ms=MS,markersize=MS, linewidth=LW, c="green")


    papa_improve1 = 1- (average_memory["PAPA"][0]/average_memory["MDSketch"][0])
    print "1D PAPA improve memory: ", papa_improve1

    papa_improve2 = 1- (average_memory["PAPA"][1]/average_memory["MDSketch"][1])
    print "2D PAPA improve memory: ", papa_improve2

    papa_improve3 = 1- (average_memory["PAPA"][2]/average_memory["MDSketch"][2])
    print "3D PAPA improve memory: ", papa_improve3

    papa_improve4 = 1- (average_memory["PAPA"][3]/average_memory["MDSketch"][3])
    print "4D PAPA improve memory: ", papa_improve4



    napa_improve1 = (average_memory["NAPANAIVE"][0]/average_memory["MDSketch"][0])
    print "1D NAPANAIVE improve memory: ", napa_improve1

    napa_improve2 = (average_memory["NAPANAIVE"][1]/average_memory["MDSketch"][1])
    print "2D NAPANAIVE improve memory: ", napa_improve2

    napa_improve3 = 1- (average_memory["NAPANAIVE"][2]/average_memory["MDSketch"][2])
    print "3D NAPANAIVE improve memory: ", napa_improve3

    napa_improve4 = 1- (average_memory["NAPANAIVE"][3]/average_memory["MDSketch"][3])
    print "4D NAPANAIVE improve memory: ", napa_improve4


    print "PAPA memory: ", average_memory["PAPA"]
#    print "NAPATREES memory: ", average_memory["NAPATREES"]
#    print "NAPANAIVE memory: ", average_memory["NAPANAIVE"]
    print "MDSketch memory: ", average_memory["MDSketch"]

    ##for algorithm in speed:
    ##    plt.plot(phis, speed[algorithm],label=algorithm)
    #plt.xscale("log",basex=2)
    plt.yscale("log",basex=2)

    ticks,labels = plt.xticks()
    #plt.xticks(ticks[::2],labels[::2])
    #plt.gca().xaxis.set_major_locator(ticker.LogLocator(base=2))

    majors = [1,2,3,4]
    plt.gca().xaxis.set_major_locator(ticker.FixedLocator(majors))

    plt.xlabel("Dimensions", fontsize=38)
    ylabel_str = "Memory [GB]"
    plt.ylabel(ylabel_str, fontsize=42)
    plt.tick_params(labelsize=20)
    #plt.xlim(left = FIRST_PHINDEX, right=LAST_PHINDEX-1)
    #plt.ylim(0, 800000000)


    #plt.legend(loc="best") # keys of the graphs
    #plt.legend(loc="best",prop={'size':13},ncol=14) # keys of the graphs
    #plt.legend(prop={'size':14},ncol=13) # keys of the graphs

    plt.tight_layout()
    plt.savefig('../KDD/memory_limit_512_eps_8_d.png')
    plt.clf()




def cmsketch_size(eps):
    eps_1 = eps**(-1)
    return log2(delta_1) * 4 * (eps_1)


def calc_PAPA_memory(eps):
    #rangeTreeNode = 41
    rangeTreeNode = 1
    eps_d = eps**(-d)
    eps_1 = eps**(-1)
    counter_size = 8
    #sketches1 = eps_d * counter_size
    #PAPA1 = (eps_d * log2(eps_d))*rangeTreeNode + sketches1

    papa_eps_cms = eps/log2(eps_1)
    sketches2 =  log2(eps_1) * cmsketch_size(papa_eps_cms)
    PAPA = (eps_d *rangeTreeNode) + sketches2

    return PAPA

def calc_memory(d):

############################# PAPA ###############################################################

    #rangeTreeNode = 41
    rangeTreeNode = 1
    print "eps", eps
    print "d", d
    eps_d = eps**(-d)
    counter_size = 8
    #sketches1 = eps_d * counter_size
    #PAPA1 = (eps_d * log2(eps_d))*rangeTreeNode + sketches1
    eps_1 = eps**(-1)
    papa_eps_cms = eps/log2(eps_1)


    sketches2 =  log2(eps_1) * cmsketch_size(papa_eps_cms)
    PAPA = (eps_d *rangeTreeNode) + sketches2


    tmp = log2(eps_1)
    print "eps ", eps
    print "log2 ", tmp

    #print "PAPA old", PAPA1
    #print "PAPA new", PAPA

########################### NAPA #################################################################

    sample_eps = eps/(4*d)
    sample_size = sample_eps**(-2)*log(sample_eps*N,2)
    NAPA_addition = 4 * (1/eps) * d * sample_size

    NAPANAIVE = calc_PAPA_memory((eps/2)) + NAPA_addition


    samples_trees_nodes = d * sample_size
    samples_trees = (samples_trees_nodes * log2(samples_trees_nodes))*rangeTreeNode

    NAPATREES = NAPANAIVE + samples_trees



########################### MDSketch #################################################################
    md_eps_cms = eps/(log2(limit)**d)
    mdsketches =  cmsketch_size(md_eps_cms)

    MDSketch = (log2(limit)**(d))*mdsketches

    memory["PAPA"].append((PAPA/ 1e9))
    memory["NAPANAIVE"].append((NAPANAIVE/ 1e9))
    memory["NAPATREES"].append((NAPATREES/ 1e9))
    memory["MDSketch"].append((MDSketch/ 1e9))



memory = dict()
memory["PAPA"]=[]
memory["NAPANAIVE"]=[]
memory["NAPATREES"]=[]
memory["MDSketch"]=[]

for d in drange:
    out = calc_memory(d)

print "memory of y PAPA", memory["PAPA"]
print "memory of y NAPATREES", memory["NAPATREES"]
print "memory of y NAPANAIVE", memory["NAPANAIVE"]


plot_memory(memory)
