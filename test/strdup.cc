#define ZPL_IMPLEMENTATION
#include <zpl.h>

int main()
{
    char *foo = "hello world";

    //NOTE: length of a string + 1 extra byte for null terminator.
    isize len = strlen(foo) + 1;
    
    char *bar = zpl_strdup(zpl_heap(), foo, len);
    zpl_printf("%s == %s\n", foo, bar);
    return 0;
}

