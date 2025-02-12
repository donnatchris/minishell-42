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

For explanations on functions and concepts already used in previous projects, refer to the README files of my other projects:

https://github.com/donnatchris/philosophers

https://github.com/donnatchris/minitalk

However, at the end of the DOCUMENTATION section, you will find a SHORT REMINDER section with a summary of all the previously covered functions.

---

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
- `prompt`: A string displayed as a prompt before reading user input.
- **Returns**: Nothing.

The `readline()` function is part of the GNU Readline library and is used to read a line of text from standard input with advanced editing features.
It waits for user input until they press Enter.
The function provides line-editing capabilities, allowing navigation and modification of text using keyboard shortcuts such as arrow keys, Ctrl+A, and Ctrl+E.
It also supports command history, enabling users to recall previous inputs.

It returns a dynamically allocated string containing the entered line, without the newline character.
This string must be freed using `free()` after use.

For the Minishell project, `readline()` is essential for handling interactive user input.
It can be integrated with command history using `add_history()`.
Proper memory management is required, ensuring that allocated strings are freed when no longer needed.
Additionally, signal handling (`SIGINT`, `SIGQUIT`) should be implemented to maintain a clean and responsive shell experience.

---

### rl_clear_history()

> #include <readline/readline.h>
>
> #include <readline/history.h>
```c
void rl_clear_history(void);
```
- The function takes no arguments and returns nothing.

The `rl_clear_history()` function is part of the GNU Readline library and is used to completely erase the stored command history from memory.
It removes all entries from the history list, making subsequent calls to `history_list()` return an empty list.

This function is useful when you want to reset the history without closing the program, such as after a certain number of commands or when requested by the user.
However, `rl_clear_history()` does not free the memory allocated for previous entries; it only clears the list.
For better memory management, `clear_history()` can be used as an alias for `rl_clear_history()`.

---

### rl_on_new_line()

> #include <readline/readline.h>
>
> #include <readline/history.h>
```c
void (*rl_on_new_line_hook)(void);
```
- The function takes no arguments and returns nothing.

The `rl_on_new_line()` function is used in the context of the GNU Readline library, which allows for interactive user input management in command-line programs.
This function is typically used to define custom behavior when the user presses the Enter key in a Readline-based interface.
It is a hook function that gets automatically called by Readline when the Enter key is pressed.

To use it, you define a custom function and assign it to the `rl_on_new_line hook`.
This allows you to execute specific actions, such as validating input, logging, or modifying the input before it is processed by the program.
Readline also supports other hooks for different events, and you can disable rl_on_new_line by setting it to `NULL`.
Overall, `rl_on_new_line()` is a powerful tool for customizing Readline behavior when the user presses Enter, enabling richer and more controlled command-line interactions.

#### How to use it

You can assign your own custom function to the `rl_on_new_line hook` using this syntax:
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
- `text`: The new string to replace the current line,
- `cursor_pos`: is the position of the cursor in the new line (if cursor_pos is negative, the cursor is placed at the end of the line).

The `rl_replace_line()` function is part of the GNU Readline library, which allows for interactive user input management in command-line programs.
This function replaces the content of the current input line with a new string.
It is useful for dynamically modifying what the user sees in the command line, such as correcting input, displaying suggestions, or updating the display based on user actions.

The function updates the display of the input line in the user interface.
Common use cases include automatic correction, dynamic suggestions, updating the interface based on user actions, and replacing text.
For example, you can use it to correct a misspelled command, display autocomplete suggestions, or insert a file path.
An example of its usage is `rl_replace_line("New input line", -1)`, which replaces the current input line with "New input line" and places the cursor at the end.
The cursor position is important as it determines where the user can continue typing
Overall, `rl_replace_line()` is a powerful function for dynamically manipulating the input line in a Readline-based interface,
enabling richer and more interactive command-line experiences.

---

### rl_redisplay()

> #include <readline/readline.h>
>
> #include <readline/history.h>
```c
void rl_redisplay(void);
```
- The function takes no arguments and returns nothing.

The `rl_redisplay()` function is part of the GNU Readline library, which allows for interactive user input management in command-line programs.
This function refreshes or redisplays the current input line in the user interface.
It is useful when you want to update the display of the input line after making adjustments or modifications, without having to replace the entire content of the line.

