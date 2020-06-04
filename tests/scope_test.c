

#include <unistd.h>
#include "../inc/symbol.h"
#include "../inc/compiler.h"
#include <stdbool.h>


bool    scope_variable_test(void)
{
    t_scope     *function_env;
    t_symbol    *inherited_variable;
    t_symbol    *start;

    printf("====================== Scope Variable Test ==========\n\n");
    function_env = NULL;
    inherited_variable = NULL;
    printf("Adding inherited, top level variables.\n");
    inherited_variable = insert_variable(inherited_variable, "c", datatypes[CHAR].name,
        datatypes[CHAR].size, "x", 4, 0, false, 0);
    inherited_variable = insert_variable(inherited_variable, "x",  datatypes[INT].name,
        datatypes[INT].size, "214",5, 0, false, 0);
    inherited_variable = insert_variable(inherited_variable, "k", datatypes[LONG].name,
        datatypes[LONG].size, "12414213567", 6, 0, false, 0);

    function_env = push_scope(function_env, inherited_variable);
    printf("Scope of Depth == 1 and variables set\n");
    printf("%d\n", function_env->depth);
    start = function_env->inherited_symbols;
    printf("niherited_variables:\n");
    while (start)
    {
        printf("%s\n", start->name);
        start = start->next;
    }
    printf("Current scope variables.\n");
    function_env->symbols = insert_variable(function_env->symbols, "l", datatypes[INT].name,
        datatypes[INT].size, "42", 11, 0, false, 0);
    function_env->symbols = insert_variable(function_env->symbols, "h", datatypes[INT].name,
        datatypes[INT].size, "84", 12, 0, false, 0);
    function_env->symbols = insert_variable(function_env->symbols, "i", datatypes[INT].name,
        datatypes[INT].size, "125", 13, 0, false, 0);
    
    printf("{\n");
    start = function_env->symbols;
    while (start)
    {
        printf("\t%s\n", start->name);
        start = start->next;
    }
    printf("}");
    printf("\n\n================================================\n\n");
    return (true);
}

bool    variable_test(void)
{
    extern struct s_datatype datatypes[13];
    t_symbol    *variables;
    t_symbol    *valr;
    int         checker;

    printf("\n\n========== Scope Variable Test ============\n\n");
    init_datatypes();
    variables = NULL;
    t_symbol *throwaway = variables;
    variables = insert_variable(variables, "c", datatypes[CHAR].name,
            datatypes[CHAR].size, NULL, 4, 0, false, 0);
    variables = insert_variable(variables, "i", datatypes[INT].name,
            datatypes[INT].size, NULL, 5, 0, false, 0);
    variables = insert_variable(variables, "x", datatypes[UNSIGNED_INT].name,
            datatypes[UNSIGNED_INT].size, NULL, 6, 0, false, 0);
    t_symbol *start = variables;
    printf("3 variables created\n");
    checker = 0;
    while (start)
    {
        printf("%s\n", start->name);
        start = start->next;
        checker++;
    }
    if (checker != 3) return (false);
    printf("3 variables created : PASS\n\n");

    printf("Set already assigned variables with values\n");
    if (reset_variable(variables, "c", "a") == false) return (false);
    if (reset_variable(variables, "i", "42") == false) return (false);
    if (reset_variable(variables, "x", "12341241231") == false) return (false);
    start = variables;
    while (start)
    {
        printf("%s = %s\n", start->name, start->value);
        start = start->next;
    }
    printf("Variable value assignment : PASS\n\n");
    printf("Lookup certain variables by name\n");
    t_symbol *var;
    var = lookup_variable(variables, "c");
    if (strcmp(var->name, "c") == 0) printf("Variable name : c : found\n"); 
    else return (false);

    var = lookup_variable(variables, "i");
    if (strcmp(var->name, "i") == 0) printf("Variable name : i : found\n");
    else return (false);

    var = lookup_variable(variables, "y");
    if (var == NULL) printf("Variable name : y : not found\n"); 
    else return (false);
    printf("Lookup variables by nam : PASS\n\n");

    printf("Reset existing variables\n");
    var = lookup_variable(variables, "c");
    printf("Before update: %s == %s\n", var->name, var->value);
    if (reset_variable(variables, "c", "b") == false) return (false); 
    var = lookup_variable(variables, "c");
    if (strcmp(var->value, "b") == 0) printf("Variable %s == %s\n", var->name, var->value);
    else return (false);
    printf("Variable reset : PASS\n\n");

    printf("Alter a nonexistent variable\n");
    if (reset_variable(variables, "bibidi", "41123") == true)
        return (false); 
    printf("Nonexistent test : PASS\n\n");
    printf("\nClearing up variables list\n");
    clear_all_variables(variables);
    if (variables == NULL) return (true);
    printf("Variable list clear : PASS\n\n");
    printf("\n\n=========================================\n\n");
    return (true);
} 

bool    depth_test(void)
{
    t_scope     *table;

    table = NULL;
    // testing depth
    printf("\n\n========= Depth Test ============\n\n");
    table = push_scope(table, NULL);
    printf("DEPTH == 0\n");
    if (table->depth == 0)
        printf("PASS\n");
    else
        return (false);

    table = push_scope(table, NULL);
    table = push_scope(table, NULL);
    table = push_scope(table, NULL);
    printf("Pushing 3 extra tables\nDepth is now 3\n");
    if (table->next->next->next->depth == 3)
        printf("PASS\n");
    else
        return (false);

    table = push_scope(table, NULL);
    table = push_scope(table, NULL);
    table = push_scope(table, NULL);
    table = push_scope(table, NULL);
    printf("Pushing 4 extra tables\nDepth is now 7\n");
    if (table->next->next->next->next->next->next->next->depth == 7)
        printf("PASS\n");
    else 
        return (false);

    printf("DEPTH TEST PASS\n");
    printf("\n\n=============================\n\n");
    return (true);
}

void    send_microsoft_error_report(void)
{
    char buffer[1024];
    printf("An error has occured. This program wil now shutdown.\nWould you like to send a report?\n");
    printf("[Y\\n]?\n");
    read(0, buffer, 1024);
    printf("Sending report\n");
}

int     main(void)
{
    if (depth_test() == false)
        send_microsoft_error_report();
   
    if (variable_test() == false)
        send_microsoft_error_report();

    scope_variable_test();

    return (0);
}
