/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 22:45:27 by anamedin          #+#    #+#             */
/*   Updated: 2024/10/04 12:24:19 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void free_cmd(t_cmd *cmd)
{
	int i;

	if (cmd)
	{
		if (cmd->argvs)
		{
			i = 0;
			while (cmd->argvs[i])
			{
				free(cmd->argvs[i]);
				i++;
			}
			free(cmd->argvs);
		}
		free(cmd);
	}
}

void free_cmd_list(t_cmd *cmd_list)
{
	t_cmd *tmp;

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

	if (pipex->first_cmd)
		free_cmd_list(pipex->first_cmd);
}
