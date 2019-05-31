#ifndef REGIONALG_h
#define REGIONALG_h


#include <vector>
#include "RangeTree.h"

using namespace std;
namespace RT = RangeTree;


class RegionAlg {

private:
	int d; //dimensions
	int* upper_limits;
	int* lower_limits;
	int eps_1; //1\epsilon
public:

	RT::RangeTree<int,int>* rtree;
	RegionAlg(int dimensions, int epsilon_1, int* gupperlimits, int* glowerlimits);
	void update(vector<int> x);
	int query(vector<int> x, vector<int>& lower, vector<int>& upper);
	std::vector<int> fromCorToBlock(vector<int> cor);
};


#endif