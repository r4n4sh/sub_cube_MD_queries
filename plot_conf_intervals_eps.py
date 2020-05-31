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

    if (sys.argv[1] == "Update"):
        update_values = sorted(average_speeds["Update"])

        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in update_values:
        		mean = sum(average_speeds["Update"][eps]) / len(average_speeds["Update"][eps])
        		yVals.append(mean)
        		sos = sum([(x - mean)**2 for x in average_speeds["Update"][eps]])
        		variance = (sos / (len(average_speeds["Update"][eps]) - 1) )# ** 0.5
        		err = variance * t_n_1 / pow(len(average_speeds["Update"][eps]), 0.5)
        		yErr.append(err)
        algLabel = 'PAPA'
        print 'yvals:\n',yVals
        print 'xvals:\n',update_values
        plt.errorbar(update_values, yVals, yerr=yErr,fmt='-.D' ,label=algLabel, color="blue", capsize=10, elinewidth=3, capthick=1.5)

        update_values = sorted(average_speeds["UpdateNapa"])

        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in update_values:
                mean = sum(average_speeds["UpdateNapa"][eps]) / len(average_speeds["UpdateNapa"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["UpdateNapa"][eps]])
                variance = (sos / (len(average_speeds["UpdateNapa"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["UpdateNapa"][eps]), 0.5)
                yErr.append(err)
        algLabel = 'NAPA'
        print 'yvals:\n',yVals
        print 'xvals:\n',update_values
        plt.errorbar(update_values, yVals, yerr=yErr,fmt='-.D' ,label=algLabel, color="red", capsize=10, elinewidth=3, capthick=1.5)



        update_values = sorted(average_speeds["CMHUpdate"])

        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in update_values:
                mean = sum(average_speeds["CMHUpdate"][eps]) / len(average_speeds["CMHUpdate"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["CMHUpdate"][eps]])
                variance = (sos / (len(average_speeds["CMHUpdate"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["CMHUpdate"][eps]), 0.5)
                yErr.append(err)
        algLabel = 'HCMS'
        print 'yvals:\n',yVals
        print 'xvals:\n',update_values
        print yVals, 'CMHUpdate'
        plt.errorbar(update_values, yVals, yerr=yErr,fmt='-.D' ,label=algLabel, color="orange", capsize=10, elinewidth=3, capthick=1.5)

    if (sys.argv[1] == "Query"):
        qyery_values = sorted(average_speeds["Query"])
        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in qyery_values:
                mean = sum(average_speeds["Query"][eps]) / len(average_speeds["Query"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["Query"][eps]])
                variance = (sos / (len(average_speeds["Query"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["Query"][eps]), 0.5)
                yErr.append(err)
        algLabel = 'PAPA'
        print 'yvals:\n',yVals
        print 'xvals:\n',qyery_values
        plt.errorbar(qyery_values, yVals, yerr=yErr,fmt='-.D' ,label=algLabel, color="blue", capsize=10, elinewidth=3, capthick=1.5)



        update_values = sorted(average_speeds["QueryNapa"])

        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in update_values:
                mean = sum(average_speeds["QueryNapa"][eps]) / len(average_speeds["QueryNapa"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["QueryNapa"][eps]])
                variance = (sos / (len(average_speeds["QueryNapa"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["QueryNapa"][eps]), 0.5)
                yErr.append(err)
        algLabel = 'NAPA'
        print 'yvals:\n',yVals
        print 'xvals:\n',update_values
        plt.errorbar(update_values, yVals, yerr=yErr,fmt='-.D' ,label=algLabel, color="red", capsize=10, elinewidth=3, capthick=1.5)


        update_values = sorted(average_speeds["CMHQuery"])

        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in update_values:
                mean = sum(average_speeds["CMHQuery"][eps]) / len(average_speeds["CMHQuery"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["CMHQuery"][eps]])
                variance = (sos / (len(average_speeds["CMHQuery"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["CMHQuery"][eps]), 0.5)
                yErr.append(err)
        algLabel = 'HCMS'
        print 'yvals:\n',yVals
        print 'xvals:\n',update_values
        plt.errorbar(update_values, yVals, yerr=yErr,fmt='-.D' ,label=algLabel, color="orange", capsize=10, elinewidth=3, capthick=1.5)



    if (sys.argv[1] == "QueryDiff"):
        qyery_values = sorted(average_speeds["QuerySmall"])
        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in qyery_values:
                mean = sum(average_speeds["QuerySmall"][eps]) / len(average_speeds["QuerySmall"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["QuerySmall"][eps]])
                variance = (sos / (len(average_speeds["QuerySmall"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["QuerySmall"][eps]), 0.5)
                yErr.append(err)
        algLabel = 'QuerySmall'
        print 'yvals:\n',yVals
        print 'xvals:\n',qyery_values
        plt.errorbar(qyery_values, yVals, yerr=yErr,fmt='-.D' ,label=algLabel, color="blue", capsize=10, elinewidth=3, capthick=1.5)


        qyery_values = sorted(average_speeds["QueryBig"])
        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in qyery_values:
                mean = sum(average_speeds["QueryBig"][eps]) / len(average_speeds["QueryBig"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["QueryBig"][eps]])
                variance = (sos / (len(average_speeds["QueryBig"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["QueryBig"][eps]), 0.5)
                yErr.append(err)
        algLabel = 'QueryBig'
        print 'yvals:\n',yVals
        print 'xvals:\n',qyery_values
        plt.errorbar(qyery_values, yVals, yerr=yErr,fmt='-.D' ,label=algLabel, color="green", capsize=10, elinewidth=3, capthick=1.5)
        ylabel_str = "QueryDiff/second[$10^6$]"



    if (sys.argv[1] == "dupdate"):
        qyery_values = sorted(average_speeds["Update1"])
        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in qyery_values:
                mean = sum(average_speeds["Update1"][eps]) / len(average_speeds["Update1"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["Update1"][eps]])
                variance = (sos / (len(average_speeds["Update1"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["Update1"][eps]), 0.5)
                yErr.append(err)
        algLabel = '1-d'
        print 'yvals:\n',yVals
        print 'xvals:\n',qyery_values
        plt.errorbar(qyery_values, yVals, yerr=yErr,fmt='-.^' ,label=algLabel, color="black", capsize=10, elinewidth=3, capthick=1.5)

        qyery_values = sorted(average_speeds["Update"])
        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in qyery_values:
                mean = sum(average_speeds["Update"][eps]) / len(average_speeds["Update"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["Update"][eps]])
                variance = (sos / (len(average_speeds["Update"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["Update"][eps]), 0.5)
                yErr.append(err)
        algLabel = '2-d'
        print 'yvals:\n',yVals
        print 'xvals:\n',qyery_values
        plt.errorbar(qyery_values, yVals, yerr=yErr,fmt='-.D' ,label=algLabel, color="blue", capsize=10, elinewidth=3, capthick=1.5)


        qyery_values = sorted(average_speeds["Update3"])
        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in qyery_values:
                mean = sum(average_speeds["Update3"][eps]) / len(average_speeds["Update3"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["Update3"][eps]])
                variance = (sos / (len(average_speeds["Update3"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["Update3"][eps]), 0.5)
                yErr.append(err)
        algLabel = '3-d'
        print 'yvals:\n',yVals
        print 'xvals:\n',qyery_values
        plt.errorbar(qyery_values, yVals, yerr=yErr,fmt='-.D' ,label=algLabel, color="green", capsize=10, elinewidth=3, capthick=1.5)
        plt.legend(loc="best") # keys of the graphs
        plt.legend(loc="best",prop={'size':16},ncol=20) # keys of the graphs

        qyery_values = sorted(average_speeds["Update4"])
        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in qyery_values:
                mean = sum(average_speeds["Update4"][eps]) / len(average_speeds["Update4"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["Update4"][eps]])
                variance = (sos / (len(average_speeds["Update4"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["Update4"][eps]), 0.5)
                yErr.append(err)
        algLabel = '4-d'
        print 'yvals:\n',yVals
        print 'xvals:\n',qyery_values
        plt.errorbar(qyery_values, yVals, yerr=yErr,fmt='-.o' ,label=algLabel, color="brown", capsize=10, elinewidth=3, capthick=1.5)
        plt.legend(loc="best") # keys of the graphs
        plt.legend(loc="best",prop={'size':12},ncol=20) # keys of the graphs
        ylabel_str = "Update/second [Millions]"

    if (sys.argv[1] == "dquery"):
        qyery_values = sorted(average_speeds["Query1"])
        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in qyery_values:
                mean = sum(average_speeds["Query1"][eps]) / len(average_speeds["Query1"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["Query1"][eps]])
                variance = (sos / (len(average_speeds["Query1"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["Query1"][eps]), 0.5)
                yErr.append(err)
        algLabel = '1-d'
        print 'yvals:\n',yVals
        print 'xvals:\n',qyery_values
        plt.errorbar(qyery_values, yVals, yerr=yErr,fmt='-.^' ,label=algLabel, color="black", capsize=10, elinewidth=3, capthick=1.5)

        qyery_values = sorted(average_speeds["Query"])
        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in qyery_values:
                mean = sum(average_speeds["Query"][eps]) / len(average_speeds["Query"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["Query"][eps]])
                variance = (sos / (len(average_speeds["Query"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["Query"][eps]), 0.5)
                yErr.append(err)
        algLabel = '2-d'
        print 'yvals:\n',yVals
        print 'xvals:\n',qyery_values
        plt.errorbar(qyery_values, yVals, yerr=yErr,fmt='-.D' ,label=algLabel, color="blue", capsize=10, elinewidth=3, capthick=1.5)


        qyery_values = sorted(average_speeds["Query3"])
        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in qyery_values:
                mean = sum(average_speeds["Query3"][eps]) / len(average_speeds["Query3"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["Query3"][eps]])
                variance = (sos / (len(average_speeds["Query3"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["Query3"][eps]), 0.5)
                yErr.append(err)
        algLabel = '3-d'
        print 'yvals:\n',yVals
        print 'xvals:\n',qyery_values
        plt.errorbar(qyery_values, yVals, yerr=yErr,fmt='-.D' ,label=algLabel, color="green", capsize=10, elinewidth=3, capthick=1.5)
        plt.legend(loc="best") # keys of the graphs
        plt.legend(loc="best",prop={'size':16},ncol=20) # keys of the graphs

        qyery_values = sorted(average_speeds["Query4"])
        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in qyery_values:
                mean = sum(average_speeds["Query4"][eps]) / len(average_speeds["Query4"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["Query4"][eps]])
                variance = (sos / (len(average_speeds["Query4"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["Query4"][eps]), 0.5)
                yErr.append(err)
        algLabel = '4-d'
        print 'yvals:\n',yVals
        print 'xvals:\n',qyery_values
        plt.errorbar(qyery_values, yVals, yerr=yErr,fmt='-.o' ,label=algLabel, color="brown", capsize=10, elinewidth=3, capthick=1.5)
        plt.legend(loc="best") # keys of the graphs
        plt.legend(loc="best",prop={'size':12},ncol=20) # keys of the graphs
        ylabel_str = "Query4/second [Millions]"


    if (sys.argv[1] == "Update1"):
        update_values = sorted(average_speeds["Update1"])

        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in update_values:
                mean = sum(average_speeds["Update1"][eps]) / len(average_speeds["Update1"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["Update1"][eps]])
                variance = (sos / (len(average_speeds["Update1"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["Update1"][eps]), 0.5)
                yErr.append(err)
        algLabel = 'PAPA'
        print 'yvals:\n',yVals
        print 'xvals:\n',update_values
        plt.errorbar(update_values, yVals, yerr=yErr,fmt='-.D' ,label=algLabel, color="blue", capsize=10, elinewidth=3, capthick=1.5)

        update_values = sorted(average_speeds["UpdateNapa1"])

        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in update_values:
                mean = sum(average_speeds["UpdateNapa1"][eps]) / len(average_speeds["UpdateNapa1"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["UpdateNapa1"][eps]])
                variance = (sos / (len(average_speeds["UpdateNapa1"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["UpdateNapa1"][eps]), 0.5)
                yErr.append(err)
        algLabel = 'NAPA'
        print 'yvals:\n',yVals
        print 'xvals:\n',update_values
        plt.errorbar(update_values, yVals, yerr=yErr,fmt='-.D' ,label=algLabel, color="red", capsize=10, elinewidth=3, capthick=1.5)



        update_values = sorted(average_speeds["CMHUpdate1"])

        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in update_values:
                mean = sum(average_speeds["CMHUpdate1"][eps]) / len(average_speeds["CMHUpdate1"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["CMHUpdate1"][eps]])
                variance = (sos / (len(average_speeds["CMHUpdate1"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["CMHUpdate1"][eps]), 0.5)
                yErr.append(err)
        algLabel = 'HCMS'
        print 'yvals:\n',yVals
        print 'xvals:\n',update_values
        print yVals, 'CMHUpdate'
        plt.errorbar(update_values, yVals, yerr=yErr,fmt='-.v' ,label=algLabel, color="orange", capsize=10, elinewidth=3, capthick=1.5)
        ylabel_str = "Update/second [Millions]"



    if (sys.argv[1] == "Query1"):
        update_values = sorted(average_speeds["Query1"])

        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in update_values:
                mean = sum(average_speeds["Query1"][eps]) / len(average_speeds["Query1"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["Query1"][eps]])
                variance = (sos / (len(average_speeds["Query1"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["Query1"][eps]), 0.5)
                yErr.append(err)
        algLabel = 'PAPA'
        print 'yvals:\n',yVals
        print 'xvals:\n',update_values
        plt.errorbar(update_values, yVals, yerr=yErr,fmt='-.D' ,label=algLabel, color="blue", capsize=10, elinewidth=3, capthick=1.5)

        update_values = sorted(average_speeds["QueryNapaNaive1"])

        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in update_values:
                mean = sum(average_speeds["QueryNapaNaive1"][eps]) / len(average_speeds["QueryNapaNaive1"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["QueryNapaNaive1"][eps]])
                variance = (sos / (len(average_speeds["QueryNapaNaive1"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["QueryNapaNaive1"][eps]), 0.5)
                yErr.append(err)
        algLabel = 'NAPA'
        print 'yvals:\n',yVals
        print 'xvals:\n',update_values
        plt.errorbar(update_values, yVals, yerr=yErr,fmt='-.D' ,label=algLabel, color="red", capsize=10, elinewidth=3, capthick=1.5)



        update_values = sorted(average_speeds["CMHQuery1"])

        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in update_values:
                mean = sum(average_speeds["CMHQuery1"][eps]) / len(average_speeds["CMHQuery1"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["CMHQuery1"][eps]])
                variance = (sos / (len(average_speeds["CMHQuery1"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["CMHQuery1"][eps]), 0.5)
                yErr.append(err)
        algLabel = 'HCMS'
        print 'yvals:\n',yVals
        print 'xvals:\n',update_values
        print yVals, 'CMHQuery1'
        plt.errorbar(update_values, yVals, yerr=yErr,fmt='-.v' ,label=algLabel, color="orange", capsize=10, elinewidth=3, capthick=1.5)
        ylabel_str = "Query/second [Millions]"

    if (sys.argv[1] == "Update2"):
        update_values = sorted(average_speeds["Update2"])

        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in update_values:
                mean = sum(average_speeds["Update2"][eps]) / len(average_speeds["Update2"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["Update2"][eps]])
                variance = (sos / (len(average_speeds["Update2"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["Update2"][eps]), 0.5)
                yErr.append(err)
        algLabel = 'PAPA'
        print 'yvals:\n',yVals
        print 'xvals:\n',update_values
        plt.errorbar(update_values, yVals, yerr=yErr,fmt='-.D' ,label=algLabel, color="blue", capsize=10, elinewidth=3, capthick=1.5)

        update_values = sorted(average_speeds["UpdateNapa2"])

        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in update_values:
                mean = sum(average_speeds["UpdateNapa2"][eps]) / len(average_speeds["UpdateNapa2"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["UpdateNapa2"][eps]])
                variance = (sos / (len(average_speeds["UpdateNapa2"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["UpdateNapa2"][eps]), 0.5)
                yErr.append(err)
        algLabel = 'NAPA'
        print 'yvals:\n',yVals
        print 'xvals:\n',update_values
        plt.errorbar(update_values, yVals, yerr=yErr,fmt='-.D' ,label=algLabel, color="red", capsize=10, elinewidth=3, capthick=1.5)



        update_values = sorted(average_speeds["CMHUpdate2"])

        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in update_values:
                mean = sum(average_speeds["CMHUpdate2"][eps]) / len(average_speeds["CMHUpdate2"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["CMHUpdate2"][eps]])
                variance = (sos / (len(average_speeds["CMHUpdate2"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["CMHUpdate2"][eps]), 0.5)
                yErr.append(err)
        algLabel = 'MDSketch'
        print 'yvals:\n',yVals
        print 'xvals:\n',update_values
        print yVals, 'CMHUpdate'
        plt.errorbar(update_values, yVals, yerr=yErr,fmt='-.v' ,label=algLabel, color="orange", capsize=10, elinewidth=3, capthick=1.5)
        ylabel_str = "Update/second [Millions]"


    if (sys.argv[1] == "Query2"):
        update_values = sorted(average_speeds["Query2"])

        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in update_values:
                mean = sum(average_speeds["Query2"][eps]) / len(average_speeds["Query2"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["Query2"][eps]])
                variance = (sos / (len(average_speeds["Query2"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["Query2"][eps]), 0.5)
                yErr.append(err)
        algLabel = 'PAPA'
        print 'yvals:\n',yVals
        print 'xvals:\n',update_values
        plt.errorbar(update_values, yVals, yerr=yErr,fmt="-.8" ,label=algLabel, color="blue", capsize=MS, markersize=MS, elinewidth=LW, capthick=CT)

        update_values = sorted(average_speeds["QueryNapa2"])

        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in update_values:
                mean = sum(average_speeds["QueryNapa2"][eps]) / len(average_speeds["QueryNapa2"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["QueryNapa2"][eps]])
                variance = (sos / (len(average_speeds["QueryNapa2"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["QueryNapa2"][eps]), 0.5)
                yErr.append(err)
        algLabel = 'NAPA'
        print 'yvals:\n',yVals
        print 'xvals:\n',update_values
        plt.errorbar(update_values, yVals, yerr=yErr,fmt=":*" ,label=algLabel, color="red", capsize=MS, markersize=MS, elinewidth=LW, capthick=CT)



        update_values = sorted(average_speeds["CMHQuery2"])

        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in update_values:
                mean = sum(average_speeds["CMHQuery2"][eps]) / len(average_speeds["CMHQuery2"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["CMHQuery2"][eps]])
                variance = (sos / (len(average_speeds["CMHQuery2"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["CMHQuery2"][eps]), 0.5)
                yErr.append(err)
        algLabel = 'MDSketch'
        print 'yvals:\n',yVals
        print 'xvals:\n',update_values
        print yVals, 'CMHQuery2'
        plt.errorbar(update_values, yVals, yerr=yErr,fmt="--v" ,label=algLabel, color="green", capsize=MS, markersize=MS, elinewidth=LW, capthick=CT)
        ylabel_str = "Query/second[$10^6$]"


    if (sys.argv[1] == "newUpdate2"):
        update_values = sorted(average_speeds["UpdatePAPA"])

        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in update_values:
                mean = sum(average_speeds["UpdatePAPA"][eps]) / len(average_speeds["UpdatePAPA"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["UpdatePAPA"][eps]])
                variance = (sos / (len(average_speeds["UpdatePAPA"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["UpdatePAPA"][eps]), 0.5)
                yErr.append(err)
        algLabel = 'PAPA'
        print 'yvals:\n',yVals
        print 'xvals:\n',update_values
        plt.errorbar(update_values, yVals, yerr=yErr,fmt="-.8" ,label=algLabel, color="blue", capsize=MS, markersize=MS, elinewidth=LW, capthick=CT)

        update_values = sorted(average_speeds["UpdateNapa"])

        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in update_values:
                mean = sum(average_speeds["UpdateNapa"][eps]) / len(average_speeds["UpdateNapa"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["UpdateNapa"][eps]])
                variance = (sos / (len(average_speeds["UpdateNapa"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["UpdateNapa"][eps]), 0.5)
                yErr.append(err)
        algLabel = 'NAPA'
        print 'yvals:\n',yVals
        print 'xvals:\n',update_values
        plt.errorbar(update_values, yVals, yerr=yErr,fmt=":*" ,label=algLabel, color="red", capsize=MS, markersize=MS, elinewidth=LW, capthick=CT)



        update_values = sorted(average_speeds["CMHUpdate2"])

        yErr = []
        yVals = []
        t_n_1 = 2.262 # t statistic for 9 degrees of freedom @ 0.95 confidence two tail
        for eps in update_values:
                mean = sum(average_speeds["CMHUpdate2"][eps]) / len(average_speeds["CMHUpdate2"][eps])
                yVals.append(mean)
                sos = sum([(x - mean)**2 for x in average_speeds["CMHUpdate2"][eps]])
                variance = (sos / (len(average_speeds["CMHUpdate2"][eps]) - 1) )# ** 0.5
                err = variance * t_n_1 / pow(len(average_speeds["CMHUpdate2"][eps]), 0.5)
                yErr.append(err)
        algLabel = 'MDSketch'
        print 'yvals:\n',yVals
        print 'xvals:\n',update_values
        print yVals, 'CMHUpdate'
        plt.errorbar(update_values, yVals, yerr=yErr,fmt="--v",label=algLabel, color="green", capsize=MS, markersize=MS, elinewidth=LW, capthick=CT)
        ylabel_str = "Update/second[$10^6$]"

    plt.xscale("log",basex=2)
    plt.yscale("log",basex=2)
    plt.gca().xaxis.set_major_locator(ticker.LogLocator(base=2))
    plt.xlabel("Accuracy Guarantee ($\epsilon$)", fontsize=38)
    #ylabel_str = "Update/second [Millions]" #For Queries in Millions

    plt.ylabel(ylabel_str, fontsize=38)
    plt.tick_params(labelsize=20)
    plt.xlim(left = 2**-(maxEps-1), right=2**-minEps)
    #plt.ylim(10**(-1), 2)
#    plt.yticks([10**(-4),10**1])
    #plt.yticks([0,1])

    #plt.legend(loc="best") # keys of the graphs
    #plt.legend(loc="best",prop={'size':18},ncol=20) # keys of the graphs

    plt.tight_layout()
    #plt.savefig('graphs/'+ sys.argv[1] +'_result_epsilon.png')
    #plt.savefig('graphs/'+ sys.argv[1] +'_newfacebook_napa_dataset_epsilon.png')
    plt.savefig('graphs/KDD/'+ sys.argv[1] + '_' + sys.argv[2] +'_epsilon.png')
    plt.clf()





if (sys.argv[1] == "Update"):
    #csvFiles = 'update_test.txt'
    #csvFiles = 'fupdate.txt'
    #csvFiles = 'newfupdate.txt'
    csvFiles = 'update_all_synth.txt'
if (sys.argv[1] == "Query"):
    #csvFiles = 'query_test.txt'
    #csvFiles = 'fquery_test.txt'
    #csvFiles = 'newfquery.txt'
    csvFiles = 'query_all_synth.txt'
if (sys.argv[1] == "QueryDiff"):
    #csvFiles = 'querydiff_test.txt'
    #csvFiles = 'fquerydiff_test.txt'
    csvFiles = 'newfquerydiff.txt'
if (sys.argv[1] == "dupdate"):
    csvFiles = 'dupdate_test.txt'
if (sys.argv[1] == "dquery"):
    csvFiles = 'papa_query3d.txt'
if (sys.argv[1] == "Updatewnapa"):
    csvFiles = 'update_napa_test.txt'
if (sys.argv[1] == "Update1"):
    csvFiles = 'update1_all_synth.txt'
if (sys.argv[1] == "Query1"):
    csvFiles = 'query1_all_synth.txt'
if (sys.argv[1] == "Update2"):
    csvFiles = 'update2_all_synth_excms.txt'
############################ NEW KDD #################################

if (sys.argv[1] == "Query2"):
    #csvFiles = 'query2_all_synth_excms.txt'
    csvFiles = 'query2_all_synth_wcms_new.txt'
if (sys.argv[1] == "newUpdate2"):
    csvFiles = 'change_range_m_256.txt'
#    csvFiles = 'change_range_m_1024.txt'

minEps = 2
maxEps = 9
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
	speeds[alg][counters].append((ops / float(timing))/ 1e6)
plot_speeds(speeds)
