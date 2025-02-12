# PROJECT MINISHELL FOR 42
By chdonnat (Christophe Donnat from 42 Perpignan, France)

## AIM OF THE PROJECT:

### BONUS PART:


### ABOUT MY PROJECT:

## SOME COMMANDS YOU CAN USE:

compile the program and suppress the .o files:

	make && make clean

execute the program

	./minishell

## ARCHITECTURE:

- philo/ directory with files for the mandatory part
	- src/ directory for main files of the project
	- utils/ directory for secondary files
	- include/ directory for headers
- philo_bonus/ directory with files for the bonus part
	- src/ directory for main files of the project
	- utils/ directory for secondary files
	- include/ directory for headers
- test/ directory fot tests files
- Makefile (with rules: make bonus clean fclean re)
- readme.md for quick explanation and main commands of the project

## DOCUMENTATION:

### GNU readline library

The GNU Readline library is a powerful tool that provides line-editing and command history capabilities for interactive programs,
making it a fundamental component in many Unix-like command-line interfaces, including bash and gdb.
It allows users to edit input efficiently using keyboard shortcuts, recall previous commands, and navigate through text seamlessly.
To use readline() in a C program, the required headers are <readline/readline.h> and <readline/history.h>.
When compiling, the program must be linked with -lreadline, and in some cases, -lncurses is also needed.
The compilation command is: gcc minishell.c -o minishell -lreadline -lncurses.
If the library is not installed, it can be added using sudo apt-get install libreadline-dev on Debian-based systems or brew install readline on macOS.

compile with the library:

	gcc minishell.c -o minishell -lreadline

compile with the library and -lncurses if needed

	gcc minishell.c -o minishell -lreadline -lncurses

install libreadline if needed (linux)

	sudo apt-get install libreadline-dev

 install libreadlin if needed (Macos)

 	brew install readline


### readline()

> #include <readline/readline.h>
>
> #include <readline/history.h>  // Pour gérer l'historique des commandes

	char *readline(const char *prompt);


The readline() function is part of the GNU Readline library and is used to read a line of text from standard input with advanced editing features.
It waits for user input until they press Enter.
The function provides line-editing capabilities, allowing navigation and modification of text using keyboard shortcuts such as arrow keys, Ctrl+A, and Ctrl+E.
It also supports command history, enabling users to recall previous inputs.

The function prototype is char *readline(const char *prompt); where prompt is a string displayed as a prompt before reading user input.

It returns a dynamically allocated string containing the entered line, without the newline character.
This string must be freed using free() after use.

For the Minishell project, readline() is essential for handling interactive user input.
It can be integrated with command history using add_history().
Proper memory management is required, ensuring that allocated strings are freed when no longer needed.
Additionally, signal handling (SIGINT, SIGQUIT) should be implemented to maintain a clean and responsive shell experience.


