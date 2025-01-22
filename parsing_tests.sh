#!/bin/bash

# Paths to executables
MINISHELL="./minishell"
BASH="/bin/bash"

# Colors for output
BLUE="\\033[1;34m"
CYAN="\\033[1;36m"
GREEN="\\033[1;32m"
RED="\\033[1;31m"
YELLOW="\\033[1;33m"   # Yellow
MAGENTA="\\033[1;35m"  # Magenta
RESET="\\033[0m"

# Initialize the log file
echo "Starting Minishell Tests"

# Define test cases
declare -a TESTS=(
    # "echo jslusark"
    # "pwd"
    # "ls -l"
    # "export TEST_VAR=42 && echo $TEST_VAR"
    # "cat < missing_file"

    ##
    " "
    ""
    "|"
    ## echo -n option
    "echo -n hello"
    "echo -n -n hello"
    "echo -n -n -n hello"
    "echo -n -n hello -n"
    "echo hello -n"
    "echo -nnnn hello"
    "echo -nnnn -n -nn hello"
    "echo hello -nnnnn"
    "echo hello -nnnnn -n"
    "echo -nnnnm -n -nnnn hello"
    "echo -n"
    "echo -nnnn"
    "echo -nnnn -n -nn -nnnnn"
    "echo -nnnn -nm hello -n"
    "echo -nnm hello -n"
    "echo -l"
    "echo - n"
    "echo-n"
    "echo -"
    "echo -n      -"
    "echo -n                  "
    "echo -n  \"              \""
    "echo-"
    "echo -N"
    "echo \"-n\"nnn hello"
    "echo \"-n\"nnm hello"
    "echo '-n'nnn hello"
    "echo '-n'nnm hello"
    "echo \"-n\" hello"
    "echo '-n' hello"
    "echo\"-n\" hello"
    "echo'-n' hello"
    "echo \"\"\"\"\"\"-n\"\" hello"
    "echo \"\"\"-\"\"\"n\"\" hello"
    "echo -\"\"\"\"\"\"n\"\" hello"
    "echo ''''''-n'' hello"
    "echo ''''-''n'' hello"
    "echo -''''''n'' hello"
    "echo \"''\"\"-n\"\"''\""
    "echo \"'\"-n\"'\""
    "echo \"'\"'\"\"-n\"'\"'\""
    "echo '\"-n\"'"
    "-n"
    "echo > file -n hey"
    "echo > file hey -n"
    "echo hey -n > file"
    "echo > -n ciao"
    "echo > file -nm"
    "cd -n hello ciao"
    "echo > -n"
    "echo > -n ciao"
    "echo > -n ciao -n"
    "echo -n > file hey"
    "echo -n arg > file"
    "echo -n arg > file hey"
    "echo -n | echo -n"
    "echo -n| echo -n"

    ## expansion
    "echo\"\"$_\"\""
    # "echo \"$(""
    "echo $$"
    "echo $$$"
    "echo $$$$"
    "echo CIAO=\"$USER\""
    "echo \"$\""
    "echo \"$ \""
    "echo \"$  ciao\""
    "echo \" $\""
    "echo \"$ ciao\" come stai"
    "echo \"$'US'ER\""
    "echo \"$?\""
    "echo \"$? \""
    "echo \" $?\""
    "echo \"$? ciao\""
    "echo \"$? ciao      \" come stai"
    "echo \"$PWD\""
    "echo \"$USER\""
    "echo \"$US-ER\""
    "echo \"$GNOME_TERMINAL_SERVICE\""
    "echo \"$US\"ER"
    "echo \"$\"USER\"\""
    "echo \"$US\"ER\"\""
    "echo \"'$'USER \""
    "echo \"$US 'ER' \""
    "echo \"$0\""
    "echo \"$1\""
    "echo \"$-\""
    "\"$?$USER\""
    "\"$/USER\""
    "\"$USER/\""
    "\"export echo=\"\"echo\"\""
    "\"\"$echo\"\" hello\""
    "\"$NOTREAL\" ciao"
    "$USER"
    "$NOTREAL ciao"
    "\" \" ciao"
    "\"\" ciao"
    "' ciao"
    "\"export echo=\"\"echo\"\""
    "\"\"$echo\"\" hello\""
    "echo \"\"$\"\""
    "echo \"\"\"$\"\"\""
    "echo \"\"\"\"$\"\"\"\""
    "echo \"\"\"\"\"$\"\"\"\"\""
    "echo \"$\"$\"\""
    "echo \"$$\"$\"\""
    "echo \"$\"$\"\"$\"\""
    "echo \"$\"\"$\"\"$\"\"\""
    "echo \"$\"$\"\"$\"\"$\"\""
    "echo \"$\"$\"\"\"$\"\"$\"\""
    "echo |\"$\""
    "echo \"$\"|"
    "echo \"$\"|echo hello"
    "echo$US\"ER\""
    "echo $US\"ER\""
    "echo$\"US\"ER"
    "echo $\"US\"ER"
    "\"export echo=\"\"echo\"\""
    "$echo hello\""
    "\"export echo=\"\"echo\"\""
    "echo |$echo hello\""
    "echo $|"
    "echo $| echo"
    "echo $| echo hello"
    "echo |$?"
    "echo|$"
    "echo|$ciacia"
    "echo | \"   \""
    "\"export CI=CA=ca"
    "echo \"\"$CI=CA\"\"\""
    "echo$USER"
    "echo $USERciao"
    "echo$USERciao"
    "echo$"
    "echo $USER$USER"
    "echo $?"
    "echo$?"
    "echo $?ciao"
    "echo$?ciao"
  )

  # Function to print test results
  print_result() {
    local description=$1
    local color=$2
    echo -e "$color$description$RESET"
  }

  # Function to clean Minishell output
  clean_minishell_output() {
    local output=$1
    # Remove the first line, any 'Minishell> exit', and any line exactly matching 'exit'
    echo "$output" | sed -n '2,$p' | sed '/^Minishell> exit$/d' | sed '/^exit$/d'
  }



  # Run the test cases
  for i in "${!TESTS[@]}"; do
    TEST="${TESTS[i]}"
    echo "Running Test $((i+1)): \"$TEST\""

    # Run command in Bash
    BASH_OUT=$(echo "$TEST" | $BASH 2>&1)

    # Run command in Minishell
    RAW_MINISHELL_OUT=$(echo "$TEST" | $MINISHELL 2>&1)
    MINISHELL_OUT=$(clean_minishell_output "$RAW_MINISHELL_OUT")

    # Print results
    echo -e "Test $((i+1)): \"$TEST\""

    # Bash Output
    print_result "$BLUE - Bash:$RESET"
    print_result " $CYAN OUT: $RESET $BASH_OUT"

    # Minishell Output
    print_result "$BLUE - Minishell:$RESET"
    print_result " $CYAN OUT $RESET: $MINISHELL_OUT"

    # Match Results
    if [ "$BASH_OUT" == "$MINISHELL_OUT" ]; then
      print_result "- OUTPUT MATCHES" "$GREEN"
    else
      print_result "- OUTPUT DOES NOT MATCH" "$RED"
    fi

  echo
done

# Final message
echo "Testing Complete."
