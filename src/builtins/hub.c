/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:03:35 by vpirotti          #+#    #+#             */
/*   Updated: 2025/05/21 10:03:35 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

t_all	hub(t_all all, char **args)
{
	if (ft_strncmp("echo", args[0], 5) == 0)
		ft_echo(&args[1]);
	else if (ft_strncmp("cd", args[0], 3) == 0)
		ft_cd(args, all.env);
	else if (ft_strncmp("pwd", args[0], 4) == 0)
		ft_pwd();
	else if (ft_strncmp("env", args[0], 4) == 0)
		ft_env(all.env);
	else if (ft_strncmp("export", args[0], 7) == 0)
		ft_export(args[1], all);
	else if (ft_strncmp("unset", args[0], 6) == 0)
		all.env = ft_unset(args[1], all);
	return (all);
}