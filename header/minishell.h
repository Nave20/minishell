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

//-------------------------------INCLUDE-------------------------------
# include <stdio.h>
# include <stdint.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

//-------------------------------STRUCTS-------------------------------
typedef enum e_quote
{
	N_QUOTE,
	S_QUOTE,
	D_QUOTE
}						t_quote;
typedef enum e_type
{
	CMD,
	CMD_BI,
	ARG,
	FLAG,
	ENV_V,
	INFILE,
	OUTFILE,
	DELIM,
	PIPE,
	REDIR_IN,
	HEREDOC,
	REDIR_OUT,
	APPEND
}						t_type;
typedef struct s_cmd	t_cmd;
typedef struct s_token	t_token;
typedef struct s_data	t_data;
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
	char				*arg;
	char				*flag;
	char				*infile;
	char				*outfile;
	char				*delim;
	t_cmd				*next;
};

struct					s_data
{
	char				*input;
	int					cmd_count;
	t_token				*token;
	t_cmd				*cmd;
};

typedef	struct	s_env
{
	char			*name;
	char			*line;
	struct s_env	*next;
}				t_env;

typedef struct	s_all
{
	t_env	*env;
}				t_all;
//--------------------------------MAIN---------------------------------

//-------------------------------PARSING-------------------------------
int						word_count(char *input);
int						tokenize_input(t_data *data, char *input);
char					*put_token(t_data *data, int start, int end);
bool					is_locked(char *tab, int c);
void					define_token(t_data *data);
bool					is_locked(char *tab, int c);
bool					is_build_in(char *cmd);
bool					is_simple_cmd(t_data *data, int end);
void					free_data(t_data *data);
void					set_infile(t_data *data);
void					set_outfile(t_data *data);

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
t_all	hub(t_all all, char **args);

//---------------------------------DEV---------------------------------
void	env_printer(t_env *env);

#endif