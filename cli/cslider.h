#pragma once
#ifndef __CBUTTON
#include "citem.h"

class cslider : public citem
{
public:
	cslider(int value, int from, int to, std::string name, std::function<void()> func)
		: citem(name, func) {
		this->name = name;
		this->func = func;
		this->value = value;
	}
	~cslider() {}

	inline std::string display() override {
		std::string output = "[" + std::to_string(value) + "] " + name;
		return output;
	}

	inline void call() override {
		int temp; 
		std::cin >> temp;
		if (temp >= from && temp <= to) {
			value = temp;
			func();
		}
	}

private:
	int value; int from; int to;
	std::string name;
	std::function<void()> func;
};

#endif // !__CBUTTON


