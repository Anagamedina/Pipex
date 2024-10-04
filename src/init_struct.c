/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:38:11 by anamedin          #+#    #+#             */
/*   Updated: 2024/10/04 23:37:58 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char *get_cmd_path(char *cmd, char **paths)
{
    char *cmd_path;
    char *full_path;
    int i;

    i = 0;
    while (paths[i])
    {
        full_path = ft_strjoin(paths[i], "/"); // Concatenar la ruta y "/"
        cmd_path = ft_strjoin(full_path, cmd); // Concatenar el comando
        free(full_path); // Liberar la memoria usada para concatenar "/"

        if (access(cmd_path, X_OK) == 0) // Comprobar si el comando es accesible
            return (cmd_path); // Devolver la ruta completa del comando

        free(cmd_path); // Liberar la memoria si no es accesible
        i++;
    }
    return (NULL); // Retorna NULL si no se encontró el comando
}




//FUNCION PARA CREAR UN NUEVO COMANDO 
t_cmd	*cmd_new(char *str) //t_pipex *pipex)
{
	t_cmd	*new;
	char 	*cmd_path;

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

	// Obtener la ruta del comando
        cmd_path = get_cmd_path(cmd->argvs[0], pipex->path);
        if (!cmd_path)
        {
            perror("Error: Command not found");
            exit(EXIT_FAILURE);
        }

        printf("Trying to execute: %s\n", cmd_path);
        if (execve(cmd_path, cmd->argvs, pipex->env) == -1)
        {
            perror("Error: Command execution failed");
            free(cmd_path);
            exit(EXIT_FAILURE);
        }
        free(cmd_path);
	new->next = NULL;//establecer que no hay comando por ahora 
	return(new);


}


t_cmd	*create_cmd_list(t_pipex *pipex)
{
	t_cmd	*first;
	t_cmd	*cmd;
	t_cmd	*new;
	int		i;

	i = 0;
	first = cmd_new(pipex->argvs[2]);
	if (!first)
		return (NULL);
	first->num = 2;
	cmd = first;

	while(i < pipex->cmd_count - 1)
	{
		new = cmd_new(pipex->argvs[3 + i]);
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


void print_paths(char **paths)
{
	int i = 0;
	if(paths == NULL)
	{
		printf("NO paths found. \n");
		return;
	}
	while(paths[i])
	{
		printf("path[%d]: %s\n", i, paths[i]);
		i++;
	}
}

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


/******************function principal *********************/


t_pipex	init_pipex(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	pipex.cmd_count = argc - 3;
	pipex.argvs = argv;
	pipex.input_fd = open(argv[1], O_RDONLY);
	if (pipex.input_fd == -1)
		perror("Error: Cannot open INPUT file");
	pipex.output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex.output_fd == -1)
		perror("Error: Cannot open OUTPUT file");
	pipex.env = env;
	pipex.path = get_path(env);
	// print_paths(pipex.path);
	pipex.first_cmd = create_cmd_list(&pipex);

	return (pipex);
}

