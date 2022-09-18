/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <mcorneli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:07:03 by mcorneli          #+#    #+#             */
/*   Updated: 2022/09/18 15:28:45 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdarg.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <signal.h>

typedef struct s_env {
	int		size;
	t_list	*en_list;
	char	**env;
	char	**my_env;
}				t_env;

typedef struct s_main {
	t_env	*my_env;
	char	*str;
	int		status;
	t_list	*head;
	t_list	*curr;
}	t_main;

typedef struct s_pid_fd
{
	int	**pids;
	int	file;
	int	size_pid;
	int	*fid;
}				t_pid_fd;

typedef struct s_sig {
	int	status;
	int	flag;
}				t_sig;

extern t_sig	g_sig;

void	print_cmds(t_cmdinfo *cmds);
int		print_double_char(char **str, int count);
void	print_lex_list(t_list *lex);

int		ft_error(char *cmd, char *args, char *error);
int		error_syntax(int token);
int		error_env(char *cmd, char *arg);
int		error_usage(char *cmd, char *argv);

void	clean_double_char(char **arr, int size);
void	clear_path_array_int(int **array, int size);
void	clear_t_list(t_list *lst);
void	clear_t_cmdlist(t_cmdinfo *lst);
void	clear_t_main(t_main *mi);
void	clear_group_list(t_list *head);

void	create_envp_arr(t_env *env);
void	create_envp_list(char **envp, t_env *env);
void	init_s(t_main *mi, char **envp);
void	print_env_list(t_list *env);
int		get_keys_in_envp_lst(t_list *lst, char *src);
t_list	*find_env_elem(char *name, t_list *lst);

void	start_parse(t_list **g_list, t_main *mi);
int		get_lex_type(char *str, int i, t_list *lex_list);
t_list	*get_lexer(char *str);
int		check_group_status(t_list *lex_list);
char	*parse_word(t_main *mi, int size, char *t);
char	*get_dollar(char *str, t_main *mi);
char	*parse_quotes(int size, char *t);
char	*parse_double_quotes(t_main *mi, int size, char *t);
int		get_lex_type_helper_2(char *str, int i, t_list *lex_list);
void	execute_group_level(t_list *g_list, t_main *mi);
t_list	*get_redirect(t_list *lst, t_cmdinfo *cmd, t_main *mi);
char	*get_word_value(t_list *lst, t_main *mi);

void	start_exec(int size, t_cmdinfo *lst, t_main *mi, int *fid);
void	execute(t_cmdinfo *cmds, t_main *mi);
int		**pipe_init(int **pipes, int size);
void	set_exit_code(int status);
void	close_pipes(int **pipes, int size);
char	*find_path(char **env, char *name);
void	exec_cmd(t_cmdinfo *cmd, t_main *mi);
void	ft_close_files(t_cmdinfo *cmds);
int		ft_open_files(t_cmdinfo *cmd);

void	if_here_doc(t_cmdinfo *cmds, t_main *mi, int **pipes, int i);
void	ft_gnl_read(t_cmdinfo *cmd, int *pid);

void	change_signal(void);
int		check_build_in(t_cmdinfo *cmd, t_main *mi);
int		build_echo(t_cmdinfo *cmd);
int		build_export(t_cmdinfo *cmd, t_main *mi);
int		build_unset(t_cmdinfo *cmd, t_main *mi);
int		build_pwd(void);
int		build_cd(t_cmdinfo *cmd, t_env *env);
int		ft_exit(char **prog_args, t_main *mi, t_cmdinfo *cmd);

#endif