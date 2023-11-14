#ifndef MYHEADERS_H
#define MYHEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10

void execute_exit(void);
void execute_env(void);
void execute_cd(char **args);
int str_equal(const char *str1, const char *str2);
void execute_int_command(char **args);
char *read_command(int is_interactive);
void execute_command(char **args);
void free_args(char **args);

#endif
