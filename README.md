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

## MINISHELL INPUT HANDLING LIST

### **1. Special Characters to Parse and Handle**  
These characters have a special meaning and must be properly **tokenized and interpreted**.  

#### **Command Separators**  
- `;` → Separates multiple commands executed sequentially.  

#### **Logical Operators**  
- `&&` → Executes the next command **only if** the previous one succeeds.  
- `||` → Executes the next command **only if** the previous one fails.  

#### **Redirections**  
- `>`  → Output redirection (overwrites the file).  
- `>>` → Output redirection (appends to the file).  
- `<`  → Input redirection (reads from a file).  
- `<<` → **Heredoc** (reads multiple lines until a delimiter).  

#### **Pipeline Operators**  
- `|` → Redirects the output of one command to the input of another (**pipe**).  

#### **Expansion and Substitution**  
- `$VAR` → Expands environment variables.  
- `$?` → Expands the exit status of the last command.  
- `` `cmd` `` or `$(cmd)` → Executes a command and replaces it with the output.  

#### **Quoting and Escaping**  
- `'...'` → Prevents any expansion.  
- `"..."` → Allows expansion (`$VAR` works inside).  
- `\` → Escapes a special character (`\n`, `\$`, etc.).  

#### **Grouping and Subshells**  
- `(cmds)` → Runs the commands in a **subshell**.  
- `{ cmds ; }` → Runs the commands in the **current shell**.  

#### **Metacharacters and Wildcards**  
- `*` → Matches any file (`ls *.c`).  
- `?` → Matches a single character (`file?.txt`).  
- `[abc]` → Matches one of the listed characters.  

#### **Others**  
- `&` → Runs a command in the background (**not required in Minishell**).  

### **2. Builtin Commands to Implement**  
Builtins are **internal commands** that must be implemented **without `execve()`**.  

- `echo` → Prints text (handle `-n` to remove the newline).  
- `cd` → Changes the current directory (`cd /path`, `cd ..`, `cd ~`).  
- `pwd` → Prints the current directory.  
- `export` → Sets an environment variable (`export VAR=value`).  
- `unset` → Unsets an environment variable (`unset VAR`).  
- `env` → Displays environment variables.  
- `exit` → Exits the shell (`exit`, `exit 42`).  

### **3. External Commands (Using `execve()`)**  
If the user types a command that **is not a builtin**, Minishell must:  
- **Search for the command in `$PATH`** (e.g., `/bin/ls`).
- **Execute the command via `execve()`**.
- **Handle errors (`command not found`, permissions, etc.).**  

Examples:  
- `ls -l`  
- `/bin/echo "Hello"`  
- `grep "text" file.txt`

### **4. Signal Handling (`Ctrl + Keys`)**  
Minishell must **catch certain signals** for proper behavior:  

- **`Ctrl + C` (`SIGINT`)** → Interrupts the current command (but not the shell).  
- **`Ctrl + D` (`EOF`)** → Exits the shell if entered on an empty line.  
- **`Ctrl + \` (`SIGQUIT`)** → Ignored except for child processes.  

### **5. Special Cases to Handle**  
- **Empty command** (`""`, multiple spaces) → Should do nothing.
- **Invalid commands** (`xyzxyz`) → Print `command not found`.
- **Non-executable files (`chmod -x file`)** → Print `Permission denied`.
- **Non-existing files in redirections (`< file` with `file` missing)**.
- **Heredoc (`<< limiter`)** → Read until the `limiter` is reached.
- **Variable expansion in arguments** (`echo $USER`).  

### **Summary**  
In **Minishell**, you must handle:  
✔ **All special characters** (redirections, pipes, expansions...).  
✔ **All builtin commands** (`cd`, `echo`, `exit`, etc.).  
✔ **All external commands** via `execve()`.  
✔ **Signals (`Ctrl + C`, `Ctrl + D`, `Ctrl + \`)**.  
✔ **Errors and edge cases** (invalid commands, permissions, etc.).

## ORDER OF PRIORITY FOR HANDLING USER INPUT IN MINISHELL
To ensure **correct execution** of commands, the **parsing and processing** of user input should follow a structured approach. Here’s the recommended order:

### **1. Lexical Analysis (Tokenization)**
- **First**, break the input string into **tokens**.
- Identify the **type** of each token (command, argument, operator, etc.).  

**Example:**  
> Input:  
> ```shell
> echo "Hello; world" > output.txt
> ```
> Tokens:  
> ```plaintext
> [echo] ["Hello; world"] [>] [output.txt]
> ```
At this stage, **do not** interpret anything—just split and classify.

### **2. Handle Quoting & Escaping**
- **Process quotes** (`'...'`, `"..."`) to group words correctly.
- **Process escape characters** (`\` to escape special symbols).  

**Example:**  
Input:  
```shell
echo "Hello; world"
```
Should be **one argument**, not split at `;`:  
```plaintext
[echo] ["Hello; world"]
```

### **3. Syntax Parsing & Syntax Error Detection**
- Check for **syntax errors** before executing anything.
- Detect **unmatched quotes, missing arguments**, or invalid syntax.  

**Example Errors to Catch Early:**  
- `echo "Hello` (missing closing quote)  
- `| ls` (pipe at the start without a command before)  
- `cat <` (missing file after `<`)  

