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
auto f1 = [](int a) { std::vector<int> b = {a}; return b;};


int main(int argc, char * argv[]) {

	int *upper_limits = new int[3];
	int *lower_limits = new int[3];
	int epsilon_1 = 4;
	int numItems = 344000;
	//int numItems = 10;
	//int numItems = 10;

	int d = 2;
//	ifstream myfile ("dfacebookdataset2d.txt");
//	ifstream myfile ("testemp.txt"); //TODO: testing
//	ifstream myfile ("dataset.txt");
//	ifstream myfile ("dataset1.txt");
	ifstream myfile ("cmdataset.txt");

	double emp_error = 0;
	int limit = 256;



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
			if (strcmp(argv[i], "-r") == 0)
			{
			limit = atoi(argv[i+1]);
			i++;
			}
		}
	}

	upper_limits[0] = limit;
	upper_limits[1] = limit;
	upper_limits[2] = limit;

	lower_limits[0] = 0;
	lower_limits[1] = 0;
	lower_limits[2] = 0;


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
	int datalen = numItems;
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
/*
	begint = clock();
	ftime(&begintb);

	for (int i = 0; i < numItems; i++) {
		alg->update(vdata[i % datalen]);
	}

	endt = clock();
	ftime(&endtb);
	time = ((double)(endt-begint))/CLK_PER_SEC;
	//printf( "UpdateNapa %d pairs took %lfs %d 1/epsilon %d range %d dimensions \n", numItems, time, epsilon_1, limit, d);
*/

	/*
		Query Test NAPA using trees of samples*/
/*
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
	printf( "QueryNapa %d pairs took %lfs %d 1/epsilon %d range %d dimensions\n", numItems, time, epsilon_1, limit, d);
	//printf( "QueryNapaTrees %d pairs took %lfs %d 1/epsilon\n", numItems, time, epsilon_1);
*/

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

/*
		Update Test in 1-d

	begint = clock();
	ftime(&begintb);

	for (int i = 0; i < numItems; i++) {
		alg->update1(vdata[i % datalen]);
	}

	endt = clock();
	ftime(&endtb);
	time = ((double)(endt-begint))/CLK_PER_SEC;
	//printf("UpdateNapa1 %d pairs took %lfs %d 1/epsilon\n", numItems, time, epsilon_1);
*/
	/*
		Query Test NAPA using scan of samples
	*/
/*	begint = clock();
	ftime(&begintb);


	for (int i = 0; i < numItems; i++) {
		vector<int> lower;
		vector<int> upper;

		int lower1 = rand() % (upper_limits[0] - 1);
		int upper1 =  lower1 + 1 + rand() % (upper_limits[0] - lower1 - 1);

		lower.push_back(lower1);
		upper.push_back(upper1);

		alg->countQueryTrees1(lower, upper);
	}

	endt = clock();
	ftime(&endtb);
	time = ((double)(endt-begint))/CLK_PER_SEC;
	printf( "countQueryTrees1 %d pairs took %lfs %d 1/epsilon\n", numItems, time, epsilon_1);
*/
/*======================  TEST that shows scan samples is more effective than building trees #########*/

/*
	double time_2;


	for (int i = 0; i < numItems/2; i++) {
		alg->update(vdata[i % datalen]);
	}


	begint = clock();
	ftime(&begintb);


	for (int i = 0; i < numItems/2; i++) {
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



	for (int i = numItems/2; i < numItems; i++) {
		alg->update(vdata[i % datalen]);
	}


	begint = clock();
	ftime(&begintb);


	for (int i = numItems/2; i < numItems; i++) {
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
	time_2 = ((double)(endt-begint))/CLK_PER_SEC;




	printf( "QueryNapaNaive %d pairs took %lfs %d 1/epsilon\n", numItems, (time+time_2), epsilon_1);*/

/*================================= TEST ERROR MEMORY ======================================*/

	double estimated, curr_error = 0;
	double exact = 0;
    std::vector<RT::Point<int,int>> points = {};
	int xfactor = ceil(double(upper_limits[0])/double(epsilon_1));
	int yfactor = ceil(double(upper_limits[1])/double(epsilon_1));


	for (int i = 0; i < numItems; i++) {
		alg->update(vdata[i % datalen]);
	}


    for (int i = 0; i < numItems; i++)  {
		vector<int> lower;
		vector<int> upper;
		exact = 0;



		int lower1 = rand() % (upper_limits[0] - 1);
		int upper1 =  lower1 + 1 + rand() % (upper_limits[0] - lower1 - 1);


		int lower2 = rand() % (upper_limits[1] - 1);
		int upper2 =  lower2 + rand() % (upper_limits[1] - lower2 - 1);


		lower.push_back(lower1);
		lower.push_back(lower2);
		upper.push_back(upper1);
		upper.push_back(upper2);


		estimated = alg->countQueryNaive(lower, upper);


		for (int j =0; j <datalen; j++) {
			if (inRange(lower, upper, vdata[j]) && (vdata[j][0]==vdata[i][0]) && (vdata[j][1]==vdata[i][1]))
				++exact;
		}


		curr_error = exact - estimated;

/*
		if (curr_error != 0) {
			cout << "curr_error " << curr_error << " estimated: " << estimated << " exact: " << exact << endl;
			cout << "query estimated and exact: x: " << lower[0] <<" ,"<< upper[0] <<" y:  "<< lower[1] <<" ,"<< upper[1] << endl;
			estimated = alg->countQueryNaive(lower, upper);
		}
		// TODO: testing For debug
*/
		curr_error = pow(curr_error, 2);
		emp_error += curr_error;
	}

	emp_error = sqrt((emp_error/numItems));

	printf( "./napa %d pairs emp error: %lf [%d eps_1]\n", numItems, emp_error, epsilon_1);



