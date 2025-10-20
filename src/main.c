/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boksuz <boksuz@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:35:20 by boksuz            #+#    #+#             */
/*   Updated: 2025/10/20 17:35:21 by boksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	char	**args;
	int		should_free_args;

	if (argc < 2)
		return (0);
	args = parse_arguments(argc, argv);
	should_free_args = (argc == 2);
	if (!args || !check_args(args))
	{
		if (should_free_args && args)
			free_split_array(args);
		error_exit();
	}
	stack_a = create_stack_from_args(args);
	if (should_free_args)
		free_split_array(args);
	if (!stack_a || has_duplicates(stack_a))
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


