#include "../../inc/pipex_bonus.h"

int	handle_here_doc(t_pipex *pipex, char *limiter)
{
	char	*line;
	int		pipe_fd[2];
	size_t	limiter_len;

	if (pipe(pipe_fd) < 0)
		return (p_error("pipe"));
	pipex->infile = pipe_fd[0];
	limiter_len = ft_strlen(limiter);
	line = get_next_line(0);
	while (line)
	{
		// Check if line starts with limiter and is followed by a newline or is exactly the limiter
		if ((ft_strncmp(line, limiter, limiter_len) == 0 && 
			(line[limiter_len] == '\n' || line[limiter_len] == '\0')))
		{
			free(line);
			break;
		}
		ft_putstr_fd(line, pipe_fd[1]);
		free(line);
		line = get_next_line(0);
	}
	close(pipe_fd[1]);
	return (0);
}
