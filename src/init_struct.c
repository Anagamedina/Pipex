/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:38:11 by anamedin          #+#    #+#             */
/*   Updated: 2024/09/28 19:25:13 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

//FUNCION PARA CREAR UN NUEVO COMANDO 
t_cmd	*cmd_new(char *str, t_pipex *pipex)
{
	t_cmd	*new;
	char	*cmd_path;

	new = malloc(sizeof(t_cmd));
	if (!new)
	{
		perror("Error: malloc failed");
		return (NULL);
	}
	//separamos la cadena del comando en argumentos
	new->argvs = ft_split(str, ' ');
	if (!new->argvs)
	{
		perror("Error: ft_split failed");
		free(new);
		return (NULL);
	}

	//comprobar si el comando es accesible 
	if (access(new->argvs[0], X_OK) != 0)
	{
		//cmd_path = get_cmd_path(new->argvs[0], pipex->path);
		//if (cmd_path == NULL || access(cmd_path, X_OK))
			//perrro("");
	}
	new->next = NULL //establecer que no hay comando por ahora 
	return(new);


}


t_cmd	*create_cmd_list(t_pipex *pipex)
{
	t_cmd	*first;
	t_cmd	*cmd;
	t_cmd	*new;
	int		i;

	i = 0;
	first = cmd_new(pipex->argvs[2], pipex);
	if (!first)
		return (NULL);
	first->num = 2;
	cmd = first;

	while(i < pipex->cmd_count - 1)
	{
		new = cmd_new(pipex->argvs[3 + i], pipex);
		new->num = i + 3;
		cmd->next = new;
		cmd = new;
		i++;
	}
	return (first);
}
/*
PATH=
/opt/homebrew/bin
:/opt/homebrew/sbin
:/usr/local/bin
:/System/Cryptexes/App/usr/bin
:/usr/bin:/bin:/usr/sbin:/sbin
:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin
:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin
:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin
:/opt/X11/bin
:/Applications/iTerm.app/Contents/Resources/utilities
:/Users/catalinaburgos/Library/Application Support/JetBrains/Toolbox/scripts
:/Users/catalinaburgos/Library/Python/3.9/bin
*/ 

char **get_path(char **env)
{
	char	**paths; //array para almacenar las rutas
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

t_pipex	init_pipex(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	pipex.cmd_count = argc - 3;
	pipex.input_fd = open(argv[1], O_RDONLY);
	if (pipex.input_fd == -1)
		perror("Error: Cannot open input file");
	pipex.output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex.output_fd == -1)
		perror("Error: Cannot open output file");
	pipex.args = argv;
	pipex.env = env;
	pipex.path = get_path(env);
	pipex.first_cmd = create_cmd_list(&pipex);

	return (pipex);
}

