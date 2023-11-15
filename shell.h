#ifndef HSH_H
#define HSH_H

#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 1024

void execute_command(char *command);
void comm_exit(char *status);
void env(void);
void cd(char *directory);

#endif
