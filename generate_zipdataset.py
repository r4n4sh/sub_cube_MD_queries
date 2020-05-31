#!/usr/bin/python

import sys
import random 
import numpy as np



a = 1.1 # parameter


def main():
	size = int(sys.argv[1]) * (int(sys.argv[2]))
	s = np.random.zipf(a, size)

	print s

	w =  0

	result = (s/int(max(s)))*200

	print min(s), max(s)
	print min(result), max(result)

	print result

	k = 0
	w = 0
	f = open("datasetzip.txt","w+")

#	for g in range(size):
#		print result[w]
#		print w
#		w = w + 1

	for i in range(int(sys.argv[1])):
		for j in range(int(sys.argv[2]) - 1):
			f.write("%d " % (result[k]))
			k = k + 1

		f.write("%d\n" % (result[k]))
		k = k + 1

	f.close() 



def main1():
	size = int(sys.argv[1]) * (int(sys.argv[2]))
	s = np.random.zipf(a, size)

	w =  0
	k = 0
	#print min(s), max(s)

	OldMax = max(s)
	OldMin = min(s)
	NewMax = 200
	NewMin = 0

	OldRange = (OldMax - OldMin)  
	NewRange = (NewMax - NewMin)  


	result = []

	for g in range(size):
		new_val = int((((s[g] - OldMin) * NewRange) / float(OldRange) + NewMin))
		if (new_val < 0):
			print "***********************"
			print g, s[g], OldMin, NewRange, OldRange, NewMin
			tmp = s[g] - OldMin
			print tmp
			#result.append(0)
			sys.exit()

		else:
			result.append(new_val)
		#print g, new_val

	#print result


	f = open("datasetzip.txt","w+")

	for i in range(int(sys.argv[1])):
		for j in range(int(sys.argv[2]) - 1):
			f.write("%d " % (result[k]))
			k = k + 1

		f.write("%d\n" % (result[k]))
		k = k + 1

	f.close() 



#main()
main1()


