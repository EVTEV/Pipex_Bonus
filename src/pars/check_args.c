
#include "../../inc/pipex_bonus.h"

int	check_infile(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
		return (p_error("Error\n Invalid infile\n"));
	close(fd);
	return (0);
}

int	check_args(int ac, char **av)
{
	if (ft_strncmp(av[1], HERE_DOC, ft_strlen(HERE_DOC)) == 0)
	{
		if (ac < 6)
			return (p_error("Error\n Invalid number of arguments for here_doc\n"));
	}
	else if (ac < 5)
		return (p_error("Error\n Invalid number of arguments\n"));
	return (0);
}
