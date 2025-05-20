/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasp <lucasp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:31:36 by vpirotti          #+#    #+#             */
/*   Updated: 2025/05/20 22:28:52 by lucasp           ###   ########.fr       */
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
	S_QUOTE,
	D_QUOTE,
	N_QUOTE
}			t_quote;
typedef enum e_type
{
	STRING,
	CMD,
	CMD_BI,
	FLAG,
	PIPE,
	ENV_V,
	INFILE,
	OUTFILE,
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
typedef struct s_data
{
	char	*input;
	t_token	*token;
}			t_data;

//--------------------------------MAIN---------------------------------
int			word_count(char *input);
//-------------------------------PRINTF--------------------------------

#endif
