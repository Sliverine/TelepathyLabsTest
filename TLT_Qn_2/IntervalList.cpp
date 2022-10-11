
#include "IntervalList.h"

#include <algorithm>

IntervalList::IntervalList() {
}

IntervalList::~IntervalList() {
}

bool IntervalList::insert(std::pair<int, int> pt) {
	if (hasExactInterval(pt))
		return false;
	
	intervals[pt.first].insert(pt.second);
	return true;
}

std::tuple<bool, int, int> IntervalList::search(std::pair<int, int> pt) {
	bool found = false;
	int x = pt.first, y = pt.second;
	int targetX = -INT_MAX, targetY = INT_MAX;
	if (intervals.empty())
		return std::make_tuple(found, targetX, targetY);

	auto itx = intervals.lower_bound(x);
	if (itx != intervals.end()) {
		if (itx != intervals.begin() && itx->first > x)
			--itx;
		targetX = itx->first;
	}
	else {
		targetX = (*intervals.rbegin()).first;
	}

	auto ity = intervals[targetX].upper_bound(y);
	if (ity != intervals[targetX].end()) {
		if (ity != intervals[targetX].begin()) {
			--ity;
			if (*ity < y)
				++ity;
		}
		targetY = (*ity);
	}
	else {
		targetY = *(intervals[targetX].rbegin());
	}

	found = (targetX <= x) && (targetY >= y);
	return std::make_tuple(found, targetX, targetY);
}

std::vector<std::pair<int, int>> IntervalList::printAll() {
	std::vector<std::pair<int, int>> res;

	for (auto& x : intervals) {
		for (auto& y : x.second) {
			res.emplace_back(std::make_pair(x.first, y));
		}
	}

	return res;
}

bool IntervalList::hasExactInterval(std::pair<int, int> pt) {
	if (intervals.find(pt.first) != intervals.end()) {
		if (intervals[pt.first].find(pt.second) != intervals[pt.first].end())
			return true;
	}
	return false;
}