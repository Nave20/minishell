/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:31:31 by vpirotti          #+#    #+#             */
/*   Updated: 2025/05/13 11:31:31 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include "../libft/libft.h"

int main(int argc, char **argv, char **env)
{
	(void) argc;
	t_all	all;
	(void) env;
	(void) argv;

	terminal(all);
	// all.env = pars_env(env);
	// ft_cd(&argv[1], all.env);
	// ft_pwd();
	// ft_cd(&argv[3], all.env);
	// ft_pwd();
	// free_env(all.env);
}