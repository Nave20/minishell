#include "../header/minishell.h"

int	put_token_new(char *old, char **new, int start, int end)
{
	int			i;
	static int	nbword;

	i = 0;
	if (!old)
	{
		nbword = 0;
		return (0);
	}
	// printf("nbword = %d\n", nbword);
	new[nbword] = ft_calloc(end - start + 2, sizeof(char));
	if (!new[nbword])
		return (-1);
	while (start <= end)
	{
		new[nbword][i] = old[start];
		start++;
		i++;
	}
	new[nbword][i] = '\0';
	nbword++;
	if (nbword > ft_tablen(new))
		nbword = 0;
	return (0);
}

static int	char_check(char *old, char **new, int *i)
{
	if (old[*i] == ' ')
		(*i)++;
	if (old[*i] == '"')
	{
		if (handle_double_quote_new(old, new, i) == -1)
			return (-1); // faire fonction erreur
	}
	if (old[*i] == '\'')
	{
		if (handle_simple_quote_new(old, new, i) == -1)
			return (-1); // VDD
	}
	if (old[*i] == '|' || old[*i] == '<' || old[*i] == '>')
	{
		if (handle_special_c_new(old, new, i) == -1)
			return (-1);
	}
	if (old[*i] != ' ' && old[*i] != '\'' && old[*i] != '"')
	{
		if (handle_normal_new(old, new, i) == -1)
			return (-1);
	}
	return (0);
}

static int	fill_new(char *old, char **new)
{
	int	i;

	i = 0;
	while (old[i])
	{
		if (char_check(old, new, &i) == -1)
			return (-1);
	}
	return (0);
}

int	fill_new_token(t_data *data, char **new, int nbword)
{
	int	i;

	i = 0;
	data->token = ft_calloc(nbword + 1, sizeof(t_token));
	if (!data->token)
		return (-1);
	while (new[i])
	{
		data->token[i].tab = ft_strdup(new[i]);
		i++;
	}
	free_double_tab(new);
	operator_check(data);
	define_operator(data);
	define_token(data, 1);
	put_token_new(NULL, NULL, 0, 0);
	return (0);
}

int	last_split(t_data *data)
{
	int		i;
	int		nbword;
	char	**new;

	i = 0;
	nbword = 0;
	while (data->token[i].tab)
		nbword += word_count(data->token[i++].tab);
	printf("nbword = %d\n", nbword);
	new = ft_calloc(nbword + 1, sizeof(char *));
	if (!new)
		exit_failure(data, "minishell : memory allocation failed\n");
	i = 0;
	while (data->token[i].tab)
	{
		if (fill_new(data->token[i].tab, new) == -1)
			return (-1);
		i++;
	}
	free_token(data);
	fill_new_token(data, new, nbword);
	return (0);
}
