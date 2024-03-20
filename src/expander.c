/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:45:54 by aweissha          #+#    #+#             */
/*   Updated: 2024/03/20 12:36:00 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * expander takes the token list from the lexer. 
 * the tokens from lexer however can still contain 
 * something like bla>bla or bla|bla and so on, so
 * pipes and redirects have to be separated from 
 * the rest and additional token have to be created.
 * If the token is quoted, this does not have to be done.
 * For double quotes, environment variables have to be
 * handled. For single quotes, nothing has to be done. 
 * Finally quotes have to be trimmed off.
*/

void	expander(t_data *data)
{
	
}
