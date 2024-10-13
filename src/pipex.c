/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:08:49 by anamedin          #+#    #+#             */
/*   Updated: 2024/10/14 01:03:23 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		perror("Error: ./pipex infile cmd1 cmd2 outfile");
		return (EXIT_FAILURE);
	}
	pipex = init_pipex(argc, argv, env);
	if (!pipex.first_cmd)
	{
		free_pipex(pipex);
		return (EXIT_FAILURE);
	}
	handle_commands(&pipex);
	free_pipex(pipex);
	return (0);
}
