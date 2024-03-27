/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:44:13 by aweissha          #+#    #+#             */
/*   Updated: 2024/03/27 17:50:20 by aweissha         ###   ########.fr       */
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
	WORD,
	EXEC,
	BUILDIN,
	REDIR,
	REDINPT,
	REDOUT,
	REDAPPND,
	HEREDOC,
	PIPE,
	TOKEN_SPACE,
}	type;

typedef struct s_token	t_token;
typedef struct s_node	t_node;
typedef struct s_env	t_env;

typedef struct s_node
{
	// all types
	type	node_type;
	// exec type
	char	**command;
	// redir types
	char	*infile;
	char	*outfile;
	char	*limiter;
	t_node	*next;
	// pipe type
	t_node	*left;
	t_node	*right;
}	t_node;

typedef struct s_token
{
	type		token_type;
	char		*token_str;
	t_token		*next;
	t_token		*previous;
}	t_token;

typedef struct s_env
{
	char	*var_name;
	char	*var_str;
	t_env	*next;
}	t_env;

typedef struct s_data
{
	int		argc;
	char	**argv;
	char 	**env;
	t_token	*token_list;
	t_node	*parse_tree;
	t_env	*env_list;
}	t_data;

// env_list_utils.c
t_env	*env_list_last(t_env *env_list);
t_env	*env_list_new(char *var_name, char *var_str);
void	env_list_add_back(t_env **env_list, t_env *new);

// env.c
char	*get_var_str(char *env_line);
char	*get_var_name(char *env_line);
void	create_env_list(t_data *data);

// error.c
void	ft_error(char *message, int code);

// free.c
void	free_token(t_token	*token);

// handle_quotes.c
int		quotes_left(char *start, char *position, char c);
int		quotes_right(char *start, char *position, char c);
int		in_quotes(char *start, char *position);

// init.c
t_node	*init_node(type node_type);
t_data	*init_data(int argc, char **argv, char **env);

// lexer.c
type	tok_type(char *token_str);
// char	*ft_strtok_mod(char *str, const char *sep);
void	lexer(char *input, t_data *data);

// parse_utils.c
void	update_token_list(t_token **token_list, t_token *redir_token);
void	config_redir_node(t_token *redir_token, t_node *redir_node);
t_token	*find_token(t_token	*token_list, type token_type);

// parser.c
t_node	*parse_exec(t_token *token_list);
t_node	*parse_redir(t_token *token_list);
t_node	*parse_pipe(t_token *token_list);

// token_list_utils.c
int		toklist_size(t_token *token_list);
void	toklist_clear(t_token **token_list);
t_token	*ft_toknew(char *token_str, type token_type);
t_token	*ft_toklast(t_token *token_list);
void	ft_tokadd_back(t_token **token_list, t_token *new);

// utils.c
int		ft_fork(void);

#endif