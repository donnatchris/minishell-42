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

Compile with the library:

	gcc minishell.c -o minishell -lreadline

Compile with the library and -lncurses if needed

	gcc minishell.c -o minishell -lreadline -lncurses

Install libreadline if needed (linux)

	sudo apt-get install libreadline-dev

Install libreadline if needed (Macos)

 	brew install readline

---

### readline()

> #include <readline/readline.h>
>
> #include <readline/history.h>
```c
char *readline(const char *prompt);
```
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

---

### rl_clear_history()

> #include <readline/readline.h>
>
> #include <readline/history.h>
```c
void rl_clear_history(void);
```
The rl_clear_history() function is part of the GNU Readline library and is used to completely erase the stored command history from memory.
It removes all entries from the history list, making subsequent calls to history_list() return an empty list.

The function takes no arguments and returns nothing.

This function is useful when you want to reset the history without closing the program, such as after a certain number of commands or when requested by the user.
However, rl_clear_history() does not free the memory allocated for previous entries; it only clears the list.
For better memory management, clear_history() can be used as an alias for rl_clear_history().

---

### rl_on_new_line()

> #include <readline/readline.h>
>
> #include <readline/history.h>
```c
void (*rl_on_new_line_hook)(void);
```
The rl_on_new_line function is used in the context of the GNU Readline library, which allows for interactive user input management in command-line programs.
This function is typically used to define custom behavior when the user presses the Enter key in a Readline-based interface.
It is a hook function that gets automatically called by Readline when the Enter key is pressed.

The function takes no arguments and returns nothing.

To use it, you define a custom function and assign it to the rl_on_new_line hook.
This allows you to execute specific actions, such as validating input, logging, or modifying the input before it is processed by the program.
Readline also supports other hooks for different events, and you can disable rl_on_new_line by setting it to NULL.
Overall, rl_on_new_line is a powerful tool for customizing Readline behavior when the user presses Enter, enabling richer and more controlled command-line interactions.

#### How to use it

You can assign your own custom function to the rl_on_new_line hook using this syntax:
```c
rl_on_new_line_hook = my_own_on_newline_function;
```
This allows you to define custom behavior that will be executed every time the user presses the Enter key.
Make sure your custom function follows the expected prototype:

	void my_own_on_newline_function(void);

This ensures that the function takes no arguments and returns nothing, as required by Readline.

---

### rl_replace_line()

> #include <readline/readline.h>
>
> #include <readline/history.h>
```c
void rl_replace_line(const char *text, int cursor_pos);
```
The rl_replace_line function is part of the GNU Readline library, which allows for interactive user input management in command-line programs.
This function replaces the content of the current input line with a new string.
It is useful for dynamically modifying what the user sees in the command line, such as correcting input, displaying suggestions, or updating the display based on user actions.

The function prototype is void rl_replace_line(const char *text, int cursor_pos),
where text is the new string to replace the current line,
and cursor_pos is the position of the cursor in the new line.
If cursor_pos is negative, the cursor is placed at the end of the line.

The function updates the display of the input line in the user interface.
Common use cases include automatic correction, dynamic suggestions, updating the interface based on user actions, and replacing text.
For example, you can use it to correct a misspelled command, display autocomplete suggestions, or insert a file path.
An example of its usage is rl_replace_line("New input line", -1), which replaces the current input line with "New input line" and places the cursor at the end.
The cursor position is important as it determines where the user can continue typing
Overall, rl_replace_line is a powerful function for dynamically manipulating the input line in a Readline-based interface,
enabling richer and more interactive command-line experiences.

---

### rl_redisplay()

> #include <readline/readline.h>
>
> #include <readline/history.h>
```c
void rl_redisplay(void);
```
The rl_redisplay function is part of the GNU Readline library, which allows for interactive user input management in command-line programs.
This function refreshes or redisplays the current input line in the user interface.
It is useful when you want to update the display of the input line after making adjustments or modifications, without having to replace the entire content of the line.

