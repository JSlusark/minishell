#!/bin/bash

# Paths to executables
MINISHELL="./minishell"
BASH="/bin/bash"

# Colors for output
BLUE="\\033[1;34m"
CYAN="\\033[1;36m"
GREEN="\\033[1;32m"
RED="\\033[1;31m"
RESET="\\033[0m"

# Log file for results
LOGFILE="test_results.log"

# Initialize the log file
echo "Starting Minishell Tests" > $LOGFILE

# Define test cases
declare -a TESTS=(
  "echo jslusark"
  "pwd"
  "ls -l"
  "export TEST_VAR=42 && echo $TEST_VAR"
  "cat < missing_file"
)

# Function to print test results
print_result() {
  local description=$1
  local color=$2
  echo -e "$color$description$RESET" | tee -a $LOGFILE
}

# Function to clean Minishell output
clean_minishell_output() {
  local output=$1
  # Skip the first line and any trailing prompt lines (e.g., "Minishell> exit")
  echo "$output" | sed -n '2,$p' | sed '/^Minishell> exit$/d'
}

# Run the test cases
for i in "${!TESTS[@]}"; do
  TEST="${TESTS[i]}"
  echo "Running Test $((i+1)): \"$TEST\"" | tee -a $LOGFILE

  # Run command in Bash
  BASH_OUT=$(echo "$TEST" | $BASH 2>&1)
  BASH_EXIT=$?

  # Run command in Minishell
  RAW_MINISHELL_OUT=$(echo "$TEST" | $MINISHELL 2>&1)
  MINISHELL_OUT=$(clean_minishell_output "$RAW_MINISHELL_OUT")
  MINISHELL_EXIT=$?

  # Print results
  echo -e "Test $((i+1)): \"$TEST\"" | tee -a $LOGFILE

  # Bash Output
  print_result "- Bash:" "$BLUE"
  print_result "  OUT: $BASH_OUT" "$BLUE"
  print_result "  EXIT: $BASH_EXIT" "$BLUE"

  # Minishell Output
  print_result "- Minishell:" "$CYAN"
  print_result "  OUT: $MINISHELL_OUT" "$CYAN"
  print_result "  EXIT: $MINISHELL_EXIT" "$CYAN"

  # Match Results
  if [ "$BASH_OUT" == "$MINISHELL_OUT" ]; then
    print_result "- OUTPUT MATCHES" "$GREEN"
  else
    print_result "- OUTPUT DOES NOT MATCH" "$RED"
  fi

  if [ "$BASH_EXIT" -eq "$MINISHELL_EXIT" ]; then
    print_result "- EXIT MATCHES" "$GREEN"
  else
    print_result "- EXIT DOES NOT MATCH" "$RED"
  fi

  echo | tee -a $LOGFILE
done

# Final message
echo "Testing Complete. Results saved to $LOGFILE."
