/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:43:03 by acaes             #+#    #+#             */
/*   Updated: 2025/03/24 15:43:03 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

static int	check_command(t_pipex *pipex, int i)
{
	if (!pipex->cmds[i] || !pipex->cmds[i][0] || pipex->cmds[i][0][0] == '\0')
	{
		ft_putstr_fd("Error: Empty command\n", 2);
		return (1);
	}
	if (!pipex->cmd_paths[i])
	{
		ft_putstr_fd("Command not found: ", 2);
		if (pipex->cmds[i][0])
			ft_putstr_fd(pipex->cmds[i][0], 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (0);
}

static void	exit_child(t_pipex *pipex, int exit_code)
{
	if (pipex->infile >= 0)
		close(pipex->infile);
	if (pipex->outfile >= 0)
		close(pipex->outfile);
	close_pipes(pipex);
	free_pipex(pipex);
	if (pipex->env_path)
		free_env_path(pipex->env_path);
	exit(exit_code);
}

void	child_process(t_pipex *pipex, int i, char **envp)
{
	setup_stdin(pipex, i);
	setup_stdout(pipex, i);
	close_pipes(pipex);
	if (check_command(pipex, i) != 0)
		exit_child(pipex, 127);
	if (execve(pipex->cmd_paths[i], pipex->cmds[i], envp) < 0)
	{
		ft_putstr_fd("Error: execve", 2);
		exit_child(pipex, 127);
	}
}
