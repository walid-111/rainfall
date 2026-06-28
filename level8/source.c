#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *auth = NULL;
char *service = NULL;

int main(void)
{
  char line[128];
  while (1)
  {
      printf("%p, %p \n", auth, service);
      if (fgets(line, 0x80, stdin) == NULL)
          return 0;
      if (strncmp(line, "auth ", 5) == 0)
      {
          auth = malloc(4);
          auth[0] = '\0';
          auth[1] = '\0';
          auth[2] = '\0';
          auth[3] = '\0';
          if (strlen(line + 5) < 0x1f)
              strcpy(auth, line + 5);
      }
      if (strncmp(line, "reset", 5) == 0)
      {
          free(auth);
      }
      if (strncmp(line, "service", 6) == 0)
      {
          service = strdup(line + 8);
      }
      if (strncmp(line, "login", 5) == 0)
      {
          if (*(int *)(auth + 0x20) == 0)
              fwrite("Password:\n", 1, 10, stdout);
          else
              system("/bin/sh");
      }
  }
}