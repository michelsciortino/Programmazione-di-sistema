#include "stdafx.h"
#include "Cacher.h"

using namespace std;

void Cacher::CacheNewSolution(vector<int> lista, result res)
{
	cache.insert(pair<vector<int>, result>(lista, res));
}

bool Cacher::LookUpForSolution(vector<int> sequenza, result& result)
{
	auto it = cache.find(sequenza);
	if (it != cache.end())
	{
		result = it->second;
		return true;
	}
	return false;
}
