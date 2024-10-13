/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:38:11 by anamedin          #+#    #+#             */
/*   Updated: 2024/10/13 17:12:05 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// FUNCION PARA CREAR UN NUEVO COMANDO
t_cmd	*cmd_new(char *str, char **paths)
{
	t_cmd	*new;
	char	*cmd_path;

	new = malloc(sizeof(t_cmd));
	if (!new)
	{
		perror("Error: malloc failed");
		return (NULL);
	}
	new->cmd_args = ft_split(str, ' ');
	if (!new->cmd_args)
	{
		perror("Error: ft_split failed");
		free(new);
		return (NULL);
	}
	//-----------------------------------------------------------
	// verificacion si arcvio existe y comando
	if (access(new->cmd_args[0], F_OK) == -1)
	{
		perror("Error: Command not found F_OK ");
//		free_split_result(new->cmd_args);
		free(new);
		return (NULL);
	}
	if (access(new->cmd_args[0], X_OK) == -1)
	{
		perror("Error: Permission denied  X_OK");
//		free_split_result(new->cmd_args);
		free(new);
		return (NULL);
	}
	//-----------------------------------------------------------
	cmd_path = get_cmd_path(new->cmd_args[0], paths);
	if (!cmd_path)
	{
		perror("Error: Command not found hereee");
//		free_split_result(new->cmd_args);
		free(new);
		return (NULL);
	}
	printf("Command path found: %s\n", cmd_path);
	free(new->cmd_args[0]);
	new->cmd_args[0] = cmd_path;
	new->next = NULL;
	return (new);
}

t_cmd	*create_cmd_list(t_pipex *pipex)
{
	t_cmd	*first;
	t_cmd	*cmd;
	t_cmd	*new;
	int		i;

	i = 0;
	first = cmd_new(pipex->argvs[2], pipex->path);
	if (!first)
		return (NULL);
	first->cmd_id = 2;
	cmd = first;
	while (i < pipex->cmd_count - 1)
	{
		new = cmd_new(pipex->argvs[3 + i], pipex->path);
		new->cmd_id = i + 3;
		cmd->next = new;
		cmd = new;
		i++;
	}
	return (first);
}

char	**get_path(char **env)
{
	char	**paths;
	char	*path_var;
	int		i;

	paths = NULL;
	path_var = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_var = ft_strdup(env[i] + 5);
			break ;
		}
		i++;
	}
	if (path_var)
	{
		paths = ft_split(path_var, ':');
		free(path_var);
	}
	return (paths);
}

/******************function principal *********************/
t_pipex	init_pipex(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	pipex.cmd_count = (argc - 3);
	pipex.argvs = argv;
	pipex.input_fd = open(argv[1], O_RDONLY);
	if (pipex.input_fd == -1)
	{
		perror("Error: Cannot open INPUT file");
		exit(EXIT_FAILURE);
	}
	pipex.output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex.output_fd == -1)
	{
		perror("Error: Cannot open OUTPUT file");
		close(pipex.input_fd);
		exit(EXIT_FAILURE);
	}
	pipex.env = env;
	pipex.path = get_path(env);
	pipex.first_cmd = create_cmd_list(&pipex);
	return (pipex);
}
