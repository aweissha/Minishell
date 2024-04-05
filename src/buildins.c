/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:34:46 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/05 15:45:08 by aweissha         ###   ########.fr       */
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
