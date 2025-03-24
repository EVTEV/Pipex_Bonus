/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:47:31 by acaes             #+#    #+#             */
/*   Updated: 2025/03/24 15:47:31 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

static int	allocate_pipes(t_pipex *pipex)
{
	pipex->pipes = (int **)malloc(sizeof(int *) * pipex->pipe_count);
	if (!pipex->pipes)
		return (1);
	return (0);
}

static int	create_single_pipe(t_pipex *pipex, int i)
{
	pipex->pipes[i] = (int *)malloc(sizeof(int) * 2);
	if (!pipex->pipes[i])
		return (1);
	if (pipe(pipex->pipes[i]) < 0)
	{
		free(pipex->pipes[i]);
		p_error("pipe");
	}
	return (0);
}

static void	cleanup_pipes(t_pipex *pipex, int i)
{
	while (--i >= 0)
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		free(pipex->pipes[i]);
	}
	free(pipex->pipes);
	pipex->pipes = NULL;
}

void	create_pipes(t_pipex *pipex)
{
	int	i;

	if (pipex->pipe_count <= 0)
	{
		pipex->pipes = NULL;
		return ;
	}
	if (allocate_pipes(pipex) != 0)
		return ;
	i = 0;
	while (i < pipex->pipe_count)
	{
		if (create_single_pipe(pipex, i) != 0)
		{
			cleanup_pipes(pipex, i);
			return ;
		}
		i++;
	}
}

void	close_pipes(t_pipex *pipex)
{
	int	i;

	if (!pipex->pipes)
		return ;
	i = 0;
	while (i < pipex->pipe_count)
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		i++;
	}
}
