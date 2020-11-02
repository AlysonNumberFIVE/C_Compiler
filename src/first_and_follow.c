
#include "../inc/compiler.h"


t_hashtable *first_and_follow(void)
{
	t_hashtable *ht;

	ht = create_table(100000);
	ht_insert(ht, "char", "* ID )");
	ht_insert(ht, "const", "* ID )");
	ht_insert(ht, "void", "* ID )");
	ht_insert(ht, "struct", "ID )");
	ht_insert(ht, "int", "* ID ) unsigned");
	ht_insert(ht, "short", "* ID )");
	ht_insert(ht, "double", "* ID )");
	ht_insert(ht, "float", "* ID )");
	ht_insert(ht, "size_t", "* ID )");
	ht_insert(ht, "NULL", ";");
	ht_insert(ht, "bool", "*ID )");
	ht_insert(ht, "long", "* ID )");
	ht_insert(ht, "sizeof", "(");
	ht_insert(ht, "longlong", "* ID )");
	ht_insert(ht, "signed", "* ID )");
	ht_insert(ht, "extern", "char int void unsigned long struct");
	ht_insert(ht, "unsigned", "ID int char long double");
	ht_insert(ht, "do", "{");
	ht_insert(ht, "void", "* ID )");
	ht_insert(ht, "for", "(");
	ht_insert(ht, "*", "* ID ) NUM sizeof");
	ht_insert(ht, "ID", "( ; = < > & + - / * ++ += >>= <<= >> << || && , ) -> . [ ] == &&");
	ht_insert(ht, "->", "ID");
	ht_insert(ht, ".", "NUM ID sizeof");
	ht_insert(ht, "true", ")");
	ht_insert(ht, "false", ")");
	ht_insert(ht, "(", "( sizeof char true false const bool void struct int short double float size_t long longlong signed void ID NUM LITERAL");
	ht_insert(ht, ";", " ( DONE } NUM sizeof return char bool const void struct int short double float size_t long longlong signed void if for while do");
	ht_insert(ht, "LITERAL", ") ; , } +");
	ht_insert(ht, "]", "; + - / = == * )");
	ht_insert(ht, "[", "ID NUM sizeof");
	ht_insert(ht, "@", "ID");
	ht_insert(ht, "CHAR", ") ; , }");
	ht_insert(ht, "=", "ID NUM LITERAL ( { & @ sizeof");
	ht_insert(ht, ",", "ID NUM char const void struct int short double float size_t long longlong signed void CHAR");
	ht_insert(ht, ")", "; { ID NUM LITERAL + -");
	ht_insert(ht, "NUM", "+ - / * ) ; , > < == ] }");
	ht_insert(ht, "{", "ID char const void struct int short double float size_t long longlong signed void return NUM CHAR sizeof");
	ht_insert(ht, "}", "DONE ; } while");
	ht_insert(ht, "return", "( ; ID NUM sizeof");
	ht_insert(ht, "&", "ID ");
	ht_insert(ht, "for", "(");
	ht_insert(ht, "&&", "ID NUM");
	ht_insert(ht, "<<", "ID NUM sizeof");
	ht_insert(ht, ">>", "ID NUM sizeof");
	ht_insert(ht, "|", "ID NUM sizeof");
	ht_insert(ht, "/", "ID NUM sizeof");
	ht_insert(ht, "else", "{ if");
	ht_insert(ht, "\'", ") + -");
	ht_insert(ht, "==", "\\");
	ht_insert(ht, "!=", "ID NUM ( ");
	ht_insert(ht, "+", "ID NUM sizeof");
	ht_insert(ht, "-", "ID NUM sizeof");
	ht_insert(ht, "++", ") ;");
	ht_insert(ht, "<", "NUM FLOAT sizeof");		
	
	return (ht);
}
