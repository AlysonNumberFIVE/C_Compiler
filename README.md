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
 - KEYWORDS: (also known as "Terminals" in compsci speak); these are reserved tokens that are part of the language and may not be used in any other context such as variable names.<br>
 - IDs (also known as "nonterminals" alongside literal strings and characters, possibly numbers too but probably not).<br> 
 - NUMs basically all numbers. I've included floats as part of these but considering separating them out.<br><br>

The `line` variable determines at what line number in the source file this token is located. This will be used when handling errors in semantic analysis. A separate structure with all source file names and their source code will be referenced and the `line` number will be used to index into the file to when printing out the error in the format
```
error : [filename] [line number] [message]
```
but that's still to come. <br><br>
### Lexer pseudocode
The main lexer loop uses the following 2 logic functions (written in a Python-esque style for ease of readability).<br>
The first is the lexer that loops over each of the files passed into the compiler as arguments and the second is a scanner, enclosed in the main lexer loop the returns individual tokens from each of the files.<br><br>
Pseudocode for `scan()`.
```
line_number = 0 // the current line number in the source file

function scan(source_code, file_name):
    
    for character in source_code:
         if character is whitespace:
             continue
         else if character is newline:
             line_number += 1
         break
        
    if character is token:
        return token_object{token_name, token_type, line_number, file_name}
    return NULL
```
This is the formular for grabbing each token. The function above is enclosed further in a loop that iterates over the names of each of the files passed in as arguments to the compiler.
```

function lexer(files):
    token_list = Tokens()

    for file in files:
        file_name = file.name
        
        for source_code in file.source_code:
            token = scan(source_code, file_name)
            token_list.push_token(tokens)
```
 This is the basic formular for iterating over the source file. It's a bit simplistic as the concenpt of a memory address position was hard to translate into this pseudocode. You can assume that `source_code` in the above in C uses the same rule as the concept of using `&source_code[i]` if source code is a `char *` variable and `i` is an index into the string.
 
 The source code for the lexer can be seen in `src/lexer.c`.
 
 ### Semantic Analysis
 This step has to be the hardest part of this project. It's made worse by the fact that this step has a lot of room for some really nice class inheritance but as C doesn't support classes, there was a lot of repeated logic which (at time of writing) I'm currently working on fixing 

As the analysis step is far from ready for prime time, I thought I might prep your appetite with a little bit of theory that's necessarly to understand how to do semantic analysis correctly (althogh having said this, there's probably tons of ways to do it but these are the techniques I learnt from the above sources).<br>
The two important concepts which took me a bit of work and further research apart from the above sources to understand are the concepts of <b>First and Follow</b> and <b>Context Free/Sensitive Grammars</b>. These ideas are critical when it comes to designing a compiler and, for the more ambitious ones of you out there, designing a language from scratch. A lot of my struggles came from translating the theory, which focuses on general langauge design, into practice with the C language's standard. So let's go over them briefly and look at some examples of what these concepts look like practically in C.<br><br>

### First and Follow
First and Follow is the concept of tokens and what tokens are legallly allowed to follow after one another. So the <b>FIRST</b> token will have a list of tokens that are allowed to <b>FOLLOW</b>. In my program, this datastructure is a custom hashtable where the KEYs are the FIRST tokens and the VALUEs are the FOLLOW tokens.<br>
Let's take the example of the following source code that demonstrates what I'm talking about:

```
char *str = "42";
```
In the above, we'd start by looking at the `char` token. Using the above hashtable concept, the `char` is our KEY. Next, we'll need a list of tokens that are _allowed_ to follow after `char`. A few that come to mind are `*` or variable names and even `)` (for typecasting rules).
Our First and Follow mapping for `char` would look like this.
```
{"char": ["*", "ID", ")"]}
```
These are legally, in at least 1 circumstance in the language, allowed to follow after the token `char`.<br><br>
Another example, using the same code snippet above would be the `=` token. The values allowed to directly follow this token are `ID`s (variables), `(`, `NUM`s, `FLOAT`s, `LITERAL`s (strings) `CHAR`s (characters), `{` (for array initialization), `&` for variable referencing and probably a few others I'm forgetting. The `=` first and follow structure would then look something like this<br>
```
{"=": ["ID", "FLOAT", "LITERAL", "CHAR", "{", ...]}
```
It's simple enough to implement as C already has it's first and follow mapped out for us because it's existed for decades. I imagine it's a lot harder to implement if you had to make a language from scratch and design its ruleset. This concept is fairly straightforward I hope. If you'd like to know a little more about the theory of First and Follow, the best video I came across on YouTube was <a href="https://youtu.be/SBnjVW8dUqo" blank_="">this</a> one by Mifta Sintaha (incidentally, check out her Github here <a href="https://github.com/msintaha">@msintaha</a>. Her teachings were invaluable).<br>




