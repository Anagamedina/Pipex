/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 22:45:27 by anamedin          #+#    #+#             */
/*   Updated: 2024/09/28 22:45:29 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void free_cmd(t_cmd *cmd)
{
	int i;

	if (cmd)
	{
		// Liberar cada string dentro del array de argumentos
		if (cmd->argvs)
		{
			i = 0;
			while (cmd->argvs[i])
			{
				free(cmd->argvs[i]);
				i++;
			}
			// Liberar el propio array de argumentos
			free(cmd->argvs);
		}
		// Liberar el propio nodo de la lista
		free(cmd);
	}
}

void free_cmd_list(t_cmd *cmd_list)
{
	t_cmd *tmp;

	// Recorrer la lista de comandos y liberar cada nodo
	while (cmd_list)
	{
		tmp = cmd_list->next;
		free_cmd(cmd_list);
		cmd_list = tmp;
	}
}

void free_pipex(t_pipex *pipex)
{
	int i;

	// Liberar el array de rutas del PATH
	if (pipex->path)
	{
		i = 0;
		while (pipex->path[i])
		{
			free(pipex->path[i]);
			i++;
		}
		free(pipex->path);
	}

	// Liberar la lista de comandos
	if (pipex->first_cmd)
		free_cmd_list(pipex->first_cmd);
}
