/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:08:49 by anamedin          #+#    #+#             */
/*   Updated: 2024/10/04 23:23:54 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <stdio.h>  // Para printf
#include <stdlib.h> // Para free (si es necesario)

// Función para imprimir la estructura t_pipex
/*void print_pipex(t_pipex *pipex)
{
    t_cmd *current_cmd = pipex->first_cmd; // Iniciar en el primer comando

    // Imprimir información básica de t_pipex
    printf("Pipex Structure:\n");
    printf("Command Count: %d\n", pipex->cmd_count);
    printf("Input File Descriptor: %d\n", pipex->input_fd);
    printf("Output File Descriptor: %d\n", pipex->output_fd);
    
    // Imprimir las rutas disponibles
    printf("Paths:\n");
    int i = 0;
    while (pipex->path[i] != NULL)
    {
        printf("  path[%d]: %s\n", i, pipex->path[i]);
        i++;
    }
    
    // Imprimir los comandos en la lista
    printf("Commands:\n");
    while (current_cmd != NULL)
    {
        printf("  Command Number: %d\n", current_cmd->num);
        printf("  Arguments:\n");
        
        int j = 0;
        while (current_cmd->argvs[j] != NULL)
        {
            printf("    arg[%d]: %s\n", j, current_cmd->argvs[j]);
            j++;
        }

        // Imprimir los descriptores de archivo del pipe
        printf("  Pipe FD: [%d, %d]\n", current_cmd->pipe[0], current_cmd->pipe[1]);
        
        // Avanzar al siguiente comando
        current_cmd = current_cmd->next;
    }
}*/






int main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		perror("Usage: ./pipex infile cmd1 cmd2 outfile");
		return (EXIT_FAILURE);
	}

	pipex = init_pipex(argc, argv, env);
	
	if (!pipex.first_cmd)
	{
		//free_pipex(&pipex);  // Liberar si hay algún fallo
		return (EXIT_FAILURE);
	}

	// print_pipex(&pipex);
	//free_pipex(&pipex);
	handle_commands(&pipex);

	return (EXIT_SUCCESS);
}

	
