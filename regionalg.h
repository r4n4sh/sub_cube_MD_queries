#ifndef REGIONALG_h
#define REGIONALG_h


#include <vector>

using namespace std;


class RegionAlg {

private:
	int d; //dimensions
	int* upper_limits;
	int* lower_limits;
	int eps_1; //1\epsilon
public:

	RegionAlg(int dimensions, int epsilon_1, int* gupperlimits, int* glowerlimits);
	void update(vector<int> x);
	int query(vector<int> x, vector<int>& lower, vector<int>& upper);
	std::vector<int> fromCorToBlock(vector<int> cor);
};


#endif