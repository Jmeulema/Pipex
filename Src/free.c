/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeulema <jmeulema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 15:31:22 by mlazzare          #+#    #+#             */
/*   Updated: 2023/02/14 13:18:45 by jmeulema         ###   ########.fr       */
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

void	free_struct(t_cmd *c)
{
	int	i;

	i = 0;
	if (c->cmd)
		free (c->cmd);
	if (c->cmd_path)
		free (c->cmd_path);
	if (c->path)
		free_arr(c->path);
	while (c->args[i])
		free (c->args[i++]);
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
