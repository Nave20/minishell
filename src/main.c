/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaysant <lpaysant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:24:01 by lpaysant          #+#    #+#             */
/*   Updated: 2025/05/13 16:28:48 by lpaysant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

char	*put_token(t_data *data, int start, int end)
{
	char	token[end - start + 1];
	int		i;

	i = 0;
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

	i = 0;
	while (tab[i])
	{
		if (tab[i] == c)
			return (true);
		i++;
	}
	return (false);
}

int	handle_quote(t_data *data, char *input, int quote, int *i)
{
	int			start;
	int			end;
	static int	word;

	if (!is_locked(input + *i, quote))
		return (-1); // a completer avec erreur correspondante
	start = i;
	while (input[*i])
	{
		if (input[*i] == quote)
		{
			end = i;
			data->token[word].tab = put_token(data, start, end);
			// copie le token entre quotes dans tab
			if (quote == '\'')
				data->token[word].quote = S_QUOTE;
			if (quote == '"')
				data->token[word].quote = D_QUOTE;
			word++;
		}
		i++;
	}
	return (0);
}

void	input_pars(t_data *data, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"')
		{
			if (handle_quote(data, data->input, '"', &i) == -1)
				return (-1); // completer gestion d'erreur
		}
		if (input[i] == '\'')
		{
			if (handle_quote(data, data->input, '\'', &i) == -1)
				return (-1); // VDD
		}
	}
}

int	main(void)
{
	t_data	data;

	data.input = readline("minishell>");
	if (data.input)
	{
		input_pars(&data, data.input);
		free(data.input);
	}
}
