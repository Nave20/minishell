#include "../header/minishell.h"

static int	handle_quotes(t_data *data, int *nbword, int *i)
{
	int	start;
	int	end;

	if (!is_locked(data->input))
		return (err_return_token(data, "minishell : unclosed quotes\n"));
	start = (*i);
	while (data->input[*i])
	{
		while (data->input[*i] == '\'' || data->input[*i] == '"')
			skip_quotes(data->input, i);
		if (data->input[*i] == ' ' || data->input[*i] == '\0')
		{
			end = (*i);
			data->token[*nbword].tab = put_token(data, start, end);
			if (!data->token[*nbword].tab)
				return (err_return_token(data,
						"minishell: memory allocation failed\n"));
			(*nbword)++;
			return (0);
		}
		else
			(*i)++;
	}
	return (0);
}

static int	handle_redirect(t_data *data, int *nbword, int *i, int c)
{
	if (data->input[*i + 1] == c)
	{
		data->token[*nbword].tab = put_token(data, *i, *i + 1);
		if (!data->token[*nbword].tab)
			return (err_return_token(data,
					"minishell: memory allocation failed\n"));
		(*i) += 2;
	}
	else
	{
		data->token[*nbword].tab = put_token(data, *i, *i);
		if (!data->token[*nbword].tab)
			return (err_return_token(data,
					"minishell: memory allocation failed\n"));
		(*i)++;
	}
	(*nbword)++;
	return (0);
}

static int	handle_chevron(t_data *data, int *nbword, int *i)
{
	if (data->input[*i] == '<')
	{
		if (data->input[*i + 1] == '<')
			data->token[*nbword].type = HEREDOC;
		else
			data->token[*nbword].type = REDIR_IN;
		if (handle_redirect(data, nbword, i, '<') == -1)
			return (-1);
	}
	if (data->input[*i] == '>')
	{
		if (data->input[*i + 1] == '>')
			data->token[*nbword].type = APPEND;
		else
			data->token[*nbword].type = REDIR_OUT;
		if (handle_redirect(data, nbword, i, '>') == -1)
			return (-1);
	}
	return (0);
}

static int	handle_special_c(t_data *data, int *nbword, int *i)
{
	if (data->input[*i] == '|')
	{
		data->token[*nbword].tab = put_token(data, *i, *i);
		if (!data->token[*nbword].tab)
			return (err_return_token(data,
					"minishell: memory allocation failed\n"));
		data->token[*nbword].type = PIPE;
		(*nbword)++;
		(*i)++;
		return (0);
	}
	if (data->input[*i] == '<' || data->input[*i] == '>')
	{
		if (handle_chevron(data, nbword, i) == -1)
			return (-1);
	}
	return (0);
}

static int	handle_normal(t_data *data, int *nbword, int *i)
{
	int	start;
	int	end;

	start = *i;
	while (data->input[*i])
	{
		(*i)++;
		skip_quotes(data->input, i);
		if (data->input[*i] == ' ' || data->input[*i] == '\0'
			|| data->input[*i] == '<' || data->input[*i] == '>'
			|| data->input[*i] == '|')
		{
			end = (*i) - 1;
			data->token[*nbword].tab = put_token(data, start, end);
			if (!data->token[*nbword].tab)
				return (err_return_token(data,
						"minishell: memory allocation failed\n"));
			(*nbword)++;
			return (0);
		}
	}
	return (0);
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
		if (input[i] == '"' || input[i] == '\'')
		{
			if (handle_quotes(data, &nbword, &i) == -1)
				return (-1);
		}
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			if (handle_special_c(data, &nbword, &i) == -1)
				return (-1);
		}
		if (input[i] != ' ' && input[i] != '\'' && input[i] != '"')
		{
			if (handle_normal(data, &nbword, &i) == -1)
				return (-1);
		}
	}
	return (0);
}
