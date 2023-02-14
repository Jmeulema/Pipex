/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeulema <jmeulema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 15:31:22 by mlazzare          #+#    #+#             */
/*   Updated: 2023/02/14 12:03:11 by jmeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/pipex.h"

int	free_arr(char **path)
{
	int	i;

	i = 0;
	while (path[i])
		free(path[i++]);
	if (path)
		free(path);
	return (0);
}

// void	free_cmd_path(t_cmd *c)
// {
// 	free (c->cmd_path);
// }

void	free_struct(t_cmd *c)
{
	int	i;

	i = 0;
	printf("ready%s\n", c->cmd_path);
	if (c->cmd)
		free (c->cmd);
	printf("1%s\n", c->cmd_path);
	// free (c->cmd_path);
	free_arr(c->path);
	printf("2%s\n", c->cmd_path);
	while (c->args[i])
		free (c->args[i++]);
	printf("fail%s\n", c->cmd_path);
}

void	free_all(t_cmd *a, t_cmd *b)
{
	free_struct(a);
	free_struct(b);
}

void	error_cmd_msg(char *c)
{
	write(2, c, ft_strlen(c));
	write(2, ": ", 2);
	write(2, "command not found\n", 18);
}
