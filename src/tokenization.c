#include "../header/minishell.h"

static int	handle_double_quote(t_data *data, int *nbword, int *i)
{
	int	start;
	int	end;

	if (!is_locked(data->input))
		return (-1); // a completer avec erreur correspondante
	(*i)++;
	start = (*i) - 1;
	while (data->input[*i])
	{
		(*i)++;
		if (data->input[*i] == '"' && (data->input[(*i) + 1] == ' '
				|| data->input[(*i) + 1] == '\0'))
		{
			end = (*i);
			data->token[*nbword].tab = put_token(data, start, end);
			// copie le token entre quotes dans tab
			(*nbword)++;
			(*i)++;
			return (0);
		}
	}
	return (0);
}

static int	handle_simple_quote(t_data *data, int *nbword, int *i)
{
	int	start;
	int	end;

	if (!is_locked(data->input))
		return (-1); // a completer avec erreur correspondante
	(*i)++;
	start = (*i) - 1;
	while (data->input[*i])
	{
		(*i)++;
		if (data->input[*i] == '\'' && (data->input[(*i) + 1] == ' '
			|| data->input[(*i) + 1] == '\0'))
		{
			end = (*i);
			data->token[*nbword].tab = put_token(data, start, end);
			// copie le token entre quotes dans tab
			(*nbword)++;
			(*i)++;
			return (0);
		}
	}
	return (0);
}

static void	handle_redirect(t_data *data, int *nbword, int *i, int c)
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

static void	handle_special_c(t_data *data, int *nbword, int *i)
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

static void	handle_normal(t_data *data, int *nbword, int *i)
{
	int	start;
	int	end;

	start = *i;
	while (data->input[*i])
	{
		(*i)++;
		if (data->input[*i] == ' ' || data->input[*i] == '\0'
			|| data->input[*i] == '<' || data->input[*i] == '>'
			|| data->input[*i] == '|')
		{
			end = (*i) - 1;
			data->token[*nbword].tab = put_token(data, start, end);
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
			if (handle_double_quote(data, &nbword, &i) == -1)
				return (-1); // faire fonction erreur
		}
		if (input[i] == '\'')
		{
			if (handle_simple_quote(data, &nbword, &i) == -1)
				return (-1); // VDD
		}
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			handle_special_c(data, &nbword, &i);
		if (input[i] != ' ' && input[i] != '\'' && input[i] != '"')
			handle_normal(data, &nbword, &i);
	}
	return (0);
}
