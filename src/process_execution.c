/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 23:08:09 by anamedin          #+#    #+#             */
/*   Updated: 2024/10/04 19:32:20 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



//HIJO PRIMERO USANDO UN PREV_PIPE PARA COMUNICAR MEJOR
void execute_child(t_cmd *cmd, t_pipex *pipex, int *prev_pipe)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("Error: Fork failed");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		if (prev_pipe)
		{
			dup2(prev_pipe[0], STDIN_FILENO);
			close(prev_pipe[0]);
			close(prev_pipe[1]);
		}
//ls y grep
//salida->ls como entrada ->grep
//crear una pipe y dup2 para redirigir STDOUT a la pipe
//en le segundo child dup2(STDIN_FILENO)para que grep lea la salida de ls
	
		if (cmd->next) // si hay un comando next crea una nueva pipe
		{
			int pipe_fd[2];
			pipe(pipe_fd);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}

		if (execve(cmd->argvs[0], cmd->argvs, pipex->env) == -1)
		{
			perror("Error: Command execution failed");
			exit(EXIT_FAILURE);
		}
	}
}

void execute_parent(int *prev_pipe)
{
	if (prev_pipe)
		close(prev_pipe[0]);

	wait(NULL);
}




/*********************** principal******* */
void handle_commands(t_pipex *pipex)
{
	t_cmd *cmd;
	
	cmd = pipex->first_cmd;
	int pipe_fd[2];

	while (cmd)
	{ 
		if (cmd->next)
		{
			if(pipe(pipe_fd) == -1)
			{
				perror("Error: pipe creation");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			pipe_fd[0] = -1;
			pipe_fd[1] = -1;
			execute_child(cmd, pipex, pipe_fd);
			execute_parent(pipe_fd);
			cmd = cmd->next;
			
		}
	}
}