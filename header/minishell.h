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

#ifndef PHILO_H
# define PHILO_H

# define CLEAR "\033[H\033[J"
# define YELLOW "\033[33m"
# define RESET "\033[0m"
# define BLUE "\033[34m"
# define CYAN "\033[36m"
# define RED "\033[31m"

//-------------------------------INCLUDE-------------------------------
# include <stdio.h>
# include <stdint.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include "../libft/libft.h"

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
	OUTFILE
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

//------------------------------BUILTINS-------------------------------
bool	ft_echo(char **content);
bool	ft_pwd(void);
void	ft_env(char **env);

#endif