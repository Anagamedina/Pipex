/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:27:19 by anamedin          #+#    #+#             */
/*   Updated: 2024/09/28 21:20:33 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h> //flork, pipe // dup2 // exceve // close // read // write//
#include <stdlib.h> //malooc // free // exit 
#include <stdio.h> //perror // printf 
#include <fcntl.h> //open // 
#include <sys/wait.h> // wait // waitid
#include <sys/types.h> //pid_t

/**********   ERROR MACROS *******/


/********     STRUCTS      *******/

typedef struct s_cmd
{
	char			**argvs;  //arrays de args (incluye el comando)
	struct s_cmd	*next;  // puntero al siguiente comando 
	int				num;   // numero del comando para control
	int				pipe[2];  //fd para los pipes entre comandos
	int				input_fd;  //entrada
	int				output_fd; //salida
}				t_cmd;

typedef struct s_pipex		args;  //argumentos del programax
{
	t_cmd			*first_cmd;  //primer comando de la lista enlazada
	char			**path;     // array de rutas de posibles ubi de comandos
	int				cmd_count; //numero total de comandos
	char			args;  //argumentos del programa:
	char			**env;   //varible de entorno
	int				input_fd;
	int				output_fd;
}				t_pipex;


/********     FUNCTIONS      *******/

t_cmd		*cmd_new(char *str, t_pipex *pipex);
t_cmd		*create_cmd_list(t_pipex *pipex);
char 		**get_path(char **env);
t_pipex		init_pipex(int argc, char **argv, char **env);
int 		main(int argc, char **argv, char **env);

#endif
