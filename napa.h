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

class NapaAlg {

private:
	int d; //dimensions
	int* upper_limits;
	int* lower_limits;
	int eps_1; //1\epsilon
	int eps_1_tag;
	vector<RT::Point<int,int>> *samples_row;
	vector<RT::Point<int,int>> *samples_col;
	vector<vector<int>> samples_overall;

	int* samples_row_num;
	int* samples_col_num;

	RT::RangeTree<int,int>** row_trees;
	RT::RangeTree<int,int>** col_trees;
	int sample_size;
	int stream_size;
public:

	RT::RangeTree<int,int>* rtree;
	NapaAlg(int dimensions, int epsilon_1, int* gupperlimits, int* glowerlimits);
	void update(vector<int> x);
	int countQueryTrees(vector<int>& lower, vector<int>& upper);
	int countQueryNaive(vector<int>& lower, vector<int>& upper);
	void update3(vector<int> x);
	void update1(vector<int> x);
	int countQuery3(vector<int>& lower, vector<int>& upper);
	int countQueryNaive1(vector<int>& lower, vector<int>& upper);
	int countQueryTrees1(vector<int>& lower, vector<int>& upper);
	std::vector<int> fromCorToBlock(vector<int> cor);
	int countQueryTreesFrequency(vector<int>& lower, vector<int>& upper, std::vector<int> x);
};


#endif