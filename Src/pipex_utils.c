/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeulema <jmeulema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 15:31:22 by mlazzare          #+#    #+#             */
/*   Updated: 2023/02/14 13:00:04 by jmeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/pipex.h"

int	check_empty(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] != ' ')
			return (0);
	}
	ft_putstr("Empty command", 0);
	return (1);
}

int	check_cmd(t_cmd *c)
{
	int		i;

	i = -1;
	if (access(c->cmd, X_OK) == 0)
	{
		c->cmd_access = c->cmd;
		return (1);
	}
	while (c->path[++i])
	{
		c->cmd_path = ft_strjoin(c->path[i], c->cmd);
		if (!c->cmd_path)
			return (0);
		if (access(c->cmd_path, X_OK) != -1)
		{
			return (1);
		}
		free(c->cmd_path);
	}
	error_cmd_msg(c->cmd);
	return (0);
}

static void	child_one(int *pipefd, t_cmd *c, char **envp)
{
	int		i;

	i = -1;
	if (dup2(c->fd, STDIN_FILENO) < 0 || dup2(pipefd[1], STDOUT_FILENO) < 0)
		return (perror("Child One"));
	close(pipefd[0]);
	if (c->cmd_path)
	{
		if (execve(c->cmd_path, c->args, envp))
			ft_putstr(strerror(errno), 0);
	}
	else
	{
		if (execve(c->cmd_access, c->args, envp))
			ft_putstr(strerror(errno), 0);
	}
}

static void	child_two(int *pipefd, t_cmd *c, char **envp)
{
	int		i;

	i = -1;
	if (dup2(c->fd, STDOUT_FILENO) < 0 || dup2(pipefd[0], STDIN_FILENO) < 0)
		return (perror("Child Two"));
	close(pipefd[1]);
	if (c->cmd_path)
	{
		if (execve(c->cmd_path, c->args, envp) == -1)
			ft_putstr(strerror(errno), 0);
	}
	else
	{
		if (execve(c->cmd_access, c->args, envp) == -1)
			ft_putstr(strerror(errno), 0);
	}
}

void	exec_cmd(t_cmd *cmd1, t_cmd *cmd2, char **envp)
{
	int		status;
	int		pipefd[2];
	pid_t	pid_1;
	pid_t	pid_2;

	status = 0;
	pipe(pipefd);
	pid_1 = fork();
	if (pid_1 < 0)
		return (perror("Fork One"));
	if (!pid_1)
		child_one(pipefd, cmd1, envp);
	pid_2 = fork();
	if (pid_2 < 0)
		return (perror("Fork Two"));
	if (!pid_2)
		child_two(pipefd, cmd2, envp);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
}	
