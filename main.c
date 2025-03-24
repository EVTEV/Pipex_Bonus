#include "inc/pipex_bonus.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac < 5)
	{
		if (ac >= 2 && ft_strncmp(av[1], HERE_DOC, ft_strlen(HERE_DOC)) == 0)
			ft_putstr_fd("Usage: ./pipex here_doc LIMITER cmd1 cmd2 file\n", 2);
		else
			ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 ... cmdn file2\n", 2);
		return (1);
	}
	
	// Additional validation for here_doc mode
	if (ac >= 6 && av[1] && ft_strncmp(av[1], HERE_DOC, ft_strlen(HERE_DOC)) == 0)
	{
		if (!av[2] || !av[3] || !av[4] || !av[5])
		{
			ft_putstr_fd("Error: Invalid arguments for here_doc mode\n", 2);
			return (1);
		}
	}
	return (my_exec(&pipex, ac, av, envp));
}
