#include "main.h"
/**
  * prompt - Print the prompt to the user
  */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
}

/**
  * input - Reads the input from the users
  *
  * Return: Character variable to the program
  */
char *input(void)
{
	size_t count = 0;
	char *buf = NULL;
	ssize_t nread;

	nread = getline(&buf, &count, stdin);
	if (nread ==  -1)
	{
		free(buf);
		exit(0);
	}
	return (buf);
}

/**
  * execute_command - Executes the input from the buffer
  * @input: The argument from the buffer
  * @argv: Array of argument
  * @env: Environment variables
  */

void execute_command(char *input, char *argv[], char **env)
{
	char *args[10];
	char *path, *shell_name;
	int status, num_args;
	pid_t child_pid;

	shell_name = argv[0];
	num_args = tokenize_input(input, args);

	if (num_args == 0)
		return;
	if (handle_builtin_commands(args, num_args, input, env) == 1)
		return;
	path = get_file_path(args[0]);

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error: Failed to create");
		free(input);
		exit(1);
	}

	if (child_pid == 0)
	{
		if (execve(path, args, NULL) == -1)
		{
			write(2, shell_name, strlen(shell_name));
			write(2, ": 1: ", 5);
			write(2, args[0], strlen(args[0]));
			write(2, ": not found\n", 12);
			exit(127);
		}
	}
	else
		wait(&status);

	free(path);
}

/**
  * tokenize_input - Tokenizes the input strings
  * @input: Argument input
  * @args: The array of strings
  *
  * Return: Number of the items tokenized
  */
int tokenize_input(char *input, char *args[])
{
	char *token;
	int i;

	token = strtok(input, " \n");
	i = 0;

	while (token != NULL)
	{
		args[i] = token;
		token = strtok(NULL, " \n");
		i++;
	}
	args[i] = NULL;
	return (i);
}
/**
 * main - Getline function
 * @argc: Argument count
 * @argv: Array of argument values
 * @env: Environment
 * Return: 0 on success
 */

int main(int argc, char *argv[], char **env)
{
	char *input_buffer;

	(void)argc;
	while (1)
	{
		prompt();
		input_buffer = input();
		execute_command(input_buffer, argv, env);
		free(input_buffer);
	}
	return (0);
}
