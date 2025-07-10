#include "../header/minishell.h"

static void	cmd_count(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i].tab)
	{
		if (data->token[i].tab[0] == '|')
			data->cmd_count++;
		i++;
	}
	data->cmd_count++;
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
			if (handle_quotes(data, &nbword, &i) == -1)
				return (-1);
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			if (handle_special_c(data, &nbword, &i) == -1)
				return (-1);
		if (input[i] != ' ' && input[i] != '\'' && input[i] != '"')
			if (handle_normal(data, &nbword, &i) == -1)
				return (-1);
	}
	return (0);
}

static int	parsing_hub(t_data *data)
{
	if (tokenize_input(data, data->input) == -1)
		return (-1);
	print_token(data);
	free(data->input);
	data->input = NULL;
	data->cmd_count = 0;
	if (operator_check(data) == -1)
		return (-1);
	if (define_token(data, 0) == -1)
		return (-1);
	// print_token(data);
	cmd_count(data);
	if (create_cmd_lst(data) == -1)
		return (-1);
	return (0);
}

static int	main_hub(t_data *data)
{
	int	nbword;

	data->input = readline("minishell> ");
	if (data->input)
	{
		add_history(data->input);
		nbword = word_count(data->input);
		printf("nbword = %d\n", nbword);
		data->token = ft_calloc(nbword + 1, sizeof(t_token));
		if (!data->token)
			return (err_return_token(data,
					"minishell : memory allocation failed\n", 1));
		if (parsing_hub(data) == -1)
			return (-1);
		exec_one(data);
		free_data(data);
	}
	else
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	while (1)
	{
		data.env = pars_env(envp);
		if (main_hub(&data) == 1)
			return (1);
	}
	return (0);
}
