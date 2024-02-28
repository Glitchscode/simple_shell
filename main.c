#include "main.h"

/**
 * main - Getline function
 * @argc: Argument count
 * @argv: Array of argument values
 *
 * Return: 0 on success
 */

int main(int argc, char **argv)
{
	(void)argc;
	char *buf = NULL, *token;
	size_t count = 0;
	ssize_t nread;
	pid_t child_pid;
	int i, status;
	char *path;

	while (1)
	{
Here:
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		nread = getline(&buf, &count, stdin);

		if (nread ==  -1)
		{
			exit(1);
		}

		if (nread == 1)
			goto Here;

		token = strtok(buf, " \n");

		argv = malloc(sizeof(char *) * 1024);
		i = 0;

		while (token != NULL)
		{
			argv[i] = token;
			token = strtok(NULL, " \n");
			i++;
		}

		argv[i] = NULL;
		path = get_file_path(argv[0]);
		child_pid = fork();

		if (child_pid == -1)
		{
			perror("Failed to create.");
			exit(41);
		}

		if (child_pid == 0)
		{
			if (execve(path, argv, NULL) == -1)
			{
				exit(97);
			}
		}
		else
		{
			wait(&status);
		}
	}
	free(path);
	free(buf);
	return (0);
}
