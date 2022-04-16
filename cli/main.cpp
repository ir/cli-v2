// cli.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include "CLI.h"

void p(std::optional<std::string> s)
{
	std::cout << s.value() << std::endl;
}

int main()
{
	std::unique_ptr<CLI> pCli = std::make_unique<CLI>();

	pCli->add_dir("root");
	pCli->add_dir("menu", "root");
	pCli->add_dir("cmd", "menu");
	

	pCli->add_command(pCli->get_dir("menu"), Command("command", p,1,"command text"));

	while (1)
	{
		pCli->run();
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
