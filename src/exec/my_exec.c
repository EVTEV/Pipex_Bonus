#include "../../inc/pipex_bonus.h"

int	my_exec(t_pipex *pipex, int ac, char **av, char **envp)
{
	int	value;

	ft_memset(pipex, 0, sizeof(t_pipex));
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->env_path = get_env_path(envp); //fonction qui récupère le PATH
	if (init_command(pipex, ac, av) != 0) //initialisation des commandes et des pipes
	{
		if (pipex->env_path)
			free_env_path(pipex->env_path);
		return (1);
	}
	value = exec_command(pipex, envp); //exécution des commandes
	if (pipex->outfile_error)
		value = 1;
	free_pipex(pipex);
	if (pipex->env_path)
		free_env_path(pipex->env_path);
	return (value);
}
