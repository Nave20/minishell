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

static void	update_tab(char **str, int start, int end, char *env_var)
{
	char	*update;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(*str) - (end - start) + ft_strlen(env_var);
	update = malloc((len + 1) * sizeof(char));
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
}

static void	rep_env_var(t_data *data, int i, int start, int end)
{
	char	*var;
	char	*env_var;
	int		j;

	j = 0;
	var = malloc((end - start + 1) * sizeof(char));
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
		update_tab(&data->token[i].tab, start, end, env_var);
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
		}
		start++;
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
		while (data->token[i].tab[j] && data->token[i].tab[0] != '\'')
		{
			if (data->token[i].tab[j] == '$' && data->token[i].tab[j
				+ 1] != '\0')
				get_env_var(data, i);
			j++;
		}
		j = 0;
		i++;
	}
}
