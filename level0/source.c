#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    char *shell;
    char *args[2];
    int  gid;
    int  uid;

    if (atoi(argv[1]) == 0x1a7)
    {
        shell = strdup("/bin/sh");
        args[0] = shell;
        args[1] = NULL;
        gid = getegid();
        uid = geteuid();
        setresgid(gid, gid, gid);
        setresuid(uid, uid, uid);
        execv(shell, args);
    }
    else
        fwrite("No !\n", 1, 5, stdout);
    return (0);
}