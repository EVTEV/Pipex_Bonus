#include "inc/pipex_bonus.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	ft_memset(&pipex, 0, sizeof(t_pipex));
	if (ac < 5)
	{
		if (ac >= 2 && ft_strncmp(av[1], HERE_DOC, ft_strlen(HERE_DOC)) == 0)
			ft_putstr_fd("Usage: ./pipex here_doc LIMITER cmd1 cmd2 file\n", 2);
		else
			ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 ... cmdn file2\n", 2);
		return (1);
	}
	return (my_exec(&pipex, ac, av, envp));
}
