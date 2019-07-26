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
#include "napa.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>



#ifndef CLK_PER_SEC
#ifdef CLOCKS_PER_SEC
#define CLK_PER_SEC CLOCKS_PER_SEC
#endif
#endif


double delta = 0.01;

auto f = [](int a, int b) { std::vector<int> c = {a, b}; return c;};
auto g = [](bool a, bool b) { std::vector<bool> c = {a, b}; return c;};
auto f3 = [](int a, int b, int c) { std::vector<int> d = {a, b, c}; return d;};


int main(int argc, char * argv[]) {

	int *upper_limits = new int[3];
	int *lower_limits = new int[3];
	int epsilon_1 = 8;
	//int numItems = 990;
	int numItems = 200000;
	//int numItems = 10;

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

	NapaAlg* alg = new NapaAlg(d, epsilon_1, upper_limits, lower_limits);

	clock_t begint, endt;
	struct timeb begintb, endtb;
	double time;
	string line;
	int datalen = 10;
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
		Update Test */

	begint = clock();
	ftime(&begintb);

	for (int i = 0; i < numItems; i++) {
		alg->update(vdata[i % datalen]);
	}

	endt = clock();
	ftime(&endtb);
	time = ((double)(endt-begint))/CLK_PER_SEC;
	//printf( "UpdateNapa %d pairs took %lfs %d 1/epsilon\n", numItems, time, epsilon_1);




	/*
		Query Test */


	begint = clock();
	ftime(&begintb);


	for (int i = 0; i < numItems; i++) {
		vector<int> lower;
		vector<int> upper;

		int lower1 = rand() % (upper_limits[0] - 1);
		int upper1 =  rand() % (upper_limits[1] - 1);



		lower.push_back(lower1);
		lower.push_back(lower1 + 1 + (rand() % (upper_limits[0] - lower1 - 1)));
		upper.push_back(upper1);
		upper.push_back(upper1 + 1 +(rand() % (upper_limits[1] - upper1 - 1)));

		alg->countQuery(lower, upper);
	}

	endt = clock();
	ftime(&endtb);
	time = ((double)(endt-begint))/CLK_PER_SEC;
	printf( "QueryNapa %d pairs took %lfs %d 1/epsilon\n", numItems, time, epsilon_1);

}


std::vector<int> NapaAlg::fromCorToBlock(vector<int> cor)
{
	std::vector<int> result;

	for (int i = 0; i < d; i++) {
		int step = floor(float(upper_limits[i])/float(eps_1));
		int p = ceil(float(cor[i])/float(step));
		result.push_back(p);
	}

	return result;
}


