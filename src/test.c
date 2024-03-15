/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:07:54 by aweissha          #+#    #+#             */
/*   Updated: 2024/03/15 14:16:28 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	t_token	*tmp;
	char	*input;

	input = readline("Minishell $> ");
	data = init_data(argc, argv, env);
	lexer(input, data);

	tmp = data->tokens;
	while (tmp != NULL)
	{
		printf("type: %u\ntoken_str: %s\n", tmp->type, tmp->token);
		tmp = tmp->next;
	}
}
