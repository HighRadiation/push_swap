/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boksuz <boksuz@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:35:20 by boksuz            #+#    #+#             */
/*   Updated: 2025/10/20 17:35:21 by boksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "parsing.h"

/* Create stack from parsed arguments */
t_stack	*create_stack_from_args(char **args)
{
	t_stack	*stack_a;
	t_stack	*new_node;
	int		i;
	int		value;

	stack_a = NULL;
	i = 0;
	while (args[i])
	{
		value = ft_atoi(args[i]);
		new_node = stack_new(value);
		if (!new_node)
		{
			free_stack(&stack_a);
			return (NULL);
		}
		stack_add_back(&stack_a, new_node);
		i++;
	}
	return (stack_a);
}
