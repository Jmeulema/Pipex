/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeulema <jmeulema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 15:31:22 by mlazzare          #+#    #+#             */
/*   Updated: 2023/01/26 20:32:21 by jmeulema         ###   ########.fr       */
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
	error_cmd_msg(s);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	int	fd1;
	int	fd2;

	if (ac > 5)
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