When `rl_redisplay()` is called, it refreshes the display of the current input line based on its current state,
including the cursor position, content, and any other display parameters.
This function is often used after modifications to the input line, such as insertions, deletions, or cursor movements, to ensure the display is up to date.
Common use cases include updating the display after modifying the input line content, refreshing the display after programmatically moving the cursor,
and correcting the display if it becomes incorrect or misaligned.
For example, you can use `rl_redisplay()` after inserting or deleting text, moving the cursor with functions like `rl_beginning_of_line` or `rl_end_of_line`,
or adjusting the display due to changes in the terminal size.
An example of its usage is `rl_redisplay()`, which refreshes the input line display after modifying its content.
The function ensures that the display is consistent and up to date, which is important for maintaining a smooth and responsive user experience.
Overall, `rl_redisplay()` is an essential function for keeping the input line display consistent and up to date in a Readline-based interface, enabling more fluid and interactive command-line interactions.

---

### add_history()

> #include <readline/readline.h>
>
> #include <readline/history.h>
```c
void add_history(const char *string);
```
- `string`: A character string representing the command or user input to be added to the history.
- **Returns**: Nothing.

The `add_history()` function is part of the GNU Readline library, which allows for managing command history in command-line interfaces.
This function is used to add a user input entry to the command history, enabling the system to keep track of previous commands for later reuse.

When `add_history()` is called, the string passed as an argument is added to the command history.
The history is an ordered list of previous commands, and each new entry is appended to the end of this list.
The history can be accessed and reused by the user using navigation keys (such as the up/down arrows) or specific Readline commands.
Common use cases include preserving user-entered commands for later reuse, customizing the history by adding specific commands or suggestions,
and dynamically adding commands to the history based on user actions.
For example, you can use `add_history()` to save commands entered by the user, add frequently used commands to the history for quick access,
or dynamically generate and add commands to the history in an interactive interface.

An example of its usage is `add_history(input)`, which adds the user input to the command history after it is entered.
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
- `pathname`: A string representing the path of the file or directory whose permissions you want to check.
- `mode`: An integer specifying the type of permission to check.
- **Returns**: `0` if access is permitted, `-1` on failure, and the global variable errno is set to indicate the error.

The `access()` function in C is used to check the access permissions of a file or directory.
It allows you to determine if the current user has permission to read, write, or execute a specific file.
This function is particularly useful for performing security checks or ensuring that file operations are permitted before executing them.

Possible values for mode are:
- `F_OK`: Checks if the file exists.
- `R_OK`: Checks if the file is readable.
- `W_OK`: Checks if the file is writable.
- `X_OK`: Checks if the file is executable.

These values can be combined using the bitwise OR operator | to check multiple permissions at once (e.g., `R_OK` | `W_OK`).

The access function checks permissions based on the effective privileges of the current user.
This means it considers the file's permission bits and the system's security rules (such as ACLs or capabilities).
If the function fails, the global variable errno can be used to get information about the error.
For example, errno might be set to `EACCES` if access is denied or `ENOENT` if the file does not exist.

The access function is often used for security checks, such as ensuring a file is readable before opening it or that a directory is executable before accessing it.
In summary, access is an essential function for checking file or directory access permissions in C, ensuring that file operations are authorized and secure.

---

### wait3()

> #include <sys/types.h>
>
> #include <sys/wait.h>
>
> #include <sys/resource.h>

```c
pid_t wait3(int *status, int options, struct rusage *rusage);
```
- `status`: A pointer to an integer where the termination status of the child process will be stored.
- `options`: An integer representing behavior options (e.g., `WNOHANG` or `WUNTRACED`).
- `rusage`: A pointer to a `struct rusage` where resource usage information will be stored.
- **Returns**: The PID of the terminated child process, or `-1` on error.


The `wait3()` function extends the functionality of `wait()` by allowing you to retrieve detailed information about the resource usage of a terminated child process. Here’s what `wait3()` offers:

#### **1. Retrieving Termination Status**
Like `wait()`, `wait3()` allows you to retrieve the termination status of the child process via a pointer to an integer (`int *status`). This includes information such as:
- The exit code of the child process.
- Whether the process was terminated by a signal, and if so, which signal.

