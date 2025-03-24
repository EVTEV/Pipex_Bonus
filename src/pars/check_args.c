/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:46:40 by acaes             #+#    #+#             */
/*   Updated: 2025/03/24 15:46:40 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

int	check_args(int ac, char **av)
{
	if (ft_strncmp(av[1], HERE_DOC, ft_strlen(HERE_DOC)) == 0)
	{
		if (ac < 6)
			return (p_error("Error: Not enough arguments for here_doc"));
	}
	else if (ac < 5)
		return (p_error("Error: Invalid number of arguments"));
	return (0);
}

char	*find_cmd_path(char *cmd, char **env_path)
{
	char	*part_path;
	char	*cmd_path;
	int		i;

	if (!env_path)
		return (NULL);
	if (ft_strchr(cmd, '/') && access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	i = 0;
	while (env_path[i])
	{
		part_path = ft_strjoin(env_path[i], "/");
		cmd_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char	**get_env_path(char **envp)
{
	char	*path_var;
	char	**path;
	int		i;

	path_var = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_var = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!path_var)
		return (NULL);
	path = ft_split(path_var, ':');
	return (path);
}
