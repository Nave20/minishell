/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 08:50:27 by vpirotti          #+#    #+#             */
/*   Updated: 2025/05/21 08:50:27 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

void	terminal(t_all all)
{
	char	*input;

	while (true)
	{
		input = readline(CYAN UNDER BOLD"MiniShell:"RESET);
		if (!input)
			break ;
		if (*input)
			add_history(input);
		printf("%s\n", input);
		free(input);
	}
}