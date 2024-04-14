/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:24:09 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/14 14:18:46 by aweissha         ###   ########.fr       */
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
		if (ft_strcmp(var_name, env_list->var_name) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

void	set_quote_flags(char *str, int *s_quote_open, int *d_quote_open)
{
	if (*str == '\"' && *s_quote_open == 0 && *d_quote_open == 0)
		*d_quote_open = 1;
	else if (*str == '\'' && *s_quote_open == 0 && *d_quote_open == 0)
		*s_quote_open = 1;
	else if (*str == '\"' && *s_quote_open == 0 && *d_quote_open == 1)
		*d_quote_open = 0;
	else if (*str == '\'' && *s_quote_open == 1 && *d_quote_open == 0)
		*s_quote_open = 0;
}

int	ft_isspace(char c)
{
	if (c == ' '
		|| (c <= 13 && c >= 9))
		return (1);
	else
		return (0);
}
