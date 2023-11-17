#include "shell.h"

char** part_input(char* input_str, int* arg_count, int* exit_status) {
    char* token;
    char** args = NULL;
    *arg_count = 0;

    token = strtok(input_str, " ");
    while (token != NULL) {
        if (strcmp(token, "$?") == 0) {
            char exit_status_str[4];
            snprintf(exit_status_str, sizeof(exit_status_str), "%d", *exit_status);
            args = realloc(args, (*arg_count + 1) * sizeof(char*));
            args[*arg_count] = strdup(exit_status_str);
        } else {
            if (strcmp(token, "$$") == 0) {
                char pid_str[10];
                snprintf(pid_str, sizeof(pid_str), "%d", getpid());
                args = realloc(args, (*arg_count + 1) * sizeof(char*));
                args[*arg_count] = strdup(pid_str);
            } else {
                args = realloc(args, (*arg_count + 1) * sizeof(char*));
                args[*arg_count] = strdup(token);
            }
        }
        (*arg_count)++;
        token = strtok(NULL, " ");
    }

    return args;
}

void process_input(char* input_str) {
    char** args = NULL;
    int arg_count = 0;
    int exit_status = -1;
    int i;

    args = part_input(input_str, &arg_count, &exit_status);

    if (arg_count > 0) {
        args = realloc(args, (arg_count + 1) * sizeof(char*));
        args[arg_count] = NULL;
        exit_status = exec_com(args);
        i = 0;

        while (i <= arg_count) {
            free(args[i]);
            i++;
        }
        free(args);
        args = NULL;
        arg_count = 0;
    }
}
