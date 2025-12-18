/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boksuz <boksuz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 08:52:00 by boksuz            #+#    #+#             */
/*   Updated: 2025/12/18 08:52:00 by boksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate(t_list **stack)
{
	t_list	*first;
	t_list	*last;

	if (!*stack || !(*stack)->next)
		return ;
	first = *stack;
	last = ft_lstlast(*stack);
	*stack = first->next;
	first->next = NULL;
	last->next = first;
}

void	ra(t_list **a)
{
	rotate(a);
	ft_putstr_fd("ra\n", 1);
}

void	rb(t_list **b)
{
	rotate(b);
	ft_putstr_fd("rb\n", 1);
}

void	rr(t_list **a, t_list **b)
{
	rotate(a);
	rotate(b);
	ft_putstr_fd("rr\n", 1);
}
