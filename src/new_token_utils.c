#include "../header/minishell.h"

int	handle_double_quote_new(char *old, char **new, int *i)
{
	int	start;
	int	end;

	if (!is_locked(old))
		return (-1);
	(*i)++;
	start = (*i) - 1;
	while (old[*i])
	{
		(*i)++;
		if (old[*i] == '"' && (old[(*i) + 1] == ' ' || old[(*i) + 1] == '\0'))
		{
			end = (*i);
			if (put_token_new(old, new, start, end) == -1)
				return (-1);
			(*i)++;
			return (0);
		}
	}
	return (0);
}

int	handle_simple_quote_new(char *old, char **new, int *i)
{
	int	start;
	int	end;

	if (!is_locked(old))
		return (-1); // a completer avec erreur correspondante
	(*i)++;
	start = (*i) - 1;
	while (old[*i])
	{
		(*i)++;
		if (old[*i] == '\'' && (old[(*i) + 1] == ' ' || old[(*i) + 1] == '\0'))
		{
			end = (*i);
			if (put_token_new(old, new, start, end) == -1)
				return (-1);
			(*i)++;
			return (0);
		}
	}
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

int	handle_special_c_new(char *old, char **new, int *i)
{
	if (old[*i] == '|')
	{
		if (put_token_new(old, new, *i, *i) == -1)
			return (-1);
		(*i)++;
	}
	if (old[*i] == '<')
	{
		if (handle_redirect_new(old, new, i, '<') == -1)
			return (-1);
	}
	if (old[*i] == '>')
	{
		if (handle_redirect_new(old, new, i, '>') == -1)
			return (-1);
	}
	return (0);
}

int	handle_normal_new(char *old, char **new, int *i)
{
	int	start;
	int	end;

	start = *i;
	while (old[*i])
	{
		(*i)++;
		if (old[*i] == ' ' || old[*i] == '\0' || old[*i] == '<'
			|| old[*i] == '>' || old[*i] == '|')
		{
			end = (*i) - 1;
			if (put_token_new(old, new, start, end) == -1)
				return (-1);
			return (0);
		}
	}
	return (0);
}
