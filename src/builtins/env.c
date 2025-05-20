/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:04:03 by vpirotti          #+#    #+#             */
/*   Updated: 2025/05/15 15:04:03 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

void	ft_env(t_env *env)
{
	while (env->next)
	{
		printf(YELLOW"%s="RESET"%s\n", env->name, env->line);
		env = env->next;
	}
	printf(YELLOW"%s="RESET"%s\n", env->name, env->line);
}