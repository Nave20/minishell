/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:50:38 by vpirotti          #+#    #+#             */
/*   Updated: 2025/05/19 10:50:38 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include "../libft/libft.h"

void	env_printer(t_env *env)
{
	t_env	*ptr;

	ptr = env;
	while (ptr->next)
	{
		printf("%s : %s\n", ptr->name, ptr->line);
		ptr = ptr->next;
	}
}