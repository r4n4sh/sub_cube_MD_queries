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

//#define SKETCH 1



auto f = [](int a, int b) { std::vector<int> c = {a, b}; return c;};
auto g = [](bool a, bool b) { std::vector<bool> c = {a, b}; return c;};
auto f3 = [](int a, int b, int c) { std::vector<int> d = {a, b, c}; return d;};
auto f1 = [](int a) { std::vector<int> b = {a}; return b;};


int main(int argc, char * argv[]) {

	int *upper_limits = new int[3];
	int *lower_limits = new int[3];
	int epsilon_1 = 4;
	int numItems = 344000;
	//int numItems = 200000; //TODO testing
	int d = 2;
	//ifstream myfile ("dfacebookdataset2d.txt");
	//ifstream myfile ("dataset.txt"); //TODO: testing
	//ifstream myfile ("testemp.txt"); //TODO: testing
	//ifstream myfile ("dataset3.txt"); //TODO: testing
	//ifstream myfile ("datasetzip.txt");
	//ifstream myfile ("dataset1.txt"); //TODO: testing
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

	upper_limits[0] = limit;
	upper_limits[1] = limit;
	upper_limits[2] = limit;

	lower_limits[0] = 0;
	lower_limits[1] = 0;
	lower_limits[2] = 0;


	clock_t begint, endt;
	struct timeb begintb, endtb;
	double time;
	string line;
	int datalen = numItems; //TODO testing

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



	begint = clock();
	ftime(&begintb);

	for (int i = 0; i < numItems; i++) {
		alg->update(vdata[i % datalen]);
	}

	endt = clock();
	ftime(&endtb);
	time = ((double)(endt-begint))/CLK_PER_SEC;
	//printf( "UpdatePAPA %d pairs took %lfs %d 1/epsilon %d range %d dimensions \n", numItems, time, epsilon_1, upper_limits[0] ,d);
*/

/*
		Query Test*/
/*
	begint = clock();
	ftime(&begintb);

	for (int i = 0; i < numItems; i++) {
		int x1 = 1 + rand() % (epsilon_1 - 2);
		int diff1 = 1+ rand() % (epsilon_1 - x1);
		int y1 = 1 + rand() % (epsilon_1 - 2);
		int diff2 = 1 + rand() % (epsilon_1 - y1);


		alg->rtree->countInSketchRange(f(x1, y1), f(x1 + diff1, y1 + diff2));
	}

	endt = clock();
	ftime(&endtb);
	time = ((double)(endt-begint))/CLK_PER_SEC;
	printf( "QueryPAPA %d pairs took %lfs %d 1/epsilon %d range %d dimensions\n", numItems, time, epsilon_1, upper_limits[0] ,d);
  */


	/*
		Query Test - small rectangles 
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
	printf( "QuerySmall %d pairs took %lfs %d 1/epsilon\n", numItems, time, epsilon_1);*/


	/*
		Query Test - BIG rectangles 
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
	printf( "QueryBig %d pairs took %lfs %d 1/epsilon\n", numItems, time, epsilon_1);*/



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
	//printf( "Update3 %d pairs took %lfs %d 1/epsilon\n", numItems, time, epsilon_1);*/


	/*
		Query Test in 3d

	begint = clock();
	ftime(&begintb);

	for (int i = 0; i < numItems; i++) {
		int x1 = 1 + rand() % (epsilon_1 - 2);
		int diff1 = 1 + rand() % (epsilon_1 - x1);
		int y1 = 1 + rand() % (epsilon_1 - 2);
		int diff2 = 1 + rand() % (epsilon_1 - y1);
		int z1 = 1 + rand() % (epsilon_1 - 2);
		int diff3 = 1 + rand() % (epsilon_1 - z1);

		alg->rtree->countInSketchRange(f3(x1, y1, z1), f3(x1 + diff1, y1 + diff2, z1+diff3));
	}

	endt = clock();
	ftime(&endtb);
	time = ((double)(endt-begint))/CLK_PER_SEC;
	printf( "Query3 %d pairs took %lfs %d 1/epsilon\n", numItems, time, epsilon_1);*/
  




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
	//printf("Update1 %d pairs took %lfs %d 1/epsilon\n", numItems, time, epsilon_1);
*/


	/*
		Query Test in 1d 

	begint = clock();
	ftime(&begintb);

	for (int i = 0; i < numItems; i++) {
		int x1 = 1 + rand() % (epsilon_1 - 2);
		int diff1 = 1 + rand() % (epsilon_1 - x1);

		alg->rtree->countInSketchRange(f1(x1), f1(x1 + diff1));
	}

	endt = clock();
	ftime(&endtb);
	time = ((double)(endt-begint))/CLK_PER_SEC;
	printf( "Query1 %d pairs took %lfs %d 1/epsilon\n", numItems, time, epsilon_1);
*/
/*====================== TEST ERROR MEMORY COUNTING===============================*/
/*====================== Change relevant nodes in the code========================*/


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
//    cout << "printing exact tree" << endl;

//	exacttree.print(); //TODO:testing

	for (int i = 0; i < numItems; i++) {
		alg->update(vdata[i % datalen]);
	}


//	cout << "printing counters after update********" << endl; //TODO testing
//	alg->rtree->printwCounter(); //TODO testing

    for (int i = 0; i < numItems; i++)  {
		int x1 = 1 + rand() % (epsilon_1 - 2);
		int diff1 = 1+ rand() % (epsilon_1 - x1);
		int y1 = 1 + rand() % (epsilon_1 - 2);
		int diff2 = 1 + rand() % (epsilon_1 - y1);


		estimated = alg->rtree->countInSketchRange(f(x1, y1), f(x1 + diff1, y1 + diff2));
		exact = exacttree.countInRange(f(xfactor*(x1-1), yfactor*(y1-1)), f(xfactor*(x1 + diff1) - 1, yfactor*(y1 + diff2) - 1));

		curr_error = exact - estimated;

		if (curr_error != 0) {
			cout << "curr_error " << curr_error << " estimated: " << estimated << " exact: " << exact << endl;
			cout << "query estimated: " << x1 <<" ,"<< x1+diff1 <<" ,"<< y1 <<" ,"<< y1+diff2 << endl;
			cout << "query exact: " << xfactor*(x1-1) <<" ,"<< xfactor*(x1 + diff1) - 1 <<" ,"<< yfactor*(y1-1) <<" ,"<< yfactor*(y1 + diff2) - 1<< endl;

			estimated = alg->rtree->countInSketchRange(f(x1, y1), f(x1 + diff1, y1 + diff2));
		}
		// TODO: testing For debug


		curr_error = pow(curr_error, 2);
		emp_error += curr_error;
	}

	emp_error = sqrt((emp_error/numItems));

	printf( "./papa %d pairs emp error: %lf [%d eps_1]\n", numItems, emp_error, epsilon_1);


/*====================== TEST ERROR MEMORY FRQUENCY===============================

	double estimated, curr_error = 0;
	double exact = 0;
    std::vector<RT::Point<int,int>> points = {};
	int xfactor = ceil(double(upper_limits[0])/double(epsilon_1));
	int yfactor = ceil(double(upper_limits[1])/double(epsilon_1));
	int success = 0;

	for (int i = 0; i < numItems; i++) {
		alg->updatefrequency(vdata[i % datalen]);
	}

    for (int i = 0; i < numItems; i++)  {
		int x1 = 1 + rand() % (epsilon_1 - 2);
		int diff1 = 1+ rand() % (epsilon_1 - x1);
		int y1 = 1 + rand() % (epsilon_1 - 2);
		int diff2 = 1 + rand() % (epsilon_1 - y1);
		exact = 0;


		for (int j =0; j <datalen; j++) {
			if (inRange(f(xfactor*(x1-1), yfactor*(y1-1)), f(xfactor*(x1 + diff1) - 1, yfactor*(y1 + diff2) - 1), vdata[j]) && (vdata[j][0]==vdata[i][0]) && (vdata[j][1]==vdata[i][1]))
				++exact;
		}


		estimated = alg->rtree->frequencyInSketchRange(f(x1, y1), f(x1 + diff1, y1 + diff2), vdata[i % datalen]);

		curr_error = exact - estimated;
*/
/*
		if (curr_error != 0) {
			cout << "curr_error " << curr_error << " estimated: " << estimated << " exact: " << exact << " x: " << vdata[i][0] << " , " << vdata[i][1] <<endl;
			cout << "query estimated: " << x1 <<" ,"<< x1+diff1 <<" ,"<< y1 <<" ,"<< y1+diff2 << endl;
			cout << "query exact: " << xfactor*(x1-1) <<" ,"<< xfactor*(x1 + diff1) - 1 <<" ,"<< yfactor*(y1-1) <<" ,"<< yfactor*(y1 + diff2) - 1<< endl;

			estimated = alg->rtree->frequencyInSketchRange(f(x1, y1), f(x1 + diff1, y1 + diff2), vdata[i % datalen]);
		} else {
			++success;
		}
*/
		// TODO: testing For debug
/*
		curr_error = pow(curr_error, 2);
		emp_error += curr_error;
	}

	emp_error = sqrt((emp_error/numItems));

	printf( "./papa %d pairs frequency emp error: %lf [%d eps_1] %d success\n", numItems, emp_error, epsilon_1, success);*/
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
		//rtree->print(); //TODO: testing
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
		/* Prepare the points to build the range tree */
		std::vector<RT::Point<int,int>> points = {};

		for (int i = 1; i <= epsilon_1; i++) {
			RT::Point<int, int> a(f1(i), 0);
			points.push_back(a);
		}

		/* Construct the range tree */
		rtree = new RT::RangeTree<int,int>(points);
	}
}


