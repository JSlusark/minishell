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


declare -a SINGLE_TOKEN=(
    " "
    ""
    "|"
    #pipes involved
    "echo | \"   \""
)

declare -a ECHO_N=(
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
  #Redir Inbolved
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
  #Pipes involved
  "echo -n | echo -n"
  "echo -n| echo -n"
)

declare -a EXPANSION=(
  "echo\"\"$_\"\""
  "echo $$"
  "echo $$$"
  "echo $$$$"
  "$USER"
  "$NOTREAL ciao"
  "echo$USER"
  "echo $USERciao"
  "echo$USERciao"
  "echo$"
  "echo $USER$USER"
  "echo $?"
  "echo$?"
  "echo $?ciao"
  "echo$?ciao"
  # not-env characters
  "echo$US\"ER\""
  "echo $US\"ER\""
  #with pipes
    "echo |$echo hello\""
    "echo $|"
    "echo $| echo"
    "echo $| echo hello"
    "echo |$?"
    "echo|$"
    "echo|$ciacia"
)

declare -a EXPANSION_DQUOTE=(
  # "echo \"$(""
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
  "\"$?$USER\""
  "\"$/USER\""
  "\"$USER/\""
  "\"$NOTREAL\" ciao"
  "echo \"$0\""
  "echo \"$1\""
  "echo \"$-\""
  # not-env characters
  "echo$\"US\"ER"
  "echo $\"US\"ER"
# double "quotes" with 'single' quotes inside
  "echo \"'$'USER \""
  "echo \"$US 'ER' \""
# double "quotes" with many 'double' quotes inside
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
  #pipes involved
  "echo |\"$\""
  "echo \"$\"|"
  "echo \"$\"|echo hello"
  #redir involved
)

# Define test cases
declare -a TESTS=(

  "${SINGLE_TOKEN[@]}"
  "${ECHO_N[@]}"
  "${EXPANSION[@]}"
  "${EXPANSION_DQUOTE[@]}"




    ##EXPORT STUFF (not to be used in tester for now)
    # "\"export echo=\"\"echo\"\""
    # "$echo hello\""

    # "\"export CI=CA=ca"
    # "echo \"\"$CI=CA\"\"\""
)

# Arrays to store failed tests
FAILED_OUTPUTS=()
FAILED_EXITS=()

# Function to print test results
print_result()
{
    local description=$1
    local color=$2
    echo -e "$color$description$RESET"
}

# Function to clean Bash output
clean_bash_output()
{
    local output=$1
    # Remove "/bin/bash: line 1:" prefix from Bash errors
    echo "$output" | sed 's|/bin/bash: line [0-9]*: ||'
}

# Function to clean Minishell output
clean_minishell_output()
{
    local output=$1
    # Remove the first line, any 'Minishell> exit', and the 'Minishell>' prompt
    echo "$output" | sed -n '2,$p' | sed '/^Minishell> exit$/d' | sed '/^Minishell>/d'
}

# Run the test cases
for i in "${!TESTS[@]}"; do
    TEST="${TESTS[i]}"

    # Run command in Bash
    RAW_BASH_OUT=$(echo "$TEST" | $BASH 2>&1)
    BASH_OUT=$(clean_bash_output "$RAW_BASH_OUT")
    BASH_EXIT=$?

    # Run command in Minishell
    RAW_MINISHELL_OUT=$(echo "$TEST" | $MINISHELL 2>&1)
    MINISHELL_OUT=$(clean_minishell_output "$RAW_MINISHELL_OUT")
    MINISHELL_EXIT=$?

    # Print results
    echo
    echo -e "$MAGENTA------------ Test $((i+1)): \"$TEST\" ------------$RESET"

    # Bash Output / bash exit code is not right
    echo
    print_result "$GREEN - Bash:$RESET $BASH_OUT"
    print_result "$YELLOW Exit Code:$RESET $BASH_EXIT"
    echo
    print_result "$GREEN - Mini:$RESET $MINISHELL_OUT"
    print_result "$YELLOW Exit Code:$RESET $MINISHELL_EXIT"
    echo

    # Match Results
    OUTPUT_RESULT="✅"
    EXIT_RESULT="✅"

    if [ "$BASH_OUT" != "$MINISHELL_OUT" ]; then
        OUTPUT_RESULT="❌"
        FAILED_OUTPUTS+=("Test $((i+1)): \"$TEST\"")
    fi

    if [ "$BASH_EXIT" -ne "$MINISHELL_EXIT" ]; then
        EXIT_RESULT="❌"
        FAILED_EXITS+=("Test $((i+1)): \"$TEST\"")
    fi

echo
done
echo -e "📋 $BLUE Fail Summary:$RESET"
if [ ${#FAILED_OUTPUTS[@]} -eq 0 ] && [ ${#FAILED_EXITS[@]} -eq 0 ]; then
    echo -e "$GREEN All tests passed! 🎉$RESET"
else
    printf "%-10s %-40s %-10s %-10s\n" "Test No." "Command" "OUT" "EXIT"
    printf "%-10s %-40s %-10s %-10s\n" "--------" "----------------------------------------" "----" "-----"

    for i in "${!TESTS[@]}"; do
        TEST="${TESTS[i]}"
        OUT_STATUS="✅"
        EXIT_STATUS="✅"

        if [[ " ${FAILED_OUTPUTS[*]} " =~ "Test $((i+1)): \"$TEST\"" ]]; then
            OUT_STATUS="❌"
        fi
        if [[ " ${FAILED_EXITS[*]} " =~ "Test $((i+1)): \"$TEST\"" ]]; then
            EXIT_STATUS="❌"
        fi

        if [ "$OUT_STATUS" == "❌" ] || [ "$EXIT_STATUS" == "❌" ]; then
            printf "%-10s %-40s %-10s %-10s\n" "$((i+1))" "$TEST" "$OUT_STATUS" "$EXIT_STATUS"
        fi
    done
fi
echo -e "$MAGENTA------------------------------------------------$RESET"
echo
echo -e "$GREEN Testing Complete.$RESET"