If an error is found, **stop execution immediately**.

### **4. Handle Logical Operators (`&&`, `||`)**
- **Process** `&&` and `||` before anything else.
- These determine **which commands should run** based on success/failure.  

**Example:**  
```shell
mkdir test && cd test || echo "Failed"
```
- `mkdir test` **runs**  
- If it **succeeds**, `cd test` **executes**  
- If `cd test` **fails**, then `echo "Failed"` runs  

### **5. Handle Command Grouping (`( )`, `{ }`)**
- **If parentheses are used**, they create a **subshell**.
- **If `{ }` is used**, commands execute in the **current shell**.  

**Example:**  
```shell
(cd /tmp && ls) > output.txt
```
- **Subshell ensures `cd` does not affect the main shell**  
- **Entire group output is redirected**  

### **6. Handle Pipes (`|`)**
- **Split commands** based on `|` and set up **pipes**.
- Ensure **input/output redirection** between commands works.  

**Example:**  
```shell
cat file.txt | grep "hello" | wc -l
```
- `cat` sends output to `grep`  
- `grep` filters lines and sends output to `wc -l`  
- `wc -l` counts the lines  

At this stage, commands are **not yet executed**, just structured into a pipeline.

### **7. Handle Redirections (`>`, `>>`, `<`, `<<`)**
- **Before executing commands**, set up file descriptors.
- **Check for file errors** (non-existent file, permission issues).  

**Example:**  
```shell
echo "Hello" > output.txt
```
- Open `output.txt` **before** running `echo`.  

### **8. Handle Variable Expansion (`$VAR`, `$?`)**
- **Expand environment variables** **before execution**.
- **Replace** `$VAR` with its value.
- **Expand `$?`** to the **last exit status**.  

**Examples:**  
```shell
echo $HOME
```
If `$HOME=/Users/user`, then command becomes:  
```shell
echo /Users/user
```
```shell
ls nonexistent_folder; echo $?
```
If `ls` fails (`exit status 2`), then:  
```shell
echo 2
```

### **9. Execute Builtin Commands (`cd`, `exit`, etc.)**
- **Before searching in `$PATH`**, check if the command is a **builtin**.
- If it's a builtin, **execute it without `execve()`**.  

**Example:**  
```shell
cd /tmp
```
- `cd` is a **builtin**, so it must be executed **directly** inside Minishell.  
- It does **not** create a new process.

### **10. Execute External Commands (via `execve()`)**
- **Search for the command in `$PATH`**.
- **If found, execute it via `execve()`**.
- **If not found, print an error message (`command not found`)**.  

**Example:**  
```shell
ls -l /home
```
- Minishell **searches for `ls` in `$PATH`**.  
- If found (`/bin/ls`), it **executes it using `execve()`**.  


### **11. Handle Background Execution (`&`)**
*(Optional, not required for Minishell, but can be handled for extra functionality)*  
- If `&` is detected, run the command in the **background**.  

**Example:**  
```shell
sleep 5 &
```
- The shell **does not wait** for `sleep 5` to finish.  
- The process runs in the **background**.  

