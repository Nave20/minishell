/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:44:18 by vpirotti          #+#    #+#             */
/*   Updated: 2025/05/27 11:44:18 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

void sigint_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\nminishell> ", 12);
}

// void	exec_two(t_all *all)
// {
//
// }

void	exec_one(t_data *data)
{
	int		pipe_fd[2];
	int		prev_fd;
	t_cmd	*cmd;
	// pid_t	now_pid;
	pid_t	pid[MAX_COM];
	int		i;
	int		j;
	int		status;
	t_all	all;

	all.data = data;
	all.cmd = data->cmd;
	all.env = data->env;
	all.env_tab = NULL;
	all.exit_code = -1;
	prev_fd = -1;
	cmd = all.cmd;
	i = 0;
	j = 0;
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	while (cmd)
	{
		if (cmd->hrdc_path)
		{
			cmd->infile = open(cmd->hrdc_path, O_RDONLY);
			if (cmd->infile == -1)
			{
				ft_putstr_fd(RED"Error opening heredoc file :", 2);
				ft_putendl_fd(all.cmd->hrdc_path, 2);
				ft_putendl_fd(".\n"RESET, 2);
				perror(NULL);
			}
		}
		else if (cmd->infile_name)
		{
			cmd->infile = open(cmd->infile_name, O_RDONLY);
			if (cmd->infile == -1)
				perror("open infile");
		}
		else
			cmd->infile = -1;
		if (cmd->outfile_name)
		{
			cmd->outfile = open(cmd->outfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (cmd->outfile == -1)
				perror("open outfile");
		}
		else
			cmd->outfile = -1;
		if (cmd->next && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		// if (0)
		// {
		// 	now_pid = fork();
		// 	if (now_pid == -1)
		// 	{
		// 		perror("fork");
		// 		if (pipe_fd[0] != -1)
		// 			close(pipe_fd[0]);
		// 		if (pipe_fd[1] != -1)
		// 			close(pipe_fd[1]);
		// 		if (prev_fd != -1)
		// 			close(prev_fd);
		// 		while (i > 0)
		// 			waitpid(pid[--i], NULL, 0);
		// 		break;
		// 	}
		// 	if (now_pid == 0)
		// 	{
		// 		signal(SIGINT, SIG_DFL);
		// 		signal(SIGQUIT, SIG_DFL);
		// 		if (cmd->infile != -1)
		// 			dup2(cmd->infile, STDIN_FILENO);
		// 		else if (prev_fd != -1)
		// 			dup2(prev_fd, STDIN_FILENO);
		// 		if (cmd->outfile != -1)
		// 			dup2(cmd->outfile, STDOUT_FILENO);
		// 		else if (cmd->next)
		// 			dup2(pipe_fd[1], STDOUT_FILENO);
		// 		if (pipe_fd[0] != -1 && pipe_fd[0] != STDIN_FILENO)
		// 			close(pipe_fd[0]);
		// 		if (pipe_fd[1] != -1 && pipe_fd[1] != STDOUT_FILENO)
		// 			close(pipe_fd[1]);
		// 		if (prev_fd != -1 && prev_fd != STDIN_FILENO)
		// 			close(prev_fd);
		// 		// exec_two(*all);
		// 		exit(EXIT_FAILURE);
		// 	}
		// 	else
		// 	{
		// 		if (cmd->hrdc_path)
		// 		{
		// 			unlink(cmd->hrdc_path);
		// 			free(cmd->hrdc_path);
		// 			cmd->hrdc_path = NULL;
		// 		}
		// 		pid[i++] = now_pid;
		// 		if (prev_fd != -1)
		// 			close(prev_fd);
		// 		if (cmd->infile != -1)
		// 			close(cmd->infile);
		// 		if (cmd->outfile != -1)
		// 			close(cmd->outfile);
		// 		if (cmd->next)
		// 			prev_fd = pipe_fd[0];
		// 		else
		// 			prev_fd = -1;
		// 		if (pipe_fd[1] != -1)
		// 			close(pipe_fd[1]);
		// 		cmd = cmd->next;
		// 	}
		// }
		// else
		// {
			printf(RED"test"RESET);
			hub(all);
			break;
		// }
	}
	while (j < i)
	{
		waitpid(pid[j], &status, 0);
		if (WIFEXITED(status))
			all.exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			int sig = WTERMSIG(status);
			if (sig == SIGINT)
				write(1, "\n", 1);
			all.exit_code = 128 + sig;
			printf("Process %d terminated by signal %d\n", pid[j], sig);
		}
		j++;
	}
	if (prev_fd != -1)
		close(prev_fd);
}
