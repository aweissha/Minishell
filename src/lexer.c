/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:24:02 by aweissha          #+#    #+#             */
/*   Updated: 2024/03/13 18:44:46 by aweissha         ###   ########.fr       */
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

void	add_tok_types(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_tokens)
	{
		if (ft_strcmp(data->tokens[i].token, "<") == 0)
			data->tokens[i].type = REDINPT;
		else if (ft_strcmp(data->tokens[i].token, ">") == 0)
			data->tokens[i].type = REDOUT;
		else if (ft_strcmp(data->tokens[i].token, ">>") == 0)
			data->tokens[i].type = REDAPPND;
		else if (ft_strcmp(data->tokens[i].token, "<<") == 0)
			data->tokens[i].type = HEREDOC;
		else if (ft_strcmp(data->tokens[i].token, "|") == 0)
			data->tokens[i].type = PIPE;
		else if (is_buildin(data->tokens[i].token) == 1)
			data->tokens[i].type = BUILDIN;
		i++;
	}
}

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

void	lexer(char *input, t_data *data)
{
	char	*token;
	int		i;

	data->nb_tokens = count_tokens(input, ' ');
	data->tokens = malloc(sizeof(t_token) * (data->nb_tokens));
	if (data->tokens == NULL)
		ft_error("Memory allocation of token array failed", errno);
	token = ft_strtok(input, " ");
	i = 0;
	while (token != NULL)
	{
		data->tokens[i].token = ft_strdup(token);
		token = ft_strtok(NULL, " ");
		i++;
	}
	free(input);
	add_tok_types(data->tokens);
}
