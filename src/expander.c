/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:45:54 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/16 15:23:39 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	strlen_expanded(char *str, t_data *data)
{
	int		i;
	int		d_quote;
	int		s_quote;

	d_quote = 0;
	s_quote = 0;
	i = 0;
	while (*str != '\0')
	{
		i += add_strlen(str, &d_quote, &s_quote, data);
		str += add_str(str, &s_quote);
	}
	return (i);
}

void	create_expanded_str(char *exp_str, char *orig_str, t_data *data)
{
	int		d_quote;
	int		s_quote;

	d_quote = 0;
	s_quote = 0;
	if (exp_str != NULL)
	{
		while (*orig_str != '\0')
		{
			if (*orig_str == '$' && s_quote != 1)
				copy_over(&exp_str, orig_str, data);
			else if (edit_quote_counters(orig_str, &s_quote, &d_quote) == 1)
			{
				*exp_str = *orig_str;
				exp_str++;
			}
			orig_str += add_str(orig_str, &s_quote);
		}
		*exp_str = '\0';
	}
}

char	*expand_str(t_token *token, t_data *data)
{
	char	*exp_str;

	exp_str = malloc(strlen_expanded(token->token_str, data) + 1);
	if (exp_str == NULL)
		ft_error_and_free("Memory allocation of expand_str failed\n",
			errno, data);
	create_expanded_str(exp_str, token->token_str, data);
	return (exp_str);
}

void	remove_empty_tokens(t_data *data)
{
	t_token	*token_list;
	t_token	*tmp;

	// printf("hello from remove_token\n");
	token_list = data->token_list;
	while (token_list != NULL && ft_strlen(token_list->token_str) == 0)
	{
		data->token_list = token_list->next;
		free_token(token_list);
		token_list = data->token_list;
		if (token_list != NULL)
			token_list->previous = NULL;
	}
	while (token_list != NULL)
	{
		if (ft_strlen(token_list->token_str) == 0)
		{
			tmp = token_list->previous;
			tmp->next = token_list->next;
			if (token_list->next != NULL)
				token_list->next->previous = tmp;
			free_token(token_list);
		}
		token_list = token_list->next;
	}
}

void	expander(t_data *data)
{
	char	*tmp;
	t_token	*token_list;

	token_list = data->token_list;
	if (token_list == NULL)
		return ;
	while (token_list != NULL)
	{
		if (token_list->token_type == WORD && token_list->token_str != NULL)
		{
			tmp = expand_str(token_list, data);
			free(token_list->token_str);
			token_list->token_str = tmp;
		}
		token_list = token_list->next;
	}
	remove_empty_tokens(data);
}
