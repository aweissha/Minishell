/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:49:04 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/16 11:48:24 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_error(char *message, int code)
{
	perror(message);
	exit(code);
}

void	ft_error_and_free(char *message, int code, t_data *data)
{
	perror(message);
	free_everything(data);
	exit(code);
}
