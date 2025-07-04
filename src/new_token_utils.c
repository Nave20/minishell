#include "../header/minishell.h"

int	handle_double_quote_new(t_data *data, char *old, char **new, int *i)
{
	int	start;
	int	end;

	if (!is_locked(old))
		return (err_return_token(data, "minishell: unclosed quotes\n", 2));
	start = (*i);
	while (old[*i] && old[*i] != ' ')
	{
		if (old[*i] == '\'' || old[*i] == '"')
			skip_quotes(old, i);
		else
			(*i)++;
	}
	end = (*i);
	if (put_token_new(old, new, start, end) == -1)
		return (err_return_token(data, "minishell: memory allocation failed\n",
				1));
	return (0);
}

int	handle_simple_quote_new(t_data *data, char *old, char **new, int *i)
{
	int	start;
	int	end;

	if (!is_locked(old))
		return (err_return_token(data, "minishell: unclosed quotes\n", 2));
	start = (*i);
	while (old[*i] && old[*i] != ' ')
	{
		if (old[*i] == '\'' || old[*i] == '"')
			skip_quotes(old, i);
		else
			(*i)++;
	}
	end = (*i);
	if (put_token_new(old, new, start, end) == -1)
		return (err_return_token(data, "minishell: memory allocation failed\n",
				1));
	return (0);
}

int	handle_redirect_new(char *old, char **new, int *i, int c)
{
	if (old[*i + 1] == c)
	{
		if (put_token_new(old, new, *i, *i + 1) == -1)
			return (-1);
		(*i) += 2;
	}
	else
	{
		if (put_token_new(old, new, *i, *i) == -1)
			return (-1);
		(*i)++;
	}
	return (0);
}

int	handle_special_c_new(t_data *data, char *old, char **new, int *i)
{
	if (old[*i] == '|')
	{
		if (put_token_new(old, new, *i, *i) == -1)
			return (err_return_token(data,
					"minishell: memory allocation failed\n", 1));
		(*i)++;
	}
	if (old[*i] == '<')
	{
		if (handle_redirect_new(old, new, i, '<') == -1)
			return (err_return_token(data,
					"minishell: memory allocation failed\n", 1));
	}
	if (old[*i] == '>')
	{
		if (handle_redirect_new(old, new, i, '>') == -1)
			return (err_return_token(data,
					"minishell: memory allocation failed\n", 1));
	}
	return (0);
}

int	handle_normal_new(t_data *data, char *old, char **new, int *i)
{
	int	start;
	int	end;

	start = *i;
	while (old[*i])
	{
		(*i)++;
		skip_quotes(old, i);
		if (old[*i] == ' ' || old[*i] == '\0' || old[*i] == '<'
			|| old[*i] == '>' || old[*i] == '|')
		{
			end = (*i) - 1;
			if (put_token_new(old, new, start, end) == -1)
				return (err_return_token(data,
						"minishell: memory allocation failed\n", 1));
			return (0);
		}
	}
	return (0);
}
