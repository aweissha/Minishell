/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:45:54 by aweissha          #+#    #+#             */
/*   Updated: 2024/03/27 18:15:36 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// /**
//  * expander takes the token list from the lexer.
//  * For double quotes, environment variables have to be
//  * handled. For single quotes, nothing has to be done. 
//  * Finally quotes have to be trimmed off.
//  * empty quoted str much result in an empty string
// */

// char	*remove_false_variable(char *str, char *position, int var_length)
// {
// 	int		str_len;
// 	char	*new_str;
// 	int		i;

// 	if ((*(position + 1) <= 13 && *(position + 1) >= 9)
// 		|| *(position + 1) == '\0')
// 		str_len = ft_strlen(str);
// 	else
// 		str_len = ft_strlen(str) - var_length;
// 	new_str = malloc(sizeof(char) * (str_len + 1));
// 	if (new_str == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (str != position)
// 	{
// 		new_str[i] = *str;
// 		i++;
// 		str++;
// 	}
// 	while (!(*str <= 13 && *str >= 9)
// 		&& *str != '$' && *str != '\0')
// 		str++;
	
// }

// char	*ft_strcomb(char *str, char *position, int var_length, t_env *var)
// {
// 	int		str_len;
// 	char	*comb_str;
// 	int		i;
// 	int		j;

// 	str_len = ft_strlen(str) - var_length + ft_strlen(var->var_str);
// 	comb_str = malloc(sizeof(char) * (str_len + 1));
// 	if (comb_str == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (str != position)
// 	{
// 		comb_str[i] = *str;
// 		i++;
// 		str++;
// 	}
// 	j = 0;
// 	while (var->var_str[j] != '\0')
// 	{
// 		comb_str[i] = var->var_str[j];
// 		j++;
// 		i++;
// 	}
// 	while (!(*str <= 13 && *str >= 9)
// 		&& *str != '$' && *str != '\0')
// 		str++;
// 	while (*str != '\0')
// 	{
// 		comb_str[i] = *str;
// 		str++;
// 		i++;
// 	}
// 	comb_str[i] = '\0';
// 	return (comb_str);
// }

t_env	*find_var(char *str, int var_length, t_data *data)
{
	t_env	*env_list;

	env_list = data->env_list;
	while (env_list != NULL)
	{
		if (ft_strncmp(str, env_list->var_name, var_length) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

// int	var_length(char *str)
// {
// 	int	i;

// 	i = 1;
// 	if (str[i] == '?')
// 		return (2);
// 	while (!(str[i] <= 13 && str[i] >= 9) 
// 		&& str[i] != '$' && str[i] != '\0')
// 		i++;
// 	return (i);
// }

// /*
// Expander: 
// Str durchgehen bis zu einem $ Zeichen.
// Anzahl an Zeichen n zaehlen bis zu naechstem dollar Zeichen oder space.
// Mit stncmp vergelichen mit ganzer env liste.
// Wenn treffer, dann die n characters mit der env variable replacen,
// wenn nicht, dann rausloeschen (Dollar sign + n characters).
// Wenn nur ein einsames dollar sign, dann drin lassen.
// Space drin lassen.
// Repeat.
// */

// void	expand_str(t_token *token, t_data *data)
// {
// 	int		i;
// 	char	*tmp;
// 	char	*var_len;
// 	t_env	*env_var;

// 	env_var = NULL;
// 	i = 0;
// 	while (token->token_str[i] != '\0')
// 	{
// 		if (token->token_str[i] == '$')
// 		{
// 			var_len = var_length(&token->token_str[i]); // length of dollar sign + characters that are not space or dollar or \0
// 			if (var_len > 1)
// 				env_var = find_var(&token->token_str[i + 1], var_len - 1, data);
// 			if (env_var != NULL)
// 			{
// 				tmp = ft_strcomb(token->token_str, &token->token_str[i], var_len, env_var);
// 				free(token->token_str);
// 				token->token_str = tmp;
// 				i = i + (ft_strlen(env_var->var_str) + 1);
// 			}
// 			else
// 			{
// 			// handle $$ and single $ and incorrect variables
// 				tmp = remove_false_variable(token->token_str, &token->token_str[i], env_var);
// 				free(token->token_str);
// 				token->token_str = tmp;
// 				// i = i + (ft_strlen(env_var->var_str) + 1);
// 			}
// 		}
// 		else
// 			i++;
// 	}
// }

int	var_length(char *str)
{
	int	i;

	i = 0;
	while (!(str[i] <= 13 && str[i] >= 9)
		&& str[i] != '$' && str[i] != '\0'
		&& str[i] != '\"' && str[i] != '\'')
		i++;
	return (i);
}

int	edit_quote_counters(char *str, int *s_quote_open, int *d_quote_open)
{
	if (*str == '\"' && *s_quote_open == 0 && *d_quote_open == 0)
	{
		*d_quote_open = 1;
		return (0);
	}
	else if (*str == '\'' && *s_quote_open == 0 && *d_quote_open == 0)
	{
		*s_quote_open = 1;
		return (0);
	}
	else if (*str == '\"' && *s_quote_open == 0 && *d_quote_open == 1)
	{
		*d_quote_open = 0;
		return (0);
	}
	else if (*str == '\'' && *s_quote_open == 1 && *d_quote_open == 0)
	{
		*s_quote_open = 0;	
		return (0);
	}
	return (1);
}

int	add_strlen(char *str, int *d_quote_open, int *s_quote_open, t_data *data)
{
	char	*var;

	if (*str == '$')
	{
		if (s_quote_open != 1 && *str != '\0')
		{
			var = find_var(str, var_length(str), data)->var_str;
			if (var != NULL)
				return (ft_strlen(var));
			else
				return (0);
		}
	}
	else
		return(edit_quote_counters(str, &s_quote_open, &d_quote_open));
}

int	add_str(char *str, int *d_quote_open, int *s_quote_open)
{
	if (*str == '$')
	{
		if (s_quote_open != 1 && *str != '\0')
			return(var_length(str));
	}
	else
		return (1);
}

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
		str+= add_str(str, &d_quote_open, &s_quote_open);
		i+= add_strlen(str, &d_quote_open, &s_quote_open, data);
	}
	return (i);
}

void	create_expanded_str(char *expanded_str, char *original_str, t_data *data)
{
	int		d_quote_open;
	int		s_quote_open;
	char	*start_expanded_str;

	start_expanded_str = expanded_str;
	d_quote_open = 0;
	s_quote_open = 0;
	while (*original_str != '\0')
	{
		
	}
	
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
	while (token_list != NULL)
	{
		tmp = expand_str(token_list, data);
		free(token_list->token_str);
		token_list = tmp;
	}
}
