/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasp <lucasp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:24:01 by lpaysant          #+#    #+#             */
/*   Updated: 2025/05/20 21:58:57 by lucasp           ###   ########.fr       */
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

int	handle_quote(t_data *data, int *nbword, int quote, int *i)
{
	int	start;
	int	end;

	if (!is_locked(data->input + (*i), quote))
		return (-1); // a completer avec erreur correspondante
	(*i)++;
	start = *i;
	while (data->input[*i] != quote)
		(*i)++;
	end = (*i) - 1;
	data->token[*nbword].tab = put_token(data, start, end);
	// copie le token entre quotes dans tab
	if (quote == '\'')
		data->token[*nbword].quote = S_QUOTE;
	if (quote == '"')
		data->token[*nbword].quote = D_QUOTE;
	(*nbword)++;
	(*i)++;
	return (0);
}

void	handle_redirect(t_data *data, int *nbword, int *i, int c)
{
	if (data->input[*i + 1] == c)
	{
		data->token[*nbword].tab = put_token(data, *i, *i + 1);
		(*i) += 2;
	}
	else
	{
		data->token[*nbword].tab = put_token(data, *i, *i);
		(*i)++;
	}
	(*nbword)++;
	return ;
}

void	handle_special_c(t_data *data, int *nbword, int *i)
{
	if (data->input[*i] == '|')
	{
		data->token[*nbword].tab = put_token(data, *i, *i);
		(*nbword)++;
		(*i)++;
		return ;
	}
	if (data->input[*i] == '<')
	{
		if (data->input[*i + 1] == '<')
			data->token[*nbword].type = HEREDOC;
		else
			data->token[*nbword].type = REDIR_IN;
		handle_redirect(data, nbword, i, '<');
	}
	if (data->input[*i] == '>')
	{
		if (data->input[*i + 1] == '>')
			data->token[*nbword].type = APPEND;
		else
			data->token[*nbword].type = REDIR_OUT;
		handle_redirect(data, nbword, i, '>');
	}
}

void	handle_normal(t_data *data, int *nbword, int *i)
{
	int	start;
	int	end;

	start = *i;
	while (data->input[*i])
	{
		(*i)++;
		if (data->input[*i] == ' ' || data->input[*i] == '\0'
			|| data->input[*i] == '\'' || data->input[*i] == '"'
			|| data->input[*i] == '<' || data->input[*i] == '>'
			|| data->input[*i] == '|')
		{
			end = (*i) - 1;
			data->token[*nbword].tab = put_token(data, start, end);
			data->token[*nbword].quote = N_QUOTE;
			(*nbword)++;
			return ;
		}
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
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			handle_special_c(data, &nbword, &i);
		if (input[i] != ' ' && input[i] != '\'' && input[i] != '"')
			handle_normal(data, &nbword, &i);
	}
	return (0);
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

int	word_count(char *input)
{
	int	i;
	int	nbword;

	i = 0;
	nbword = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '"' && input[i] != '\''
			&& input[i] != '|' && input[i] != '<' && input[i] != '>')
		{
			nbword++;
			while (input[i] != ' ' && input[i] != '"' && input[i] != '\''
				&& input[i] != '\0' && input[i] != '|' && input[i] != '<'
				&& input[i] != '>')
				i++;
		}
		if (input[i] == '|')
		{
			nbword++;
			i++;
		}
		if (input[i] == '<')
		{
			nbword++;
			i++;
			if (input[i] == '<')
				i++;
		}
		if (input[i] == '>')
		{
			nbword++;
			i++;
			if (input[i] == '>')
				i++;
		}
		while (input[i] == ' ')
			i++;
		if (input[i] == '"')
		{
			i++;
			while (input[i] && input[i] != '"')
				i++;
			if (input[i] == '"')
			{
				nbword++;
				i++;
			}
		}
		if (input[i] == '\'')
		{
			i++;
			while (input[i] && input[i] != '\'')
				i++;
			if (input[i] == '\'')
			{
				nbword++;
				i++;
			}
		}
	}
	printf("nbword = %d\n", nbword);
	return (nbword);
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
		if (input_pars(&data, data.input) == -1)
			return (-1); // gestion erreur
		free(data.input);
		print_token(&data);
	}
	return (0);
}
