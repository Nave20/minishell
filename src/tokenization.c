#include "../header/minishell.h"

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
		data->token[*nbword].type = PIPE;
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

int	tokenize_input(t_data *data, char *input)
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
