#!/usr/bin/python

import sys
import random 


#./generate_dataset.py n d range

def main():
	f= open("cmdataset.txt","w+")
#	f= open("tmpdataset.txt","w+")

	limit = int(sys.argv[3])
	for i in range(int(sys.argv[1])):
		for j in range(int(sys.argv[2]) - 1):
			f.write("%d " % (random.randint(1, limit)))

		f.write("%d\n" % (random.randint(1, limit)))

	f.close() 


main()