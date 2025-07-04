/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:31:36 by vpirotti          #+#    #+#             */
/*   Updated: 2025/05/13 08:32:49 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define CLEAR "\033[H\033[J"
# define YELLOW "\033[33m"
# define RESET "\033[0m"
# define BLUE "\033[34m"
# define CYAN "\033[36m"
# define RED "\033[31m"
# define BOLD "\033[1m"
# define UNDER "\033[4m"
# define BLINK "\033[5m"
# define REVERSE "\033[7m"
# define MAX_COM 100

//-------------------------------INCLUDE-------------------------------
# include <stdio.h>
# include <stdint.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
#include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

//-------------------------------STRUCTS-------------------------------
typedef enum e_type
{
	NONE,
	CMD,
	CMD_BI,
	STR,
	INFILE,
	OUTFILE,
	DELIM,
	PIPE,
	REDIR_IN,
	HEREDOC,
	REDIR_OUT,
	APPEND
}						t_type;
typedef struct s_data	t_data;
typedef struct s_token	t_token;
typedef struct s_cmd	t_cmd;

struct					s_data
{
	char				*input;
	int					cmd_count;
	int					err_code;
	t_token				*token;
	t_cmd				*cmd;
};
struct					s_token
{
	int					quote;
	int					type;
	char				*tab;
};
struct					s_cmd
{
	char				*cmd;
	char				*cmd_bi;
	char				**str;
	char				*hrdc_path;
	char				*infile_name;
	char				*outfile_name;
	int					infile;
	int					outfile;
	t_cmd				*next;
};

typedef	struct	s_env
{
	char			*name;
	char			*line;
	struct s_env	*next;
}				t_env;

typedef struct	s_all
{
	t_cmd	*cmd;
	t_data	*data;
	t_env	*env;
	int		exit_code;
	char	**base_env;
}				t_all;
//--------------------------------MAIN---------------------------------

//-------------------------------PARSING-------------------------------
int						word_count(char *input);
int						tokenize_input(t_data *data, char *input);
char					*put_token(t_data *data, int start, int end);
bool					is_operator(char *str);
void					operator_check(t_data *data);
void					define_token(t_data *data, int k);
void					define_operator(t_data *data);
void					handle_simple_cmd(t_data *data, int start, int end);
void					handle_redir_cmd(t_data *data, int start, int end);
void					handle_redirin_cmd(t_data *data, int *i);
void					handle_redirout_cmd(t_data *data, int *i);
bool					is_locked(char *tab);
bool					is_build_in(char *cmd);
bool					is_simple_cmd(t_data *data, int end);
bool					ft_isspace(char c);
void					free_data(t_data *data);
void					free_token(t_data *data);
void					free_cmd(t_data *data);
void					free_cmd_content(t_cmd *cmd);
void					free_double_tab(char **str);
void					set_env_var(t_data *data);
void					remove_quotes(t_data *data);
void					create_cmd_lst(t_data *data);
t_cmd					*ft_cmdnew(t_data *data);
void					ft_cmdadd_back(t_cmd **lst, t_cmd *new);
t_cmd					*ft_cmdlast(t_cmd *lst);
void					set_infile(t_data *data);
void					set_outfile(t_data *data);
void					set_infile(t_data *data);
void					set_outfile(t_data *data);
void					set_heredoc(t_data *data);
bool					is_last_inf_hrdc(t_data *data, int start, int end);
void					exit_failure(t_data *data, char *str);
int						last_split(t_data *data);
int						handle_normal_new(char *old, char **new, int *i);
int						handle_special_c_new(char *old, char **new, int *i);
int						handle_redirect_new(char *old, char **new, int *i,
							int c);
int						handle_simple_quote_new(char *old, char **new, int *i);
int						handle_double_quote_new(char *old, char **new, int *i);
int						ft_tablen(char **tab);
int						put_token_new(char *old, char **new, int start,
							int end);
void					print_lst(t_data *data);
void					print_token(t_data *data);

//------------------------------TERMINAL-------------------------------
void	terminal(t_all all);

//------------------------------PARS_ENV-------------------------------
t_env	*pars_env(char **env);
t_env	*alloc(char *str);
t_env	*free_env(t_env *head);
t_env	*free_node(t_env *node);

//------------------------------BUILTINS-------------------------------
bool	ft_echo(char **content);
bool	ft_cd(char **args, t_env *env);
bool	ft_pwd(void);
void	ft_env(t_env *env);
void	ft_export(char *str, t_all all);
t_env	*ft_unset(char *str, t_all all);
void	ft_exit(t_all all);
t_all	hub(t_all all);

//---------------------------------DEV---------------------------------
void	env_printer(t_env *env);

#endif