void RegionAlg::update(vector<int> x)
{
	int firstCor = ceil (double(x[0] + 1) / double(ceil(double(upper_limits[0])/double(eps_1))));
	int secondCor = ceil (double(x[1] + 1) / double (ceil(double(upper_limits[1])/double(eps_1))));

	//TODO: this is only for 2d and the lowers start from 0!
	//std::cout << "update x: " << x[0] << " , " << x[1] << "   Cord: " << firstCor << " , " << secondCor << endl; //TODO: testing
	return rtree->updateSketch(new RT::Point<int,int> (f(firstCor,secondCor), 0));
}

#ifdef SKETCH
void RegionAlg::updatefrequency(vector<int> x)
{
	int firstCor = ceil (double(x[0] + 1) / double(ceil(double(upper_limits[0])/double(eps_1))));
	int secondCor = ceil (double(x[1] + 1) / double (ceil(double(upper_limits[1])/double(eps_1))));

	//TODO: this is only for 2d and the lowers start from 0!
	//std::cout << "update x: " << x[0] << " , " << x[1] << "   Cord: " << firstCor << " , " << secondCor << endl; //TODO: testing
	return rtree->updateSketchfrequency(new RT::Point<int,int> (f(firstCor,secondCor), 0), x);
}
#endif

void RegionAlg::update3(vector<int> x)
{
	int firstCor = ceil (double(x[0] + 1) / double(ceil(double(upper_limits[0])/double(eps_1))));
	int secondCor = ceil (double(x[1] + 1) / double (ceil(double(upper_limits[1])/double(eps_1))));
	int third = ceil (double(x[2] + 1) / double (ceil(double(upper_limits[2])/double(eps_1))));

	//TODO: this is only for 2d and the lowers start from 0!
	return rtree->updateSketch(new RT::Point<int,int> (f3(firstCor,secondCor,third), 0));
}


