#include "../header/minishell.h"

static void	cpy_env_var(int *i, char *env_var, char *update)
{
	int	j;

	j = 0;
	while (env_var && env_var[j])
	{
		update[*i] = env_var[j];
		(*i)++;
		j++;
	}
}

static int	update_var(char **str, int start, int end, char *env_var)
{
	char	*update;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(*str) - (end - start) + ft_strlen(env_var);
	update = malloc((len + 1) * sizeof(char));
	if (!update)
		return (-1);
	while ((*str)[j])
	{
		if (j == start)
		{
			cpy_env_var(&i, env_var, update);
			j = end;
		}
		if ((*str)[j])
			update[i++] = (*str)[j++];
	}
	update[i] = '\0';
	free(*str);
	*str = update;
	return (0);
}

static int	update_null_var(char **str, int start, int end)
{
	char	*update;
	int		len;
	int		i;
	int		j;

	if (ft_strlen(*str) - (end - start) == 0)
	{
		free(*str);
		*str = ft_calloc(1, sizeof(char));
		return (0);
	}
	len = ft_strlen(*str) - (end - start);
	update = malloc((len + 2) * sizeof(char));
	i = 0;
	j = 0;
	if (!update)
		return (-1);
	while ((*str)[i])
	{
		if (i == start)
			i = end;
		update[j] = (*str)[i];
		if ((*str)[i])
			i++;
		j++;
	}
	update[j] = '\0';
	free(*str);
	*str = update;
	return (0);
}

static void	rep_env_var(t_data *data, int i, int start, int end)
{
	char	*var;
	char	*env_var;
	int		j;

	j = 0;
	var = malloc((end - start + 1) * sizeof(char));
	if (!var)
		exit_failure(data, "minishell : memory allocation failed\n");
	while (start < end)
	{
		var[j] = data->token[i].tab[start];
		start++;
		j++;
	}
	var[j] = '\0';
	start = end - j - 1;
	env_var = getenv(var);
	if (env_var)
	{
		if (update_var(&data->token[i].tab, start, end, env_var) == -1)
			exit_failure(data, "minishell : memory allocation failed\n");
	}
	else
	{
		if (update_null_var(&data->token[i].tab, start, end) == -1)
			exit_failure(data, "minishell : memory allocation failed\n");
	}
	free(var);
}

static void	get_env_var(t_data *data, int i)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (data->token[i].tab[start])
	{
		if (data->token[i].tab[start] == '$' && data->token[i].tab[start
			+ 1] != '\0')
		{
			end = start + 1;
			while (ft_isalnum(data->token[i].tab[end])
				|| data->token[i].tab[end] == '_')
				end++;
			rep_env_var(data, i, start + 1, end);
			if (data->token[i].tab[0] == '\0')
				return ;
		}
		start++;
	}
}

static char	*cpy_no_quotes(char *str)
{
	char	*cpy;
	int		i;
	int		j;

	j = 0;
	i = 0;
	cpy = malloc(ft_strlen(str) * sizeof(char));
	if (!cpy)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				cpy[j++] = str[i++];
			if (str[i] == '\'')
				i++;
		}
		else if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				cpy[j++] = str[i++];
			if (str[i] == '"')
				i++;
		}
		else
			cpy[j++] = str[i++];
	}
	cpy[j] = '\0';
	printf("cpynoquotes = %s\n", cpy);
	free(str);
	return (cpy);
}

void	remove_quotes(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->token[i].tab)
	{
		while (data->token[i].tab[j] && data->token[i].tab[j] != '\''
			&& data->token[i].tab[j] != '"')
			j++;
		if (data->token[i].tab[j] == '\'' || data->token[i].tab[j] == '"')
		{
			data->token[i].tab = cpy_no_quotes(data->token[i].tab);
			if (!data->token[i].tab)
				exit_failure(data, "minishell : memory allocation failed\n");
		}
		i++;
		j = 0;
	}
}

void	set_env_var(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->token[i].tab)
	{
		j = 0;
		while (data->token[i].tab[j] && data->token[i].tab[0]
			&& data->token[i].type != DELIM)
		{
			if (data->token[i].tab[j] == '\'')
			{
				j++;
				while (data->token[i].tab[j] && data->token[i].tab[j] != '\'')
					j++;
			}
			if (data->token[i].tab[j] == '$' && data->token[i].tab[j
				+ 1] != '\0' && data->token[i].tab[j + 1] != '"'
				&& data->token[i].tab[j + 1] != ' ' && data->token[i].tab[j
				+ 1] != '\'')
				get_env_var(data, i);
			j++;
		}
		i++;
	}
}