### **12. Signal Handling (`Ctrl + C`, `Ctrl + D`, `Ctrl + \`)**
- **After forking child processes**, handle signals properly.  
	- `Ctrl + C` → Should **interrupt** running commands but **not Minishell itself**.  
	- `Ctrl + D` → If the user presses `EOF` on an **empty line**, **exit the shell**.  
	- `Ctrl + \` → Ignore unless handling a **child process**.  

### **Final Summary: Order of Execution**  
1️⃣ **Tokenize input** (split into words, classify tokens)  
2️⃣ **Handle quoting & escaping**  
3️⃣ **Check for syntax errors** (e.g., unmatched quotes, misplaced pipes)  
4️⃣ **Process logical operators (`&&`, `||`)**  
5️⃣ **Handle grouping (`( )`, `{ }`)**  
6️⃣ **Set up pipes (`|`)**  
7️⃣ **Prepare redirections (`>`, `<`, `>>`, `<<`)**  
8️⃣ **Expand variables (`$VAR`, `$?`)**  
9️⃣ **Check and execute builtins** (`cd`, `export`, `exit`, etc.)  
🔟 **Execute external commands** (via `execve()`)  
1️⃣1️⃣ **Handle background execution (`&`)** *(if implemented)*  
1️⃣2️⃣ **Handle signals (`Ctrl + C`, `Ctrl + D`)**  

## DOCUMENTATION:

For explanations on functions and concepts already used in previous projects, refer to the README files of my other projects:

https://github.com/donnatchris/philosophers

https://github.com/donnatchris/minitalk

However, at the end of the DOCUMENTATION section, you will find a SHORT REMINDER section with a summary of all the previously covered functions.

---

### GITHUB COOPERATION

Here are the main commands to wotk with multiples branches:


#### Create a new branch and switch to that branch
```bash
git checkout -b <name_of_the_branch>
```

#### Switch to a branch
```bash
git checkout <name_of_the_branch>
```

#### Push your work on your branch
```bash
git add <name_of_file1> <name_of_file2> <...>

git commit -m "your_message"

git push origin <name_of_the_branch>
```

#### Merge your branch with main
```bash
git checkout main

git pull origin main #needed to fetch

git merge origin <name_of_the_branch>

