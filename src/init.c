/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:33:18 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/20 14:48:24 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data	*init_data(int argc, char **argv, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		ft_error("Memory allocation for data struct failed", EXIT_FAILURE);
	data->argc = argc;
	data->argv = argv;
	data->env = env;
	data->nb_pipes = 0;
	data->nb_tokens = 0;
	data->tokens = NULL;
	return (data);
}
