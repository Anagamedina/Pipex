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


void execute_child(t_pipex *pipex, t_cmd *cmd, int *pipe_fd)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("Error: Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
        close(pipe_fd[0]);
        
        dup2(pipex->input_fd, STDIN_FILENO);
        close(pipex->input_fd);
        execve(cmd->cmd_args[0], cmd->cmd_args, pipex->argvs);
        perror("execve failed"); 
        exit(EXIT_FAILURE);
    }
    close(pipe_fd[1]); // importamte!
    pid_t pid2 = fork();
    if (pid2 < 0)
    {
        perror("Error: Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0)
    {
        dup2(pipe_fd[0], STDIN_FILENO); 
        close(pipe_fd[1]); 
        close(pipe_fd[0]); 

        dup2(pipex->output_fd, STDOUT_FILENO);
        close(pipex->output_fd);
        execve(cmd->next->cmd_args[0], cmd->next->cmd_args, pipex->argvs); 
        perror("execve failed");
        exit(EXIT_FAILURE);
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);

    wait(NULL);
    wait(NULL);
}

/******* Manejar la ejecución de los comandos ************/
void handle_commands(t_pipex *pipex)
{
    t_cmd *cmd;
    int pipe_fd[2];

    cmd = pipex->first_cmd;
    while (cmd && cmd->next)
    {
        if (pipe(pipe_fd) == -1)
        {
            perror("Error: Pipe creation failed");
            exit(EXIT_FAILURE);
        }
        execute_child(pipex, cmd, pipe_fd);
        write(2, "entro\n", 6);
        cmd = cmd->next;
    }
}
