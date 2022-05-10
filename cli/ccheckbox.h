#pragma once
#ifndef __CCHECKBOX
#include "citem.h"

class ccheckbox : public citem
{
public:
	ccheckbox(std::string name, std::function<void()> func) 
		: citem(name, func) {
		this->name = name;
		this->func = func;
	}
	~ccheckbox() {}
	
	inline std::string display() override {
		std::string output = "[ ] " + name;
		if (*data)
			output[1] = (char)"X";
		else	  
			output[1] = (char)" ";
		return output;
	}
	
	inline void call() override {
		*data = !*data;
		func();
	}

private:
	bool* data = false;
	std::string name;
	std::function<void()> func;
};


#endif // !__CCHECKBOX


