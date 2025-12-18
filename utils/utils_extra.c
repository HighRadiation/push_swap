/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boksuz <boksuz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 08:56:00 by boksuz            #+#    #+#             */
/*   Updated: 2025/12/18 09:12:00 by boksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_lstsize(t_list *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	get_pos_on_stack(t_list **stack, int val)
{
	t_list	*head;
	int		pos;

	head = *stack;
	pos = 0;
	while (head)
	{
		if (head->index == val)
			return (pos);
		pos++;
		head = head->next;
	}
	return (-1);
}

void	index_stack(t_list **stack)
{
	t_list	*ptr;
	t_list	*inner;
	int		count;

	ptr = *stack;
	while (ptr)
	{
		inner = *stack;
		count = 0;
		while (inner)
		{
			if (inner->value < ptr->value)
				count++;
			inner = inner->next;
		}
		ptr->index = count;
		ptr = ptr->next;
	}
}

int	is_sorted(t_list **stack)
{
	t_list	*head;

	head = *stack;
	while (head && head->next)
	{
		if (head->value > head->next->value)
			return (0);
		head = head->next;
	}
	return (1);
}
