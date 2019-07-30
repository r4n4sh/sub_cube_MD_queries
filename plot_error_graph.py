#!/usr/bin/python
import subprocess
import matplotlib as mpl
from matplotlib import pyplot as plt;  plt.rcdefaults()
from matplotlib import ticker
import numpy as np
import re
import cPickle
import numpy
from math import log
from math import sqrt
import sys


def plot_speeds(perf, x_axis):
    average_memory= perf
    MS = 12
    LW = 4

    if (sys.argv[1] == "Update"):
        plt.plot(x_axis["Update"], perf["Update"],"-.8"	,label="Update",markersize=MS, linewidth=LW, c="purple")
    if (sys.argv[1] == "query"):
        plt.plot(x_axis["Query"], perf["Query"],"--v"	,label="Query",markersize=MS, linewidth=LW, c="cyan")

    #plt.bar(queue, aborts, align='center', alpha=0.5)

    ##for algorithm in speed:
    ##    plt.plot(phis, speed[algorithm],label=algorithm)
    plt.xscale("log",basex=2)
    plt.yscale("log",basex=2)

    ticks,labels = plt.xticks()
    plt.gca().xaxis.set_major_locator(ticker.LogLocator(base=2))

    plt.xlabel("epsilon", fontsize=24)
    if (sys.argv[1] == "Update"):
        ylabel_str = "Update Throughput"
    if (sys.argv[1] == "query"):
        ylabel_str = "Query Throughput"

    plt.ylabel(ylabel_str, fontsize=24)
    plt.tick_params(labelsize=20)
    #plt.ylim(0, 80000000)

#    plt.xticks([10, 50, 100, 1000])

    plt.legend(loc="best") # keys of the graphs
    #plt.legend(loc="best",prop={'size':13},ncol=14) # keys of the graphs
    #plt.legend(prop={'size':9},ncol=13) # keys of the graphs

    plt.tight_layout()
    plt.savefig(sys.argv[1] + '_epsilon_results.png')
    plt.clf()

if (sys.argv[1] == "Update"):
    csvFiles = 'update_test.txt'
if (sys.argv[1] == "query"):
    csvFiles = 'query_test.txt'

lines = open(csvFiles).readlines()
perf = dict()
x_axis = dict()
for line in lines:
    alg = line.split(' ')[0]
    if (alg not in perf):
        perf[alg]=[]
        x_axis[alg] = []
    ops = re.search(r'(\d+) pairs', line).groups()[0]
    epsilon = re.search(r'(\d+) 1/epsilon', line).groups()[0]
    print (1/ float(epsilon))
    timing = re.search("\s(\d+\.\d+)s\s", line).groups()[0] # all timing values
    x_axis[alg].append(1/float(epsilon))
    perf[alg].append((float(ops) / float(timing))) #For Queries in Millions
plot_speeds(perf, x_axis)
