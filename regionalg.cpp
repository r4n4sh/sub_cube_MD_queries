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
#include "regionalg.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>



#ifndef CLK_PER_SEC
#ifdef CLOCKS_PER_SEC
#define CLK_PER_SEC CLOCKS_PER_SEC
#endif
#endif



auto f = [](int a, int b) { std::vector<int> c = {a, b}; return c;};
auto g = [](bool a, bool b) { std::vector<bool> c = {a, b}; return c;};
auto f3 = [](int a, int b, int c) { std::vector<int> d = {a, b, c}; return d;};


int main(int argc, char * argv[]) {

	int *upper_limits = new int[3];
	int *lower_limits = new int[3];
	int epsilon_1 = 10;
	//int numItems = 99003;
	int numItems = 200000;
	int d = 2;
	ifstream myfile ("dfacebookdataset2d.txt");

	upper_limits[0] = 200;
	upper_limits[1] = 200;
	upper_limits[2] = 200;
	lower_limits[0] = 0;
	lower_limits[1] = 0;
	lower_limits[2] = 0;


	/*
		Parse Arguments
	*/

	for (int i = 1; i < argc; i++)
	{
		if (i + 1 != argc)
		{
            if (strcmp(argv[i], "-n") == 0) // This is your parameter name
	        {
				numItems = atoi(argv[i+1]);
	            i++;    // Move to the next flag
	        }

			if (strcmp(argv[i], "-f") == 0)
			{
				ifstream myfile (argv[i+1]);
				i++;
			}
			if (strcmp(argv[i], "-e") == 0)
			{
				epsilon_1 = atoi(argv[i+1]);
				i++;
			}
			if (strcmp(argv[i], "-d") == 0)
			{
				d = atoi(argv[i+1]);
				i++;
			}

		}
	}

	RegionAlg* alg = new RegionAlg(d, epsilon_1, upper_limits, lower_limits);

/*
	int count = alg->rtree->countInRange(f(2, 1), f(2, 3), g(true, true), g(true, true));
	cout << "count in range: "<< count << endl;

    RT::Point<int,int>* a = new RT::Point<int,int> (f(2,4), 0);

	alg->rtree->updateSketch(new RT::Point<int,int> (f(2,3), 0));
	alg->rtree->updateSketch(new RT::Point<int,int> (f(2,2), 0));
	alg->rtree->updateSketch(new RT::Point<int,int> (f(2,1), 0));


    int res1 = alg->rtree->countInSketchRange(f(2, 1), f(2, 3));
	cout << "count sketch range: "<< res1 << endl;
*/

	clock_t begint, endt;
	struct timeb begintb, endtb;
	double time;
	string line;
	int datalen = 200000;
	vector<int> vdata[datalen];

    std::vector<std::string> tokens;

	if (myfile.is_open()) {
		int i = 0;
		while (getline (myfile,line) && i < datalen)
		{
		    split(tokens, line, boost::is_any_of(" ")); // here it is
			for(auto& s: tokens) {
				vdata[i].push_back(stoi(s));
			}
			i++;
		}
	}


	/* Translate from points to blocks */


	/*
		Update Test*/

	begint = clock();
	ftime(&begintb);

	for (int i = 0; i < numItems; i++) {
		alg->update(vdata[i % datalen]);
	}

	endt = clock();
	ftime(&endtb);
	time = ((double)(endt-begint))/CLK_PER_SEC;
	//printf( "Update %d pairs took %lfs %d 1/epsilon\n", numItems, time, epsilon_1);


	/*
		Query Test

	begint = clock();
	ftime(&begintb);

	for (int i = 0; i < numItems; i++) {
		int x1 = rand() % epsilon_1;
		int diff1 = rand() % (epsilon_1 - x1);
		int y1 = rand() % epsilon_1;
		int diff2 = rand() % (epsilon_1 - y1);

		alg->rtree->countInSketchRange(f(x1, y1), f(x1 + diff1, y1 + diff2));
	}

	endt = clock();
	ftime(&endtb);
	time = ((double)(endt-begint))/CLK_PER_SEC;
	printf( "Query %d pairs took %lfs %d 1/epsilon\n", numItems, time, epsilon_1);*/
  


	/*
		Query Test - small rectangles*/

	begint = clock();
	ftime(&begintb);

	for (int i = 0; i < numItems; i++) {
		int x1 = rand() % epsilon_1;
		int diff1 = 1;
		int y1 = rand() % epsilon_1;
		int diff2 = 1;

		alg->rtree->countInSketchRange(f(x1, y1), f(x1 + diff1, y1 + diff2));
	}

	endt = clock();
	ftime(&endtb);
	time = ((double)(endt-begint))/CLK_PER_SEC;
	printf( "QuerySmall %d pairs took %lfs %d 1/epsilon\n", numItems, time, epsilon_1);


	/*
		Query Test - BIG rectangles */

	begint = clock();
	ftime(&begintb);

	for (int i = 0; i < numItems; i++) {
		int x1 = rand() % epsilon_1;
		int diff1 = 1;
		int y1 = rand() % epsilon_1;
		int diff2 = 1;

		alg->rtree->countInSketchRange(f(0, 0), f(epsilon_1, epsilon_1));
	}

	endt = clock();
	ftime(&endtb);
	time = ((double)(endt-begint))/CLK_PER_SEC;
	printf( "QueryBig %d pairs took %lfs %d 1/epsilon\n", numItems, time, epsilon_1);



/*
		Update Test in 3-d

	begint = clock();
	ftime(&begintb);

	for (int i = 0; i < numItems; i++) {
		alg->update3(vdata[i % datalen]);
	}

	endt = clock();
	ftime(&endtb);
	time = ((double)(endt-begint))/CLK_PER_SEC;
	printf( "Update3 %d pairs took %lfs %d 1/epsilon\n", numItems, time, epsilon_1);*/

	return 0;
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


	if (dimensions == 2) {
		/* Prepare the points to build the range tree */
		std::vector<RT::Point<int,int>> points = {};

		for (int i = 1; i <= epsilon_1; i++) {
			for (int j = 1; j <= epsilon_1; j++) {
				RT::Point<int, int> a(f(i, j), 0);
				points.push_back(a);
			}
		}

		/* Construct the range tree */
		rtree = new RT::RangeTree<int,int>(points);
	} else if (dimensions == 3) {
		/* Prepare the points to build the range tree */
		std::vector<RT::Point<int,int>> points = {};

		for (int i = 1; i <= epsilon_1; i++) {
			for (int j = 1; j <= epsilon_1; j++) {
				for (int k = 1; k <= epsilon_1; k++) {
					RT::Point<int, int> a(f3(i, j, k), 0);
					points.push_back(a);
				}
			}
		}

		/* Construct the range tree */
		rtree = new RT::RangeTree<int,int>(points);
	}
}


