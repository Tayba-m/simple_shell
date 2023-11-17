#ifndef _HSH_H
#define _HSH_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_PATH 1024

extern char **environ;

int exec_com(char *const args[]);
void process_input(char *input_str);
void exec_shell(void);
int main(int argc, char *argv[]);

#endif