The function takes no arguments and returns nothing.

When rl_redisplay is called, it refreshes the display of the current input line based on its current state, including the cursor position, content, and any other display parameters.
This function is often used after modifications to the input line, such as insertions, deletions, or cursor movements, to ensure the display is up to date.
Common use cases include updating the display after modifying the input line content, refreshing the display after programmatically moving the cursor,
and correcting the display if it becomes incorrect or misaligned.
For example, you can use rl_redisplay after inserting or deleting text, moving the cursor with functions like rl_beginning_of_line or rl_end_of_line,
or adjusting the display due to changes in the terminal size.
An example of its usage is rl_redisplay(), which refreshes the input line display after modifying its content.
The function ensures that the display is consistent and up to date, which is important for maintaining a smooth and responsive user experience.
Overall, rl_redisplay is an essential function for keeping the input line display consistent and up to date in a Readline-based interface, enabling more fluid and interactive command-line interactions.

---

### add_history()

> #include <readline/readline.h>
>
> #include <readline/history.h>
```c
void add_history(const char *string);
```
The add_history function is part of the GNU Readline library, which allows for managing command history in command-line interfaces.
This function is used to add a user input entry to the command history, enabling the system to keep track of previous commands for later reuse.

The function prototype is void add_history(const char *string), where string is a character string representing the command or user input to be added to the history.

When add_history is called, the string passed as an argument is added to the command history.
The history is an ordered list of previous commands, and each new entry is appended to the end of this list.
The history can be accessed and reused by the user using navigation keys (such as the up/down arrows) or specific Readline commands.
Common use cases include preserving user-entered commands for later reuse, customizing the history by adding specific commands or suggestions,
and dynamically adding commands to the history based on user actions.
For example, you can use add_history to save commands entered by the user, add frequently used commands to the history for quick access,
or dynamically generate and add commands to the history in an interactive interface.
To use add_history, you need to include the Readline headers: #include <readline/readline.h> and #include <readline/history.h>.
An example of its usage is add_history(input), which adds the user input to the command history after it is entered.
The function ensures that commands are saved and can be reused, which is important for providing a smooth and efficient user experience.
Additionally, Readline can be configured to save the history to a file, allowing it to persist across sessions.
Users can navigate the command history using navigation keys or specific Readline commands.
Overall, add_history is an essential function for managing command history in a Readline-based interface, enabling more fluid and efficient command-line interactions.

---

### access()

> #include <unistd.h>
```c
int access(const char *pathname, int mode);
```

The access function in C is used to check the access permissions of a file or directory.
It allows you to determine if the current user has permission to read, write, or execute a specific file.
This function is particularly useful for performing security checks or ensuring that file operations are permitted before executing them.

The function prototype is int access(const char *pathname, int mode);
- The pathname parameter is a string representing the path of the file or directory whose permissions you want to check.
- The mode parameter is an integer specifying the type of permission to check.

Possible values for mode are:
- F_OK: Checks if the file exists.
- R_OK: Checks if the file is readable.
- W_OK: Checks if the file is writable.
- X_OK: Checks if the file is executable.

These values can be combined using the bitwise OR operator | to check multiple permissions at once (e.g., R_OK | W_OK).

The function returns 0 if access is permitted.
It returns -1 on failure, and the global variable errno is set to indicate the error.

The access function checks permissions based on the effective privileges of the current user.
This means it considers the file's permission bits and the system's security rules (such as ACLs or capabilities).
If the function fails, the global variable errno can be used to get information about the error.
For example, errno might be set to EACCES if access is denied or ENOENT if the file does not exist.

The access function is often used for security checks, such as ensuring a file is readable before opening it or that a directory is executable before accessing it.
In summary, access is an essential function for checking file or directory access permissions in C, ensuring that file operations are authorized and secure.

---







# SHORT REMINDERS

## open(), close() and read()

