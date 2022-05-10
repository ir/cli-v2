#pragma once
#ifndef __CMENU
#include <string>
#include <vector>
#include <functional>
#include "citem.h"

/*
* store all items
* handle display, selection, and input
*/

class cmenu
{
public:
	cmenu() {}
	~cmenu() {}

private:
	std::vector<citem*> item_list;
};



#endif // !__CMENU


