/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:11:27 by anamedin          #+#    #+#             */
/*   Updated: 2024/10/13 23:53:54 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_cmd_path(char *cmd, char **paths)
{
    char	*cmd_path;
    char    *full_path;
    int     i;

	if (cmd[0] == '/' || cmd[0] == '.')
    {
        if (access(cmd, X_OK) == 0)
        {
            // printf("cmd:  %s\n", cmd);
            return (ft_strdup(cmd));
        }
        else
            return (NULL);
    }
    i = 0;
    while (paths[i])
    {
        full_path = ft_strjoin(paths[i], "/");
        cmd_path = ft_strjoin(full_path, cmd); 
        free(full_path);
        if (access(cmd_path, X_OK) == 0)
            return (cmd_path);
        free(cmd_path);
        i++;
    }
    return (NULL); 
}

	// if (cmd[0] == '/' || cmd[0] == '.')
    // {
    //     if (access(cmd, X_OK) == 0)
    //     {
    //         // printf("cmd:  %s\n", cmd);
    //         return (ft_strdup(cmd));
    //     }
    //     else
    //         return (NULL);
    // }
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
