/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:34:46 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/07 13:26:39 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env_buildin(t_data *data)
{
	t_env	*env_list;

	env_list = data->env_list;
	while (env_list != NULL)
	{
		printf("%s=%s\n", env_list->var_name, env_list->var_str);
		env_list = env_list->next;
	}
}

// was, wenn das argument von export nicht korrekt ist, zb kein = vorhanden ?
void	export(char *variable, t_data *data)
{
	env_list_add_back(&data->env_list, env_list_new(get_var_name(variable), get_var_str(variable)));
}

void	unset(char *variable, t_data *data)
{
	t_env	*env_list;
	t_env	*tmp;

	if (data->env_list != NULL)
	{
		env_list = data->env_list;
		if (ft_strcmp(env_list->var_name, variable) == 0)
		{
			data->env_list = env_list->next;
			free_env(env_list);
		}
		else
		{
			while (env_list->next != NULL)
			{
				if (ft_strcmp(env_list->next->var_name, variable) == 0)
				{
					tmp = env_list->next;
					env_list->next = tmp->next;
					return (free_env(tmp));
				}
				env_list = env_list->next;
			}
		}
	}
}