#### **2. Retrieving Resource Usage Information**
Unlike `wait()`, `wait3()` also allows you to retrieve detailed information about the resource usage of the terminated child process. This includes metrics such as:
- CPU time used (user and system time).
- Memory usage.
- Number of page faults.
- Number of disk reads/writes.
- Other resource-related statistics.

This information is stored in a `struct rusage`, which you pass as the third argument to `wait3()`.

#### **3. Additional Options**
Like `waitpid()`, `wait3()` accepts a second argument (`int options`) to control its behavior. For example:
- `WNOHANG`: If this option is specified, `wait3()` returns immediately if no child process has exited.
- `WUNTRACED`: If this option is specified, `wait3()` also reports stopped child processes (e.g., those stopped by `SIGSTOP`).

---

### wait4()

> #include <sys/types.h>
>
> #include <sys/wait.h>
>
> #include <sys/resource.h>
```c
pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);
```
- `pid`: The PID of the child process to wait for. You can use special values like:
  - `-1`: Wait for any child process.
  - `0`: Wait for any child process in the same process group as the caller.
  - A positive value: Wait for a specific child process with the given PID.
- `status`: A pointer to an integer where the termination status of the child process will be stored.
- `options`: An integer representing behavior options (e.g., `WNOHANG` or `WUNTRACED`).
- `rusage`: A pointer to a `struct rusage` where resource usage information will be stored.
- **Returns**: The PID of the terminated child process, `0` if no child matches the criteria, or `-1` on error.
The `wait4()` function is essentially the same as `wait3()`, but it adds one additional feature: **the ability to wait for a specific child process**. This is done by passing the PID of the child process as the first argument.

#### **Summary of `wait3()` vs `wait4()`**
- `wait3()`: Waits for **any child process** to terminate and retrieves its termination status and resource usage information.
- `wait4()`: Allows you to wait for a **specific child process** (or any child process, depending on the `pid` argument) and retrieves the same information as `wait3()`.

Both functions are more powerful than `wait()` because they provide detailed resource usage information and support additional options like `WNOHANG` and `WUNTRACED`.

---

### exit()

> #include <stdlib.h>
```c
void exit(int status);
```
- `status`: An integer representing the exit status code of the program. By convention:
  - `0` or `EXIT_SUCCESS`: Indicates that the program terminated successfully.
  - Any other value (or `EXIT_FAILURE`): Indicates an error or failure.
- **Returns**: Nothing.

The `exit()` function in C is used to terminate a program normally.
It allows you to specify an **exit status code** that can be retrieved by the parent process or used to indicate the success or failure of the program.
Here is a detailed explanation of how it works, especially in the context of child and parent processes, and what it cleans up.

#### **How `exit()` Works**
1. **Program Termination**:
   - The `exit()` function immediately terminates the currently running program.
   - It never returns to the caller.

2. **Resource Cleanup**:
   - Before terminating the program, `exit()` performs cleanup of dynamically allocated resources:
     - **Output Buffers**: The stdout and stderr buffers are flushed, ensuring that all pending data is written.
     - **Functions Registered with `atexit()`**: These functions are called in reverse order of their registration, allowing custom cleanup tasks to be executed.
     - **Temporary Files**: Files created with `tmpfile()` or `tmpnam()` are closed and deleted.

3. **Exit Status Code**:
   - The exit status code (`status`) is returned to the operating system and can be retrieved by the parent process using functions like `wait()`, `waitpid()`, or `wait3()`.

#### **Behavior in Child and Parent Processes**
- **Child Process**:
  - When a child process calls `exit()`, it terminates immediately and returns the exit status code to the parent process.
  - The parent process can retrieve this code using functions like `wait()`, `waitpid()`, or `wait3()`.
  - For example, if a child process executes `exit(42)`, the parent can check this code to determine if the child terminated successfully or with an error.

- **Parent Process**:
  - If the parent process calls `exit()`, it terminates as well, along with any child processes that are not running in the background (background child processes may continue running).
  - The parent's exit status code can be used by the operating system or another process to determine the success or failure of the program.

#### **What `exit()` Cleans Up**
1. **Output Buffers**:
   - The stdout and stderr buffers are flushed, ensuring that all pending data is written before the program terminates.

