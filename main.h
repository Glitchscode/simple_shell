#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>

char *get_file_path(char *file_name);
char *get_file_loc(char *path, char *file_name);
int startsWithForwardSlash(const char *str);
void prompt(void);
char *input(void);
void execute_command(char *input, char *argv[], char **env);
int tokenize_input(char *input, char *args[]);
int handle_builtin_commands(char **args,
			    int num_args, char *input, char **env);
void print_env(char **env);
void handle_exit(char *input, int exit_status);
int shell_exit(char **args, char *input);
void handle_cd(char **args, int num_args);
#endif /* MAIN_H */
