/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boksuz <boksuz@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:35:20 by boksuz            #+#    #+#             */
/*   Updated: 2025/10/14 17:35:21 by boksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_stack	*create_stack(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*new_node;
	int		i;
	int		value;

	stack_a = NULL;
	i = 1;
	while (i < argc)
	{
		value = ft_atoi(argv[i]);
		new_node = stack_new(value);
		if (!new_node)
		{
			free_stack(&stack_a);
			error_exit();
		}
		stack_add_back(&stack_a, new_node);
		i++;
	}
	return (stack_a);
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (argc < 2)
		return (0);
	if (!check_args(argv))
		error_exit();
	stack_a = create_stack(argc, argv);
	if (!stack_a)
		error_exit();
	if (has_duplicates(stack_a))
	{
		free_stack(&stack_a);
		error_exit();
	}
	stack_b = NULL;
	push_swap(&stack_a, &stack_b);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}

