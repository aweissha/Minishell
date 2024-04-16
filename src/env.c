/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:29:47 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/16 11:46:58 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_var_str(char *env_line)
{
	int		i;
	int		j;
	char	*str_name;

	i = 0;
	while (env_line[i] != '=' && env_line[i] != '\0')
		i++;
	if (env_line[i] == '=')
		i++;
	j = 0;
	while (env_line[i + j] != '\0')
		j++;
	str_name = ft_strndup(&env_line[i], j);
	return (str_name);
}

char	*get_var_name(char *env_line)
{
	int		i;
	char	*var_name;

	i = 0;
	while (env_line[i] != '=' && env_line[i] != '\0')
		i++;
	var_name = ft_strndup(env_line, i);
	return (var_name);
}

void	create_env_list(t_data *data)
{
	int		i;
	t_env	*new_node;
	char	*var_str;
	char	*var_name;

	i = 0;
	while (data->env[i] != NULL)
	{
		var_name = get_var_name(data->env[i]);
		if (var_name == NULL)
			ft_error_and_free("Memory allocation of var_name failed\n",
				errno, data);
		var_str = get_var_str(data->env[i]);
		if (var_str == NULL)
			ft_error_and_free("Memory allocation of var_str failed\n",
				errno, data);
		new_node = env_list_new(var_name, var_str);
		if (new_node == NULL)
			ft_error_and_free("Memory allocation of env_list_node failed\n",
				errno, data);
		env_list_add_back(&data->env_list, new_node);
		i++;
	}
}
