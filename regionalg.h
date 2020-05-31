#ifndef REGIONALG_h
#define REGIONALG_h


#include <vector>
#include "RangeTree.h"

using namespace std;
namespace RT = RangeTree;


inline bool inRange(std::vector<int> lower, std::vector<int> upper, std::vector<int> x)
{
	if (x[0] >= lower[0] && x[0] <= upper[0] && x[1] >= lower[1] && x[1] <= upper[1])
		return true;
	return false;
}

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
	void updatefrequency(vector<int> x);
	int countQuery(vector<int>& lower, vector<int>& upper);
	int countQueryfrequency(vector<int>& lower, vector<int>& upper, std::vector<int> x);
	void update3(vector<int> x);
	void update1(vector<int> x);
	int countQuery3(vector<int>& lower, vector<int>& upper);
	int countQuery1(vector<int>& lower, vector<int>& upper);
	std::vector<int> fromCorToBlock(vector<int> cor);
};


#endif