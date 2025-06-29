#include "../header/minishell.h"

static void	cmd_count(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i].tab)
	{
		if (data->token[i].tab[0] == '|')
		{
			printf("cmd++ for '|'\n");
			data->cmd_count++;
		}
		i++;
	}
	data->cmd_count++;
	printf("i = %d, cmd count = %d\n", i, data->cmd_count);
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
	free_data(data);
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
	}
	else
		return (1);
	return (0);
}

int	main(void)
{
	t_data	data;

	while (1)
	{
		if (main_hub(&data) == 1)
			return (1);
	}
	return (0);
}
