#!/usr/bin/python
import subprocess
import matplotlib as mpl
from matplotlib import pyplot as plt
from matplotlib import ticker
import numpy as np
import re
import cPickle
import sys


minEps = 2
maxEps = 9


LW = 2
MS = 8
CT = 2

def plot_speeds(speeds):
    average_speeds = speeds
    ylabel_str = sys.argv[1] + "/second [$10^4$]" #For Queries in Millions


############ PAPA #######################################################

    qyery_values = sorted(average_speeds["papa1"])
    yErr = []
    yVals = []
    t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
    for eps in qyery_values:
            mean = sum(average_speeds["papa1"][eps]) / len(average_speeds["papa1"][eps])
            yVals.append(mean)
            sos = sum([(x - mean)**2 for x in average_speeds["papa1"][eps]])
            variance = (sos / (len(average_speeds["papa1"][eps]) - 1) )# ** 0.5
            err = variance * t_n_1 / pow(len(average_speeds["papa1"][eps]), 0.5)
            yErr.append(err)
    algLabel = 'P-1d'
    print 'yvals:\n',yVals
    print 'xvals:\n',qyery_values
    plt.errorbar(qyery_values, yVals, yerr=yErr,fmt="-.8" ,label=algLabel, color="black",  capsize=MS, markersize=MS, elinewidth=LW, capthick=CT)

    qyery_values = sorted(average_speeds["papa2"])
    yErr = []
    yVals = []
    t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
    for eps in qyery_values:
            mean = sum(average_speeds["papa2"][eps]) / len(average_speeds["papa2"][eps])
            yVals.append(mean)
            sos = sum([(x - mean)**2 for x in average_speeds["papa2"][eps]])
            variance = (sos / (len(average_speeds["papa2"][eps]) - 1) )# ** 0.5
            err = variance * t_n_1 / pow(len(average_speeds["papa2"][eps]), 0.5)
            yErr.append(err)
    algLabel = 'P-2d'
    print 'yvals:\n',yVals
    print 'xvals:\n',qyery_values
    plt.errorbar(qyery_values, yVals, yerr=yErr,fmt="-.8" ,label=algLabel, color="blue",  capsize=MS, markersize=MS, elinewidth=LW, capthick=CT)


    qyery_values = sorted(average_speeds["papa3"])
    yErr = []
    yVals = []
    t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
    for eps in qyery_values:
            mean = sum(average_speeds["papa3"][eps]) / len(average_speeds["papa3"][eps])
            yVals.append(mean)
            sos = sum([(x - mean)**2 for x in average_speeds["papa3"][eps]])
            variance = (sos / (len(average_speeds["papa3"][eps]) - 1) )# ** 0.5
            err = variance * t_n_1 / pow(len(average_speeds["papa3"][eps]), 0.5)
            yErr.append(err)
    algLabel = 'P-3d'
    print 'yvals:\n',yVals
    print 'xvals:\n',qyery_values
    plt.errorbar(qyery_values, yVals, yerr=yErr,fmt="-.8" ,label=algLabel, color="green",  capsize=MS, markersize=MS, elinewidth=LW, capthick=CT)

    qyery_values = sorted(average_speeds["papa4"])
    yErr = []
    yVals = []
    t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
    for eps in qyery_values:
            mean = sum(average_speeds["papa4"][eps]) / len(average_speeds["papa4"][eps])
            yVals.append(mean)
            sos = sum([(x - mean)**2 for x in average_speeds["papa4"][eps]])
            variance = (sos / (len(average_speeds["papa4"][eps]) - 1) )# ** 0.5
            err = variance * t_n_1 / pow(len(average_speeds["papa4"][eps]), 0.5)
            yErr.append(err)
    algLabel = 'P-4d'
    print 'yvals:\n',yVals
    print 'xvals:\n',qyery_values
    plt.errorbar(qyery_values, yVals, yerr=yErr,fmt="-.8" ,label=algLabel, color="brown",  capsize=MS, markersize=MS, elinewidth=LW, capthick=CT)

