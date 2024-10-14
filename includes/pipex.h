/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:27:19 by anamedin          #+#    #+#             */
/*   Updated: 2024/10/14 10:38:38 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h> //flork, pipe // dup2 // exceve // close // read // write//
#include <stdlib.h> //malloc // free // exit 
#include <stdio.h> //perror // printf 
#include <fcntl.h> //open // 
#include <sys/wait.h> // wait // waitid
#include <sys/types.h> //pid_t
#include "libft.h"


/********     STRUCTS      *******/

typedef struct s_cmd
{
	//"wc -l" seria wc comado -l seria parametros 
	//	cmd_args[1][0] = "wc"
	//	cmd_args[1][1] = "-l" 
	char			**cmd_args;  //arrays de args (incluye el comando y sus parametros )
	int				cmd_id;   // numero del comando para control
	int				pipe[2];  //pipe[0] = infile	pipe[1] = outfile 
	int				input_fd;  //entrada
	int				output_fd; //salida
	struct s_cmd	*next;  // puntero al siguiente comando 
}				t_cmd;

typedef struct s_pipex  //argumentos del programax
{
	t_cmd			*first_cmd;  //primer comando de la lista enlazada
	char			**path;     // array de rutas de posibles ubi de comandos
	int				cmd_count; //numero total de comandos
	char			**argvs;  //argumentos del programa:
	char			**env;   //varible de entorno
	int				input_fd;
	int				output_fd;
}				t_pipex;


/********     FUNCTIONS      *******/

t_cmd   	*cmd_new(char *str, char **paths);
t_cmd		*create_cmd_list(t_pipex *pipex);
char 		**get_path(char **env);
t_pipex		init_pipex(int argc, char **argv, char **env);
int 		main(int argc, char **argv, char **env);
void 		execute_child(t_pipex *pipex, t_cmd *cmd, int *pipe_fd);
void 		handle_commands(t_pipex *pipex);
char 		*get_cmd_path(char *cmd, char **paths);
void 		free_cmd(t_cmd *cmd);
void 		free_cmd_list(t_cmd *cmd_list);
void 		free_paths(t_pipex pipex);
void 		free_pipex(t_pipex pipex);
void		free_split_result(char **result);
t_cmd 		*handle_cmd_error(t_cmd *new);
#endif
