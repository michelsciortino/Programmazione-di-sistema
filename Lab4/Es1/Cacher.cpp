#include "stdafx.h"
#include "Cacher.h"
using namespace std;
template<typename Problem, typename Solution>
bool cache_t::get(const Problem& p, Solution& s) {
	lock_guard<mutex> lock(cacheMutex);
	auto it = cache.find(p);
	if (it != cache.end())
	{
		s = it->second;
		return true;
	}
	return false;
}
template<typename Problem, typename Solution>

void cache_t::put(const Problem& p, const Solution& s)
{
	lock_guard<mutex> lock(cacheMutex);
	cache.insert(pair<Problem, Solution>(p, s));
}