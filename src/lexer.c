/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:24:02 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/10 11:06:20 by aweissha         ###   ########.fr       */
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

type	tok_type(char *token_str)
{
	if (ft_strcmp(token_str, "<") == 0
		|| ft_strcmp(token_str, ">") == 0
		|| ft_strcmp(token_str, ">>") == 0
		|| ft_strcmp(token_str, "<<") == 0)
		return (REDIR);
	else if (ft_strcmp(token_str, "|") == 0)
		return (PIPE);
	else
		return (WORD);
}

// char	*ft_strtok_mod(char *str, const char *sep)
// {
// 	static char	*position;
// 	char		*token_start;

// 	if (str == NULL && position == NULL)
// 		return (NULL);
// 	if (str != NULL)
// 		position = str;
// 	while (ft_strchr(sep, *position) != NULL && *position != '\0')
// 		position++;
// 	if (*position == '\0')
// 	{
// 		position = NULL;
// 		return (NULL);
// 	}
// 	token_start = position;
// 	while ((ft_strchr(sep, *position) == NULL && *position != '\0')
// 		|| (in_quotes(token_start, position) == 1 && *position != '\0'))
// 		position++;
// 	if (*position != '\0')
// 		*(position)++ = '\0';
// 	else
// 		position = NULL;
// 	return (token_start);
// }

// void	lexer(char *input, t_data *data)
// {
// 	char	*token_str;

// 	token_str = ft_strtok_mod(input);
// 	while (token_str != NULL)
// 	{
// 		ft_tokadd_back(&data->token_list, ft_toknew(token_str, tok_type(token_str)));
// 		token_str = ft_strtok_mod(NULL);
// 	}
// }

type classify_char(char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (REDINPT);
	else if (c == '>')
		return (REDOUT);
	else if (isspace(c)) //isspace replacen
		return (TOKEN_SPACE);
	return (WORD);
}

int	add_token(t_token **token_list, char *str)
{
	type	token_type;
	int		i;
	int		s_quote_open;
	int		d_quote_open;

	s_quote_open = 0;
	d_quote_open = 0;
	token_type = classify_char(*str);
	i = 0;
	while ((classify_char(str[i]) == token_type && str[i] != '\0')
		|| ((s_quote_open == 1 || d_quote_open == 1) && str[i] != '\0'))
		{
			set_quote_flags(&str[i], &s_quote_open, &d_quote_open);
			i++;
			if ((i > 1 && token_type == REDINPT)
				|| (i > 1 && token_type == REDOUT)
				|| (i > 0 && token_type == PIPE))
				break ;
		}
	if (token_type == REDINPT || token_type == REDOUT)
		ft_tokadd_back(token_list, ft_toknew(strndup(str, i), REDIR));
	else
		ft_tokadd_back(token_list, ft_toknew(strndup(str, i), token_type));
	return (i);
}

void	lexer(char *input, t_data *data)
{
	while (input && *input != '\0')
	{
		while (classify_char(*input) == TOKEN_SPACE && *input != '\0')
			input++;
		if (*input != '\0')
			input += add_token(&data->token_list, input);
	}
}
