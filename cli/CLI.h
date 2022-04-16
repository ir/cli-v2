#pragma once
#ifndef __CLI
#define __CLI
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <optional>
#include <functional>
#include <algorithm>

// command struct - title, function, argsize (-1 infinite, 0 none, >0 normal), help text
struct Command {
	Command(std::string title, std::function<void(std::optional<std::string>)> func = 0, 
		int argsize = 0, std::string helptext = "Generic text") 
		: title(title), func(func), argsize(argsize), helptext(helptext) {}
	std::string title;
	std::function<void(std::optional<std::string>)> func;
	int argsize;
	std::string helptext;
};

// dir struct - title, parent, vector of commands
struct Dir
{
	// constructor
	Dir(std::string title, std::vector<Command> commands = {}, std::vector<Dir> sub_dirs = {}, Dir* parent = nullptr)
		: title(title), sub_dirs(sub_dirs), commands(commands), parent(parent) {}
	std::string title;
	std::vector<Dir> sub_dirs;
	std::vector<Command> commands;
	Dir* parent;
};

class CLI
{
public:
	CLI() { std::cout << "constructor called\n"; }
	~CLI() { std::cout << "destructor called\n"; }

	// vectors
	std::vector<std::shared_ptr<Dir>> dir_list;

	// funcs
	void add_dir(std::string title, std::string parent = "");
	void add_command(Dir* dir, Command command);
	
	// inline funcs
	inline void print_help();
	inline Dir* get_dir(std::string title);

	// input handler
	void run();
	
	// pub cmds

private:
	std::string cur_dir;

	// sort function for dir_list
	void sort_dir(std::vector<std::shared_ptr<Dir>>& dlist);
	// sort function for commands
	void sort_cmds(Dir& Dir);
	// return index of first dir with title
	int find_dir(std::string title);
	// split string by delimiter
	std::vector<std::string> split(std::string str, char delimiter);
	// priv cmds

};

void CLI::print_help()
{
	std::cout<< "list of all commands:\n";
	
	for (const auto& d : dir_list)
	{
		if (d->title == cur_dir)
		{
			for (size_t i = 0; i < d->commands.size(); i++)
			{
				std::string title = d->commands[i].title;
				
				if (title.length() > 16)
					title = title.substr(0, 16);

				while (title.length() < 16)
					title += " ";
				if (!std::isupper(title.at(0)))
					title.at(0) = std::toupper(title.at(0));

				std::cout << " " + title + d->commands[i].helptext;

				std::cout << std::endl;
			}
		}
	}

	std::cout << std::endl;
	
}

// returns dir of title arg if found
Dir* CLI::get_dir(std::string title)
{
	for (auto& dir : dir_list)
	{
		if (dir->title == title)
			return dir.get();
	}
	return nullptr;
}



#endif // !__CLI



