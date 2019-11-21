#include "ctf-common.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>   // For strtok() and strcmp()
#include <sys/wait.h> // For waitpid() and associated macros
#include <unistd.h>   // For fork(), pid_t

FILE *fd;

void read_flag() {
  char key[64];
  fgets(key, 64, fd);
  printf("Congratulations!! Take this key with you\n");
  printf("-----------------------------------------------\n");
  printf("%s", key);
  printf("-----------------------------------------------\n");
  exit(0);
}

void open_flag() {
  if (is_inside_gdb())
    fd = fopen("simple-bof.dummykey", "r");
  else
    fd = fopen("simple-bof.key", "r");

  if (fd == NULL) {
    printf("Something wrong with key file, Please contect admin\n");
    exit(0);
  }
}
void challenge() {
  char buf[16];
  printf("Enter your payload>>> ");
  fflush(stdout);
  gets(buf);
}

int main(int argc, char **argv) {
  ctf_init(ERASE_ENV | PROVIDE_GADGETS | APPLY_SECCOMP);
  challenge();

  return EXIT_SUCCESS;
}
