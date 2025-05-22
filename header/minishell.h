/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaysant <lpaysant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:31:36 by vpirotti          #+#    #+#             */
/*   Updated: 2025/05/22 15:41:26 by lpaysant         ###   ########.fr       */
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
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

//-------------------------------STRUCTS-------------------------------
typedef enum e_quote
{
	N_QUOTE,
	S_QUOTE,
	D_QUOTE
}			t_quote;
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
}			t_type;
typedef struct s_token
{
	int		quote;
	int		type;
	char	*tab;
}			t_token;

typedef struct s_cmd
{
	char	*cmd;
	char	*arg;
	char	*opt;
	int		infile;
	int		outfile;
	int		delim;
	t_cmd	*next;
}			t_cmd;

typedef struct s_data
{
	char	*input;
	int		cmd_count;
	t_token	*token;
	t_list	*cmd;
}			t_data;

//--------------------------------MAIN---------------------------------

//-------------------------------PARSING-------------------------------
int			word_count(char *input);
int			tokenize_input(t_data *data, char *input);
char		*put_token(t_data *data, int start, int end);
bool		is_locked(char *tab, int c);
void		define_token(t_data *data);
bool		is_locked(char *tab, int c);
bool		is_build_in(char *cmd);
bool		is_simple_cmd(t_data *data, int end);
void		free_data(t_data *data);

#endif
