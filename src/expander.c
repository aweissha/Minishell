/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:45:54 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/09 16:01:31 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	strlen_expanded(char *str, t_data *data)
{
	int		i;
	int		d_quote_open;
	int		s_quote_open;

	d_quote_open = 0;
	s_quote_open = 0;
	i = 0;
	while (*str != '\0')
	{
		// printf("hello\n");
		// printf("%d\n", i);
		// printf("%p\n", str);
		i+= add_strlen(str, &d_quote_open, &s_quote_open, data);
		str+= add_str(str, &s_quote_open);
	}
	return (i);
}

void	create_expanded_str(char *expanded_str, char *original_str, t_data *data)
{
	int		d_quote_open;
	int		s_quote_open;

	d_quote_open = 0;
	s_quote_open = 0;
	while (*original_str != '\0')
	{
		if (*original_str == '$' && s_quote_open != 1)
			copy_over(&expanded_str, original_str, data);
		else if (edit_quote_counters(original_str, &s_quote_open, &d_quote_open) == 1)
		{
			*expanded_str = *original_str;
			expanded_str++;
		}
		original_str += add_str(original_str, &s_quote_open);
	}
	*expanded_str = '\0';
}

char	*expand_str(t_token *token, t_data *data)
{
	char	*expanded_str;

	expanded_str = malloc(sizeof(char) * (strlen_expanded(token->token_str, data) + 1));
	if (expanded_str == NULL)
		ft_error("Memory allocation of expanded str failed", errno);
	create_expanded_str(expanded_str, token->token_str, data);
	return (expanded_str);
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
		if (token_list->token_type == WORD)
		{
			tmp = expand_str(token_list, data);
			free(token_list->token_str);
			token_list->token_str = tmp;
		}
		token_list = token_list->next;
	}
}
