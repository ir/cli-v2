#pragma once
#ifndef __CMENU
#include <string>
#include <vector>
#include <functional>
#include "citem.h"
#include "cbutton.h"
#include "ccheckbox.h"
#include "cslider.h"
/*
* store all items
* handle display, selection, and input
*/

struct cmenu_item {
	int id;
	citem* item;
};

class cmenu
{
public:
	cmenu() {}
	~cmenu() {}
	inline virtual void add_item(citem* item) { 
		count++;
		item_list.push_back({ count, item });
	}

	inline virtual void display_items()
	{
		for (const auto& i : item_list)
		{
			i.item->display();
		}
	}
	
private:
	int count = 0;
	std::vector<cmenu_item> item_list;
};



#endif // !__CMENU


