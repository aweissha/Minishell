/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:44:13 by aweissha          #+#    #+#             */
/*   Updated: 2024/03/13 18:35:43 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "../libft/libft.h"


typedef enum
{
	EXEC,
	BUILDIN,
	REDIR,
	PIPE,
}	node_type;

typedef enum
{
	WORD,
	BUILDIN,
	REDINPT,
	REDOUT,
	REDAPPND,
	HEREDOC,
	PIPE,
}	token_type;


typedef struct s_node
{
	// all types
	node_type	type;
	// exec type
	char		**command;
	// redir types
	char		*infile;
	char		*outfile;
	char		*limiter;
	node_type	*exec;
	// pipe type
	node_type	*left;
	node_type	*right;
}	t_node;

typedef struct s_token
{
	token_type	type;
	char		*token;
}	t_token;

typedef struct s_data
{
	int			argc;
	char 		**argv;
	char 		**env;
	t_token		*tokens;
	t_node		*parse_tree;
	int			nb_tokens;
	// int			nb_pipes;
	// int			nb_commands;
	// t_command	*command_table;
	// char		*infile;
	// char		*outfile;
	// token_type	output_redir_type;
	// token_type	input_redir_type;
}	t_data;




// // error.c
// void	ft_error(char *message, int code);

// // init.c
// t_data	*init_data(int argc, char **argv, char **env);


#endif