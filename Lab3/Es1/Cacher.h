#pragma once
#include "stdafx.h"
using namespace std;
class Cacher
{
public:
	Cacher() {};
	~Cacher() {};

	void CacheNewSolution(vector<int>, result);
	bool LookUpForSolution(vector<int> sequenza, result& result);

private:
	map<vector<int>, result> cache;
};