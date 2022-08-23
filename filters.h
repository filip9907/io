#pragma once
#include <string>
#include "filter.h"
#include "filter_median.h"
#include "filter_min.h"
#include "filter_max.h"
#include "filter_add.h"
class filters
{
protected:
	string name;
public:
	void setName(string nazwa)
	{
		name = nazwa;
	}
};
class filter : public filters {};
class filter_add : public filters {};
class filter_min : public filters {};
class filter_median : public filters {};
class filter_max : public filters {};