> #include <fcntl.h>

### **1. `open()`**
```c
int open(const char *pathname, int flags);
```
- **`pathname`**: The path to the file you want to open.
- **`flags`**: Specifies the mode, such as `O_RDONLY` (read-only), `O_WRONLY` (write-only), or `O_RDWR` (read/write).
- **Returns**: A file descriptor (an integer) if successful, or `-1` on error.
- **Purpose**: Opens a file and returns a file descriptor for reading, writing, or both.


### **2. `read()`**
```c
ssize_t read(int fd, void *buf, size_t count);
```
- **`fd`**: The file descriptor of the file to read from.
- **`buf`**: A pointer to a buffer where the data will be stored.
- **`count`**: The maximum number of bytes to read.
- **Returns**: The number of bytes read, `0` if the end of the file is reached, or `-1` on error.
- **Purpose**: Reads data from a file descriptor into a buffer.


### **3. `close()`**
```c
int close(int fd);
```
- **`fd`**: The file descriptor of the file to close.
- **Returns**: `0` on success, or `-1` on error.
- **Purpose**: Closes a file descriptor, freeing up system resources and ensuring the file is properly saved and closed.

---

## fork(), wait(), waitpid(), wait2(), wait3() and wait4()

> #include <unistd.h>
> 
> #include <sys/types.h>
> 
 >#include <sys/wait.h>

### **1. `fork()`**
```c
pid_t fork(void);
```
- **Parameters**: None.
- **Returns**: Returns `0` to the child process, and the PID of the child process to the parent process. Returns `-1` on error.
- **Purpose**: Creates a new process by duplicating the current process. The new process is called the child process, and the original process is called the parent process.

---

### **2. `wait()`**
```c
pid_t wait(int *status);
```
- **`status`**: A pointer to an integer where the status of the terminated child process will be stored.
- **Returns**: The PID of the terminated child process, or `-1` on error.
- **Purpose**: Suspends the calling process until one of its child processes terminates. It also retrieves the termination status of the child process.


### **3. `waitpid()`**
```c
pid_t waitpid(pid_t pid, int *status, int options);
```
- **`pid`**: The PID of the child process to wait for, or special values like `-1` (wait for any child) or `0` (wait for any child in the same process group).
- **`status`**: A pointer to an integer where the status of the terminated child process will be stored.
- **`options`**: Options to control the behavior of the function, such as `WNOHANG` (return immediately if no child has exited) or `WUNTRACED` (report stopped children).
- **Returns**: The PID of the terminated child process, `0` if no child matches the criteria, or `-1` on error.
- **Purpose**: Provides more control over waiting for child processes, allowing you to wait for specific children or modify the behavior of the wait.


### **4. `wait3()`**
```c
pid_t wait3(int *status, int options, struct rusage *rusage);
```
- **`status`**: A pointer to an integer where the status of the terminated child process will be stored.
- **`options`**: Options to control the behavior of the function, similar to `waitpid()`.
- **`rusage`**: A pointer to a `struct rusage` where resource usage information about the terminated child process will be stored.
- **Returns**: The PID of the terminated child process, or `-1` on error.
- **Purpose**: Waits for a child process to terminate and retrieves both the termination status and resource usage information.


### **5. `wait4()`**
```c
pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);
```
- **`pid`**: The PID of the child process to wait for, or special values like `-1` (wait for any child) or `0` (wait for any child in the same process group).
- **`status`**: A pointer to an integer where the status of the terminated child process will be stored.
- **`options`**: Options to control the behavior of the function, similar to `waitpid()`.
- **`rusage`**: A pointer to a `struct rusage` where resource usage information about the terminated child process will be stored.
- **Returns**: The PID of the terminated child process, `0` if no child matches the criteria, or `-1` on error.
- **Purpose**: Combines the functionality of `waitpid()` and `wait3()`, allowing you to wait for a specific child process and retrieve both its termination status and resource usage information.

