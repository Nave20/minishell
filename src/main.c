#include "../header/minishell.h"

static int	main_hub(t_data *data)
{
	int	nbword;

	data->input = readline("minishell> ");
	if (data->input)
	{
		add_history(data->input);
		nbword = word_count(data->input);
		data->token = ft_calloc(nbword + 1, sizeof(t_token));
		if (!data->token)
			return (err_return_token(data,
					"minishell : memory allocation failed\n"));
		if (tokenize_input(data, data->input) == -1)
		{
			data->err_code = 2;
			return (2); // gestion erreur
		}
		print_token(data);
		free(data->input);
		data->input = NULL;
		if (operator_check(data) == -1)
			return (2);
		data->cmd_count = 1;
		define_token(data, 0);
		// print_token(data);
		create_cmd_lst(data);
		free_data(data);
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
		// data.input = readline("minishell> ");
		// if (data.input)
		// {
		// 	add_history(data.input);
		// 	nbword = word_count(data.input);
		// 	printf("nbword = %d\n", nbword);
		// 	data.token = ft_calloc(nbword + 1, sizeof(t_token));
		// 	if (!data.token)
		// 		err_return(&data, "minishell : memory allocation failed\n");
		// 	if (tokenize_input(&data, data.input) == -1)
		// 	{
		// 		ft_putstr_fd("minishell : unclosed quotes\n", 2);
		// 		data.err_code = 2;
		// 		return (2); // gestion erreur
		// 	}
		// 	free(data.input);
		// 	data.input = NULL;
		// 	operator_check(&data);
		// 	data.cmd_count = 1;
		// 	print_token(&data);
		// 	define_token(&data, 0);
		// 	// print_token(&data);
		// 	create_cmd_lst(&data);
		// 	free_data(&data);
		// }
	}
	return (0);
}
