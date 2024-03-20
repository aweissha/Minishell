/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:07:54 by aweissha          #+#    #+#             */
/*   Updated: 2024/03/19 14:35:33 by aweissha         ###   ########.fr       */
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

	tmp = data->token_list;
	while (tmp != NULL)
	{
		printf("type: %u\ntoken_str: %s\n", tmp->token_type, tmp->token_str);
		tmp = tmp->next;
	}
}
