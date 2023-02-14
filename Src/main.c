/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeulema <jmeulema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 15:31:22 by mlazzare          #+#    #+#             */
/*   Updated: 2023/02/14 16:23:24 by jmeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/pipex.h"

static void	init_cmd(t_cmd *c, int fd)
{
	c->fd = fd;
	c->path = NULL;
	c->cmd = NULL;
	c->cmd_path = NULL;
	c->args[0] = NULL;
}

static char	**get_path(char **envp)
{
	char	**my_path;
	char	*env_path;
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", PATH))
		{
			env_path = ft_substr(envp[i], START, ft_strlen(envp[i]));
			if (!env_path)
				return (NULL);
			my_path = ft_splitpath(env_path, ':');
			if (!my_path)
			{
				free (env_path);
				return (NULL);
			}
			free (env_path);
			return (my_path);
		}
	}
	return (NULL);
}

static int	get_cmd(char **ep, t_cmd *c, char *cmd)
{
	int		i;
	char	**tmp;

	i = -1;
	c->path = get_path(ep);
	if (!c->path)
		return (0);
	tmp = ft_splitpath(cmd, ' ');
	if (!tmp)
		return (0);
	c->cmd = ft_substr(tmp[i + 1], 0, ft_strlen(tmp[i + 1]) - 1);
	if (!c->cmd)
		return (free_arr(tmp));
	while (tmp[++i])
	{
		c->args[i] = ft_substr(tmp[i], 0, ft_strlen(tmp[i]) - 1);
		if (!c->args[i])
		{
			free_arr(c->args);
			return (free_arr(tmp));
		}
	}
	c->args[i] = 0;
	free_arr(tmp);
	return (1);
}

void	pipex(int fd1, int fd2, char **av, char **envp)
{
	t_cmd	cmd1;
	t_cmd	cmd2;
	int		error;

	error = 0;
	init_cmd(&cmd1, fd1);
	init_cmd(&cmd2, fd2);
	if (!get_cmd(envp, &cmd1, av[2]) || !get_cmd(envp, &cmd2, av[3]))
	{
		free_all(&cmd1, &cmd2);
		exit(EXIT_FAILURE);
	}
	if (!check_cmd(&cmd1))
	{
		error++;
	}
	if (!check_cmd(&cmd2))
		error++;
	if (error > 0)
		exit(EXIT_FAILURE);
	exec_cmd(&cmd1, &cmd2, envp);
	free_all(&cmd1, &cmd2);
}

int	main(int ac, char **av, char **envp)
{
	int	fd1;
	int	fd2;

	if (ac != 5)
		return (ft_putstr("Invalid number of arguments.", 0));
	if (check_empty(av[2]) || check_empty(av[3]))
		return (1);
	fd1 = open(av[1], O_RDONLY);
	fd2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd1 < 0)
		return (ft_putstr(strerror(errno), av[1]));
	if (fd2 < 0)
		return (ft_putstr(strerror(errno), av[4]));
	pipex(fd1, fd2, av, envp);
	if (close(fd1) < 0 || close(fd2) < 0)
		return (ft_putstr(strerror(errno), 0));
	return (0);
}
