#pragma once
#include <map>
#include <vector>

template<typename Problem, typename Solution>
class cache_t
{
public:
	bool get(const Problem& p, Solution& s); //ritorna false in caso di MISS
	void put(const Problem& p, const Solution& s);
private:
	std::map<Problem, Solution> cache;
	std::mutex cacheMutex;
};