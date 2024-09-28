/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 23:08:09 by anamedin          #+#    #+#             */
/*   Updated: 2024/09/28 23:08:11 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void execute_child(t_cmd *cmd, t_pipex *pipex, int *prev_pipe)
{
	// Crear un nuevo proceso
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("Error: Fork failed");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)  // Proceso hijo
	{
		// Si hay un pipe anterior, redirigir la entrada
		if (prev_pipe)
		{
			dup2(prev_pipe[0], STDIN_FILENO);
			close(prev_pipe[0]);
			close(prev_pipe[1]);
		}

		// Si no es el último comando, crear un nuevo pipe para la salida
		if (cmd->next)
		{
			int pipe_fd[2];
			pipe(pipe_fd);  // Crear un nuevo pipe
			dup2(pipe_fd[1], STDOUT_FILENO);  // Redirigir salida
			close(pipe_fd[0]);  // Cerrar el extremo de lectura en el hijo
			close(pipe_fd[1]);  // Cerrar el extremo de escritura (esto puede hacerse en el padre después)
		}

		// Ejecutar el comando
		if (execve(cmd->argvs[0], cmd->argvs, pipex->env) == -1)
		{
			perror("Error: Command execution failed");
			exit(EXIT_FAILURE);
		}
	}
}

void execute_parent(t_cmd *cmd, int *prev_pipe)
{
	// Cerrar el extremo de lectura del pipe anterior si existe
	if (prev_pipe)
		close(prev_pipe[0]);

	// Esperar a que el hijo termine
	wait(NULL);
}

void handle_commands(t_pipex *pipex)
{
	t_cmd *cmd = pipex->first_cmd;  // Empezar desde el primer comando
	int pipe_fd[2];  // Para el pipe entre comandos

	while (cmd)
	{
		// Ejecutar el comando en el hijo
		execute_child(cmd, pipex, (cmd->next) ? pipe_fd : NULL);

		// Ejecutar la lógica del padre
		execute_parent(cmd, (cmd->next) ? pipe_fd : NULL);

		cmd = cmd->next;  // Pasar al siguiente comando
	}
}

