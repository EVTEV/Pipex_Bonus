#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../Libft/inc/libft.h"
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>

# define HERE_DOC "here_doc"

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		**pipes;
	pid_t	*pids;
	char	**env_path;
	char	***cmds;
	char	**cmd_paths;
	int		cmd_count;
	int		pipe_count;
	int		here_doc;
	char	*limiter;
}	t_pipex;

/* Parse */
int		check_args(int ac, char **av);
char	*find_cmd_path(char *cmd, char **env_path);
char	**get_env_path(char **envp);

/* Pipe */
void	create_pipes(t_pipex *pipex);
void	close_pipes(t_pipex *pipex);
void	free_pipex(t_pipex *pipex);
void	free_env_path(char **env_path);
void	free_cmds(char ***cmds, int cmd_count);

/* Exec */
void	child_process(t_pipex *pipex, int i, char **envp);
int		init_command(t_pipex *pipex, int ac, char **av);
int		exec_command(t_pipex *pipex, char **envp);
int		my_exec(t_pipex *pipex, int ac, char **av, char **envp);

/* Here_doc */
int		handle_here_doc(t_pipex *pipex, char *limiter);

/* Utils */
void	msg_error(char *msg);
void	free_tab(char **tab);
int		p_error(char *msg);

#endif