/*================================= TEST ERROR MEMORY FREQUENCY ===================================

	double estimated, curr_error = 0;
	double exact = 0;
    std::vector<RT::Point<int,int>> points = {};
	int xfactor = ceil(double(upper_limits[0])/double(epsilon_1));
	int yfactor = ceil(double(upper_limits[1])/double(epsilon_1));


	for (int i = 0; i < numItems; i++) {
		alg->update(vdata[i % datalen]);
	}


    for (int i = 0; i < numItems; i++)  {
		vector<int> lower;
		vector<int> upper;
		exact = 0;



		int lower1 = rand() % (upper_limits[0] - 1);
		int upper1 =  lower1 + 1 + rand() % (upper_limits[0] - lower1 - 1);


		int lower2 = rand() % (upper_limits[1] - 1);
		int upper2 =  lower2 + rand() % (upper_limits[1] - lower2 - 1);


		lower.push_back(lower1);
		lower.push_back(lower2);
		upper.push_back(upper1);
		upper.push_back(upper2);


		estimated = alg->rtree->frequencyInSketchRange(f(x1, y1), f(x1 + diff1, y1 + diff2), vdata[i % datalen]);


		for (int j =0; j <datalen; j++) {
			if (inRange(lower, upper, vdata[j]) && (vdata[j][0]==vdata[i][0]) && (vdata[j][1]==vdata[i][1]))
				++exact;
		}


		curr_error = exact - estimated;
*/
/*
		if (curr_error != 0) {
			cout << "curr_error " << curr_error << " estimated: " << estimated << " exact: " << exact << endl;
			cout << "query estimated and exact: x: " << lower[0] <<" ,"<< upper[0] <<" y:  "<< lower[1] <<" ,"<< upper[1] << endl;
			estimated = alg->countQueryNaive(lower, upper);
		}*/
		// TODO: testing For debug