######################## MDSketch ###########################################

    qyery_values = sorted(average_speeds["mdsketch1"])
    yErr = []
    yVals = []
    t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
    for eps in qyery_values:
            mean = sum(average_speeds["mdsketch1"][eps]) / len(average_speeds["mdsketch1"][eps])
            yVals.append(mean)
            sos = sum([(x - mean)**2 for x in average_speeds["mdsketch1"][eps]])
            variance = (sos / (len(average_speeds["mdsketch1"][eps]) - 1) )# ** 0.5
            err = variance * t_n_1 / pow(len(average_speeds["mdsketch1"][eps]), 0.5)
            yErr.append(err)
    algLabel = 'MD-1d'
    print 'yvals:\n',yVals
    print 'xvals:\n',qyery_values
    plt.errorbar(qyery_values, yVals, yerr=yErr,fmt="--v"  ,label=algLabel, color="black",  capsize=MS, markersize=MS, elinewidth=LW, capthick=CT)

    qyery_values = sorted(average_speeds["mdsketch2"])
    yErr = []
    yVals = []
    t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
    for eps in qyery_values:
            mean = sum(average_speeds["mdsketch2"][eps]) / len(average_speeds["mdsketch2"][eps])
            yVals.append(mean)
            sos = sum([(x - mean)**2 for x in average_speeds["mdsketch2"][eps]])
            variance = (sos / (len(average_speeds["mdsketch2"][eps]) - 1) )# ** 0.5
            err = variance * t_n_1 / pow(len(average_speeds["mdsketch2"][eps]), 0.5)
            yErr.append(err)
    algLabel = 'MD-2d'
    print 'yvals:\n',yVals
    print 'xvals:\n',qyery_values
    plt.errorbar(qyery_values, yVals, yerr=yErr,fmt="--v"  ,label=algLabel, color="blue",  capsize=MS, markersize=MS, elinewidth=LW, capthick=CT)


    qyery_values = sorted(average_speeds["mdsketch3"])
    yErr = []
    yVals = []
    t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
    for eps in qyery_values:
            mean = sum(average_speeds["mdsketch3"][eps]) / len(average_speeds["mdsketch3"][eps])
            yVals.append(mean)
            sos = sum([(x - mean)**2 for x in average_speeds["mdsketch3"][eps]])
            variance = (sos / (len(average_speeds["mdsketch3"][eps]) - 1) )# ** 0.5
            err = variance * t_n_1 / pow(len(average_speeds["mdsketch3"][eps]), 0.5)
            yErr.append(err)
    algLabel = 'MD-3d'
    print '*********mdsketch3 yvals:\n',yVals
    print '*********mdsketch3 xvals:\n',qyery_values
    plt.errorbar(qyery_values, yVals, yerr=yErr,fmt="--v"  ,label=algLabel, color="green",  capsize=MS, markersize=MS, elinewidth=LW, capthick=CT)


    qyery_values = sorted(average_speeds["mdsketch4"])
    yErr = []
    yVals = []
    t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
    for eps in qyery_values:
            mean = sum(average_speeds["mdsketch4"][eps]) / len(average_speeds["mdsketch4"][eps])
            yVals.append(mean)
            sos = sum([(x - mean)**2 for x in average_speeds["mdsketch4"][eps]])
            variance = (sos / (len(average_speeds["mdsketch4"][eps]) - 1) )# ** 0.5
            err = variance * t_n_1 / pow(len(average_speeds["mdsketch4"][eps]), 0.5)
            yErr.append(err)
    algLabel = 'MD-4d'
    print 'yvals:\n',yVals
    print 'xvals:\n',qyery_values
    plt.errorbar(qyery_values, yVals, yerr=yErr,fmt="--v"  ,label=algLabel, color="brown",  capsize=MS, markersize=MS, elinewidth=LW, capthick=CT)







##############################################################################
    #plt.legend(loc="best") # keys of the graphs
    #plt.legend(loc="best",prop={'size':9},ncol=20) # keys of the graphs
    if (sys.argv[1] == "Update"):
        ylabel_str = "Update/second[$10^6$]"
    if (sys.argv[1] == "Query"):
        ylabel_str = "Query/second[$10^6$]"



    plt.xscale("log",basex=2)
    plt.yscale("log",basex=2)
    plt.gca().xaxis.set_major_locator(ticker.LogLocator(base=2))
    plt.xlabel("Accuracy Guarantee ($\epsilon$)", fontsize=38)
    #ylabel_str = "Update/second [Millions]" #For Queries in Millions

    plt.ylabel(ylabel_str, fontsize=38)
    plt.tick_params(labelsize=20)
    plt.xlim(left = 2**-(maxEps-1), right=2**-minEps)
    #plt.ylim(10**(-1), 2)
    #plt.yticks([10**(-1),10**1])

    plt.tight_layout()
    plt.savefig('graphs/KDD/'+ sys.argv[1] + '_'+ sys.argv[2] + '_epsilon.png')
    plt.clf()


if (sys.argv[1] == "Update"):
#    csvFiles = 'dupdate_all_compare.txt'
    csvFiles = 'dupdate_all_compare_new.txt'

if (sys.argv[1] == "Query"):
#    csvFiles = 'dquery_all_compare.txt'
    csvFiles = 'dquery_all_compare_new.txt'



speeds = dict()


lines = open(csvFiles).readlines()
for line in lines:
	alg = line.split(' ')[0] # algo = Update
	if (alg not in speeds):
		speeds[alg]=dict()
       	counters = int(re.search(r'(\d+) 1/epsilon', line).groups()[0])
        counters = 1 / float(counters);
       	ops = int(re.search(r'(\d+) pairs', line).groups()[0])
   	if (counters not in speeds[alg]):
   		speeds[alg][counters]=[]
	timing = re.search("\s(\d+\.\d+)s\s", line).groups()[0] # all timing values
	print timing, alg
	speeds[alg][counters].append((ops / float(timing))/ 1e4)
plot_speeds(speeds)
