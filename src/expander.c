/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:45:54 by aweissha          #+#    #+#             */
/*   Updated: 2024/03/26 13:30:01 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * expander takes the token list from the lexer.
 * For double quotes, environment variables have to be
 * handled. For single quotes, nothing has to be done. 
 * Finally quotes have to be trimmed off.
 * empty quoted str much result in an empty string
*/

char	*remove_false_variable(char *str, char *position, int var_length)
{
	int		str_len;
	char	*new_str;
	int		i;

	if ((*(position + 1) <= 13 && *(position + 1) >= 9)
		|| *(position + 1) == '\0')
		str_len = ft_strlen(str);
	else
		str_len = ft_strlen(str) - var_length;
	new_str = malloc(sizeof(char) * (str_len + 1));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (str != position)
	{
		new_str[i] = *str;
		i++;
		str++;
	}
	while (!(*str <= 13 && *str >= 9)
		&& *str != '$' && *str != '\0')
		str++;
	
}

char	*ft_strcomb(char *str, char *position, int var_length, t_env *var)
{
	int		str_len;
	char	*comb_str;
	int		i;
	int		j;

	str_len = ft_strlen(str) - var_length + ft_strlen(var->var_str);
	comb_str = malloc(sizeof(char) * (str_len + 1));
	if (comb_str == NULL)
		return (NULL);
	i = 0;
	while (str != position)
	{
		comb_str[i] = *str;
		i++;
		str++;
	}
	j = 0;
	while (var->var_str[j] != '\0')
	{
		comb_str[i] = var->var_str[j];
		j++;
		i++;
	}
	while (!(*str <= 13 && *str >= 9)
		&& *str != '$' && *str != '\0')
		str++;
	while (*str != '\0')
	{
		comb_str[i] = *str;
		str++;
		i++;
	}
	comb_str[i] = '\0';
	return (comb_str);
}

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

int	var_length(char *str)
{
	int	i;

	i = 1;
	if (str[i] == '?')
		return (2);
	while (!(str[i] <= 13 && str[i] >= 9) 
		&& str[i] != '$' && str[i] != '\0')
		i++;
	return (i);
}

/*
Expander: 
Str durchgehen bis zu einem $ Zeichen.
Anzahl an Zeichen n zaehlen bis zu naechstem dollar Zeichen oder space.
Mit stncmp vergelichen mit ganzer env liste.
Wenn treffer, dann die n characters mit der env variable replacen,
wenn nicht, dann rausloeschen (Dollar sign + n characters).
Wenn nur ein einsames dollar sign, dann drin lassen.
Space drin lassen.
Repeat.
*/

void	expand_str(t_token *token, t_data *data)
{
	int		i;
	char	*tmp;
	char	*var_len;
	t_env	*env_var;

	env_var = NULL;
	i = 0;
	while (token->token_str[i] != '\0')
	{
		if (token->token_str[i] == '$')
		{
			var_len = var_length(&token->token_str[i]); // length of dollar sign + characters that are not space or dollar or \0
			if (var_len > 1)
				env_var = find_var(&token->token_str[i + 1], var_len - 1, data);
			if (env_var != NULL)
			{
				tmp = ft_strcomb(token->token_str, &token->token_str[i], var_len, env_var);
				free(token->token_str);
				token->token_str = tmp;
				i = i + (ft_strlen(env_var->var_str) + 1);
			}
			else
			{
			// handle $$ and single $ and incorrect variables
				tmp = remove_false_variable(token->token_str, &token->token_str[i], env_var);
				free(token->token_str);
				token->token_str = tmp;
				// i = i + (ft_strlen(env_var->var_str) + 1);
			}
		}
		else
			i++;
	}
}

void	expander(t_data *data)
{
	char	*tmp;
	t_token	*token_list;

	token_list = data->token_list;
	while (token_list != NULL)
	{
		if (token_list->token_str[0] == '\"')
		{
			tmp = expand_str(token_list, data);
			free(token_list->token_str);
			token_list = ft_strtrim(tmp, "\"");
			free(tmp);
		}
		else if (token_list->token_str[0] == '\'')
		{
			tmp = ft_strtrim(token_list->token_str, "'");
			free(token_list->token_str);
			token_list->token_str = tmp;
		}
		token_list = token_list->next;
	}
}