2. **Functions Registered with `atexit()`**:
   - Functions registered with `atexit()` are called in reverse order of their registration, allowing custom cleanup tasks to be executed.

3. **Temporary Files**:
   - Temporary files created with `tmpfile()` or `tmpnam()` are closed and deleted.

4. **System Resources**:
   - Dynamically allocated resources (e.g., memory) are released by the operating system.

5. **Closure of all file descriptors opened by the process.**


#### **Difference Between `exit()` and `_exit()`**
- **`exit()`**:
  - Performs a full cleanup (flushes buffers, calls `atexit()` functions, etc.).
  - Used for normal program termination.

- **`_exit()`**:
  - Terminates the program immediately without performing cleanup (buffers are not flushed, `atexit()` functions are not called).
  - Used in cases where cleanup is not necessary or desired (e.g., in a child process after a critical error).

#### **Summary**
- `exit()` terminates a program normally and performs cleanup of resources (flushes buffers, calls `atexit()` functions, etc.).
- In the context of child and parent processes, the exit status code returned by `exit()` can be retrieved by the parent to determine the success or failure of the child.
- `exit()` is ideal for clean and controlled termination, while `_exit()` is used for immediate termination without cleanup.

---

### `getcwd()`

> #include <unistd.h>

```c
char *getcwd(char *buf, size_t size);
```
- `buf`: A pointer to a character array where the current working directory will be stored.  
- `size`: The size of the buffer in bytes.  
- **Returns**: A pointer to the buffer containing the current working directory on success, or `NULL` on error.  

The `getcwd()` function retrieves the absolute pathname of the current working directory and stores it in the provided buffer.
It is commonly used in shell implementations and file management applications to determine the current directory of a process.  

#### Retrieving the Current Working Directory  
`getcwd()` fills the buffer with the full path of the current working directory.
The `size` parameter must be large enough to hold the pathname, including the null terminator.
If the buffer is too small, the function returns `NULL` and sets `errno` to `ERANGE`.  

#### Handling Dynamic Memory Allocation  
If `buf` is set to `NULL`, `getcwd()` dynamically allocates memory to store the pathname.
The returned pointer must be freed using `free()` to avoid memory leaks.  

#### Error Handling  
`getcwd()` may fail in several cases:  
- If the buffer size is too small, it returns `NULL` with `errno` set to `ERANGE`.  
- If the current directory is inaccessible due to permission issues, it returns `NULL` with `errno` set to `EACCES`.  
- If the process does not have sufficient memory to allocate a buffer dynamically, it returns `NULL` with `errno` set to `ENOMEM`.  

Using `getcwd()` properly ensures that a program can reliably determine and use the current working directory while handling potential errors gracefully.










# SHORT REMINDERS

## open(), close() and read()

> #include <fcntl.h>

### **1. `open()`**
```c
int open(const char *pathname, int flags);
```
- `pathname`: The path to the file you want to open.
- `flags`: Specifies the mode, such as `O_RDONLY` (read-only), `O_WRONLY` (write-only), or `O_RDWR` (read/write).
- **Returns**: A file descriptor (an integer) if successful, or `-1` on error.
- **Purpose**: Opens a file and returns a file descriptor for reading, writing, or both.


### **2. `read()`**
```c
ssize_t read(int fd, void *buf, size_t count);
```
- `fd`: The file descriptor of the file to read from.
- `buf`: A pointer to a buffer where the data will be stored.
- `count`: The maximum number of bytes to read.
- **Returns**: The number of bytes read, `0` if the end of the file is reached, or `-1` on error.
- **Purpose**: Reads data from a file descriptor into a buffer.


### **3. `close()`**
```c
int close(int fd);
```
- `fd`: The file descriptor of the file to close.
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


