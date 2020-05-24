echo "Compiling Scope Test"
gcc -o scope scope_test.c ../src/scope_* ../src/datatypes.c
echo "\n\n\n\nCompiling Lexer Test"
gcc -o lexer lexer_test.c ../src/lexer.c ../src/token_control.c ../src/hashtable.c ../src/lexer_token_types.c ../src/lexer_utils.c ../src/lib.a
