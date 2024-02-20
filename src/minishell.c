/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:42:48 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/20 10:25:28 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_input(char *input, t_data *data)
{
	parse_input(input, data);
	
	

}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_data	*data;


	data = init_data(argc, argv, env);
	
	// Main process: use readline() to wait for input. 
	while (1)
	{
		input = readline("Minishell $> ");
		if (input == NULL)
		{
			printf("\n");
			break ;
		}
		else if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			exit(0);
		}
		else if (ft_strlen(input) == 0)
			free(input);
		else
		{
			printf("you entered: %s\n", input);
			handle_input(input, data);
		}
	}
	free(data);
}

// Plan:
/*
- learn about how to code my own shell


structure:
display prompt
read command, check if its valid
interpret command
execute command
display prompt



*/