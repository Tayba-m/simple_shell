#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>


#define MAX_PATH 1024

extern char **environ;

int exec_com(char *const args[]);
void process_input(char *input_str);
char **part_input(char *input_str, int *arg_count, int *exit_status);
void exec_shell(void);
int main(void);

#endif
