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
	int epsilon_1 = 4;
	//int numItems = 990;
	int numItems = 200000;
	//int numItems = 10;

	int d = 2;
	ifstream myfile ("dfacebookdataset2d.txt");
	double emp_error = 0;

	upper_limits[0] = 300;
	upper_limits[1] = 300;
	upper_limits[2] = 300;
//	upper_limits[0] = 20;
//	upper_limits[1] = 20;
//	upper_limits[2] = 20;

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

/*
	// For basic testing
    RT::Point<int,int>* a = new RT::Point<int,int> (f(2,4), 0);
	vector<int> lower;
	vector<int> upper;
	lower.push_back(6);
	lower.push_back(5);
	upper.push_back(15);
	upper.push_back(15);

	alg->update(f(7,7));
	alg->update(f(8,12));

	alg->countQueryNaive(lower, upper);


*/
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
		Query Test NAPA using trees of samples
	*/
	begint = clock();
	ftime(&begintb);


	for (int i = 0; i < numItems; i++) {
		vector<int> lower;
		vector<int> upper;

		int lower1 = rand() % (upper_limits[0] - 1);
		int upper1 =  lower1 + 1 + rand() % (upper_limits[0] - lower1 - 1);


		int lower2 = rand() % (upper_limits[1] - 1);
		int upper2 =  lower2 + rand() % (upper_limits[1] - lower2 - 1);


		lower.push_back(lower1);
		lower.push_back(lower2);
		upper.push_back(upper1);
		upper.push_back(upper2);

		alg->countQueryTrees(lower, upper);
	}

	endt = clock();
	ftime(&endtb);
	time = ((double)(endt-begint))/CLK_PER_SEC;
	printf( "QueryNapa %d pairs took %lfs %d 1/epsilon\n", numItems, time, epsilon_1);
	//printf( "QueryNapaTrees %d pairs took %lfs %d 1/epsilon\n", numItems, time, epsilon_1);



	/*
		Query Test NAPA using scan of samples

	begint = clock();
	ftime(&begintb);


	for (int i = 0; i < numItems; i++) {
		vector<int> lower;
		vector<int> upper;

		int lower1 = rand() % (upper_limits[0] - 1);
		int upper1 =  lower1 + 1 + rand() % (upper_limits[0] - lower1 - 1);

		int lower2 = rand() % (upper_limits[1] - 1);
		int upper2 =  lower2 + rand() % (upper_limits[1] - lower2 - 1);


		lower.push_back(lower1);
		lower.push_back(lower2);
		upper.push_back(upper1);
		upper.push_back(upper2);

		alg->countQueryNaive(lower, upper);
	}

	endt = clock();
	ftime(&endtb);
	time = ((double)(endt-begint))/CLK_PER_SEC;
	printf( "QueryNapaNaive %d pairs took %lfs %d 1/epsilon\n", numItems, time, epsilon_1);*/

/*====================== TEST ERROR MEMORY ===============================*/

	double estimated, curr_error = 0;
	double exact = 0;
    std::vector<RT::Point<int,int>> points = {};
	int xfactor = ceil(double(upper_limits[0])/double(epsilon_1));
	int yfactor = ceil(double(upper_limits[1])/double(epsilon_1));


//	std::cout << "xfactor: " << xfactor << " yfactor: " << yfactor << std::endl; //TODO testing
	for (int i = 0; i < numItems; i++) {
		RT::Point<int,int> a(vdata[i % datalen], 0);
		points.push_back(a);
	}
 
    RT::RangeTree<int,int> exacttree(points);
    //cout << "printing exact tree" << endl;

	//exacttree.print(); //TODO:testing

	for (int i = 0; i < numItems; i++) {
		alg->update(vdata[i % datalen]);
	}


