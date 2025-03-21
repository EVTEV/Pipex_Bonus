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
	ft_putstr_fd("heredoc> ", 1); // Prompt pour indiquer l'attente d'entrée
	line = get_next_line(0);
	
	while (line)
	{
		// Vérifier si la ligne commence par limiter et est suivie d'un newline ou est exactement limiter
		if ((ft_strncmp(line, limiter, limiter_len) == 0 && 
			(line[limiter_len] == '\n' || line[limiter_len] == '\0')))
		{
			free(line);
			break;
		}
		
		if (write(pipe_fd[1], line, ft_strlen(line)) < 0)
		{
			free(line);
			close(pipe_fd[1]);
			return (p_error("write"));
		}
		
		free(line);
		ft_putstr_fd("heredoc> ", 1); // Prompt pour indiquer l'attente d'entrée
		line = get_next_line(0);
		
		// Si get_next_line échoue pour une raison autre que EOF
		if (!line && errno != 0)
		{
			close(pipe_fd[1]);
			return (p_error("get_next_line"));
		}
	}
	
	close(pipe_fd[1]);
	return (0);
}
