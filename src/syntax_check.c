/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:23:23 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/10 14:01:32 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pipe_syntax_check(t_token *token_list)
{
	while (token_list != NULL)
	{
		if (token_list->token_type == PIPE)
		{
			if (token_list->next == NULL 
				|| token_list->previous == NULL
				|| token_list->previous->token_type != WORD)
			{
				printf("minishell: syntax error near '|'\n");
				return (1);
			}
		}
		token_list = token_list->next;
	}
	return (0);
}

int	redir_syntax_check(t_token *token_list)
{
	while (token_list != NULL)
	{
		if (token_list->token_type == REDIR)
		{
			if (token_list->next == NULL || token_list->next->token_type != WORD)
			{
				printf("minishell: syntax error near '\\n'\n");
				return (1);
			}
		}
		token_list = token_list->next;
	}
	return (0);
}

// check: every redir needs to have an argument after it.
// every pipe needs to have an argument before and after it.
int	check_operators(t_token *token_list)
{
	if (pipe_syntax_check(token_list) == 1)
		return (1);
	if (redir_syntax_check(token_list) == 1)
		return (1);
	return (0);
}

int	quotes_wrong(char *str)
{
	int		s_quote_open;
	int		d_quote_open;

	s_quote_open = 0;
	d_quote_open = 0;
	while (*str != '\0')
	{
		set_quote_flags(str, &s_quote_open, &d_quote_open);
		str++;
	}
	if (s_quote_open != 0 || d_quote_open != 0)
		return (1);
	return (0);
}

int	check_quotes(t_token *token_list)
{
	while (token_list != NULL)
	{
		if (quotes_wrong(token_list->token_str) == 1)
			return (1);
		token_list = token_list->next;		
	}
	return (0);
}

int	syntax_check(t_data *data)
{
	if (check_quotes(data->token_list) == 1)
	{
		printf("invalid quotes\n");
		return (1);
	}
	else if (check_operators(data->token_list) == 1)
		return (1);
	return (0);
}
