#!/usr/bin/python
import subprocess
import matplotlib as mpl
from matplotlib import pyplot as plt
from matplotlib import ticker
import numpy as np
import re
import cPickle
import sys

LW = 9
MS = 14
CT = 4


def plot_speeds(speeds):
    average_speeds = speeds
    ylabel_str = sys.argv[1] + "/second [Millions]" #For Queries in Millions

    update_values = sorted(average_speeds["PAPA"])

    yErr = []
    yVals = []
    t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
    for eps in update_values:
            mean = sum(average_speeds["PAPA"][eps]) / len(average_speeds["PAPA"][eps])
            yVals.append(mean)
            sos = sum([(x - mean)**2 for x in average_speeds["PAPA"][eps]])
            variance = (sos / (len(average_speeds["PAPA"][eps]) - 1) )# ** 0.5
            err = variance * t_n_1 / pow(len(average_speeds["PAPA"][eps]), 0.5)
            yErr.append(err)
    algLabel = 'PAPA'
    print 'PAPA yvals:\n',yVals
    print 'PAPA xvals:\n',update_values
    plt.errorbar(update_values, yVals, yerr=yErr,fmt="-.8" ,label=algLabel, color="blue", capsize=MS, markersize=MS, elinewidth=LW, capthick=CT)

    update_values = sorted(average_speeds["NAPA"])

    yErr = []
    yVals = []
    t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
    for eps in update_values:
            mean = sum(average_speeds["NAPA"][eps]) / len(average_speeds["NAPA"][eps])
            yVals.append(mean)
            sos = sum([(x - mean)**2 for x in average_speeds["NAPA"][eps]])
            variance = (sos / (len(average_speeds["NAPA"][eps]) - 1) )# ** 0.5
            err = variance * t_n_1 / pow(len(average_speeds["NAPA"][eps]), 0.5)
            yErr.append(err)
    algLabel = 'NAPA'
    print 'NAPA yvals:\n',yVals
    print 'NAPA xvals:\n',update_values
    plt.errorbar(update_values, yVals, yerr=yErr,fmt=":*" ,label=algLabel, color="red", capsize=MS, markersize=MS, elinewidth=LW, capthick=CT)

    update_values = sorted(average_speeds["MDSketch"])

    yErr = []
    yVals = []
    t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
    for eps in update_values:
            mean = sum(average_speeds["MDSketch"][eps]) / len(average_speeds["MDSketch"][eps])
            yVals.append(mean)
            sos = sum([(x - mean)**2 for x in average_speeds["MDSketch"][eps]])
            variance = (sos / (len(average_speeds["MDSketch"][eps]) - 1) )# ** 0.5
            err = variance * t_n_1 / pow(len(average_speeds["MDSketch"][eps]), 0.5)
            yErr.append(err)
    algLabel = 'MDSketch'
    print 'MDsketch yvals:\n',yVals
    print 'MDsketch xvals:\n',update_values
    print yVals, 'MDSketch'
    plt.errorbar(update_values, yVals, yerr=yErr,fmt="--v",label=algLabel, color="green", capsize=MS, markersize=MS, elinewidth=LW, capthick=CT)
    
    if (sys.argv[1] == "Update2"):
        ylabel_str = "Update/second[$10^6$]"
    if (sys.argv[1] == "Query2"):
        ylabel_str = "Query/second[$10^6$]"


    plt.xscale("log",basex=2)
    plt.yscale("log",basex=2)
    plt.gca().xaxis.set_major_locator(ticker.LogLocator(base=2))
    plt.xlabel("Range", fontsize=38)
    #ylabel_str = "Update/second [Millions]" #For Queries in Millions

    plt.ylabel(ylabel_str, fontsize=38)
    plt.tick_params(labelsize=20)
    plt.xlim(left = 2**minrange, right=2**maxrange)
    #plt.ylim(10**(-1), 2)
#    plt.yticks([10**(-4),10**1])
    #plt.yticks([0,1])

    #plt.legend(loc="best") # keys of the graphs
    #plt.legend(loc="best",prop={'size':18},ncol=20) # keys of the graphs

    plt.tight_layout()
    #plt.savefig('graphs/'+ sys.argv[1] +'_result_epsilon.png')
    #plt.savefig('graphs/'+ sys.argv[1] +'_newfacebook_napa_dataset_epsilon.png')
    plt.savefig('graphs/KDD/'+ sys.argv[1] + '_' + sys.argv[2] +'_range.png')
    plt.clf()



if (sys.argv[1] == "Update2"):
    csvFiles = 'change_range_update.txt'
if (sys.argv[1] == "Query2"):
    csvFiles = 'change_range_query.txt'

minrange = 8
maxrange = 13
speeds = dict()


lines = open(csvFiles).readlines()
for line in lines:
	alg = line.split(' ')[0] # algo = Update
	if (alg not in speeds):
		speeds[alg]=dict()
       	counters = int(re.search(r'(\d+) range', line).groups()[0])
       	ops = int(re.search(r'(\d+) pairs', line).groups()[0])
        print "ops: ", ops
   	if (counters not in speeds[alg]):
   		speeds[alg][counters]=[]
	timing = re.search("\s(\d+\.\d+)s\s", line).groups()[0] # all timing values
	print timing, alg
	speeds[alg][counters].append((ops / float(timing))/ 1e6)
plot_speeds(speeds)
