/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boksuz <boksuz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 08:52:00 by boksuz            #+#    #+#             */
/*   Updated: 2025/12/18 09:16:00 by boksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	free_errors(t_list **a, char **args, int argc_flag)
{
	int	i;

	free_stack(a);
	if (argc_flag == 2 && args)
	{
		i = 0;
		while (args[i])
			free(args[i++]);
		free(args);
	}
	error_exit();
}

static void	check_duplicates(t_list **stack)
{
	t_list	*head;
	t_list	*tmp;

	head = *stack;
	while (head)
	{
		tmp = head->next;
		while (tmp)
		{
			if (head->value == tmp->value)
				free_errors(stack, NULL, 0);
			tmp = tmp->next;
		}
		head = head->next;
	}
}

static void	process_args(t_list **a, char **args, int argc_flag)
{
	long	nb;
	int		j;

	j = 0;
	if (argc_flag != 2)
		j = 1;
	while (args[j])
	{
		if (!is_num(args[j]))
			free_errors(a, args, argc_flag);
		nb = ft_atol(args[j]);
		if (nb > INT_MAX || nb < INT_MIN)
			free_errors(a, args, argc_flag);
		ft_lstadd_back(a, ft_lstnew_node((int)nb));
		if (argc_flag == 2)
			free(args[j]);
		j++;
	}
	if (argc_flag == 2)
		free(args);
}

void	stack_init(t_list **a, char **argv, int argc_flag)
{
	char	**args;

	if (argc_flag == 2)
		args = ft_split(argv[1], ' ');
	else
		args = argv;
	process_args(a, args, argc_flag);
	check_duplicates(a);
	index_stack(a);
}
