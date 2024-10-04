/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 23:08:09 by anamedin          #+#    #+#             */
/*   Updated: 2024/10/04 12:42:43 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	
		if (cmd->next)
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

void execute_parent(t_cmd *cmd, int *prev_pipe)
{
	if (prev_pipe)
		close(prev_pipe[0]);

	wait(NULL);
}

void handle_commands(t_pipex *pipex)
{
	t_cmd *cmd;
	
	cmd = pipex->first_cmd;
	int pipe_fd[2];

	while (cmd)
	{
		// execute_child();

		// execute_parent();

		cmd = cmd->next;
	}
}

