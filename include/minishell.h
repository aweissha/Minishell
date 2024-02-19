/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:44:13 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/19 16:15:30 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "../libft/libft.h"

typedef enum
{
	PCOMMAND,
	COMMAND,
	OPTN,
	ARG,
	REDIR,
	PIPE,
}	token_type;

typedef struct	s_token
{
	token_type	tok_type;
	char		*tok_str;
}	t_token;

typedef struct s_data
{
	int			argc;
	char 		**argv;
	char 		**env;
	int			nb_tokens;
	t_token		*tokens;
	// int		nb_pipes;
	// int		nb_commands;
}	t_data;




// error.c
void	ft_error(char *message, int code);

// init.c
t_data	*init_data(int argc, char **argv, char **env);


#endif