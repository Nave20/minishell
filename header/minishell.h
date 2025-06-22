/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaysant <lpaysant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:31:36 by vpirotti          #+#    #+#             */
/*   Updated: 2025/06/22 17:55:53 by lpaysant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define CLEAR "\033[H\033[J"
# define YELLOW "\033[33m"
# define RESET "\033[0m"
# define BLUE "\033[34m"
# define CYAN "\033[36m"
# define RED "\033[31m"

//-------------------------------INCLUDE-------------------------------
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
#endif
