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


FIRST_PHINDEX = 2
LAST_PHINDEX = 9
window_size = 65536
epsilonsrange = range(FIRST_PHINDEX,LAST_PHINDEX)
epsilons = [2**(-x) for x in epsilonsrange] #actually its counters parameters (counters = 1/epsilon)
limit_big = 100000
limit_small = 256


d = 3
N = 1000000
delta_1 = 100


def log2(x):
    return math.log(x) / math.log(2)


def plot_memory(memory):
    average_memory= memory
    phis = [2**(-x) for x in epsilonsrange]
    MS = 12
    LW = 6

    plt.plot(phis, average_memory["PAPA"],"-.8" ,label="$PAPA$",markersize=MS, linewidth=LW, c="blue")
    plt.plot(phis, average_memory["NAPATREES"],":*" ,label="$NAPA_{trees}$" , ms=MS,markersize=MS, linewidth=LW, c="red")
    plt.plot(phis, average_memory["NAPANAIVE"],"--^"   ,label="$NAPA_{naive}$" , ms=MS,markersize=MS, linewidth=LW, c="purple")
    plt.plot(phis, average_memory["MDSketchB"], "-.D" ,label="$MDSketch_{R=100K}$" , ms=MS,markersize=MS, linewidth=LW, c="green")
    plt.plot(phis, average_memory["MDSketchS"], "--v",label="$MDSketch_{R=256}$" , ms=MS,markersize=MS, linewidth=LW, c="green")



    ##for algorithm in speed:
    ##    plt.plot(phis, speed[algorithm],label=algorithm)
    plt.xscale("log",basex=2)
    plt.yscale("log",basex=2)

    #ticks,labels = plt.xticks()
    #plt.xticks(ticks[::2],labels[::2])
    plt.gca().xaxis.set_major_locator(ticker.LogLocator(base=2))

    plt.xlabel("Accuracy Guarantee ($\epsilon$)", fontsize=38)
    ylabel_str = "Memory [GB]"
    plt.ylabel(ylabel_str, fontsize=42)
    plt.tick_params(labelsize=20)
    plt.xlim(left = 2**-(LAST_PHINDEX-1), right=2**-FIRST_PHINDEX)
    #plt.ylim(0, 800000000)


    #plt.legend(loc="best") # keys of the graphs
    #plt.legend(loc="best",prop={'size':10},ncol=9) # keys of the graphs
    #plt.legend(prop={'size':10},ncol=9) # keys of the graphs

    plt.tight_layout()
    plt.savefig('../KDD/memory_d_3_eps.png')
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

def calc_memory(eps):

############################# PAPA ###############################################################

    #rangeTreeNode = 41
    rangeTreeNode = 1
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
    md_eps_cms = eps/(log2(limit_big)**d)
    mdsketches =  cmsketch_size(md_eps_cms)

    MDSketch_big = (log2(limit_big)**(d))*mdsketches


    md_eps_cms = eps/(log2(limit_small)**d)
    mdsketches =  cmsketch_size(md_eps_cms)

    MDSketch_small = (log2(limit_small)**(d))*mdsketches

    memory["PAPA"].append((PAPA/ 1e9))
    memory["NAPANAIVE"].append((NAPANAIVE/ 1e9))
    memory["NAPATREES"].append((NAPATREES/ 1e9))
    memory["MDSketchB"].append((MDSketch_big/ 1e9))
    memory["MDSketchS"].append((MDSketch_small/ 1e9))



memory = dict()
memory["PAPA"]=[]
memory["NAPANAIVE"]=[]
memory["NAPATREES"]=[]
memory["MDSketchB"]=[]
memory["MDSketchS"]=[]

for epsilon in epsilons:
    out = calc_memory(epsilon)

print "memory of y PAPA", memory["PAPA"]
print "memory of y NAPATREES", memory["NAPATREES"]
print "memory of y NAPANAIVE", memory["NAPANAIVE"]


plot_memory(memory)
