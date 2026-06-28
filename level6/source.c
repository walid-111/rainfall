#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void m(void *param_1, int param_2, char *param_3, int param_4, int param_5)
{
    puts("Nope");
}

void n(void)
{
    system("/bin/cat /home/user/level7/.pass");
}

int main(int argc, char **argv)
{
    char *buffer;
    void (**function_ptr)(void);
    buffer = malloc(0x40);
    function_ptr = (void (**)(void))malloc(4);
    *function_ptr = (void (*)(void))m;
    strcpy(buffer, argv[1]);
    (*function_ptr)();

    return 0;
}