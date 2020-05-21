

#include "../inc/compiler.h"

void    init_datatypes(void)
{
    extern struct s_datatype  datatypes[13];
    extern char               reserved;
    int counter;

    // normal stuff
    datatypes[0].name = "char"; datatypes[0].size = 1;
    datatypes[1].name = "unsigned char"; datatypes[1].size = 1;
    datatypes[2].name = "signed char"; datatypes[2].size = 1;
    datatypes[3].name = "int"; datatypes[3].size = 4;
    datatypes[4].name = "unsigned int"; datatypes[4].size = 4;
    datatypes[5].name = "short"; datatypes[5].size = 2;
    datatypes[6].name = "unsigned short"; datatypes[6].size = 2;
    datatypes[7].name = "long"; datatypes[7].size = 8;
    datatypes[8].name = "unsigned long"; datatypes[8].size = 8;

    // floats
    datatypes[9].name = "float"; datatypes[9].size = 4;
    datatypes[10].name = "double"; datatypes[10].size = 8;
    datatypes[11].name = "long double"; datatypes[11].size = 10;
    
    // forgot about this
    datatypes[12].name = "void"; datatypes[12].size = 1;

}