git push origin main
```

---

### GNU readline library

The GNU Readline library is a powerful tool that provides line-editing and command history capabilities for interactive programs,
making it a fundamental component in many Unix-like command-line interfaces, including bash and gdb.
It allows users to edit input efficiently using keyboard shortcuts, recall previous commands, and navigate through text seamlessly.
To use readline in a C program, the required headers are <readline/readline.h> and <readline/history.h>.
When compiling, the program must be linked with `-lreadline`, and in some cases, `-lncurses` is also needed.

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
- **Returns**: The string fetched from the input.

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

---

### chdir()

> #include <unistd.h>
```c
int chdir(const char *path);
```
- `path`: A string representing the absolute or relative path to the new working directory.  
- **Returns**: `0` on success, or `-1` on error with `errno` set accordingly.  

The `chdir()` function changes the current working directory of the calling process to the directory specified by `path`.
It is commonly used in shell implementations and file management applications to navigate through the filesystem.  

#### Changing the Current Working Directory  
When `chdir()` is called, the process's working directory is updated to the specified `path`.
Any subsequent file operations that use relative paths will be based on this new directory.  

#### Permissions and Accessibility  
The process must have **execute (`X`) permissions** on the target directory.
If the directory does not exist or is inaccessible, the function fails and returns `-1`, setting `errno` to indicate the error.  

#### Error Handling  
`chdir()` may fail in several cases:  
- If `path` does not exist, it returns `-1` with `errno` set to `ENOENT`.  
- If `path` is not a directory, it returns `-1` with `errno` set to `ENOTDIR`.  
- If the process lacks the necessary permissions, it returns `-1` with `errno` set to `EACCES`.  
- If the system encounters a resource limitation, it returns `-1` with `errno` set to `ENOMEM` or `EIO`.  

Properly handling `chdir()` ensures that a program can reliably navigate directories while avoiding permission issues and other potential errors.

---

### stat()

> #include <sys/types.h>
>
> #include <sys/stat.h>
> 
> #include <unistd.h>
```c
int stat(const char *pathname, struct stat *buf);
```
- `pathname`: A string representing the path to the file or directory whose information is to be retrieved.  
- `buf`: A pointer to a `struct stat` where the file's metadata will be stored.  
- **Returns**: `0` on success, or `-1` on error with `errno` set accordingly.  

The `stat()` function retrieves detailed information about a file or directory and stores it in the provided `struct stat`.
It is commonly used in shell implementations, file management applications, and system monitoring tools to check file attributes such as size, permissions, and timestamps.  

#### Retrieving File Information  
When `stat()` is called, it fills the `struct stat` with metadata about the specified file, including:  
- **File type** (regular file, directory, symbolic link, etc.).  
- **Permissions** (read, write, execute for user, group, and others).  
- **File size** (in bytes).  
- **Number of hard links** to the file.  
- **Timestamps** (last access, modification, and status change).  
- **Owner and group ID** of the file.  

#### Difference Between `stat()` and `lstat()`
- `stat()` follows symbolic links and returns information about the target file.
- `lstat()` does **not** follow symbolic links and returns information about the link itself.

#### Error Handling
`stat()` may fail in several cases:  
- If `pathname` does not exist, it returns `-1` with `errno` set to `ENOENT`.  
- If `pathname` is a symbolic link pointing to a non-existent file, it returns `-1` with `errno` set to `ENOENT`.  
- If the process lacks permission to access the file, it returns `-1` with `errno` set to `EACCES`.  
- If `buf` is an invalid pointer, it returns `-1` with `errno` set to `EFAULT`.  

Using `stat()` correctly allows a program to inspect files and directories efficiently while handling potential errors gracefully.

---

### lstat()

> #include <sys/types.h>
> 
> #include <sys/stat.h>
> 
> #include <unistd.h>
```c
int lstat(const char *pathname, struct stat *buf);
```
- `pathname`: A string representing the path to the file or symbolic link whose information is to be retrieved.  
- `buf`: A pointer to a `struct stat` where the file's metadata will be stored.  
- **Returns**: `0` on success, or `-1` on error with `errno` set accordingly.  

The `lstat()` function retrieves metadata about a file, similar to `stat()`, but **does not follow symbolic links**. Instead, if the specified path is a symbolic link, `lstat()` returns information about the link itself rather than the target file. It is commonly used in file management applications and shell implementations to differentiate between symbolic links and regular files.  

#### Retrieving File and Link Information  
When `lstat()` is called, it fills the `struct stat` with metadata about the specified file or link, including:  
- **File type** (regular file, directory, symbolic link, etc.).  
- **Permissions** (read, write, execute for user, group, and others).  
- **File size** (in bytes).  
- **Number of hard links** to the file.  
- **Timestamps** (last access, modification, and status change).  
- **Owner and group ID** of the file or link.  

If `pathname` is a **symbolic link**, `lstat()` provides information about the link itself, including its size (the length of the path it points to) and permissions, rather than the target file's attributes.  

#### Difference Between `lstat()` and `stat()`  
- `lstat()` **does not follow** symbolic links and retrieves information about the link itself.  
- `stat()` **follows** symbolic links and returns information about the target file.  

#### Error Handling  
`lstat()` may fail in several cases:  
- If `pathname` does not exist, it returns `-1` with `errno` set to `ENOENT`.  
- If the process lacks permission to access the file, it returns `-1` with `errno` set to `EACCES`.  
- If `buf` is an invalid pointer, it returns `-1` with `errno` set to `EFAULT`.  

Using `lstat()` correctly allows a program to inspect symbolic links and files while handling potential errors gracefully.

---

### `fstat()`

> #include <sys/types.h>
> 
> #include <sys/stat.h>
> 
> #include <unistd.h>  
```c
int fstat(int fd, struct stat *buf);
```
- `fd`: A file descriptor referring to an open file.  
- `buf`: A pointer to a `struct stat` where the file's metadata will be stored.  
- **Returns**: `0` on success, or `-1` on error with `errno` set accordingly.  

The `fstat()` function retrieves metadata about an **open file descriptor** and stores it in the provided `struct stat`. Unlike `stat()`, which operates on a file path, `fstat()` works with a file descriptor, making it useful when dealing with already-opened files.  

#### Retrieving File Information  
When `fstat()` is called, it fills the `struct stat` with metadata about the file associated with `fd`, including:  
- **File type** (regular file, directory, symbolic link, etc.).  
- **Permissions** (read, write, execute for user, group, and others).  
- **File size** (in bytes).  
- **Number of hard links** to the file.  
- **Timestamps** (last access, modification, and status change).  
- **Owner and group ID** of the file.  

#### Difference Between `fstat()`, `stat()`, and `lstat()`  
- `stat()` retrieves metadata using a **file path** and follows symbolic links.  
- `lstat()` retrieves metadata using a **file path** but does **not** follow symbolic links.  
- `fstat()` retrieves metadata using a **file descriptor**, making it useful for files that are already open.  

#### Error Handling  
`fstat()` may fail in several cases:  
- If `fd` is not a valid open file descriptor, it returns `-1` with `errno` set to `EBADF`.  
- If `buf` is an invalid pointer, it returns `-1` with `errno` set to `EFAULT`.  
- If `fd` refers to a file on an unreachable filesystem (e.g., a disconnected network drive), it returns `-1` with `errno` set to `EIO`.  

Using `fstat()` correctly allows a program to inspect open files without needing their path, making it particularly useful for working with file descriptors from `open()`, `dup()`, or standard input/output streams.

---

### `unlink()`

> #include <unistd.h>  
```c
int unlink(const char *pathname);
```
- `pathname`: A string representing the path to the file to be removed.  
- **Returns**: `0` on success, or `-1` on error with `errno` set accordingly.  

The `unlink()` function removes a **link** to a file, effectively deleting the file if no other hard links exist and no process has it open. It is commonly used in shell implementations, file management programs, and system utilities to delete files.  

#### Removing a File  
When `unlink()` is called, it **removes the specified directory entry** (link) associated with `pathname`. If this was the last link to the file and no process has it open, the file's data is deleted, and its disk space is freed. If another hard link exists, the file remains accessible under the other name(s).  

#### Behavior with Open Files  
If a file is **open by a process**, calling `unlink()` will remove its directory entry, but the file remains accessible until the last process using it closes it. At that point, the file is deleted from the filesystem. This is useful for temporary files that should disappear once no longer in use.  

#### Error Handling  
`unlink()` may fail in several cases:  
- If `pathname` does not exist, it returns `-1` with `errno` set to `ENOENT`.  
- If `pathname` refers to a directory, it returns `-1` with `errno` set to `EISDIR` (except on some systems where `unlink()` can remove directories).  
- If the process lacks permission to remove the file, it returns `-1` with `errno` set to `EACCES` or `EPERM`.  
- If the filesystem is read-only, it returns `-1` with `errno` set to `EROFS`.  

Using `unlink()` correctly allows a program to manage file deletion while handling edge cases like hard links and open file descriptors.

---

### `execve()`

> #include <unistd.h>  
>  
> #include <sys/types.h>  
```c
int execve(const char *pathname, char *const argv[], char *const envp[]);
```
- `pathname`: A string representing the absolute or relative path to the executable file to be run.  
- `argv`: An array of pointers to arguments for the program, where `argv[0]` is typically the program name, and the last element must be `NULL`.  
- `envp`: An array of pointers to environment variables for the new program, terminated by `NULL`.  
- **Returns**: Does not return on success (the current process is replaced). Returns `-1` on error, with `errno` set accordingly.  

The `execve()` function replaces the calling process's memory image with a **new program** specified by `pathname`. Unlike `fork()`, it does **not create a new process** but transforms the existing process into the new program while keeping the **same PID**.  

#### Executing a New Program  
When `execve()` is called, the current process is **completely replaced** by the target program. The new program inherits some characteristics of the original process, such as **open file descriptors**, but it **does not retain the previous stack, heap, or code segments**.  

- **`argv` (program arguments)**: Used to pass command-line arguments to the executed program, similar to running a command in a terminal.  
- **`envp` (environment variables)**: Defines a custom environment for the process, useful for modifying the program's behavior.  

#### Difference from Other `exec` Functions  
- `execve()` is the **lowest-level function** in the `exec` family, directly interacting with the system.  
- `execl()` and `execv()` are simpler variants that do not include `envp`.  
- `execle()` and `execve()` allow specifying a custom environment.  

#### Error Handling  
`execve()` fails and returns `-1` in several cases:  
- If the file does not exist (`ENOENT`).  
- If the file is not executable (`EACCES`).  
- If the program exceeds system memory limits (`ENOMEM`).  
- If `argv` or `envp` is malformed (`EFAULT`).  

The `execve()` function is essential for implementing a shell (such as `minishell`), as it allows executing external commands by replacing the shell process with the requested command.

#### **In Minishell**  
In **Minishell**, you call `execve()` to:  
✅ Execute an external command (e.g., `ls -l`)  
✅ Search for the command in `$PATH` if it is not an absolute path  
✅ Launch a child process with `fork()` to avoid replacing Minishell  
✅ Handle pipes and redirections before executing the command

---

### `dup()`  

> #include <unistd.h>  
```c
int dup(int oldfd);
```  
- `oldfd`: A file descriptor referring to an open file.  
- **Returns**: A new file descriptor that refers to the same file as `oldfd`, or `-1` on error with `errno` set accordingly.  

The `dup()` function creates a duplicate of the file descriptor `oldfd` and returns the lowest available file descriptor. The new descriptor refers to the **same file** as `oldfd`, meaning they share the same file offset and file status flags.  

#### **Duplicating File Descriptors**  
When `dup()` is called, it finds the lowest available file descriptor and assigns it to the duplicate. The new file descriptor and the original one can be used interchangeably to read from or write to the file.  

#### **Example Usage**  
One common use case for `dup()` is redirecting standard input, output, or error. For example, duplicating `stdout` to another descriptor allows modifying where the output is written while preserving the original output stream.  

#### **Difference Between `dup()` and `dup2()`**  
- `dup()` **always returns the lowest available file descriptor**.  
- `dup2(int oldfd, int newfd)` allows specifying the exact number for the new file descriptor, closing `newfd` first if necessary.  

#### **Error Handling**  
`dup()` may fail in several cases:  
- If `oldfd` is not a valid file descriptor, it returns `-1` with `errno` set to `EBADF`.  
- If the system runs out of file descriptors, it returns `-1` with `errno` set to `EMFILE`.  

Using `dup()` is useful in **Minishell** when handling **I/O redirections**, allowing commands to read from or write to files instead of the standard input/output.

#### **In Minishell**  
In **Minishell**, you will use `dup()` to:  
✅ **Save and restore `stdin` and `stdout`** when handling redirections (`>`, `<`)  
✅ **Manage pipes (`|`)** by properly redirecting process input/output  
✅ **Prevent permanent redirection issues** by restoring original file descriptors after execution  

Without `dup()`, your redirections and pipes could interfere with your shell's display and execution!

---

### `dup2()`  

> #include <unistd.h>  
```c
int dup2(int oldfd, int newfd);
```  
- `oldfd`: The file descriptor to be duplicated.  
- `newfd`: The file descriptor to be replaced. If `newfd` is already open, it will be closed before being reused.  
- **Returns**: The new file descriptor (`newfd`), or `-1` on error with `errno` set accordingly.  

The `dup2()` function duplicates the file descriptor `oldfd` to `newfd`. If `newfd` is already open, it is closed first before being replaced by `oldfd`. Both file descriptors then refer to the same file, meaning they share the same file offset and file status flags.

#### **Key Use Cases**  
- **Redirection**: `dup2()` is commonly used for **I/O redirection**, such as redirecting `stdout` or `stderr` to a file or pipe. By specifying `STDOUT_FILENO` (1) as the `newfd`, you can redirect output to a file.
- **Controlling File Descriptors**: It is useful when you need to control or manage which file descriptor a process uses, especially in child processes (e.g., with `fork()`).

#### **Difference Between `dup()` and `dup2()`**  
- `dup2()` allows you to specify the exact number for the new file descriptor (`newfd`).  
- `dup()` always returns the **lowest available file descriptor**.

#### **Error Handling**  
`dup2()` may fail in several cases:  
- If `oldfd` is not a valid file descriptor, it returns `-1` with `errno` set to `EBADF`.  
- If the process runs out of file descriptors, it returns `-1` with `errno` set to `EMFILE`.  

#### **In Minishell**  
In **Minishell**, you will use `dup2()` to:  
✅ **Redirect input/output** for handling redirections (`>`, `<`) and pipes (`|`)  
✅ **Redirect `stdout` to a file** when implementing output redirection  
✅ **Redirect `stdin`** from a file when implementing input redirection  
✅ **Avoid file descriptor leaks** by managing file descriptors correctly when handling pipes and redirections

---

### `pipe()`  

> #include <unistd.h>  
```c
int pipe(int pipefd[2]);
```  
- `pipefd`: An array of two integers. The first element (`pipefd[0]`) is the read end of the pipe, and the second element (`pipefd[1]`) is the write end.  
- **Returns**: `0` on success, or `-1` on error with `errno` set accordingly.  

The `pipe()` function creates a pipe, a unidirectional communication channel used to transfer data between processes. It sets up two file descriptors: one for reading from the pipe and another for writing to it. After calling `pipe()`, data written to `pipefd[1]` can be read from `pipefd[0]`.

#### **Key Use Cases**  
- **Inter-process communication (IPC)**: Pipes are commonly used in a shell to redirect the output of one command to the input of another (e.g., with the `|` operator).  
- **Data transfer between processes**: They allow the output of one process to be passed directly into another, without using temporary files.  

#### **How It Works**  
After calling `pipe()`, the file descriptors `pipefd[0]` and `pipefd[1]` can be used just like any other file descriptors. The write end (`pipefd[1]`) can be used to send data, while the read end (`pipefd[0]`) can be used to receive data. You typically use `dup2()` to redirect the standard input or output of a process to or from the pipe.  
For example, in a shell, when a user enters a command like:  
```sh
ls | grep ".c"
```
`pipe()` will be used to connect the output of `ls` (via `pipefd[1]`) to the input of `grep` (via `pipefd[0]`).

#### **Error Handling**  
`pipe()` may fail in several cases:  
- If the system runs out of file descriptors, it returns `-1` with `errno` set to `EMFILE`.  
- If there is a problem creating the pipe due to a system limitation, it returns `-1` with `errno` set to `ENFILE`.  

#### **In Minishell**  
In **Minishell**, you will use `pipe()` to:  
✅ **Create a communication channel** between processes when implementing pipes (`|`)  
✅ **Connect the output of one command** to the input of another, allowing for chaining commands  
✅ **Facilitate efficient inter-process communication** without writing to temporary files

---

### `opendir()`  

> #include <dirent.h>  
```c
DIR *opendir(const char *dirname);
```  
- `dirname`: A string representing the path of the directory to open.  
- **Returns**: A pointer to a `DIR` object on success, or `NULL` on error with `errno` set accordingly.  

The `opendir()` function is used to open a directory stream corresponding to the directory specified by `dirname`. It returns a pointer to a `DIR` object, which can be used with other directory-related functions like `readdir()` and `closedir()` to read the contents of the directory or close the directory when finished. The returned `DIR` pointer represents the directory stream and is used to interact with the directory’s entries.

#### **Key Use Cases**  
- **Directory Traversal**: `opendir()` is commonly used in file management applications to traverse or list the files within a directory.  
- **Reading Directory Contents**: After opening a directory with `opendir()`, you can use `readdir()` to iterate through the entries of the directory.

#### **How It Works**  
Once a directory is successfully opened using `opendir()`, you can read its contents by calling `readdir()`, which returns a pointer to a `struct dirent` representing each entry (e.g., file or subdirectory). To close the directory stream, you use `closedir()`.  
For example:
```c
DIR *dir = opendir("/home/user/documents");
if (dir) {
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("Found: %s\n", entry->d_name);
    }
    closedir(dir);
}
```

#### **Error Handling**  
`opendir()` may fail in several cases:  
- If the directory does not exist, it returns `NULL` with `errno` set to `ENOENT`.  
- If the user lacks permission to read the directory, it returns `NULL` with `errno` set to `EACCES`.  
- If there is a system resource error, it returns `NULL` with `errno` set to `EMFILE`.

#### **In Minishell**  
In **Minishell**, you will use `opendir()` to:  
✅ **Open directories** when implementing commands like `ls` or `cd` to list or navigate directories.  
✅ **Read directory contents** to retrieve the files and subdirectories within a specified path.  
✅ **Facilitate directory exploration** in your shell, providing functionality for users to browse and interact with the filesystem.

---

### readdir()

> #include <dirent.h>  
```c
struct dirent *readdir(DIR *dirp);
```  
- `dirp`: A pointer to the `DIR` object returned by `opendir()`, representing the directory stream to be read.  
- **Returns**: A pointer to a `struct dirent` representing the next directory entry on success, or `NULL` when no more entries are available or an error occurs.  

The `readdir()` function reads the next entry from the directory stream referred to by `dirp`. It returns a pointer to a `struct dirent` containing information about the directory entry (such as the name of the file or directory). When the end of the directory is reached, or if an error occurs, it returns `NULL`.  

#### **Key Use Cases**  
- **Directory Traversal**: `readdir()` is used to iterate through the contents of a directory that was opened with `opendir()`.  
- **Listing Directory Entries**: It is often used in combination with `opendir()` and `closedir()` to list or process files and subdirectories within a directory.

#### **How It Works**  
After opening a directory with `opendir()`, you can call `readdir()` to get the next directory entry. Each call to `readdir()` returns the next file or directory in the directory stream. If `readdir()` reaches the end of the directory, it returns `NULL`.  
For example:
```c
DIR *dir = opendir("/home/user/documents");
if (dir) {
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("Found: %s\n", entry->d_name);
    }
    closedir(dir);
}
```

#### **Error Handling**  
`readdir()` may fail in several cases:  
- If the directory stream is not valid (e.g., if the directory was not opened with `opendir()`), it returns `NULL`.  
- If there is an error while reading the directory, it returns `NULL` and sets `errno` to an appropriate error code.

#### **In Minishell**  
In **Minishell**, you will use `readdir()` to:  
✅ **Read the contents of a directory** after opening it with `opendir()` to list files and subdirectories.  
✅ **Traverse directories** when implementing commands like `ls` or `find`.  
✅ **Check for the presence of specific files** when implementing functionality like autocomplete or file searching.

---

### closedir()

> #include <dirent.h>  
```c
int closedir(DIR *dirp);
```  
- `dirp`: A pointer to the `DIR` object representing the directory stream to be closed.  
- **Returns**: `0` on success, or `-1` on error with `errno` set accordingly.  

The `closedir()` function is used to close a directory stream that was previously opened by `opendir()`. After calling `closedir()`, the directory stream is no longer valid, and it cannot be used with `readdir()` or any other directory-related function. It's important to close the directory stream after you're done reading from a directory to release system resources.

#### **Key Use Cases**  
- **Resource Management**: `closedir()` ensures that system resources allocated for the directory stream are freed after use.  
- **Directory Cleanup**: After iterating through the entries of a directory with `readdir()`, you should call `closedir()` to close the directory stream and prevent resource leaks.

#### **How It Works**  
When you're done reading a directory using `opendir()` and `readdir()`, you should always call `closedir()` to close the directory stream. This releases any system resources associated with it.  
For example:
```c
DIR *dir = opendir("/home/user/documents");
if (dir) {
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("Found: %s\n", entry->d_name);
    }
    closedir(dir);
}
```

#### **Error Handling**  
`closedir()` may fail in several cases:  
- If `dirp` is not a valid pointer to an open directory stream (e.g., if the directory was never opened or already closed), it returns `-1` and sets `errno` to `EBADF`.  
- If there is a system error while closing the directory, it returns `-1` and sets `errno` to an appropriate error code.

#### **In Minishell**  
In **Minishell**, you will use `closedir()` to:  
✅ **Close the directory stream** after reading directory contents with `readdir()` to release system resources.  
✅ **Prevent resource leaks** when dealing with multiple directories during operations like listing files or navigating the filesystem.  
✅ **Ensure proper cleanup** after directory operations to maintain efficient resource management.

---
---

# SHORT REMINDERS
Of functions we have seen in previous projects

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
- `sig`: The signal to handle (e.g., `SIGINT`, `SIGTERM`, etc.).
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
