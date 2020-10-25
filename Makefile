
# Coded by AlysonBee (Alyson Ngonyama)

executable = compiler

extern_lib = lib.a

extern_dir = alylibc/


source_files =  scope_database.c scope_stack.c semantic_analysis.c \
	semantic_else.c semantic_for.c semantic_if.c \
	semantic_variable.c structs.c \
	semantic_while.c main.c open_files.c datatype_experiment.c \
	error_list.c error_recovery.c first_and_follow.c functions.c \
	handle_csg.c hashtable.c is_valid_sum.c \
	lexer.c lexer_token_types.c lexer_utils.c token_control.c \
	typecasting.c 

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