void RegionAlg::update1(vector<int> x)
{
	int firstCor = ceil (double(x[0] + 1) / double(ceil(double(upper_limits[0])/double(eps_1))));

	//std::cout << "update x: " << x[0] << " , " << x[1] << "   Cord: " << firstCor << " , " << secondCor << endl; //TODO: testing
	return rtree->updateSketch(new RT::Point<int,int> (f1(firstCor), 0));
}

int RegionAlg::countQuery(vector<int>& lower, vector<int>& upper)
{

	int firstCorLower = ceil(lower[0] / ceil(double (upper_limits[0])/double(eps_1)));
	int secondCorLower = ceil(lower[1] / ceil(double(upper_limits[1])/double(eps_1)));

	int firstCorUpper = floor(upper[0] / ceil(double(upper_limits[0])/double(eps_1)));
	int secondCorUpper = floor(upper[1] / ceil(double(upper_limits[1])/double(eps_1)));


	return rtree->countInSketchRange(f(firstCorLower + 1,secondCorLower+1), f(firstCorUpper,secondCorUpper));
}

#ifdef SKETCH

int RegionAlg::countQueryfrequency(vector<int>& lower, vector<int>& upper, std::vector<int> x)
{

	int firstCorLower = ceil(lower[0] / ceil(double (upper_limits[0])/double(eps_1)));
	int secondCorLower = ceil(lower[1] / ceil(double(upper_limits[1])/double(eps_1)));

	int firstCorUpper = floor(upper[0] / ceil(double(upper_limits[0])/double(eps_1)));
	int secondCorUpper = floor(upper[1] / ceil(double(upper_limits[1])/double(eps_1)));


	return rtree->frequencyInSketchRange(f(firstCorLower + 1,secondCorLower+1), f(firstCorUpper,secondCorUpper), x);
}
#endif

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


int RegionAlg::countQuery1(vector<int>& lower, vector<int>& upper)
{
	//TODO deal when lower_limits = 0;

	int firstCorLower = ceil (lower[0] / ceil(double (lower_limits[0])/double(eps_1)));

	int firstCorUpper = ceil (upper[0] / ceil(double(upper_limits[0])/double(eps_1)));

	return rtree->countInSketchRange(f1(firstCorLower), f1(firstCorUpper));
}
