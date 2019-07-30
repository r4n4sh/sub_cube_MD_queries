#!/usr/bin/python

import sys
import random 


def main():
	f= open("dataset.txt","w+")

	for i in range(int(sys.argv[1])):
		for j in range(int(sys.argv[2]) - 1):
			f.write("%d " % (random.randint(1,200)))

		f.write("%d\n" % (random.randint(1,200)))

	f.close() 


main()
