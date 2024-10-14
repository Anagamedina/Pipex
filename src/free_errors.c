/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 22:45:27 by anamedin          #+#    #+#             */
/*   Updated: 2024/10/14 10:41:59 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		free_split_result(cmd->cmd_args);
		free(cmd);
	}
}

void	free_split_result(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
}

void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*tmp;

	while (cmd_list)
	{
		tmp = cmd_list;
		cmd_list = cmd_list->next;
		free_cmd(tmp);
	}
}

void	free_paths(t_pipex pipex)
{
	int	i;

	if (pipex.path)
	{
		i = 0;
		while (pipex.path[i])
		{
			free(pipex.path[i]);
			i++;
		}
		free(pipex.path);
	}
}

void	free_pipex(t_pipex pipex)
{
	if (pipex.first_cmd != NULL)
		free_cmd_list(pipex.first_cmd);
	if (pipex.path != NULL)
		free_paths(pipex);
}
