#include "../../inc/pipex_bonus.h"

int	my_exec(t_pipex *pipex, int ac, char **av, char **envp)
{
	int	value;

	// Initialisation de pipex
	ft_memset(pipex, 0, sizeof(t_pipex));
	pipex->infile = -1;
	pipex->outfile = -1;
	
	// Récupération du PATH
	pipex->env_path = get_env_path(envp);
	
	// Initialisation des commandes et des pipes
	if (init_command(pipex, ac, av) != 0)
	{
		if (pipex->env_path)
			free_env_path(pipex->env_path);
		return (1);
	}
	
	// Exécution des commandes
	value = exec_command(pipex, envp);
	
	// Nettoyage des ressources
	if (pipex->infile >= 0)
		close(pipex->infile);
	if (pipex->outfile >= 0)
		close(pipex->outfile);
	
	free_pipex(pipex);
	
	if (pipex->env_path)
		free_env_path(pipex->env_path);
	
	return (value);
}
