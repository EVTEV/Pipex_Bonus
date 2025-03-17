
#include "../../inc/pipex_bonus.h"

void	msg_error(char *msg)
{
	perror(msg);
	exit(1);
}

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	p_error(char *msg)
{
	perror(msg);
	return (1);
}