void RegionAlg::update(vector<int> x)
{
	int firstCor = ceil (x[0] / ceil(double(upper_limits[0])/double(eps_1)));
	int secondCor = ceil (x[1] / ceil(double(upper_limits[1])/double(eps_1)));

	//TODO: this is only for 2d and the lowers start from 0!
	return rtree->updateSketch(new RT::Point<int,int> (f(firstCor,secondCor), 0));
}

void RegionAlg::update3(vector<int> x)
{
	int firstCor = ceil (x[0] / ceil(double(upper_limits[0])/double(eps_1)));
	int secondCor = ceil (x[1] / ceil(double(upper_limits[1])/double(eps_1)));
	int third = ceil (x[2] / ceil(double(upper_limits[2])/double(eps_1)));

	//TODO: this is only for 2d and the lowers start from 0!
	return rtree->updateSketch(new RT::Point<int,int> (f3(firstCor,secondCor,third), 0));
}


int RegionAlg::countQuery(vector<int>& lower, vector<int>& upper)
{
	//TODO deal when lower_limits = 0;

	int firstCorLower = ceil (lower[0] / ceil(double (lower_limits[0])/double(eps_1)));
	int secondCorLower = ceil (lower[1] / ceil(double(lower_limits[1])/double(eps_1)));


	int firstCorUpper = ceil (upper[0] / ceil(double(upper_limits[0])/double(eps_1)));
	int secondCorUpper = ceil (upper[1] / ceil(double(upper_limits[1])/double(eps_1)));



	return rtree->countInSketchRange(f(firstCorLower,secondCorLower), f(firstCorUpper,secondCorUpper));
}

int RegionAlg::countQuery3(vector<int>& lower, vector<int>& upper)
{
	//TODO deal when lower_limits = 0;

	int firstCorLower = ceil (lower[0] / ceil(double (lower_limits[0])/double(eps_1)));
	int secondCorLower = ceil (lower[1] / ceil(double(lower_limits[1])/double(eps_1)));
	int thirdCorLower = ceil (lower[2] / ceil(double(lower_limits[2])/double(eps_1)));


	int firstCorUpper = ceil (upper[0] / ceil(double(upper_limits[0])/double(eps_1)));
	int secondCorUpper = ceil (upper[1] / ceil(double(upper_limits[1])/double(eps_1)));
	int thirdCorUpper = ceil (upper[2] / ceil(double(upper_limits[2])/double(eps_1)));

	return rtree->countInSketchRange(f3(firstCorLower,secondCorLower, thirdCorLower), f3(firstCorUpper,secondCorUpper, thirdCorUpper));
}

