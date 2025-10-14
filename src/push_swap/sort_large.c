/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boksuz <boksuz@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:35:20 by boksuz            #+#    #+#             */
/*   Updated: 2025/10/14 17:35:21 by boksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_max_bits(t_stack *stack)
{
	int	max;
	int	bits;

	max = stack_size(stack);
	bits = 0;
	while ((max - 1) >> bits)
		bits++;
	return (bits);
}

void	sort_large(t_stack **stack_a, t_stack **stack_b)
{
	int		max_bits;
	int		i;
	int		j;
	int		size;
	t_stack	*tmp;

	max_bits = get_max_bits(*stack_a);
	size = stack_size(*stack_a);
	i = 0;
	while (i < max_bits)
	{
		j = 0;
		while (j < size)
		{
			tmp = *stack_a;
			if (((tmp->index >> i) & 1) == 0)
				pb(stack_a, stack_b);
			else
				ra(stack_a);
			j++;
		}
		while (*stack_b)
			pa(stack_a, stack_b);
		i++;
	}
}

