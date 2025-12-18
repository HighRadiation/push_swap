/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boksuz <boksuz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 08:52:00 by boksuz            #+#    #+#             */
/*   Updated: 2025/12/18 09:18:00 by boksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_max_bits(t_list **stack)
{
	t_list	*head;
	int		max;
	int		max_bits;

	head = *stack;
	max = head->index;
	max_bits = 0;
	while (head)
	{
		if (head->index > max)
			max = head->index;
		head = head->next;
	}
	while ((max >> max_bits) != 0)
		max_bits++;
	return (max_bits);
}

static void	radix_iteration(t_list **a, t_list **b, int i, int size)
{
	t_list	*head_a;
	int		j;

	j = 0;
	while (j < size)
	{
		head_a = *a;
		if (((head_a->index >> i) & 1) == 1)
			ra(a);
		else
			pb(a, b);
		j++;
	}
}

void	radix_sort(t_list **a, t_list **b)
{
	int		i;
	int		size;
	int		max_bits;

	i = 0;
	size = ft_lstsize(*a);
	max_bits = get_max_bits(a);
	while (i < max_bits)
	{
		radix_iteration(a, b, i, size);
		while (ft_lstsize(*b) > 0)
			pa(a, b);
		i++;
	}
}
