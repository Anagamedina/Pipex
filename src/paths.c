/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:11:27 by anamedin          #+#    #+#             */
/*   Updated: 2024/10/05 13:12:07 by anamedin         ###   ########.fr       */
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
