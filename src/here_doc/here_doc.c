#include "../../inc/pipex_bonus.h"

static int	setup_here_doc_pipe(int pipe_fd[2], int *infile)
{
	if (pipe(pipe_fd) < 0)
		return (p_error("pipe"));
	*infile = pipe_fd[0];
	return (0);
}

static int	process_line(int pipe_fd[1], char *line, char *limiter,
		size_t limiter_len)
{
	if ((ft_strncmp(line, limiter, limiter_len) == 0 &&
			(line[limiter_len] == '\n' || line[limiter_len] == '\0')))
	{
		free(line);
		return (1);
	}
	if (write(pipe_fd[1], line, ft_strlen(line)) < 0)
	{
		free(line);
		close(pipe_fd[1]);
		return (p_error("write"));
	}
	free(line);
	return (0);
}

static int	read_here_doc_input(int pipe_fd[2], char *limiter,
		size_t limiter_len)
{
	char	*line;
	int		result;

	ft_putstr_fd("heredoc> ", 1);
	line = get_next_line(0);
	while (line)
	{
		result = process_line(pipe_fd, line, limiter, limiter_len);
		if (result != 0)
			return (result > 0 ? 0 : result);
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
		if (!line && errno != 0)
		{
			close(pipe_fd[1]);
			return (p_error("get_next_line"));
		}
	}
	return (0);
}

int	handle_here_doc(t_pipex *pipex, char *limiter)
{
	int		pipe_fd[2];
	size_t	limiter_len;
	int		result;

	if (setup_here_doc_pipe(pipe_fd, &pipex->infile) != 0)
		return (1);
	limiter_len = ft_strlen(limiter);
	result = read_here_doc_input(pipe_fd, limiter, limiter_len);
	close(pipe_fd[1]);
	return (result);
}
