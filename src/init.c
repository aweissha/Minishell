/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:33:18 by aweissha          #+#    #+#             */
/*   Updated: 2024/03/13 18:36:01 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data	*init_data(int argc, char **argv, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		ft_error("Memory allocation for data struct failed", errno);
	data->argc = argc;
	data->argv = argv;
	data->env = env;
	data->tokens = NULL;
	data->parse_tree = NULL;
	data->nb_tokens = 0;
	return (data);
}
