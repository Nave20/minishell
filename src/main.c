/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaysant <lpaysant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:24:01 by lpaysant          #+#    #+#             */
/*   Updated: 2025/05/15 14:29:59 by lpaysant         ###   ########.fr       */
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

	i = 0;
	while (tab[i])
	{
		if (tab[i] == c)
			return (true);
		i++;
	}
	return (false);
}

int	handle_quote(t_data *data, int *nbword, int quote, int *i)
{
	int	start;
	int	end;

	if (!is_locked(data->input + (*i), quote))
		return (-1); // a completer avec erreur correspondante
	(*i)++;
	start = *i;
	while (data->input[*i])
	{
		if (data->input[*i] == quote)
		{
			end = (*i) - 1;
			data->token[*nbword].tab = put_token(data, start, end);
			// copie le token entre quotes dans tab
			if (quote == '\'')
				data->token[*nbword].quote = S_QUOTE;
			if (quote == '"')
				data->token[*nbword].quote = D_QUOTE;
			(*nbword)++;
		}
		(*i)++;
	}
	return (0);
}

void	handle_normal(t_data *data, int *nbword, int *i, int count)
{
	int	start;
	int	end;

	start = *i;
	while (data->input[*i])
	{
		if (data->input[*i] == ' ' || data->input[*i] == '\0'
			|| data->input[*i] == '\'' || data->input[*i] == '"')
		{
			if (count == 0)
			{
				end = (*i) - 1;
				data->token[*nbword].tab = put_token(data, start, end);
				data->token[*nbword].quote = N_QUOTE;
			}
			(*nbword)++;
		}
		(*i)++;
	}
}

int	input_pars(t_data *data, char *input)
{
	int	i;
	int	nbword;

	i = 0;
	nbword = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			i++;
		if (input[i] == '"')
		{
			if (handle_quote(data, &nbword, '"', &i) == -1)
				return (-1); // faire fonction erreur
		}
		if (input[i] == '\'')
		{
			if (handle_quote(data, &nbword, '\'', &i) == -1)
				return (-1); // VDD
		}
		if (input[i] != ' ' && input[i] != '\'' && input[i] != '"')
			handle_normal(data, &nbword, &i, 0);
	}
	return (0);
}

// void	print_token(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (data->token[i])
// }

int	word_count(char *input)
{
	int	i;
	int	nbword;

	i = 0;
	nbword = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '"' && input[i] != '\'')
		{
			printf("input = %c\n", input[i]);
			nbword++;
			while (input[i] != ' ' && input[i] != '"' && input[i] != '\'')
				i++;
		}
		while (input[i] == ' ')
			i++;
		if (input[i] == '"')
		{
			while (input[i] && input[i] != '"')
				i++;
			if (input[i] == '"')
			{
				printf("input = %c\n", input[i]);
				nbword++;
				i++;
			}
		}
		if (input[i] == '\'')
		{
			while (input[i] && input[i] != '\'')
				i++;
			if (input[i] == '\'')
			{
				printf("input = %c\n", input[i]);
				nbword++;
				i++;
			}
		}
	}
	return (nbword);
}

int	main(void)
{
	t_data	data;
	int		nbword;

	data.input = readline("minishell>");
	if (data.input)
	{
		nbword = word_count(data.input);
		printf("string : %s\n nbword : %d\n", data.input, nbword);
		// input_pars(&data, data.input);
		// free(data.input);
		// print_token(&data);
	}
	return (0);
}
