# Shrimp
Compiler Construction Project

## Team Members (Group 5)
1. Shreyas R        (2018A7PS0430H)
2. Sudheer Kumar    (2018A7PS0199H)
3. Shivang Shah     (2018A7PS0295H)
4. Kushagra Gupta   (2018A7PS0208H)

## Compilation
`$ g++ -std=c++17 src/* -o lexer`

## Usage
`$ ./lexer $INPUT_FILE`

## Testing

Test cases are present in the `test` folder.

`$ ./lexer test/case_$TEST_input.txt > out`
`$ diff out test/case_$TEST_output.txt`
