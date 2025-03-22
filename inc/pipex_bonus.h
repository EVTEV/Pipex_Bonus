#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../Libft/inc/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

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
}			t_pipex;

//-----------Parse-----------//
//-----check_args.c-----//
int			check_args(int ac, char **av);
char		*find_cmd_path(char *cmd, char **env_path);
char		**get_env_path(char **envp);
//-----parse_commands.c-----//
int			parse_commands(t_pipex *pipex, char **av);

//-----------Pipe-----------//
//-----setup_pipe.c-----//
void		create_pipes(t_pipex *pipex);
void		close_pipes(t_pipex *pipex);
//-----free_resources.c-----//
void		free_pipex(t_pipex *pipex);
void		free_env_path(char **env_path);
void		free_cmds(char ***cmds, int cmd_count);

//----------child----------//
//-----child_process.c-----//
void		child_process(t_pipex *pipex, int i, char **envp);
//-----setup_io.c-----//
void		setup_stdin(t_pipex *pipex, int i);
void		setup_stdout(t_pipex *pipex, int i);

//-----------Exec-----------//
//-----init_command.c-----//
int			init_command(t_pipex *pipex, int ac, char **av);
//-----exec_command.c-----//
int			exec_command(t_pipex *pipex, char **envp);
//-----my_exec.c-----//
int			my_exec(t_pipex *pipex, int ac, char **av, char **envp);

//-----------Here_doc-----------//
//-----handle_here_doc.c-----//
int			handle_here_doc(t_pipex *pipex, char *limiter);

//-----------Utils-----------//
//-----utils.c-----//
void		msg_error(char *msg);
void		free_tab(char **tab);
int			p_error(char *msg);
int			get_exit_status(int status);
//-----setup_files.c-----//
int			setup_here_doc(t_pipex *pipex, char **av);
int			setup_files(t_pipex *pipex, char **av);

#endif
