/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:24:02 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/19 17:17:24 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strtok(char *str, const char *sep)
{
	static char	*position;
	char		*token_start;

	if (str == NULL && position == NULL)
		return (NULL);
	if (str != NULL)
		position = str;
	while (ft_strchr(sep, *position) != NULL && *position != '\0')
		position++;
	if (*position == '\0')
	{
		position = NULL;
		return (NULL);
	}
	token_start = position;
	while (ft_strchr(sep, *position) == NULL && *position != '\0')
		position++;
	if (*position != '\0')
	{
		*position = '\0';
		position++;
	}
	else
		position = NULL;
	return (token_start);
}

int	count_tokens(char *s, char c)
{
	unsigned int	counter;
	unsigned int	i;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		i++;
		if (((s[i] == c || s[i] == '\0') && s[i - 1] != c))
			counter++;
	}
	return (counter);
}

void	parse_input(char *input, t_data *data)
{
	char	*token;
	int		i;

	data->nb_tokens = count_tokens(input, ' ');
	data->tokens = malloc(sizeof(t_token) * data->nb_tokens);
	if (data->tokens == NULL)
		ft_error("Memory allocation of token array failed", EXIT_FAILURE);
	token = ft_strtok(input, " ");
	i = 0;
	while (token != NULL)
	{
		data->tokens[i].tok_str = ft_strdup(token);
		token = ft_strtok(NULL, " ");
		i++;
	}
	free(input);
}