NapaAlg::NapaAlg(int dimensions, int epsilon_1, int* gupperlimits, int* glowerlimits)
{	// Initialize the sketch based on user-supplied size
	d = dimensions;
	upper_limits = gupperlimits;
	lower_limits = glowerlimits;
	eps_1 = epsilon_1; //1\epsilon
	sample_size = epsilon_1 * log2(ceil(1/delta));

	if (dimensions == 2) {
		/* Prepare the points to build the range tree */
		std::vector<RT::Point<int,int>> points = {};

		for (int i = 1; i <= epsilon_1; i++) {
			for (int j = 1; j <= epsilon_1; j++) {
				RT::Point<int, int> a(f(i, j), 0);
				points.push_back(a);
			}
		}


		/* Count number of the samples in each row and col */
		samples_row_num = new int[epsilon_1 + 1];
		samples_col_num = new int[epsilon_1 + 1];
		
		for(int i = 0; i <= epsilon_1; i++) {
			samples_row_num[i] = 0;
			samples_col_num[i] = 0;
		}

		/* The samples itself */
		samples_row = new vector<RT::Point<int,int>>[epsilon_1 + 1];
		samples_col = new vector<RT::Point<int,int>>[epsilon_1 + 1];

		/*Array of pointers to trees */

		row_trees = new RT::RangeTree<int,int>*[epsilon_1 + 1];
		col_trees = new RT::RangeTree<int,int>*[epsilon_1 + 1];

		for(int i = 0; i <= epsilon_1; i++) {
			row_trees[i] = NULL;
			col_trees[i] = NULL;
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


void NapaAlg::update(vector<int> x)
{
	int firstCor = ceil (x[0] / ceil(double(upper_limits[0])/double(eps_1)));
	int secondCor = ceil (x[1] / ceil(double(upper_limits[1])/double(eps_1)));



	rtree->updateSketch(new RT::Point<int,int> (f(firstCor,secondCor), 0));

	/*
	###############################################################

		Add the item to the sample if the relevant row
	
	###############################################################
	*/

	++samples_row_num[secondCor];
	if(samples_row_num[secondCor] < sample_size) {
		RT::Point<int, int> a(x, 0);
		samples_row[secondCor].push_back(a);
	} else if (samples_row_num[secondCor] == sample_size) {
		RT::Point<int, int> a(x, 0);
		samples_row[secondCor].push_back(a);

		/*build the relevant range tree*/
		row_trees[secondCor] = new RT::RangeTree<int,int>(samples_row[secondCor]);
	} else {
		int j = rand() % (samples_row_num[secondCor]+1);
		// If the randomly picked index is smaller than k, then replace
		// the element present at the index with new element from stream

		if ( j < sample_size) {
		/* ###############################################
		    Replace between j and the new item
		   ############################################### */

			//std::vector<int>* vout = samples_row[secondCor][j];
			RT::Point<int, int> vout = samples_row[secondCor].at(j);
			//RT::Point<double,int> pointout(*x, 0);
			RT::Point<int,int> pointin(x, 0);
			row_trees[secondCor]->replace(pointin, vout);
			samples_row[secondCor][j] = pointin;
		}
	}


	/*
	###############################################################

		Add the item to the sample if the relevant col
	
	###############################################################
	*/


	++samples_col_num[firstCor];
	if (samples_col_num[firstCor] < sample_size) {
		RT::Point<int, int> a(x, 0);
		samples_col[firstCor].push_back(a);
		return;
	} else if (samples_col_num[firstCor] == sample_size) {
		RT::Point<int, int> a(x, 0);
		samples_col[firstCor].push_back(a);

		/*build the relevant range tree*/
		col_trees[firstCor] = new RT::RangeTree<int,int>(samples_col[firstCor]);
		return;
	} else {
		int j = rand() % (samples_col_num[firstCor]+1);
		// If the randomly picked index is smaller than k, then replace
		// the element present at the index with new element from stream

		if ( j < sample_size) {
		/* ###############################################
		    Replace between j and the new item
		   ############################################### */

			RT::Point<int, int> vout = samples_col[firstCor].at(j);
			//RT::Point<double,int> pointout(*x, 0);
			RT::Point<int,int> pointin(x, 0);
			col_trees[firstCor]->replace(pointin, vout);
			samples_col[firstCor][j] = pointin;
		}
	}

}

void NapaAlg::update3(vector<int> x)
{
	int firstCor = ceil (x[0] / ceil(double(upper_limits[0])/double(eps_1)));
	int secondCor = ceil (x[1] / ceil(double(upper_limits[1])/double(eps_1)));
	int third = ceil (x[2] / ceil(double(upper_limits[2])/double(eps_1)));

	//TODO: this is only for 2d and the lowers start from 0!
	return rtree->updateSketch(new RT::Point<int,int> (f3(firstCor,secondCor,third), 0));
}


int NapaAlg::countQuery(vector<int>& lower, vector<int>& upper)
{
	//TODO deal when lower_limits = 0;

	int firstCorLower = ceil(lower[0] / ceil(double (upper_limits[0])/double(eps_1)));
	int secondCorLower = ceil(lower[1] / ceil(double(upper_limits[1])/double(eps_1)));

	int firstCorUpper = ceil(upper[0] / ceil(double(upper_limits[0])/double(eps_1)));
	int secondCorUpper = ceil(upper[1] / ceil(double(upper_limits[1])/double(eps_1)));


	int result = rtree->countInSketchRange(f(firstCorLower,secondCorLower), f(firstCorUpper,secondCorUpper));

	int gx1 = lower[0];
	int x1 = firstCorLower*ceil(double (upper_limits[0])/double(eps_1));


	int gx2 = upper[0];
	int x2 = firstCorUpper*ceil(double (upper_limits[0])/double(eps_1));


	int gy1 = lower[1];
	int y1 = secondCorLower*ceil(double (upper_limits[0])/double(eps_1));


	int gy2 = upper[1];
	int y2 = secondCorUpper*ceil(double (upper_limits[0])/double(eps_1));


	if (gx1 < x1) {


		/*  Deal with y axis - part 1*/
		for (int i = floor(double(lower[1]*eps_1) / double(upper_limits[1])); i <= ceil(double(upper[1]*eps_1) / double(upper_limits[1])); i++){
		

			if (i == floor(double(lower[1]*eps_1) / double(upper_limits[1]))) {
				if (col_trees[i])
					result += col_trees[i]->countInSketchRange(f(gx1,gy1), f(x1, y1));
				continue;
			}
			if (i == ceil(double(upper[1]*eps_1) / double(upper_limits[1]))) {
				if (col_trees[i])
					result += col_trees[i]->countInSketchRange(f(gx1,y2), f(x1, gy2));
				continue;
			}
		
			if (col_trees[i])
				result += col_trees[i]->countInSketchRange(f(gx1,(i-1)*ceil(double(upper_limits[1])/double(eps_1))), f(x1,(i)*ceil(double(upper_limits[1])/double(eps_1))));

		}
	}



	if (gy1 < y1) {


		/*  Deal with y axis - part 1*/
		for (int i = floor(double(lower[0]*eps_1) / double(upper_limits[0])); i <= ceil(double(upper[0]*eps_1) / double(upper_limits[0])); i++){
		

			if (i == floor(double(lower[0]*eps_1) / double(upper_limits[0]))) {
				if (row_trees[i])
					result += row_trees[i]->countInSketchRange(f(gx1,gy1), f(x1, y1));
				continue;
			}

			if (i == ceil(double(upper[0]*eps_1) / double(upper_limits[0]))) {
				if (row_trees[i])
					result += row_trees[i]->countInSketchRange(f(x2,gy1), f(gx2, y1));
				continue;
			}

			if (row_trees[i])
				result += row_trees[i]->countInSketchRange(f((i-1)*ceil(double(upper_limits[0])/double(eps_1)),gy1), f((i)*ceil(double(upper_limits[0])/double(eps_1)),y1));

		}
	}

	if (x2 < gx2) {

		for (int i = floor(double(lower[1]*eps_1) / double(upper_limits[1])); i <= ceil(double(upper[1]*eps_1) / double(upper_limits[1])); i++){
		

			if (i == floor(double(lower[1]*eps_1) / double(upper_limits[1]))) {
				if (col_trees[i])
					result += col_trees[i]->countInSketchRange(f(x2,gy1), f(gx2, y1));
				continue;
			}
			if (i == ceil(double(upper[1]*eps_1) / double(upper_limits[1]))) {
				if (col_trees[i])
					result += col_trees[i]->countInSketchRange(f(x2,y2), f(gx2, gy2));
				continue;
			}
		
			if (col_trees[i])
				result += col_trees[i]->countInSketchRange(f(x2,(i-1)*ceil(double(upper_limits[1])/double(eps_1))), f(gx2,(i)*ceil(double(upper_limits[1])/double(eps_1))));

		}

	}


	if (y2 < gy2) {
		for (int i = floor(double(lower[0]*eps_1) / double(upper_limits[0])); i <= ceil(double(upper[0]*eps_1) / double(upper_limits[0])); i++){
	

		if (i == floor(double(lower[0]*eps_1) / double(upper_limits[0]))) {
			if (row_trees[i])
				result += row_trees[i]->countInSketchRange(f(gx1,y2), f(x1, gy2));
			continue;
		}

		if (i == ceil(double(upper[0]*eps_1) / double(upper_limits[0]))) {
			if (row_trees[i])
				result += row_trees[i]->countInSketchRange(f(x2,y2), f(gx2, gy2));
			continue;
		}

		if (row_trees[i])
			result += row_trees[i]->countInSketchRange(f((i-1)*ceil(double(upper_limits[0])/double(eps_1)),y2), f((i)*ceil(double(upper_limits[0])/double(eps_1)),gy2));

		}
	}


	return result;
}

int NapaAlg::countQuery3(vector<int>& lower, vector<int>& upper)
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

