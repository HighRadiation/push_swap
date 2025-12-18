/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boksuz <boksuz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 08:54:00 by boksuz            #+#    #+#             */
/*   Updated: 2025/12/18 08:54:00 by boksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_3_extra(t_list **a, int min, int next_min)
{
	t_list	*head;

	head = *a;
	if (min < next_min && next_min > head->next->next->index
		&& min < head->next->next->index)
	{
		sa(a);
		ra(a);
	}
	else if (min < next_min && next_min > head->next->next->index)
		rra(a);
}

static void	sort_3(t_list **a)
{
	t_list	*head;
	int		min;
	int		next_min;

	head = *a;
	min = head->index;
	next_min = head->next->index;
	if (min > next_min && min < head->next->next->index)
		sa(a);
	else if (min > next_min && next_min > head->next->next->index)
	{
		sa(a);
		rra(a);
	}
	else if (min > head->next->next->index
		&& next_min < head->next->next->index)
		ra(a);
	else
		sort_3_extra(a, min, next_min);
}

static int	get_min_val(t_list **stack)
{
	t_list	*ptr;
	int		min;

	ptr = *stack;
	min = ptr->index;
	while (ptr)
	{
		if (ptr->index < min)
			min = ptr->index;
		ptr = ptr->next;
	}
	return (min);
}

static void	sort_4_5(t_list **a, t_list **b)
{
	int	size;
	int	min;
	int	pos;

	size = ft_lstsize(*a);
	while (size > 3)
	{
		min = get_min_val(a);
		pos = get_pos_on_stack(a, min);
		if (pos <= ft_lstsize(*a) / 2)
		{
			while ((*a)->index != min)
				ra(a);
		}
		else
		{
			while ((*a)->index != min)
				rra(a);
		}
		pb(a, b);
		size--;
	}
	sort_3(a);
	while (*b)
		pa(a, b);
}

void	simple_sort(t_list **a, t_list **b)
{
	int	size;

	size = ft_lstsize(*a);
	if (size == 2)
		sa(a);
	else if (size == 3)
		sort_3(a);
	else
		sort_4_5(a, b);
}
