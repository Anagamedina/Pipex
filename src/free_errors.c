/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 22:45:27 by anamedin          #+#    #+#             */
/*   Updated: 2024/10/13 17:15:44 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_cmd (t_cmd *cmd)
{
	if(cmd)
	{
		free(cmd->cmd_args);
		free(cmd);
	}
}

static void	free_split_result(char **result)
{
	int	i;

	i = 0;
	while(result[i])
	{
		free(result[i]);
		i++;
	}
}

void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*tmp;

	while (cmd_list)
	{
		tmp = cmd_list;
		cmd_list = cmd_list->next;
		free_split_result(tmp->cmd_args);
		free_cmd(tmp);
	}
}

void free_paths(t_pipex pipex)
{
	int i;

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

void free_pipex(t_pipex pipex)
{
	free_paths(pipex);
	free_cmd_list(pipex.first_cmd);
}



// Función para imprimir la estructura t_pipex
/*void print_pipex(t_pipex *pipex)
{
    t_cmd *current_cmd = pipex->first_cmd;

    printf("Pipex Structure:\n");
    printf("Command Count: %d\n", pipex->cmd_count);
    printf("Input File Descriptor: %d\n", pipex->input_fd);
    printf("Output File Descriptor: %d\n", pipex->output_fd);
    
    printf("Paths:\n");
    int i = 0;
    while (pipex->path[i] != NULL)
    {
        printf("  path[%d]: %s\n", i, pipex->path[i]);
        i++;
    }
    
    printf("Commands:\n");
    while (current_cmd != NULL)
    {
        printf("  Command Number: %d\n", current_cmd->cmd_id);
        printf("  Arguments:\n");
        
        int j = 0;
        while (current_cmd->cmd_args[j] != NULL)
        {
            printf("    arg[%d]: %s\n", j, current_cmd->cmd_args[j]);
            j++;
        }

        printf("  Pipe FD: [%d, %d]\n", current_cmd->pipe[0], current_cmd->pipe[1]);
        
        current_cmd = current_cmd->next;
    }
}*/