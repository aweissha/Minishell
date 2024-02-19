/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:07:54 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/16 14:30:46 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	char *input;

	input = NULL;
	while (1)
	{
		input = readline("Enter some blablabla: ");
		if (input == NULL)
		{
            printf("\n");
            break;
        }
        // // Handle user input
        // else if (ft_strcmp(input, "exit") == 0)
		// {
        //     free(input);
        //     break;
        // } 
		else if (ft_strlen(input) == 0)
			free(input);
		else
		{
            // Process user input here
            printf("You entered: %s\n", input);
            free(input);
        }
	}
}
