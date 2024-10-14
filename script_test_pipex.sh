#!/bin/bash

run_test() {
    ./pipex $1 "$2" "$3" $4
    < $1 $2 | $3 > expected_output
    diff $4 expected_output && echo "Test passed!" || echo "Test failed!"
}

# Casos de éxito
run_test infile "ls -l" "wc -l" outfile
run_test infile "grep palabra" "wc -w" outfile
# Agrega más pruebas aquí...
echo "------------------------\n"
# Casos de error
run_test nofile "ls -l" "wc -l" outfile
run_test infile "invalidcommand" "wc -l" outfile
# Agrega más pruebas aquí...

rm -f expected_output

