/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:08:49 by anamedin          #+#    #+#             */
/*   Updated: 2024/09/28 17:51:41 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/pipex.h>

int main(int argc, char **argv, char **env)
{
	t_cmd	cmd_list;

	if (argc != 5)
	{
		perror("Usage: ./pipex infile cmd1 cmd2 outfile");
		return (EXIT_FAILURE);
	}

	//cmd = init_pipex(argc, argv, env);



}
	
