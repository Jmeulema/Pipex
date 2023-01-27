/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeulema <jmeulema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:34:21 by mlazzare          #+#    #+#             */
/*   Updated: 2023/01/27 12:08:20 by jmeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

# define PATH 5
# define START 6

typedef struct s_cmd
{
	char	*cmd;
	char	**path;
	char	*args[100];
	int		fd;
}	t_cmd;

/* Utils */

int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);
int		ft_putstr(char *s, char *t);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *str);

/* Free */

int		free_arr(char **path);
void	free_struct(t_cmd *c);
void	free_all(t_cmd *a, t_cmd *b);
void	error_cmd_msg(char *c);

/* pipex_utils */

void	exec_cmd(t_cmd *cmd1, t_cmd *cmd2, char **envp);
int		check_cmd(t_cmd *c);

/* split_path */

char	**ft_splitpath(char *s, char c);

/* pipex */

void	pipex(int fd1, int fd2, char **av, char **envp);

/* Main */

int		check_empty(char *s);

#endif