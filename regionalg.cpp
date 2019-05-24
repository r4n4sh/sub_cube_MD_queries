#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>
#include <cmath>
#include <sys/timeb.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include "RangeTree.h"
#include "regionalg.h"

namespace RT = RangeTree;



int main(int argc, char * argv[]) {

  cout << "Main Test of RegionAlg!" << endl;


	int *upper_limits = new int[2];
	int *lower_limits = new int[2];

	upper_limits[0] = 16;
	upper_limits[1] = 32;
	lower_limits[0] = 0;
	lower_limits[1] = 0;


	RegionAlg* alg = new RegionAlg(2, 4, upper_limits, lower_limits);

	vector<int> cor1 = {15,31};
	vector<int> res = alg->fromCorToBlock(cor1);

	for (int i = 0; i < 2; i++) {
  		cout << "result[" << i << "]: "<< res[i] << endl;
	}

	return 1;
}


std::vector<int> RegionAlg::fromCorToBlock(vector<int> cor)
{
	std::vector<int> result;

	for (int i = 0; i < d; i++) {
		int step = floor(float(upper_limits[i])/float(eps_1));
		int p = ceil(float(cor[i])/float(step));
		result.push_back(p);
	}

	return result;
}


RegionAlg::RegionAlg(int dimensions, int epsilon_1, int* gupperlimits, int* glowerlimits)
{	// Initialize the sketch based on user-supplied size
	d = dimensions;
	upper_limits = gupperlimits;
	lower_limits = glowerlimits;
	eps_1 = epsilon_1; //1\epsilon


	/* Prepare the points to build the range tree */
	std::vector<RT::Point<int,int>> points = {};

	auto f = [](int a, int b) { std::vector<int> d = {a, b}; return d;}; //TODO: this is relevant only for 2d
	for (int i = 1; i <= epsilon_1; i++) {
		for (int j = 1; j <= epsilon_1; j++) {
			RT::Point<int, int> a(f(i, j), 0);
			points.push_back(a);
		}
	}

	/* Construct the range tree */
	RT::RangeTree<int,int> rtree(points);

	rtree.print(); //TODO: this is only for testing
}


void RegionAlg::update(vector<int> x)
{

}


int RegionAlg::query(vector<int> x, vector<int>& lower, vector<int>& upper)
{
	//TODO implementation

	return 1;
}