### **2. `wait()`**
```c
pid_t wait(int *status);
```
- `status`: A pointer to an integer where the status of the terminated child process will be stored (can be NULL if you don't want to staore anything).
- **Returns**: The PID of the terminated child process, or `-1` on error.
- **Purpose**: Suspends the calling process until one of its child processes terminates. It also retrieves the termination status of the child process.


### **3. `waitpid()`**
```c
pid_t waitpid(pid_t pid, int *status, int options);
```
- `pid`: The PID of the child process to wait for, or special values like `-1` (wait for any child) or `0` (wait for any child in the same process group).
- `status`: A pointer to an integer where the status of the terminated child process will be stored.
- `options`: Options to control the behavior of the function, such as `WNOHANG` (return immediately if no child has exited) or `WUNTRACED` (report stopped children).
- **Returns**: The PID of the terminated child process, `0` if no child matches the criteria, or `-1` on error.
- **Purpose**: Provides more control over waiting for child processes, allowing you to wait for specific children or modify the behavior of the wait.


### **4. `wait3()`**
```c
pid_t wait3(int *status, int options, struct rusage *rusage);
```
- `status`: A pointer to an integer where the status of the terminated child process will be stored.
- `options`: Options to control the behavior of the function, similar to `waitpid()`.
- `rusage`: A pointer to a `struct rusage` where resource usage information about the terminated child process will be stored.
- **Returns**: The PID of the terminated child process, or `-1` on error.
- **Purpose**: Waits for a child process to terminate and retrieves both the termination status and resource usage information.


### **5. `wait4()`**
```c
pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);
```
- `pid`: The PID of the child process to wait for, or special values like `-1` (wait for any child) or `0` (wait for any child in the same process group).
- `status`: A pointer to an integer where the status of the terminated child process will be stored.
- `options`: Options to control the behavior of the function, similar to `waitpid()`.
- `rusage`: A pointer to a `struct rusage` where resource usage information about the terminated child process will be stored.
- **Returns**: The PID of the terminated child process, `0` if no child matches the criteria, or `-1` on error.
- **Purpose**: Combines the functionality of `waitpid()` and `wait3()`, allowing you to wait for a specific child process and retrieve both its termination status and resource usage information.

---

## kill(), signal(), sigaction(), sigemptyset(), and sigaddset()

> #include <signal.h>
>
> #include <sys/types.h>
>
> #include <sys/wait.h>

### **1. `kill()`**
```c
int kill(pid_t pid, int sig);
```
- `pid`: The process ID (PID) of the process to send the signal to, or a special value like `0` (current process group) or `-1` (all processes).
- `sig`: The signal to send (e.g., `SIGTERM` to terminate, `SIGINT` to interrupt, or `SIGKILL` to forcefully kill).
- **Returns**: `0` on success, or `-1` on error.
- **Purpose**: Sends a signal to a process or group of processes.


### **2. `signal()`**
```c
void (*signal(int sig, void (*handler)(int)))(int);
```
- `sig`: The signal to handle (e.g., `SIGINT`, `SIGTERM`, etc.).
- `handler`: A pointer to a function that will handle the signal, or `SIG_IGN` to ignore the signal, or `SIG_DFL` to use the default behavior.
- **Returns**: A pointer to the previous signal handler, or `SIG_ERR` on error.
- **Purpose**: Sets a custom handler for a specific signal.


### **3. `sigaction()`**
```c
int sigaction(int sig, const struct sigaction *act, struct sigaction *oldact);
```
- `sig`**: The signal to handle (e.g., `SIGINT`, `SIGTERM`, etc.).
- `act`: A pointer to a `struct sigaction` that defines the new signal handler and behavior.
- `oldact`: A pointer to a `struct sigaction` where the previous signal handler and behavior will be stored.
- **Returns**: `0` on success, or `-1` on error.
- **Purpose**: Provides a more flexible way to set signal handlers and behaviors.


### **4. `sigemptyset()`**
```c
int sigemptyset(sigset_t *set);
```
- `set`: A pointer to a `sigset_t` (signal set) that will be initialized to exclude all signals.
- **Returns**: `0` on success, or `-1` on error.
- **Purpose**: Initializes a signal set to exclude all signals.


### **5. `sigaddset()`**
```c
int sigaddset(sigset_t *set, int sig);
```
- `set`: A pointer to a `sigset_t` (signal set) to which the signal will be added.
- `sig`: The signal to add to the set (e.g., `SIGINT`, `SIGTERM`, etc.).
- **Returns**: `0` on success, or `-1` on error.
- **Purpose**: Adds a specific signal to a signal set.
