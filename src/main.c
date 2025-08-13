/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:56:15 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/13 21:29:59 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_exit_code;

void	cleanup_buffer_and_parser(t_data *data)
{
	if (data->parser)
	{
		free_p_list(data->parser);
		data->parser = NULL;
	}
	free(data->buffer);
}

void	main_loop(t_data *data)
{
	while (1)
	{
		setup_signal_handlers();
		init_parse_list(&data->parser);
		data->buffer = readline(PROMPT);
		if (!data->buffer)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (!check_for_unclosed_quotes(data->buffer))
		{
			init_parser(data);
			if (init_lexer(data))
				executor(data);
		}
		if (data->buffer[0])
			add_history(data->buffer);
		cleanup_buffer_and_parser(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	init_all(&data, envp);
	main_loop(&data);
	free_data(&data);
	return (g_exit_code);
}
