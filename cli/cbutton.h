#pragma once
#ifndef __CBUTTON
#include "citem.h"

class cbutton : public citem
{
public:
	cbutton(std::string name, std::function<void()> func)
		: citem(name, func) {
		this->name = name;
		this->func = func;
	}
	~cbutton() {}
	
	inline std::string display() override {
		std::string output = "[b] " + name;
		return output;
	}

	inline void call() override {
		func();
	}

private:
	std::string name;
	std::function<void()> func;
};

#endif // !__CBUTTON


