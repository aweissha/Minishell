/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:25:30 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/12 18:25:33 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:52:02 by sparth            #+#    #+#             */
/*   Updated: 2024/04/11 21:12:10 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*free_null(char *del)
{
	free(del);
	return (NULL);
}

void	path_clean(t_path_prep check, int status)
{
	int	i;

	i = 0;
	if (check.directory)
	{
		while (check.directory[i])
			free(check.directory[i++]);
		free(check.directory);
	}
	if (check.cmd_prep)
		free(check.cmd_prep);
	if (check.first_cmd)
		free(check.first_cmd);
	if (check.paths)
		free(check.paths);
	if (check.pathcheck && status == 0)
		free(check.pathcheck);
}

t_path_prep	init_struct(void)
{
	t_path_prep	check;

	check.directory = NULL;
	check.cmd_prep = NULL;
	check.pathcheck = NULL;
	check.first_cmd = NULL;
	check.paths = NULL;
	return (check);
}
char	*cmd_cut(char *cmd)
{
	int		i;
	int		k;
	char	*cutted;

	i = 0;
	while (cmd[i] != ' ' && cmd[i])
		i++;
	cutted = (char *)malloc(sizeof(char) * i + 1);
	if (!cutted)
		return (NULL);
	k = 0;
	while (k < i)
	{
		cutted[k] = cmd[k];
		k++;
	}
	cutted[k] = '\0';
	return (cutted);
}

char	*path_check2(char *cmd, t_path_prep check)
{
	int	i;

	i = 0;
	while (check.directory[i])
	{
		check.pathcheck = ft_strjoin(check.directory[i], check.cmd_prep);
		if (!check.pathcheck)
			return (path_clean(check, 0), NULL);
		if (access(check.pathcheck, X_OK) == 0)
			return (path_clean(check, 1), check.pathcheck);
		check.pathcheck = free_null(check.pathcheck);
		i++;
	}
	path_clean(check, 0);
	if (access(cmd, X_OK) == 0 && ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return (cmd);
	return (NULL);
}

char	*path_check(char *cmd, char *path)
{
	t_path_prep	check;

	check = init_struct();
	check.first_cmd = cmd_cut(cmd);
	if (!check.first_cmd)
		return (NULL);
	if (strncmp(check.first_cmd, "./", 2) == 0
		&& access(check.first_cmd, X_OK) == 0)
		return (check.first_cmd);
	if (!path)
		return (path_clean(check, 0), NULL);
	if (strncmp(check.first_cmd, "./", 2) == 0
		&& (ft_strlen(check.first_cmd) != ft_strlen(cmd) || access(cmd, X_OK)))
		return (path_clean(check, 0), NULL);
	check.cmd_prep = ft_strjoin("/", check.first_cmd);
	check.first_cmd = free_null(check.first_cmd);
	check.paths = ft_strtrim(path, "PATH=");
	check.directory = ft_split(check.paths, ':');
	if (!check.directory || !check.paths || !check.cmd_prep)
		return (path_clean(check, 0), NULL);
	check.paths = free_null(check.paths);
	return (path_check2(cmd, check));
}

void	input_redirect(t_node *node, t_data *data)
{
	int	fd_in;

	fd_in = open(node->infile, O_RDONLY);
	if (fd_in == -1)
	{
		fprintf(stderr, "error opening infile\n");
		exit(1);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
		exit (1);
	if (close(fd_in) == -1)
		exit (1);
	if (node->next)
		exec(node->next, data);
	else
		exit (0);
}

void	heredoc(t_node *node, t_data *data)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		exit (2);
	while (1)
	{
		write(1, "here_doc> ", 10);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(node->limiter, line, ft_strlen(node->limiter)) == 0
			&& ft_strlen(node->limiter) + 1 == ft_strlen(line))
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
		line = NULL;
	}
	if (dup2(fd[0], STDIN_FILENO) == -1)
		exit (1);
	if (close(fd[0]) == -1 || close(fd[1]) == -1)
		exit (1);
	if (node->next)
		exec(node->next, data);
	else
		exit (0);
}

void	output_redirect(t_node *node, t_data *data)
{
	int fd_out;
	
	fd_out = open(node->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		fprintf(stderr, "error opening outfile\n");
		exit (1);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		exit(1);
	if (close(fd_out) == -1)
		exit (1);
	if (node->next)
		exec(node->next, data);
	else
		exit (0);
}

void	output_redirect_append(t_node *node, t_data *data)
{
	int fd_out;
	
	fd_out = open(node->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out == -1)
	{
		fprintf(stderr, "error opening outfile\n");
		exit (1);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		exit(1);
	if (close(fd_out) == -1)
		exit (1);
	if (node->next)
		exec(node->next, data);
	else
		exit (0);
}

void piping(t_node *node, t_data *data)
{
		int		fd[2];
		int		wpidstatus;
		pid_t	pid_left;
		pid_t	pid_right;
		
		if (pipe(fd) == -1)
			exit (1);
		pid_left = fork();
		if (pid_left == -1)
			exit (1);
		if (pid_left == 0)
		{
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				exit (1);
			if (close(fd[0]) == -1 || close(fd[1]) == -1)
				exit(1);
			exec(node->left, data);
		}
		pid_right = fork();
		if (pid_right == -1)
			exit (1);
		if (pid_right == 0)
		{
			if (dup2(fd[0], STDIN_FILENO) == -1)
				exit (1);
			if (close(fd[0]) == -1 || close(fd[1]) == -1)
				exit(1);
			exec(node->right, data);
		}
		if (pid_right != 0 && pid_left != 0)
		{
			if (close(fd[0]) == -1 || close(fd[1]) == -1)
				exit (29);
		}
		waitpid(pid_right, &wpidstatus, 0);
		waitpid(pid_left, NULL, 0);
		if (WIFEXITED(wpidstatus))
		{
			exit (WEXITSTATUS(wpidstatus));
		}
}

void	path_error_message(char *error)
{
	if (access(cmd_cut(error), X_OK) && access(cmd_cut(error), R_OK) == 0)
		fprintf(stderr, "%s%s: %s\n", "minishell: ", cmd_cut(error), strerror(13));
	else if (strncmp(error, "./", 2) == 0)
		fprintf(stderr, "%s%s: %s\n", "minishell: ", cmd_cut(error), strerror(2));
	else
		fprintf(stderr, "%s%s: %s\n", "minishell: ", cmd_cut(error), "command not found");
}

bool	check_n_option(char *option)
{
	int	i;
	
	i = 2;
	if (option[0] == '-' && option[1] == 'n')
	{
		while (option[i])
		{
			if (option[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	else
		return (0);
}

void	echo(t_node *node)
{
	int	i;

	i = 1;
	if (!node->command[i])
		printf("\n");
	else if (check_n_option(node->command[i]))
	{
		while (node->command[++i])
		{
			printf("%s", node->command[i]);
			if (node->command[i + 1])
				printf(" ");
		}
	}
	else
	{
		while (node->command[i])
		{
			printf("%s", node->command[i++]);
			if (node->command[i])
				printf(" ");
		}
		printf("\n");
	}
	exit (0);
}

void	pwd(void)
{
	char *cwd;
	cwd = getcwd(NULL, PATH_MAX);
	printf("%s\n", cwd);
	free(cwd);
	exit (0);
}

void	check_if_buildin(t_node *node, t_data *data)
{
	if (ft_strncmp (node->command[0], "env", 4) == 0)
	{
		while (data->env_list)
		{
			printf("%s=%s\n", data->env_list->var_name, data->env_list->var_str);
			data->env_list = data->env_list->next;
		}
		exit (0);
	}
	if ((node->command[0][0] == 'e' || node->command[0][0] == 'E')
		&& (node->command[0][1] == 'c' || node->command[0][1] == 'C')
		&& (node->command[0][2] == 'h' || node->command[0][2] == 'H')
		&& (node->command[0][3] == 'o' || node->command[0][3] == 'O')
		&& node->command[0][4] == '\0')
		echo(node);
	if (ft_strncmp (node->command[0], "pwd", 4) == 0)
		pwd();
	if (ft_strncmp (node->command[0], "exit", 5) == 0
		|| ft_strncmp (node->command[0], "cd", 3) == 0
		|| ft_strncmp (node->command[0], "unset", 6) == 0
		|| ft_strncmp (node->command[0], "export", 7) == 0)
		exit (0);
}

void	execution(t_node *node, t_data *data)
{
	char	*path;
	// char	**cmd;

	check_if_buildin(node, data);
	path = path_check(node->command[0], getenv("PATH="));
	if (!path)
		path_error_message(node->command[0]);
	execve(path, node->command, NULL);
	// fprintf(stderr, "execve failed !\n");
	if (access((path), X_OK) && access((path), W_OK) == 0)
		exit (126);
	exit(127);
	
}

void	string_cut(char *s, int flag)
{
	int		slash_count;
	int		char_count;
	int		i;
	char	cut[PATH_MAX];

	slash_count = 0;
	char_count = 0;
	i = 0;
	while (s[char_count])
	{
		if (s[char_count] == '/')
			slash_count++;
		char_count++;
	}
	char_count = 0;
	if (slash_count <= 1)
		return ;
	while (slash_count)
	{
		if (slash_count - flag == 0)
			break;
		if (s[char_count] == '/')
			slash_count--;
		char_count++;
	}
	while (i < char_count)
	{
		cut[i] = s[i];
		i++;
	}
	cut[i] = '\0';
	if (chdir(cut) == -1)
	{
		printf("chdir failed\n");
		exit (1);
	}
}

// delte unset when export is working correctly 
void	change_pwds(t_data *data, bool flag)
{
	char *temp;
	char *cwd;
	
	cwd =  getcwd(NULL, PATH_MAX);
	if (flag == 0)
	{
		temp = ft_strjoin("OLDPWD=", cwd);
		if (!temp)
		{
			printf("ft_strjoin failed\n");
			exit (1);
		}
	}
	if (flag == 1)
	{
		temp = ft_strjoin("PWD=", cwd);
		if (!temp)
		{
			printf("ft_strjoin failed\n");
			exit (1);
		}
	}
	free(cwd);
	export(temp, data);
	free(temp);
}
void	prep_dir_change(t_data *data, int flag, char *path)
{
	char *cwd;
	if (path)
	{
			change_pwds(data, 0);
			if(chdir(path) == -1)
			{
				printf("chdir failed\n");
				exit (1);
			}
			change_pwds(data, 1);
	}
	else
	{
		change_pwds(data, 0);
		cwd = getcwd(NULL, PATH_MAX);
		string_cut(cwd, flag);
		free(cwd);
		change_pwds(data, 1);
	}
}

// delte unset when export is working correctly 
bool	switch_between_dir(t_data *data)
{
	char *old_pwd;
	char *temp;
	t_env *temp_lst;
	
	temp_lst = data->env_list;
	while (temp_lst)
	{
		if (ft_strncmp(temp_lst->var_name, "OLDPWD", 7) == 0)
		{
			old_pwd = getcwd(NULL, PATH_MAX);
			if (chdir(temp_lst->var_str) == -1)
			{
				printf("chdir failed\n");
				exit (1);
			}
			temp = ft_strjoin("OLDPWD=", old_pwd);
			free(old_pwd);
			if (!temp)
			{
				printf("ft_strjoin failed\n");
				exit (1);
			}
			export(temp, data);
			free(temp);
			change_pwds(data, 1);
			return (1);
		}
		temp_lst = temp_lst->next;
	}
	printf("minishell: cd: OLDPWD not set");
	return (-1);
}

int	path_change(char *cmd, t_data *data)
{
	if (access(cmd, F_OK))
	{
		fprintf(stderr, "minishell: cd: no such file or directory: %s\n", cmd);
		return (-1);
	}
	prep_dir_change(data, 0, cmd);
	return (1);
}

int	look_4_cd(t_node *node, t_data *data)
{
	if (node->node_type == EXEC && node->command[0] &&
		ft_strncmp(node->command[0], "cd", ft_strlen(node->command[0]) + 1) == 0
		&& node->command[1] == NULL)
	{
		prep_dir_change(data, 2, NULL);
		return (1);
	}
	if (node->node_type == EXEC && node->command[0] &&
		ft_strncmp(node->command[0], "cd", ft_strlen(node->command[0]) + 1) == 0
		&& node->command[1] && node->command[2] == NULL)
	{
		if (ft_strncmp(node->command[1], ".", 3) == 0)
			return (1);
		else if (ft_strncmp(node->command[1], "..", 3) == 0)
			prep_dir_change(data, 0, NULL);
		else if (ft_strncmp(node->command[1], "~", 2) == 0)
			prep_dir_change(data, 2, NULL);
		else if (ft_strncmp(node->command[1], "-", 2) == 0)
			return (switch_between_dir(data));
		else
			return (path_change(node->command[1], data));
		return (1);
	}
	return (0);
}

void	exec(t_node *node, t_data *data)
{
	
	if (node->node_type == PIPE)
		piping(node, data);
	else if (node->node_type == REDINPT)
		input_redirect(node, data);
	else if (node->node_type == REDOUT)
		output_redirect(node, data);
	else if (node->node_type == REDAPPND)
		output_redirect_append(node, data);
	else if (node->node_type == HEREDOC)
		heredoc(node, data);
	else if (node->node_type == EXEC)
		execution(node, data);
}

void	look_4_exit(t_node *node, t_data *data)
{
	if (node->node_type == EXEC && node->command[0] != NULL &&
		ft_strncmp(node->command[0], "exit", 5) == 0
		&& node->command[1] == NULL)
	{
		free_everything(data);
		printf("exit\n");
		exit (0);
	}
}

int	look_4_unset(t_node *node, t_data *data)
{
	int	i;
	
	i = 1;
	if (node->node_type == EXEC && node->command[0] != NULL &&
		ft_strncmp(node->command[0], "unset", 6) == 0)
	{
		while (node->command[i])
		{
			unset(node->command[i], data);
			i++;
		}
		return (1);
	}
	return (0);
}

int	look_4_export(t_node *node, t_data *data)
{
	int	i;
	
	i = 1;
	if (node->node_type == EXEC && node->command[0] != NULL &&
		ft_strncmp(node->command[0], "export", 7) == 0)
	{
		while (node->command[i])
		{
			export(node->command[i], data);
			i++;
		}
		return (1);
	}
	return (0);
}

int	look_4_buildins(t_node *node, t_data *data)
{
	int	r_value;

	look_4_exit(node, data);
	if (look_4_unset(node, data))
		return (1);
	if (look_4_export(node ,data))
		return (1);
	r_value = look_4_cd(node, data);
	if (r_value)
		return (r_value);
	return (0);
}

void	sig_child_int(int sig)
{
	(void)sig;
	exit(1);
}

void	sig_child_quit(int sig)
{
	(void)sig;
	exit(1);
}

int	pre_exec(t_node *node, t_data *data)
{
	pid_t	pid;
	int		wpidstatus;
	int		r_value;
	
	if (node == NULL)
		return (0);
	r_value = look_4_buildins(node, data);
	if (r_value == 1)
		return (0);
	if (r_value == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		exit (1);
	if (pid == 0)
	{
		signal(SIGINT, sig_child_int);
		signal(SIGQUIT, sig_child_quit);
		exec(node, data);
	}
	waitpid(pid, &wpidstatus, 0);
	if (WIFEXITED(wpidstatus))
		return (WEXITSTATUS(wpidstatus));
	if (WIFSIGNALED(wpidstatus))
	{
		if (128 + WTERMSIG(wpidstatus) == 131)
			write (2, "Quit: 3", 7);
		write(2, "\n", 1);
		return (128 + WTERMSIG(wpidstatus));
	}
	return (86);
}

