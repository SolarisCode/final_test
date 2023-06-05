#include "../../includes/minishell.h"

int ft_check_n(char *s)
{
	int i;

	i = 1;
	if (s[0] != '-')
		return (1);
	if (s[0] == '-')
	{
		while (s[i])
		{
			if (s[i] != 'n')
				return (1);
			i++;
		}
	}
	return 0;
}

int redirect_echo(t_cmds *cmd, int fd)
{
	int i;
	int	flag;

	i = 0;
	flag = 0;
	if (cmd->redirect & OUTPUT)
		flag |= O_TRUNC;
	else if (cmd->redirect & APPEND)
		flag |= O_APPEND;
	if (!cmd->to_file)
		return (1);
	while (cmd->to_file[i])
		i++;
	const char* filename = cmd->to_file[i - 1];
	fd = open(filename, O_WRONLY | O_CREAT | flag, 0666);
	if (fd == -1)
	{
		perror("Error opening the file\n");
		return 2;
	}
	return (fd);
}

void ft_echo(t_cmds *node)
{
	int i;
	int check_n;
	int fd;

	i = 0;
	fd = 0;
	check_n = 0;
	fd = redirect_echo(node, fd);
	if (fd == 2)
		return;
	if (!node->args)
	{
		ft_putstr_fd("\n", fd);
		return;
	}
	if (ft_check_n(node->args[i]) == 0)
		check_n = 1;
	while (ft_check_n(node->args[i]) == 0)
			i++;
	while (node->args[i])
	{
		ft_putstr_fd(node->args[i], fd);
		if (node->args[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (check_n == 0)
		ft_putstr_fd("\n", fd);
}
