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

void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_printf("%s\n", env[i]) == -1)
			perror("printf error");
		i++;
	}
}