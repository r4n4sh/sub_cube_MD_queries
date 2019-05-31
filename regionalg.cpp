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

int main(int argc, char * argv[]) {

  cout << "Main Test of RegionAlg!" << endl;


	int *upper_limits = new int[2];
	int *lower_limits = new int[2];
	int epsilon_1 = 16;
	int numItems = 1000;
	int d = 2;
	ifstream myfile ("dataset.txt");

	upper_limits[0] = 16;
	upper_limits[1] = 32;
	lower_limits[0] = 0;
	lower_limits[1] = 0;



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




	RegionAlg* alg = new RegionAlg(2, epsilon_1, upper_limits, lower_limits);

/*
	vector<int> cor1 = {15,31};
	vector<int> res = alg->fromCorToBlock(cor1);

	for (int i = 0; i < 2; i++) {
  		cout << "result[" << i << "]: "<< res[i] << endl;
	}
*/


	auto f = [](int a, int b) { std::vector<int> c = {a, b}; return c;};
	auto g = [](bool a, bool b) { std::vector<bool> c = {a, b}; return c;};

	int count = alg->rtree->countInRange(f(2, 1), f(2, 3), g(true, true), g(true, true));
	cout << "count in range: "<< count << endl;

/*
	std::vector<RT::Point<int,int> >  points = alg->rtree->pointsInRange(f(2, 1), f(2, 3), g(true, true), g(true, true));
	cout << "count in range: "<< count << endl;



	for(auto const& value: points) {
		std::vector<int> vec = value.asVector();
	    cout << "point: ";

		for(auto const& p: vec) {
			cout << p;
		}

		cout << endl;
	}
*/
    RT::Point<int,int>* a = new RT::Point<int,int> (f(2,4), 0);

	alg->rtree->updateSketch(new RT::Point<int,int> (f(2,3), 0));
	alg->rtree->updateSketch(new RT::Point<int,int> (f(2,2), 0));
	alg->rtree->updateSketch(new RT::Point<int,int> (f(2,1), 0));


    int res1 = alg->rtree->countInSketchRange(f(2, 1), f(2, 3), a);
	cout << "count sketch range: "<< res1 << endl;


	clock_t begint, endt;
	struct timeb begintb, endtb;
	double time;
	string line;
	vector<int> vdata[numItems];
    std::vector<std::string> tokens;

	if (myfile.is_open()) {
		int i = 0;
		while (getline (myfile,line) && i < numItems)
		{
		    split(tokens, line, boost::is_any_of(" ")); // here it is
			for(auto& s: tokens) {
				vdata[i].push_back(stoi(s));
			}
			i++;
		}
	}


	/*
		Update Test

	begint = clock();
	ftime(&begintb);

	for (int i = 0; i < numItems; i++) {
		//sa->update(vdata[i]);
		alg->rtree->updateSketch(new RT::Point<int,int> (vdata[i], 0));
	}

	endt = clock();
	ftime(&endtb);
	time = ((double)(endt-begint))/CLK_PER_SEC;
	printf( "Update %d pairs took %lfs %d 1/epsilon\n", numItems, time, epsilon_1);*/

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
	rtree = new RT::RangeTree<int,int>(points);

	rtree->print(); //TODO: this is only for testing
}


void RegionAlg::update(vector<int> x)
{

}


int RegionAlg::query(vector<int> x, vector<int>& lower, vector<int>& upper)
{
	//TODO implementation

	return 1;
}

