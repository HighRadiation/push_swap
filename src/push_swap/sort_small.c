/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boksuz <boksuz@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:35:20 by boksuz            #+#    #+#             */
/*   Updated: 2025/10/14 17:35:21 by boksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_max_index_pos(t_stack *stack)
{
	int	max;
	int	index;
	int	max_index;

	max = stack->value;
	index = 0;
	max_index = 0;
	while (stack)
	{
		if (stack->value > max)
		{
			max = stack->value;
			max_index = index;
		}
		index++;
		stack = stack->next;
	}
	return (max_index);
}

void	sort_three(t_stack **stack_a)
{
	int	max_index;

	max_index = get_max_index_pos(*stack_a);
	if (max_index == 0)
		ra(stack_a);
	else if (max_index == 1)
		rra(stack_a);
	if ((*stack_a)->value > (*stack_a)->next->value)
		sa(stack_a);
}

static void	push_min_to_b(t_stack **stack_a, t_stack **stack_b)
{
	int	min_pos;
	int	size;

	size = stack_size(*stack_a);
	min_pos = get_min_index(*stack_a);
	if (min_pos <= size / 2)
	{
		while (min_pos > 0)
		{
			ra(stack_a);
			min_pos--;
		}
	}
	else
	{
		while (min_pos < size)
		{
			rra(stack_a);
			min_pos++;
		}
	}
	pb(stack_a, stack_b);
}

void	sort_small(t_stack **stack_a, t_stack **stack_b)
{
	int	size;

	size = stack_size(*stack_a);
	if (size == 2)
	{
		if ((*stack_a)->value > (*stack_a)->next->value)
			sa(stack_a);
		return ;
	}
	while (size > 3)
	{
		push_min_to_b(stack_a, stack_b);
		size--;
	}
	sort_three(stack_a);
	while (*stack_b)
		pa(stack_a, stack_b);
}

