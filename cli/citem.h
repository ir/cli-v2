#pragma once
#ifndef __CBUTTON
#include <iostream>
#include <string>
#include <vector>
#include <functional>

class citem
{
public:
	citem(std::string name, std::function<void()> func) {
		this->name = name;
		this->func = func;
	}
	~citem() {}
	
	// display
	inline virtual std::string display() { return ""; }
	// calling
	inline virtual void call() {}

private:
	std::string name;
	std::function<void()> func;
};

#endif // !__CBUTTON



