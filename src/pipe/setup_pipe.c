#include "../../inc/pipex_bonus.h"

/**
 * Initialise la structure pipex avec les arguments et l'environnement
 */
void init_pipex(t_pipex *pipex, int ac, char **av, char **envp)
{
    (void)envp; // Pour éviter l'avertissement de paramètre non utilisé
    
    // Initialiser la structure à zéro
    pipex->infile = -1;
    pipex->outfile = -1;
    pipex->cmd_count = 0;
    pipex->pipe_count = 0;
    pipex->pipes = NULL;
    pipex->cmds = NULL;
    pipex->pids = NULL;
    pipex->here_doc = 0;
    pipex->limiter = NULL;
    pipex->env_path = NULL;
    pipex->cmd_paths = NULL;

    // Vérifier si on est en mode here_doc
    if (ac > 1 && !ft_strncmp(av[1], HERE_DOC, ft_strlen(HERE_DOC)))
    {
        pipex->here_doc = 1;
        pipex->limiter = av[2];
        pipex->cmd_count = ac - 4; // Ajuster le compte pour here_doc
        pipex->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    }
    else
    {
        pipex->cmd_count = ac - 3; // Cas normal
        pipex->infile = open(av[1], O_RDONLY);
        pipex->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }

    // Initialiser le nombre de pipes
    pipex->pipe_count = pipex->cmd_count - 1;
    
    // Initialiser les commandes
    if (!init_command(pipex, ac, av))
    {
        free_pipex(pipex);
        exit(1);
    }

    // Créer les pipes
    create_pipes(pipex);
}
/**
 * Libère toutes les ressources allouées dans la structure pipex
 */
void free_pipex(t_pipex *pipex)
{
    // Fermer les descripteurs de fichiers
    if (pipex->infile != -1)
        close(pipex->infile);
    if (pipex->outfile != -1)
        close(pipex->outfile);

    // Fermer et libérer les pipes
    close_pipes(pipex);
    if (pipex->pipes)
        free(pipex->pipes);

    // Libérer les commandes
    if (pipex->cmds)
        free_cmds(pipex->cmds, pipex->cmd_count);

    // Libérer les PIDs si nécessaire
    if (pipex->pids)
        free(pipex->pids);

    // Libérer les chemins d'environnement
    if (pipex->env_path)
        free_env_path(pipex->env_path);

    // Libérer les chemins de commandes
    if (pipex->cmd_paths)
    {
        int i = 0;
        while (pipex->cmd_paths[i])
        {
            free(pipex->cmd_paths[i]);
            i++;
        }
        free(pipex->cmd_paths);
    }
}

/**
 * Libère la mémoire allouée pour les chemins d'environnement
 */
void free_env_path(char **env_path)
{
    int i;

    if (!env_path)
        return;

    i = 0;
    while (env_path[i])
    {
        free(env_path[i]);
        i++;
    }
    free(env_path);
}

/**
 * Libère la mémoire allouée pour les commandes
 */
void free_cmds(char ***cmds, int cmd_count)
{
    int i;
    int j;

    if (!cmds)
        return;

    i = 0;
    while (i < cmd_count)
    {
        if (cmds[i])
        {
            j = 0;
            while (cmds[i][j])
            {
                free(cmds[i][j]);
                j++;
            }
            free(cmds[i]);
        }
        i++;
    }
    free(cmds);
}

/**
 * Ferme tous les pipes ouverts
 */
void close_pipes(t_pipex *pipex)
{
    int i;
    int j;

    if (!pipex->pipes)
        return;

    i = 0;
    while (i < pipex->pipe_count)
    {
        j = 0;
        while (j < 2) // Chaque pipe a 2 extrémités (lecture/écriture)
        {
            close(pipex->pipes[i][j]);
            j++;
        }
        i++;
    }
}