//	cout << "printing counters after update********" << endl; //TODO testing
//	alg->rtree->printwCounter(); //TODO testing

    for (int i = 0; i < numItems; i++)  {
		vector<int> lower;
		vector<int> upper;

		int lower1 = rand() % (upper_limits[0] - 1);
		int upper1 =  lower1 + 1 + rand() % (upper_limits[0] - lower1 - 1);


		int lower2 = rand() % (upper_limits[1] - 1);
		int upper2 =  lower2 + rand() % (upper_limits[1] - lower2 - 1);


		lower.push_back(lower1);
		lower.push_back(lower2);
		upper.push_back(upper1);
		upper.push_back(upper2);

		estimated = alg->countQueryNaive(lower, upper);

		exact = rtree.countInRange(lower, upper);

		curr_error = exact - estimated;

		if (curr_error != 0) {
			cout << "curr_error " << curr_error << " estimated: " << estimated << " exact: " << exact << endl;
			cout << "query estimated and exact: x: " << lower[0] <<" ,"<< upper[0] <<" y:  "<< lower[1] <<" ,"<< upper[1] << endl;
			estimated = alg->countQueryTrees(lower, upper);
		}
		// TODO: testing For debug

		curr_error = pow(curr_error, 2);
		emp_error += curr_error;
	}

	emp_error = sqrt((emp_error/numItems));

	printf( "./napa %d pairs emp error: %lf [%d eps_1]\n", numItems, emp_error, epsilon_1);





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
	sample_size = (epsilon_1)*(epsilon_1) * log2(ceil(1/delta));
	eps_1_tag = epsilon_1 * (2*dimensions+1);

	if (dimensions == 2) {
		epsilon_1_tag = epsilon_1 * (2*dimensions+1);
		/* Prepare the points to build the range tree */
		std::vector<RT::Point<int,int>> points = {};

		for (int i = 1; i <= epsilon_1_tag; i++) {
			for (int j = 1; j <= epsilon_1_tag; j++) {
				RT::Point<int, int> a(f(i, j), 0);
				points.push_back(a);
			}
		}


		/* Count number of the samples in each row and col */
		stream_size = 0;

		samples_row_num = new int[epsilon_1_tag + 1];
		samples_col_num = new int[epsilon_1_tag + 1];
		
		for(int i = 0; i <= epsilon_1_tag; i++) {
			samples_row_num[i] = 0;
			samples_col_num[i] = 0;
		}

		/* The samples itself */
		samples_row = new vector<RT::Point<int,int>>[epsilon_1_tag + 1];
		samples_col = new vector<RT::Point<int,int>>[epsilon_1_tag + 1];

		/*Array of pointers to trees */

		row_trees = new RT::RangeTree<int,int>*[epsilon_1_tag + 1];
		col_trees = new RT::RangeTree<int,int>*[epsilon_1_tag + 1];

		for(int i = 0; i <= epsilon_1_tag; i++) {
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

	int firstCor = ceil (double(x[0] + 1) / double(ceil(double(upper_limits[0])/double(eps_1_tag))));
	int secondCor = ceil (double(x[1] + 1) / double (ceil(double(upper_limits[1])/double(eps_1_tag))));




	rtree->updateSketch(new RT::Point<int,int> (f(firstCor,secondCor), 0));

	/*
	###############################################################

		Add the item to the sample if the relevant row and col
	
	###############################################################
	*/


	++stream_size;
	++samples_row_num[secondCor];
	++samples_col_num[firstCor];
	if(stream_size <= sample_size) {
		RT::Point<int, int> a(x, 0);
		samples_row[secondCor].push_back(a);
		samples_overall.push_back(x);
	} else {
		int j = rand() % (stream_size);
		// If the randomly picked index is smaller than k, then replace
		// the element present at the index with new element from stream

		if ( j < sample_size) {
		/* ###############################################
		    Replace between j and the new item
		   ############################################### */

			std::vector<int> vout = samples_overall[j];
			int firstCorOut = ceil (vout[0] / ceil(double(upper_limits[0])/double(eps_1_tag)));
			int secondCorOut = ceil (vout[1] / ceil(double(upper_limits[1])/double(eps_1_tag)));

			RT::Point<int,int> pointout(vout, 0);

			/* Erase vout from the samples cells */

			samples_col[firstCorOut].erase(std::remove(samples_col[firstCorOut].begin(), samples_col[firstCorOut].end(), pointout), samples_col[firstCorOut].end());
			samples_row[secondCorOut].erase(std::remove(samples_row[secondCorOut].begin(), samples_row[secondCorOut].end(), pointout), samples_row[secondCorOut].end());



			/* Add x to the samples cells */

			RT::Point<int,int> pointin(x, 0);
			samples_row[secondCor].push_back(pointin);
			samples_col[firstCor].push_back(pointin);

			if (row_trees[secondCor] != NULL) {
				row_trees[secondCor] = NULL;
			}

			if (col_trees[firstCor] != NULL) {
				col_trees[firstCor] = NULL;
			}

			if (row_trees[secondCorOut] != NULL) {
				row_trees[secondCorOut] = NULL;
			}

			if (col_trees[firstCorOut] != NULL) {
				col_trees[firstCorOut] = NULL;
			}
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


int NapaAlg::countQueryTrees(vector<int>& lower, vector<int>& upper)
{
	//TODO deal when lower_limits = 0;

	int firstCorLower = ceil(lower[0] / ceil(double (upper_limits[0])/double(eps_1_tag)));
	int secondCorLower = ceil(lower[1] / ceil(double(upper_limits[1])/double(eps_1_tag)));

	int firstCorUpper = floor(upper[0] / ceil(double(upper_limits[0])/double(eps_1_tag)));
	int secondCorUpper = floor(upper[1] / ceil(double(upper_limits[1])/double(eps_1_tag)));


	int result = rtree->countInSketchRange(f(firstCorLower + 1,secondCorLower+1), f(firstCorUpper,secondCorUpper));//TODO: think about papa bounds

	int gx1 = lower[0];
	int x1 = firstCorLower*ceil(double (upper_limits[0])/double(eps_1));


	int gx2 = upper[0];
	int x2 = firstCorUpper*ceil(double (upper_limits[0])/double(eps_1));


	int gy1 = lower[1];
	int y1 = secondCorLower*ceil(double (upper_limits[0])/double(eps_1));


	int gy2 = upper[1];
	int y2 = secondCorUpper*ceil(double (upper_limits[0])/double(eps_1));


	int surplus = 0;
	int surplus1, surplus2, surplus3, surplus4;

	if (gx1 < x1) {

		/* compute index */

		int index = firstCorLower;
		surplus1 = 0;

		if (samples_col[index].empty()) {
			surplus1 = 0;
		} else {
			if (col_trees[index] == NULL) {
				col_trees[index] = new RT::RangeTree<int,int>(samples_col[index]);
			}

			surplus1 +=  col_trees[index]->countInRange(f(gx1,lower[1]), f(x1,upper[1]));

			surplus1 = (surplus1/samples_col_num[index])*(stream_size);
		}
	}



	if (gy1 < y1) {


		/* compute index */

		int index = secondCorLower - 1;
		surplus2 = 0;

		if (samples_row[index].empty()) {
			surplus2 = 0;
		} else {
			if (row_trees[index] == NULL) {
				row_trees[index] = new RT::RangeTree<int,int>(samples_row[index]);
			}

			surplus2 +=  row_trees[index]->countInRange(f(lower[0],gy1), f(upper[0],y1));

			surplus2 = (surplus2/samples_row_num[index])*(stream_size);
		}
	}

	if (x2 < gx2) {

		/* compute index */

		int index = firstCorUpper + 1;
		surplus3 = 0;
		if (samples_col[index].empty()) {
			surplus3 = 0;
		} else {
			if (col_trees[index] == NULL) {
				col_trees[index] = new RT::RangeTree<int,int>(samples_col[index]);
			}

			surplus3 +=  col_trees[index]->countInRange(f(x2,lower[1]), f(gx2,upper[1]));

			surplus3 = (surplus3/samples_col_num[index])*(stream_size);
		}
	}


	if (y2 < gy2) {
		/* compute index */

		int index = secondCorUpper + 1;
		surplus4 = 0;
		if (samples_row[index].empty()) {
			surplus4 = 0;
		} else {
			if (row_trees[index] == NULL) {
				row_trees[index] = new RT::RangeTree<int,int>(samples_row[index]);
			}

			surplus4 +=  row_trees[index]->countInRange(f(lower[0],y2), f(upper[0], gy2));

			surplus4 = (surplus4/samples_row_num[index])*(stream_size);
		}
	}

	surplus = surplus1 + surplus2 + surplus3 + surplus4;

	return surplus + result;
}


int NapaAlg::countQueryNaive(vector<int>& lower, vector<int>& upper)
{
	//TODO deal when lower_limits = 0;

	int firstCorLower = ceil(lower[0] / ceil(double (upper_limits[0])/double(eps_1)));
	int secondCorLower = ceil(lower[1] / ceil(double(upper_limits[1])/double(eps_1)));

	int firstCorUpper = floor(upper[0] / ceil(double(upper_limits[0])/double(eps_1)));
	int secondCorUpper = floor(upper[1] / ceil(double(upper_limits[1])/double(eps_1)));


	int result = rtree->countInSketchRange(f(firstCorLower + 1,secondCorLower+1), f(firstCorUpper,secondCorUpper));//TODO: think about papa bounds

	int gx1 = lower[0];
	int x1 = firstCorLower*ceil(double (upper_limits[0])/double(eps_1));


	int gx2 = upper[0];
	int x2 = firstCorUpper*ceil(double (upper_limits[0])/double(eps_1));


	int gy1 = lower[1];
	int y1 = secondCorLower*ceil(double (upper_limits[0])/double(eps_1));


	int gy2 = upper[1];
	int y2 = secondCorUpper*ceil(double (upper_limits[0])/double(eps_1));


	int surplus = 0;
	int surplus1, surplus2, surplus3, surplus4;

	if (gx1 < x1) {

		/* compute index */

		int index = firstCorLower;
		surplus1 = 0;

		if (samples_col[index].empty()) {
			surplus1 = 0;
		} else {

			std::vector<RT::Point<int, int>> v = samples_col[index];
			for(auto it=std::begin(v); it!=std::end(v); ++it) {
				if (((*it).asVector())[0] <= x1 && ((*it).asVector())[0] >= gx1 && ((*it).asVector())[1] <= upper[1] && ((*it).asVector())[1] >= lower[1])
					++surplus1;
			}

			surplus1 = (surplus1/samples_col_num[index])*(stream_size);
		}
	}



	if (gy1 < y1) {


		/* compute index */

		int index = secondCorLower - 1;
		surplus2 = 0;
		if (samples_row[index].empty()) {
			surplus2 = 0;
		} else {

			std::vector<RT::Point<int, int>> v = samples_row[index];
			for(auto it=std::begin(v); it!=std::end(v); ++it) {
				if (((*it).asVector())[0] <= upper[0] && ((*it).asVector())[0] >= lower[0] && ((*it).asVector())[1] <= y1 && ((*it).asVector())[1] >= gy1)
					++surplus2;
			}

			surplus2 = (surplus2/samples_row_num[index])*(stream_size);
		}
	}

	if (x2 < gx2) {

		/* compute index */

		int index = firstCorUpper + 1;
		surplus3 = 0;
		if (samples_col[index].empty()) {
			surplus3 = 0;
		} else {

			std::vector<RT::Point<int, int>> v = samples_col[index];
			for(auto it=std::begin(v); it!=std::end(v); ++it) {
				if (((*it).asVector())[0] <= gx2 && ((*it).asVector())[0] >= x2 && ((*it).asVector())[1] <= upper[1] && ((*it).asVector())[1] >= lower[1])
					++surplus3;
			}

			surplus3 = (surplus3/samples_col_num[index])*(stream_size);
		}
	}


	if (y2 < gy2) {
		/* compute index */

		int index = secondCorUpper + 1;
		surplus4 = 0;
		if (samples_row[index].empty()) {
			surplus4 = 0;
		} else {

			std::vector<RT::Point<int, int>> v = samples_col[index];
			for(auto it=std::begin(v); it!=std::end(v); ++it) {
				if (((*it).asVector())[0] <= upper[0] && ((*it).asVector())[0] >= lower[0] && ((*it).asVector())[1] <= gy2 && ((*it).asVector())[1] >= y2)
					++surplus4;
			}

			surplus4 = (surplus4/samples_row_num[index])*(stream_size);
		}
	}

	surplus = surplus1 + surplus2 + surplus3 + surplus4;


	return surplus + result;
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

