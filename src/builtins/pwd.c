/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:56:56 by vpirotti          #+#    #+#             */
/*   Updated: 2025/05/15 14:56:56 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>

#include "../../header/minishell.h"
#include "../../libft/libft.h"

bool	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("pwd");
		return (1);
	}
	ft_printf(BLUE"%s\n"RESET, cwd);
	return (0);
}