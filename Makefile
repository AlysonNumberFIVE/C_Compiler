
# Coded by AlysonBee (Alyson Ngonyama)

executable = compiler

extern_lib = lib.a

extern_dir = alylibc/

source_files =  parser.c first_and_follow.c open_files.c token_control.c \
		lexer.c lexer_utils.c lexer_token_types.c main.c \
		hashtable.c parser_datatype.c parser_symbols.c symbol.c \
		parser_group_tokens.c parser_assign.c parser_loops.c \
                parser_if.c parser_index.c

object_files = $(source_files:.c=.o)

source_dir = src/

object_dir = obj/

sources = $(addprefix $(source_dir), $(source_files))

lib = $(addprefix $(extern_dir), $(extern_lib))

objects = $(addprefix $(object_dir), $(object_files))

compiler:
	gcc -c $(sources)
	gcc -o $(executable) $(object_files) $(lib) -lm
	mv $(object_files) $(object_dir)

all:
	make -C $(extern_dir)
	gcc -c $(sources)
	gcc -o $(executable) $(object_files) $(lib) -lm
	mv $(object_files) $(object_dir)

clean:
	make clean -C $(extern_dir)
	rm -f $(objects)
	
fclean:
	make fclean -C $(extern_dir)
	rm -f $(objects)
	rm -f $(executable)

re: fclean all

