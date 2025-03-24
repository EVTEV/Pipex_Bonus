/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:46:29 by acaes             #+#    #+#             */
/*   Updated: 2025/03/24 15:46:29 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

int	setup_here_doc(t_pipex *pipex, char **av)
{
	pipex->here_doc = 1;
	pipex->limiter = av[2];
	if (handle_here_doc(pipex, pipex->limiter) != 0)
		return (1);
	pipex->outfile = open(av[pipex->cmd_count + 3],
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (pipex->outfile < 0)
	{
		perror(av[pipex->cmd_count + 3]);
		pipex->outfile_error = 1;
	}
	return (0);
}

int	setup_files(t_pipex *pipex, char **av)
{
	if (pipex->here_doc)
		return (setup_here_doc(pipex, av));
	pipex->infile = open(av[1], O_RDONLY);
	if (pipex->infile < 0)
		perror(av[1]);
	pipex->outfile = open(av[pipex->cmd_count + 2],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile < 0)
	{
		perror(av[pipex->cmd_count + 2]);
		pipex->outfile_error = 1;
	}
	return (0);
}
