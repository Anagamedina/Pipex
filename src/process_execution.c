/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 23:08:09 by anamedin          #+#    #+#             */
/*   Updated: 2024/10/05 14:57:33by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// Ejecutar un comando en un proceso hijo
void execute_child(t_cmd *cmd, t_pipex *pipex, int *prev_pipe)
{
	pid_t pid = fork(); // Crear un nuevo proceso

	if (pid < 0)
	{
		perror("Error: Fork failed");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)  // Código del proceso hijo
	{
        printf("Child process executing command: %s\n", cmd->cmd_args[0]);
		if (prev_pipe)
		{
            printf("Redirecting input from previous pipe FD: %d\n", prev_pipe[0]);
			dup2(prev_pipe[0], STDIN_FILENO); // entrada infile
			close(prev_pipe[0]); // Cerrar lectura del pipe
            close(prev_pipe[1]); // Cerrar escritura del pipe
		}
	
		if (cmd->next) 
        {
            int pipe_fd[2];
            if (pipe(pipe_fd) == -1) // Crear el pipe
            {
                perror("Error: Pipe creation failed");
                exit(EXIT_FAILURE);
            }
            printf("Redirecting output to pipe FD: %d\n", pipe_fd[1]);
            dup2(pipe_fd[1], STDOUT_FILENO); //salida estándar al pipe
            // close(pipe_fd[0]); // Cerrar el descriptor de lectura del pipe
            close(pipe_fd[1]); // Cerrar  escritura del pipe
        }



      /***********printar *********************** */ 
        int i = 0;
        while (cmd->cmd_args[i])
        {
            printf("arg[%d]: %s\n", i, cmd->cmd_args[i]);
            i++;
        }
        printf("Trying to execute: %s\n", cmd->cmd_args[0]);



        // execve(const char *path, char *const argv[], char *envp[])
		if (execve(cmd->cmd_args[0], cmd->cmd_args, pipex->env) == -1)
		{
			perror("Error: Command execution failed");
			exit(EXIT_FAILURE);
		}
	}
}

void execute_parent(int *prev_pipe)
{
    if (prev_pipe)
    {
        close(prev_pipe[0]); // Cerrar lectura del pipe en el padre
        close(prev_pipe[1]); // Cerrar el descriptor de escritura del pipe
    }
    wait(NULL); // Esperar a que el proceso hijo termine
}



/******* Manejar la ejecución de los comandos************/
void handle_commands(t_pipex *pipex)
{
    t_cmd *cmd = pipex->first_cmd;
    int pipe_fd[2]; // Descriptores para el pipe

    while (cmd)
    { 
        if (cmd->next) 
        {
            if (pipe(pipe_fd) == -1) // Crear un nuevo pipe
            {
                perror("Error: Pipe creation failed");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            pipe_fd[0] = -1; // No hay pipe si es el último comando
            pipe_fd[1] = -1;
        }

        if (cmd->next)
			execute_child(cmd, pipex, pipe_fd);
        else
			execute_child(cmd, pipex, NULL);

        if (cmd->next)
			execute_parent(pipe_fd);

        cmd = cmd->next;
    }
}
