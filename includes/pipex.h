/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:27:19 by anamedin          #+#    #+#             */
/*   Updated: 2024/10/14 11:36:55 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>  // fork, pipe, dup2, execve, close, read, write
# include <stdlib.h>  // malloc, free, exit
# include <stdio.h>   // perror, printf
# include <fcntl.h>   // open
# include <sys/wait.h>  // wait, waitid
# include <sys/types.h>  // pid_t
# include "libft.h"

/********     STRUCTS      *******/

typedef struct s_cmd
{
	// "wc -l" sería el comando y sus parámetros:
	// cmd_args[0] = "wc"
	// cmd_args[1] = "-l"
	char			**cmd_args;
	int				cmd_id;
	int				pipe[2];
	int				input_fd;
	int				output_fd;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_pipex
{
	t_cmd			*first_cmd;
	char			**path;
	int				cmd_count;
	char			**argvs;
	char			**env;
	int				input_fd;
	int				output_fd;
}				t_pipex;

/********     FUNCTIONS      *******/

// Commands and command lists
t_cmd			*cmd_new(char *str, char **paths);
t_cmd			*create_cmd_list(t_pipex *pipex);

// Path and command management
char			**get_path(char **env);
char			*get_cmd_path(char *cmd, char **paths);

// Pipex initialization
t_pipex			init_pipex(int argc, char **argv, char **env);

// Command and pipe execution
void			execute_child(t_pipex *pipex, t_cmd *cmd, int *pipe_fd);
void			handle_commands(t_pipex *pipex);

// Memory release functions
void			free_cmd(t_cmd *cmd);
void			free_cmd_list(t_cmd *cmd_list);
void			free_paths(t_pipex pipex);
void			free_pipex(t_pipex pipex);
void			free_split_result(char **result);
t_cmd			*handle_cmd_error(t_cmd *new);

#endif
