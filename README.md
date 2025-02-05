# cli-v2
### A lightweight C++ command-line interface (CLI) library that allows for easy management of commands and directories within a terminal environment.

remake of https://github.com/ir/cli_shell trying to improve on what i learned (mainly OOP)

compile and type help for list of commands

<h5>
currently supports:
  
  input handling

  directories, subdirectories

  colored output

  custom commands (cmds.cpp)

  mouse handling

  custom cli menu/gui with tabs and options (see cmenu.h)



# CLI Usage
Example main function 
```cpp
int main()
{
      // Initialize new pCli
	std::unique_ptr<CLI> pCli = std::make_unique<CLI>();

      // Add root dir (houses everything on startup)
	pCli->add_dir("root");
      // Add sub dir to root
	pCli->add_dir("menu", "root");

      // pCli->add_command(Example_dir, Example_Command)
	pCli->add_command(pCli->get_dir("menu"), Command("print", CMDS::print, -1, "prints a message"));
	pCli->add_command(pCli->get_dir("menu"), Command("title", CMDS::console::change_title, -1, "changes the title of the console"));
	pCli->add_command(pCli->get_dir("root"), Command("inject", CMDS::dll::load, 0, "injects dll"));

      /*
      * void CMDS::cm::setup(std::optional<std::string> data)
      * {
	    *   std::shared_ptr<cmenu> pMenu = std::make_shared<cmenu>("menu");
      *
	    *   pMenu->setup();
      * }
      */
	pCli->add_command(pCli->get_dir("root"), Command("cmenu", CMDS::cm::setup, 0, "new menu"));


	while (!GetAsyncKeyState(VK_ESCAPE) && 1)
	{
		pCli->run();
	}

	return 0;
}

```