/*
		curr_error = pow(curr_error, 2);
		emp_error += curr_error;
	}

	emp_error = sqrt((emp_error/numItems));

	printf( "./napa %d pairs emp error: %lf [%d eps_1]\n", numItems, emp_error, epsilon_1);*/


	return 0;
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
	eps_1_tag = epsilon_1 * (2*dimensions+1);
	sample_size = (eps_1_tag)*(eps_1_tag) * log2(ceil(1/delta));

	if (dimensions == 2) {
		int epsilon_1_tag = epsilon_1 * (2*dimensions+1);
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
	} else if (dimensions == 1) {

		int epsilon_1_tag = epsilon_1 * (2*dimensions+1);
		/* Prepare the points to build the range tree */
		std::vector<RT::Point<int,int>> points = {};

		for (int i = 1; i <= epsilon_1_tag; i++) {
			RT::Point<int, int> a(f1(i), 0);
			points.push_back(a);
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
		samples_col[firstCor].push_back(a);
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

			/* Optimize this in update test!! */
//			samples_col[firstCorOut].erase(std::remove(samples_col[firstCorOut].begin(), samples_col[firstCorOut].end(), pointout), samples_col[firstCorOut].end());
//			samples_row[secondCorOut].erase(std::remove(samples_row[secondCorOut].begin(), samples_row[secondCorOut].end(), pointout), samples_row[secondCorOut].end());



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

void NapaAlg::update1(vector<int> x)
{
	int firstCor = ceil (double(x[0] + 1) / double(ceil(double(upper_limits[0])/double(eps_1_tag))));

	rtree->updateSketch(new RT::Point<int,int> (f1(firstCor), 0));


	/*
	###############################################################

		Add the item to the sample if the relevant row and col
	
	###############################################################
	*/

	++stream_size;
	++samples_col_num[firstCor];
	if(stream_size <= sample_size) {
		RT::Point<int, int> a(x, 0);
		samples_col[firstCor].push_back(a);
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

			RT::Point<int,int> pointout(vout, 0);

			/* Erase vout from the samples cells */

			/* Optimize this in update test!! */
			//samples_col[firstCorOut].erase(std::remove(samples_col[firstCorOut].begin(), samples_col[firstCorOut].end(), pointout), samples_col[firstCorOut].end());



			/* Add x to the samples cells */

			RT::Point<int,int> pointin(x, 0);
			samples_col[firstCor].push_back(pointin);

			if (col_trees[firstCor] != NULL) {
				col_trees[firstCor] = NULL;
			}

			if (col_trees[firstCorOut] != NULL) {
				col_trees[firstCorOut] = NULL;
			}
		}
	}
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

/*
int NapaAlg::countQueryTreesFrequency(vector<int>& lower, vector<int>& upper, std::vector<int> x)
{
	//TODO deal when lower_limits = 0;

	int firstCorLower = ceil(lower[0] / ceil(double (upper_limits[0])/double(eps_1_tag)));
	int secondCorLower = ceil(lower[1] / ceil(double(upper_limits[1])/double(eps_1_tag)));

	int firstCorUpper = floor(upper[0] / ceil(double(upper_limits[0])/double(eps_1_tag)));
	int secondCorUpper = floor(upper[1] / ceil(double(upper_limits[1])/double(eps_1_tag)));


	int result = rtree->frequencyInSketchRange(f(firstCorLower + 1,secondCorLower+1), f(firstCorUpper,secondCorUpper), x);//TODO: think about papa bounds

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

		// compute index

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


		// compute index 

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

		// compute index

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
		// compute index 

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
*/

int NapaAlg::countQueryNaive(vector<int>& lower, vector<int>& upper)
{
	//TODO deal when lower_limits = 0;

	int firstCorLower = ceil(lower[0] / ceil(double (upper_limits[0])/double(eps_1_tag)));
	int secondCorLower = ceil(lower[1] / ceil(double(upper_limits[1])/double(eps_1_tag)));

	int firstCorUpper = floor(upper[0] / ceil(double(upper_limits[0])/double(eps_1_tag)));
	int secondCorUpper = floor(upper[1] / ceil(double(upper_limits[1])/double(eps_1_tag)));


	int result = rtree->countInSketchRange(f(firstCorLower + 1,secondCorLower+1), f(firstCorUpper,secondCorUpper));//TODO: think about papa bounds

	int gx1 = lower[0];
	int x1 = firstCorLower*ceil(double (upper_limits[0])/double(eps_1_tag));


	int gx2 = upper[0];
	int x2 = firstCorUpper*ceil(double (upper_limits[0])/double(eps_1_tag));


	int gy1 = lower[1];
	int y1 = secondCorLower*ceil(double (upper_limits[0])/double(eps_1_tag));


	int gy2 = upper[1];
	int y2 = secondCorUpper*ceil(double (upper_limits[0])/double(eps_1_tag));


	int surplus = 0;
	int surplus1 = 0;
	int surplus2 = 0;
	int surplus3 = 0;
	int surplus4 = 0;

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

		int index = secondCorLower;
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




int NapaAlg::countQueryNaive1(vector<int>& lower, vector<int>& upper)
{
	//TODO deal when lower_limits = 0;

	int firstCorLower = ceil(lower[0] / ceil(double (upper_limits[0])/double(eps_1_tag)));

	int firstCorUpper = floor(upper[0] / ceil(double(upper_limits[0])/double(eps_1_tag)));


	int result = rtree->countInSketchRange(f1(firstCorLower + 1), f1(firstCorUpper));//TODO: think about papa bounds

	int gx1 = lower[0];
	int x1 = firstCorLower*ceil(double (upper_limits[0])/double(eps_1_tag));

	int gx2 = upper[0];
	int x2 = firstCorUpper*ceil(double (upper_limits[0])/double(eps_1_tag));

	int surplus = 0;
	int surplus1 = 0;
	int surplus2 = 0;
	int surplus3 = 0;
	int surplus4 = 0;

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


	surplus = surplus1 + surplus3;


	return surplus + result;
}



int NapaAlg::countQueryTrees1(vector<int>& lower, vector<int>& upper)
{
	//TODO deal when lower_limits = 0;

	int firstCorLower = ceil(lower[0] / ceil(double (upper_limits[0])/double(eps_1_tag)));
	int firstCorUpper = floor(upper[0] / ceil(double(upper_limits[0])/double(eps_1_tag)));

	int result = rtree->countInSketchRange(f1(firstCorLower + 1), f1(firstCorUpper));//TODO: think about papa bounds

	int gx1 = lower[0];
	int x1 = firstCorLower*ceil(double (upper_limits[0])/double(eps_1));

	int gx2 = upper[0];
	int x2 = firstCorUpper*ceil(double (upper_limits[0])/double(eps_1));


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

			surplus1 +=  col_trees[index]->countInRange(f1(gx1), f1(x1));

			surplus1 = (surplus1/samples_col_num[index])*(stream_size);
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

			surplus3 +=  col_trees[index]->countInRange(f1(x2), f1(gx2));

			surplus3 = (surplus3/samples_col_num[index])*(stream_size);
		}
	}

	surplus = surplus1 + surplus3;

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

