/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:24:09 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/09 11:51:18 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_fork(void)
{
	int	id;
	
	id = fork();
	if (id == -1)
		ft_error("fork() failed", errno);
	return (id);
}

t_env	*find_var(char *var_name, t_data *data)
{
	t_env	*env_list;

	env_list = data->env_list;
	while (env_list != NULL)
	{
	// printf("hello from find_var\n");
		if (ft_strcmp(var_name, env_list->var_name) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}
