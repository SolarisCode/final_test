#include "minishell.h"

void ft_exit()
{
	int pid;

	pid = fork();
	if (pid == 0)
		exit(0);
}
