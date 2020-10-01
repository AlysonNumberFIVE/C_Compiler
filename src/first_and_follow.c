
#include "../inc/compiler.h"


t_hashtable *first_and_follow(void)
{
	t_hashtable *ht;

	ht = create_table(100000);
	ht_insert(ht, "char", "* ID )");
	ht_insert(ht, "const", "* ID )");
	ht_insert(ht, "void", "* ID )");
	ht_insert(ht, "struct", "ID )");
	ht_insert(ht, "int", "* ID )");
	ht_insert(ht, "short", "* ID )");
	ht_insert(ht, "double", "* ID )");
	ht_insert(ht, "float", "* ID )");
	ht_insert(ht, "size_t", "* ID )");
	ht_insert(ht, "long", "* ID )");
	ht_insert(ht, "longlong", "* ID )");
	ht_insert(ht, "signed", "* ID )");
	ht_insert(ht, "void", "* ID )");
	ht_insert(ht, "*", "* ID )");
	ht_insert(ht, "ID", "( ; = < > & + - / * ++ += >>= <<= >> << || && , )");
	ht_insert(ht, "(", "char const void struct int short double float size_t long longlong signed void ID NUM");
	ht_insert(ht, ";", "DONE }");
	ht_insert(ht, "=", "ID NUM ( ");
	ht_insert(ht, ",", "ID NUM char const void struct int short double float size_t long longlong signed void");
	ht_insert(ht, ")", "; { ID NUM");
	ht_insert(ht, "NUM", "+ - / * ) ;");
	ht_insert(ht, "{", "ID char const void struct in short double float size_t long longlong signed void return");
	ht_insert(ht, "}", "DONE");
	ht_insert(ht, "return", "( ; ID NUM");
	return (ht);
}
