#pragma once

#include <vector>
#include <set>
#include <map>
using namespace std;

class IntervalList // assumption here is all intervals are unique, duplicate intervals are not supported
{
public:
	IntervalList();
	~IntervalList();
	bool insert(std::pair<int, int> pt);
	std::tuple<bool, int, int> search(std::pair<int, int> pt);
	std::vector<std::pair<int, int>> printAll();
	bool hasExactInterval(std::pair<int, int> pt);

private:
	std::map<int, std::set<int>> intervals;

};