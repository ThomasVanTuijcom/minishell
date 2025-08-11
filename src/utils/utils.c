/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:25:08 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/11 13:14:53 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void	try_free(char *s)
{
	if (s)
		free(s);
}

t_p_node	*skip_faulty_nodes(t_p_node *curr)
{
	size_t	runner;
	int		contain_var;

	while (curr && curr->token_type != PIPE)
	{
		runner = -1;
		contain_var = 0;
		while (curr->content[++runner])
		{
			if (curr->content[runner] == '$' && curr->content[runner + 1]
				&& curr->content[runner + 1] != '\'' && curr->content[runner
				+ 1] != '"')
				contain_var = 1;
		}
		if (contain_var && !curr->content_exp_wq[0])
			curr = curr->next;
		else
			return (curr);
	}
	return (curr);
}

bool	is_minishell(char *path)
{
	size_t	i;

	if (!ft_strcmp(path, "./minishell"))
		return (true);
	i = ft_strlen(path);
	if (i < 11)
		return (false);
	i -= 10;
	if (!ft_strcmp(&path[i], "/minishell"))
		return (true);
	return (false);
}

// TO DELETE
static void	print_str(const char *label, const char *str)
{
	printf("%s: %s\n", label, str ? str : "(null)");
}

static void	print_str_array(const char *label, char **arr)
{
	printf("%s: ", label);
	if (!arr)
	{
		printf("(null)\n");
		return ;
	}
	printf("[");
	for (int i = 0; arr[i]; i++)
	{
		printf("\"%s\"", arr[i]);
		if (arr[i + 1])
			printf(", ");
	}
	printf("]\n");
}

static void	print_int_array(const char *label, int *arr)
{
	printf("%s: ", label);
	if (!arr)
	{
		printf("(null)\n");
		return ;
	}
	printf("[");
	for (int i = 0; arr[i] != -1; i++)
	{ // sentinel value expected
		printf("%d", arr[i]);
		if (arr[i + 1] != -1)
			printf(", ");
	}
	printf("]\n");
}

const char	*token_type_to_str(enum e_token_type type)
{
	switch (type)
	{
	case APPEND:
		return ("APPEND");
	case APPEND_OF:
		return ("APPEND_OF");
	case ASTERISQUE:
		return ("ASTERISQUE");
	case CMD:
		return ("CMD");
	case CMP:
		return ("CMP");
	case CONTINUE:
		return ("CONTINUE");
	case DOUBLE_PIPE:
		return ("DOUBLE_PIPE");
	case EMPTY:
		return ("EMPTY");
	case ERROR:
		return ("ERROR");
	case INVALID_HEREDOC:
		return ("INVALID_HEREDOC");
	case HEREDOC:
		return ("HEREDOC");
	case INFILE:
		return ("INFILE");
	case LIMITATOR:
		return ("LIMITATOR");
	case LOGICAL_AND:
		return ("LOGICAL_AND");
	case OPTION:
		return ("OPTION");
	case OPTION_CMD:
		return ("OPTION_CMD");
	case OUTFILE:
		return "OUTFILE";
	case PIPE:
		return "PIPE";
	case REDIR_IN:
		return "REDIR_IN";
	case REDIR_OUT:
		return "REDIR_OUT";
	case SIMPLE_ARG:
		return "SIMPLE_ARG";
	case VAR:
		return "VAR";
	case WRONG_META:
		return "WRONG_META";
	default:
		return "(unknown)";
	}
}

void	print_p_list(const t_p_list *list)
{
	const t_p_node	*node = list->head;
	int				i;

	if (!list)
	{
		printf("(null list)\n");
		return ;
	}
	printf("=== t_p_list ===\n");
	printf("pipe: [%d, %d]\n", list->pipe[0], list->pipe[1]);
	printf("pid: %d\n", list->pid);
	i = 0;
	while (node)
	{
		printf("--- Node %d ---\n", i);
		print_str("content", node->content);
		print_str("content_exp", node->content_exp);
		print_str("content_exp_wq", node->content_exp_wq);
		print_str("new_content", node->new_content);
		print_int_array("q_meta_indexes", node->q_meta_indexes);
		printf("has_quote: %s\n", node->has_quote ? "true" : "false");
		printf("index: %d\n", node->index);
		print_str_array("cmds", node->cmds);
		print_str("path", node->path);
		printf("fd: [%d, %d]\n", node->fd[0], node->fd[1]);
		printf("token_type: %s\n", token_type_to_str(node->token_type));
		printf("prev: %p\n", (void *)node->prev);
		printf("next: %p\n", (void *)node->next);
		node = node->next;
		i++;
	}
	printf("=== end of list ===\n");
}
