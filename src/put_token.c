/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:51:22 by vpirotti          #+#    #+#             */
/*   Updated: 2025/05/27 11:51:22 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

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

char	*put_token(t_data *data, int start, int end)
{
	char	*token;
	int		i;

	i = 0;
	token = ft_calloc(end - start + 2, sizeof(char));
	if (!token)
	{
		free_data(data);
		exit(EXIT_FAILURE);
	}
	while (start <= end)
	{
		token[i] = data->input[start];
		start++;
		i++;
	}
	token[i] = '\0';
	return (token);
}

void	print_token(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i].tab)
	{
		printf("token[%d] = %s, type = %d, quote = %d\n", i, data->token[i].tab,
			data->token[i].type, data->token[i].quote);
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
		add_history(data.input);
		nbword = word_count(data.input);
		data.token = ft_calloc(nbword + 1, sizeof(t_token));
		if (!data.token)
			return (-1);
		if (tokenize_input(&data, data.input) == -1)
			return (-1); // gestion erreur
		free(data.input);
		data.cmd_count = 1;
		define_token(&data);
		// create_cmd_lst(&data);
		print_token(&data);
		free_data(&data);
	}
	return (0);
}
