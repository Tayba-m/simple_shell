#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

extern char **environ;

// Function to execute shell commands
void processCommand(char *command) {
  char **argv = NULL;
  int argc = 0;

  // Split the command into arguments
  char *token = strtok(command, " ");
  while (token != NULL) {
    argv = realloc(argv, (argc + 1) * sizeof(char *));
    argv[argc] = strdup(token);
    argc++;
    token = strtok(NULL, " ");
  }

  // Check if the command is a built-in command
  if (strcmp(argv[0], "exit") == 0) {
    exit(0);
  } else if (strcmp(argv[0], "cd") == 0) {
    if (argc == 2) {
      chdir(argv[1]);
    } else {
      printf("Usage: cd <path>\n");
    }
  } else {
    // Execute the command
    int pid = fork();
    if (pid == 0) {
      if (execve(argv[0], argv, environ) == -1) {
        perror("execve");
        exit(1);
      }
    } else {
      waitpid(pid, NULL, 0);
    }
  }

  // Free the memory allocated for the arguments
  for (int i = 0; i < argc; i++) {
    free(argv[i]);
  }
  free(argv);
}

void handleUserInput() {
  char *buffer = NULL;
  size_t bufferSize = 0;
  ssize_t bytesRead;

  while (1) {
    if (isatty(fileno(stdin))) {
      printf("shell> ");
    }

    bytesRead = getline(&buffer, &bufferSize, stdin);

    if (bytesRead == -1) {
      break;
    }

    if (!strcmp(buffer, "exit")) {
      break;
    }

    char *commentPos = strchr(buffer, '#');
    if (commentPos != NULL) {
      *commentPos = '\0';
    }

    if (!strlen(buffer)) {
      continue;
    }

    processCommand(buffer);

    free(buffer);
    buffer = NULL;
    bufferSize = 0;
  }

  if (buffer) {
    free(buffer);
  }
}

int main() {
  handleUserInput();
  return 0;
}
