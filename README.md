# C_Compiler
A C compiler written in C (similar to Java_Compiler)

## Summary
This is my first attempt at implementing a compiler from scratch. I've tried my hand at a CoreWar assembler but felt I wanted to do the kind
of project that made use of practical computer science concepts in a real application.</br>
The following books were a great help in programming this project:</br>
- <a href="https://www.amazon.com/Compilers-Principles-Techniques-Tools-2nd/dp/0321486811">Compilers: Principals, Techniques and Tools</a> by Alfred Aho and Monica Lam<br>
- <a href="https://www.amazon.com/Engineering-Compiler-Keith-Cooper/dp/012088478X">Engineering: A Compiler</a> by Kieth Cooper and Linda Torczon
- <a href="https://www.amazon.com/Introduction-Bit-Assembly-Programming-Linux/dp/1484921909">Introduction to 64-bit Assembly Programming for Linux and OSX</a> by Ray Seyfarth
<br><br>
And lastly, the following course was a great overview of the project:</br>
 - <a href="https://www.udemy.com/course/compiler-design-n/">Compiler Design</a> by Edutainer India (on Udemy)
<br>
I opted to build my compiler in C using only the theoretical knowledge gained from the courses to test my understanding of the theoretical concepts. <b>I strongly recommend against coding a compiler in C</b>.
And without further ado, here's a brief overview of my design approach and overall progress (so far, this will change as I get further along).

## Compiler Structure
My compiler is divided into 3 sections.
- <b>Lexical Analysis</b>
The tokenizing process of getting each and every valid token in the source file regardless of correctness. Error handling isn't implemented just yet.

- <b>Syntax Analysis</b>
Verifying the correctness of each token and it's position in the source file. Error messages and warning are dumped at this stage for the usual suspects (missing semicolons, invalid variables, incorrect syntax etc.)

- <b>Intermediate Code Generation</b>
Once all the code is verified as correct, this step is where the C code is translated into intermediate code in no particular language. The code at this point is similar to its assembly counterpart in structure but is kept custom to allow for the eventual translation from it into the target assembly of the system it's compiled on.

My compiler is planned to go as far as this step as I'm not completely clear on how to translate a lot of C's data structures into assembly like linked lists and multidimensional arrays.

## Detailed Apprach
### Lexing
For the lexing process, I created a linked list, with each node being an individual token with the following structure
```
typedef struct  token {
    char        *name;
    char        *type;
    int         line;
    char        *filename;
    struct token    *next;
}   t_token;
```
Where the `name` is the token in its string form (i.e "int", "{", "}", "i").<br>The `type` is determines what kind of token it is. The most important types of a language are as follows:<br>
KEYWORDS: (also known as "Terminals" in compsci speak); these are reserved tokens that are part of the language and may not be used in any other context such as variable names.<br>
IDs (also known as "nonterminals" alongside literal strings and characters, possibly numbers too but probably not).<br>
NUMs basically all numbers. I've included floats as part of these but considering separating them out.<br><br>

The `line` variable determines at what line number in the source file this token is located. This will be used when handling errors in semantic analysis. A separate structure with all source file names and their source code will be referenced and the `line` number will be used to index into the file to when printing out the error in the format
```
error : [filename] [line number] [message]
```
but that's still to come.
