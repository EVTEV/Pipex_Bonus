#include "../../inc/pipex_bonus.h"

int	handle_here_doc(t_pipex *pipex, char *limiter)
{
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		return (p_error("pipe"));
	pipex->infile = pipe_fd[0];
	line = get_next_line(0);
	while (line && ft_strncmp(line, limiter, ft_strlen(limiter)) != 0)
	{
		ft_putstr_fd(line, pipe_fd[1]);
		free(line);
		line = get_next_line(0);
	}
	if (line)
		free(line);
	close(pipe_fd[1]);
	return (0);
}
