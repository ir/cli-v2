#include "CLI.h"

void CLI::sort_dir(std::vector<std::shared_ptr<Dir>>& dlist)
{
	for (int i = 0; i < dlist.size(); i++)
	{
		int min = i;
		for (int j = i + 1; j < dlist.size(); j++)
			if (dlist[j]->title < dlist[min]->title)
				min = j;
		std::shared_ptr<Dir> temp = std::move(dlist[i]);
		dlist[i] = std::move(dlist[min]);
		dlist[min] = std::move(temp);
	}
}

void CLI::sort_cmds(Dir& dir)
{
	for (int i = 1; i < dir.commands.size(); i++)
	{
		int min = i;
		for (int j = i + 1; j < dir.commands.size(); j++)
			if (dir.commands[j].title < dir.commands[min].title)
				min = j;
		Command temp = std::move(dir.commands[i]);
		dir.commands[i] = std::move(dir.commands[min]);
		dir.commands[min] = std::move(temp);
	}
}

int CLI::find_dir(std::string title)
{
	for (int i = 0; i < dir_list.size(); i++)
		if (dir_list[i]->title == title)
			return i;
	return -1;
}


void CLI::add_dir(std::string title, std::string parent)
{
	// check if args are empty
	if (title.length() == 0)
	{
		std::cout << "[-] Error: Title cannot be empty" << std::endl;
		return;
	}
	Command help_cmd = { "help", std::bind(&CLI::print_help,this), 0,"help text"};
	std::shared_ptr<Dir> new_dir = std::make_shared<Dir>(title, std::vector<Command>({ help_cmd }));
	if (parent == "") // root menu
	{
		for (const auto& d : dir_list)
		{
			if (d->parent == nullptr)
			{
				std::cout << "[-] Error: Root menu already exists" << std::endl;
				return;
			}
		}
		new_dir->parent = nullptr;
		cur_dir = title;
	}
	else // submenu
	{
		// check if title already exists
		// gonna need to redo this and only check if title exists in current dir
		for (const auto& d : dir_list)
		{
			if (d->title == title)
			{
				std::cout << "[-] Error: Dir \"" << d->title << "\" already exists" << std::endl;
				return;
			}
		}
		new_dir->parent = get_dir(parent);

		// adding sub/parent dir commands
		for (auto& d : dir_list)
		{
			if (d->title == parent)
			{
				d->commands.push_back({ title, NULL, 0, "__Submenu of: " + d->title });
				std::cout << "added submenu\n";
				
			}
			else if (d->title == title)
			{
				d->commands.push_back({ parent, NULL, 0, "__Parentmenu of: " + d->title });

			}
		}
	}
	dir_list.push_back(new_dir);

	if (dir_list.size() > 1)
		sort_dir(dir_list);
}

void CLI::add_command(Dir* dir, Command command)
{
	if (dir->title.length() == 0)
		return;
	else if (command.title.length() > 16)
		command.title = command.title.substr(0, 16);
	dir->commands.push_back(command);
	if (dir->commands.size() > 1)
		sort_cmds(*dir);
}

// split string by delimiter
std::vector<std::string> CLI::split(std::string str, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(str);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

void CLI::run()
{
	// user input
	std::string input;
	std::cout << cur_dir << " $ ";
	std::getline(std::cin, input);
	// cleanup
	std::vector<std::string> current_input = split(input, ' ');
	if (current_input.size() == 0)
		return;
	
	// store first as command
	// then transform to lower
	std::string command = split(input, ' ').at(0);
	std::transform(command.begin(), command.end(), command.begin(), ::tolower);

	// getting correct dir
	int ind = find_dir(cur_dir);
	if (ind == -1)
		return;
	
	// argsize check
	size_t input_size = current_input.size() - 1;
	for (size_t i = 0; i < dir_list[ind]->commands.size(); i++)
	{
		if (input_size > (size_t)dir_list[ind]->commands[i].argsize &&
			dir_list[ind]->commands[i].title == command) {
			std::cout << "too many arguments\n\n";
			return;
		}
		else if (input_size < 1 && dir_list[ind]->commands[i].argsize > 0 &&
			dir_list[ind]->commands[i].title == command) {
			std::cout << "not enough arguments\n\n";
			return;
		}
	}
	
	std::vector<std::optional<std::string>> tvec{};
	std::optional<std::string> final_os;
	std::string temp_s;
	// store arguments into single string instead
	// of separating them into a vec
	if (input_size > 0)
	{
		for (size_t i = 1; i < current_input.size(); i++)
		{
			tvec.push_back(current_input[i]);
		}
		for (auto& d : tvec)
		{
			if (d.has_value())
				temp_s += d.value() + "  ";
			temp_s.resize(temp_s.size() - 1);
			final_os = temp_s;
		}
	}
	
	// getting the correct dir 
	std::shared_ptr<Dir> dir = nullptr;
	for (const auto& d : dir_list)
		if (d->title == cur_dir)
			dir = d;
	if (dir == nullptr)
		return;

	for (size_t i = 0; i < dir->commands.size(); i++)
	{
		if (command == dir->commands[i].title)
		{
			if (dir->commands[i].func != NULL)
			{
				dir->commands[i].func(final_os);
				return;
			}
		}
		else
		{
			for (auto& dd : dir_list)
			{
				if (dd->parent != nullptr && command == dd->parent->title)
				{
					std::cout << "[?] new dir: " << dd->parent->title << "\n\n";
					cur_dir = dd->parent->title;
					print_help();
					return;
				}
				else if ((command == dd->title && dd->parent->title == dir->title)
					&& dd->title != dir->title)
				{
					std::cout << "[?] new dir: " << command << "\n\n";
					cur_dir = command;
					print_help();
					return;
				}
			}
		}
	}
	std::cout << "command \"" << command << "\" not found\n\n";
}

