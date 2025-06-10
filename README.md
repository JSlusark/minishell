# Minishell
Minishell is a command-line interpreter that mimics the behavior of popular UNIX shells like bash. It is a project built in C as a part of the 42 Berlin curriculum.
Details about the assignment can be found [here]().


A short demonstration is available in the video below:
<video src="./demo.mp4" width="600" controls>
video
</video>

# Parser
The parser is the first stage in the Minishell program. Its job is to take the raw user input, interpret it, and transform it into a structured format that the executor can directly process.
That structured format is a linked list of command nodes. Each node represents a single command along with its arguments, options, redirections and execution metadata such as pipe position.

To prepare this structure, the parser acts in 2 main steps:

1. **Tokenization**: In this process the input string is scanned character by character, splitting it into tokens. This includes words, symbols, and operators like `|`, `<`, `>`, `<<`, etc... while handling quoting and escaping rules. It also expands shell variables (e.g., `$USER`, `$?`) with their actual values from the environment or shell state, taking into account quoting and special cases.
This proess will create a list of tokens and their types (e.g., word, operator, redirection, pipe) that will be used in the next step.

2. **Node Construction**: In this step, the parser processes the list of tokens generated in the first step to create a linked list of command nodes. Each node encapsulates a command, its arguments, redirections, and status flags. The parser also validates the order of each token type, ensuring that it adheres to the expected structure (e.g., no unmatched quotes, valid pipe usage, not consecutive pipes or redirections).

# Execution
The execution phase is responsible for taking the structured command nodes produced by the parser and actually running the commands, handling all the complexities of UNIX process management, redirections, and builtins.

What Execution Handles
- **Built-in Commands**: Executes shell builtins (cd, echo, env, exit, export, pwd, unset) directly in the shell process, ensuring correct environment and state management.
- **External Commands**: Locates and runs external binaries using the PATH environment variable, forking child processes as needed.
- **Pipelines**: Sets up pipes between commands in a pipeline, ensuring correct data flow from one process to the next.
- **Redirections**: Handles all standard redirections (>, >>, <, <<), including robust heredoc support with variable expansion and signal handling.
- **Signal Handling**: Manages signals (SIGINT, SIGQUIT) both in the shell and in child processes, ensuring correct interactive behavior and cleanup.
- **Exit Codes**: Propagates and updates exit codes according to UNIX conventions, including special handling for signals and errors.
- **Resource Management**: Cleans up all allocated memory, file descriptors, and process resources, even in the presence of errors or signals.

# Compilation

To compile Minishell, simply run:

```sh
make
```

This will produce the `minishell` executable in the project directory.

# Running Minishell

To start the shell, run:

```sh
./minishell
```

# Checking the Project

You can check the project by running various shell commands and builtins, as described above. Make sure to test with different combinations of pipes, redirections, and quoting.

# Memory Leaks

Minishell is designed to be leak-free. You can verify this using [Valgrind](https://valgrind.org/):

```sh
valgrind --leak-check=full --show-leak-kinds=all ./minishell
```

This will report any memory leaks or invalid memory usage. If you see "All heap blocks were freed -- no leaks are possible", the shell is leak-free.
