/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasp <lucasp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:24:01 by lpaysant          #+#    #+#             */
/*   Updated: 2025/05/20 23:27:53 by lucasp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

char	*put_token(t_data *data, int start, int end)
{
	char	*token;
	int		i;

	i = 0;
	token = ft_calloc(end - start + 1, sizeof(char));
	while (start <= end)
	{
		token[i] = data->input[start];
		start++;
		i++;
	}
	token[i] = '\0';
	return (token);
}

bool	is_locked(char *tab, int c)
{
	int	i;

	i = 1;
	while (tab[i])
	{
		if (tab[i] == c)
			return (true);
		i++;
	}
	return (false);
}

void	print_token(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i].tab)
	{
		printf("token[%d] = %s\n", i, data->token[i].tab);
		i++;
	}
}

int	main(void)
{
	t_data	data;
	int		nbword;

	data.input = readline("minishell> ");
	if (data.input)
	{
		nbword = word_count(data.input);
		data.token = ft_calloc(nbword + 1, sizeof(t_token));
		if (tokenize_input(&data, data.input) == -1)
			return (-1); // gestion erreur
		free(data.input);
		print_token(&data);
	}
	return (0);
}
