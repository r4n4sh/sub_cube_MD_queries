#!/usr/bin/python
import subprocess
import matplotlib as mpl
from matplotlib import pyplot as plt
from matplotlib import ticker
import numpy as np
import re
import cPickle
import sys
import numpy
import math
from math import log
from math import sqrt


FIRST_PHINDEX = 3
LAST_PHINDEX = 14
window_size = 65536
epsilonsrange = range(FIRST_PHINDEX,LAST_PHINDEX)
epsilons = [2**(-x) for x in epsilonsrange] #actually its counters parameters (counters = 1/epsilon)
d = 2
N = 1000000
delta_1 = 100
limit_big = 100000
limit_small = 1024

MS = 12
LW = 6


def log2(x):
    return math.log(x) / math.log(2)

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






def calc_memory(eps,alg):

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


    if (alg == "papa"):
        memory["papa"].append((PAPA/ 1e6))
    if (alg == "napa"):
        memory["napa"].append((NAPATREES/ 1e6))
    if (alg == "mdsketch"):
        memory["mdsketch"].append((MDSketch_small/ 1e6))



def memory_consumption(alg):
    epsilons = [2**(-x) for x in eprange[alg]] #actually its counters parameters (counters = 1/epsilon)

    for epsilon in epsilons:
        out = calc_memory(epsilon, alg)


def plot_speeds(speeds, dataset):
    average_speeds = speeds

    average_speeds["expected"]=[]
    epsilons = [2**(-x) for x in eprange[alg]] #actually its counters parameters (counters = 1/epsilon)

    for epsilon in epsilons:
        average_speeds["expected"].append(float(N*epsilon))
        print "expected", epsilon, N*epsilon


    memory_consumption("papa")
    memory_consumption("napa")
    memory_consumption("mdsketch")

    print "values of memory of in MB PAPA", memory["papa"]
    print "values of memory of in MB NAPA", memory["napa"]
    print "values of memory of in MB mdsketch", memory["mdsketch"]

    print "value of error in PAPA", average_speeds["papa"]
    print "value of error in NAPA", average_speeds["napa"]
    print "value of error in mdsketch", average_speeds["mdsketch"]



    memory["papa"] = [1.3642800156093495, 3.7698994953317273, 10.779906858702779, 32.45203933311075, 103.90115765688496,150,200,250]
    average_speeds["papa"] =[0,0,0,0,0,0,0,0]
    plt.plot(memory["papa"], average_speeds["papa"],"-.8" ,label="$PAPA$",ms=MS,markersize=MS, linewidth=LW, c="blue")
    #plt.plot(memory["papa"], average_speeds["papa"],"-.8" ,label="$PAPA$",markersize=MS, linewidth=LW, c="blue")

    plt.plot(memory["napa"], average_speeds["napa"],":*" ,label="$NAPA_{trees}$" , ms=MS,markersize=MS, linewidth=LW, c="red")
    plt.plot(memory["mdsketch"], average_speeds["mdsketch"],"--v"   ,label="$MDSketch$" , ms=MS,markersize=MS, linewidth=LW, c="green")

    #plt.plot(memory["papa"], average_speeds["expected"],"->",label="$expected$", markersize=MS, linewidth=LW,markeredgecolor="k",c="blue")
    #plt.plot(memory["acc2"], average_speeds["acc2"],"-.s",label="$ACC_2$", markersize=MS, linewidth=LW, markeredgecolor="k",c="red")
    #plt.plot(memory["acc4"], average_speeds["acc4"],"--^",label="$ACC_4$", markersize=MS, linewidth=LW,  markeredgecolor="k",c="yellow")
    #plt.plot(memory["acc8"], average_speeds["acc8"],":<",label="$ACC_8$", markersize=MS, linewidth=LW, markeredgecolor="k",c="orange")

    #plt.xscale("log",basex=2)
    #plt.yscale("log",basex=2)
    #plt.gca().xaxis.set_major_locator(ticker.LogLocator(base=2))

    plt.xlabel("Memory (Mbytes)", fontsize=42)
    ylabel_str = "RMSE [items] x $10^{3}$"
    plt.ylabel(ylabel_str, fontsize=38)
    plt.tick_params(labelsize=10)
    plt.xlim(1, 256)
    #plt.ylim(0, 10**6) #For Queries
    plt.legend(loc="best", numpoints=2) # keys of the graphs
    plt.tight_layout()
    plt.savefig('graphs/KDD/emp_error.png')
    plt.clf()



csvFiles = dict()
#csvFiles['Chicago16'] ='emp_error_debug.txt'
csvFiles['Chicago16'] ='tmp_emp_error.txt'
minEps = 2
maxEps = 7
speeds = dict()
eprange = dict()
eprange["papa"]= range(9,15)
eprange["napa"]= range(2,6)
eprange["mdsketch"]= range(4,11)


for dataset in csvFiles:
    memory = dict()
    memory["papa"]=[]
    memory["napa"]=[]
    memory["mdsketch"]=[]


    lines = open(csvFiles[dataset]).readlines()
    speeds[dataset] = dict()
    for line in lines:
        alg = line.split(' ')[0].replace('./','') # algo = hhh2RSS
        print alg
        if (alg not in speeds[dataset]):
            speeds[dataset][alg]=[]
        timing = re.search("\s(\d+\.\d+)\s", line).groups()[0]
        print "error", timing
        speeds[dataset][alg].append((float(timing))/ 1e3)
    plot_speeds(speeds[dataset], dataset)
