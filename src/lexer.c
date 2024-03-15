/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:24:02 by aweissha          #+#    #+#             */
/*   Updated: 2024/03/15 18:25:20 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static int	search_path(char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i] != NULL)
// 	{
// 		if (ft_strnstr(env[i], "PATH", ft_strlen(env[i])) != NULL)
// 			break ;
// 		i++;
// 	}
// 	return (i);
// }

// char	*get_path(char *str, char **env)
// {
// 	char	**path_array;
// 	char	*path1;
// 	char	*path2;
// 	int		i;

// 	path_array = ft_split(&env[search_path(env)][5], ':');
// 	i = 0;
// 	while (path_array[i] != NULL && str != NULL)
// 	{
// 		path1 = ft_strjoin(path_array[i], "/");
// 		path2 = ft_strjoin(path1, str);
// 		free(path1);
// 		if (access(path2, X_OK) == 0)
// 		{
// 			ft_free_array(path_array);
// 			return (path2);
// 		}
// 		else
// 		{
// 			free(path2);
// 			i++;
// 		}
// 	}
// 	ft_free_array(path_array);
// 	return (NULL);
// }

// int	is_comm(char *str, t_data *data)
// {
// 	if (get_path(str, data->env) == NULL)
// 		return (0);
// 	return (1);
// }

type	tok_type(char *token)
{
	if (ft_strcmp(token, "<") == 0)
		return (REDINPT);
	else if (ft_strcmp(token, ">") == 0)
		return (REDOUT);
	else if (ft_strcmp(token, ">>") == 0)
		return (REDAPPND);
	else if (ft_strcmp(token, "<<") == 0)
		return (HEREDOC);
	else if (ft_strcmp(token, "|") == 0)
		return (PIPE);
	else
		return (WORD);
}

int	quotes_left(char *start, char *position, char c)
{
	int	quote_count;

	quote_count = 0;
	position--;
	while (position >= start)
	{
		if (*position == c)
			quote_count++;
		position--;
	}
	return (quote_count);
}

int	quotes_right(char *start, char *position, char c)
{
	int	quote_count;

	quote_count = 0;
	position++;
	while (*position !='\0')
	{
		if (*position == c)
			quote_count++;
		position++;
	}
	return (quote_count);
}

int	in_quotes(char *start, char *position)
{
	if ((quotes_left(start, position, 34) % 2) == 1 
		&& quotes_right(start, position, 34) > 0 
		&& *position != 34)
		return (1);
	else if ((quotes_left(start, position, 39) % 2) == 1 
		&& quotes_right(start, position, 39) > 0 
		&& *position != 39)
		return (1);	
	else if (*position == 34 && (quotes_left(start, position, 34) % 2) == 1)
		return (1);
	else if (*position == 39 && (quotes_left(start, position, 39) % 2) == 1)
		return (1);
	else if (*position == 34 && (quotes_right(start, position, 34) > 0))
		return (1);
	else if (*position == 39 && (quotes_right(start, position, 39) > 0))
		return (1);
	return (0);
}

char	*ft_strtok_mod(char *str, const char *sep)
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
	while ((ft_strchr(sep, *position) == NULL && *position != '\0')
		|| (in_quotes(token_start, position) == 1 && *position != '\0'))
		position++;
	if (*position != '\0')
		*(position)++ = '\0';
	else
		position = NULL;
	return (ft_strtrim(token_start, "\"\'"));
}

// int	count_tokens(char *s, char c)
// {
// 	unsigned int	counter;
// 	unsigned int	i;

// 	i = 0;
// 	counter = 0;
// 	while (s[i] != '\0')
// 	{
// 		i++;
// 		if (((s[i] == c || s[i] == '\0') && s[i - 1] != c))
// 			counter++;
// 	}
// 	return (counter);
// }

t_token	*ft_toknew(char *token_str, type token_type)
{
	t_token	*token_node;

	token_node = malloc(sizeof(t_token));
	if (token_node == NULL)
		ft_error("Memory allocation for token list failed", errno);
	token_node->token = token_str;
	token_node->type = token_type;
	token_node->next = NULL;
	token_node->previous = NULL;
	return (token_node);
}

t_token	*ft_toklast(t_token *token_list)
{
	if (token_list == NULL)
		return (NULL);
	while (token_list->next != NULL)
		token_list = token_list->next;
	return (token_list);
}

void	ft_tokadd_back(t_token **token_list, t_token *new)
{
	t_token	*last;

	if (token_list && new)
	{
		if (*token_list)
		{
			last = ft_toklast(*token_list);
			last->next = new;
			last->next->previous = last;
		}
		else
			*token_list = new;
	}
}

void	lexer(char *input, t_data *data)
{
	char	*token;

	token = ft_strtok_mod(input, " ");
	while (token != NULL)
	{
		ft_tokadd_back(&data->tokens, ft_toknew(token, tok_type(token)));
		token = ft_strtok_mod(NULL, " ");
	}
}
