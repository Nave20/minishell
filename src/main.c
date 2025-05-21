/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaysant <lpaysant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:24:01 by lpaysant          #+#    #+#             */
/*   Updated: 2025/05/21 13:02:20 by lpaysant         ###   ########.fr       */
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
	token = ft_calloc(end - start + 2, sizeof(char));
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

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data)
	{
		if (data->token)
		{
			while (data->token[i].tab)
			{
				free(data->token[i].tab);
				i++;
			}
			free(data->token);
		}
	}
}

int	main(void)
{
	t_data	data;
	int		nbword;

	data.input = readline("minishell> ");
	if (data.input)
	{
		add_history(data.input);
		nbword = word_count(data.input);
		data.token = ft_calloc(nbword + 1, sizeof(t_token));
		if (tokenize_input(&data, data.input) == -1)
			return (-1); // gestion erreur
		free(data.input);
		define_token(&data);
		// print_token(&data);
		free_data(&data);
	}
	return (0);
}
