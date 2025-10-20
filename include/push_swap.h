/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boksuz <boksuz@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:35:26 by boksuz            #+#    #+#             */
/*   Updated: 2025/10/20 17:35:27 by boksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "stack_ops.h"
# include "utils.h"
# include "ft_string.h"
# include "parsing.h"

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

t_stack	*stack_new(int value);
void	stack_add_back(t_stack **stack, t_stack *new);
void	stack_add_front(t_stack **stack, t_stack *new);
int		stack_size(t_stack *stack);
t_stack	*stack_last(t_stack *stack);
void	free_stack(t_stack **stack);

void	sort_three(t_stack **stack_a);
void	sort_small(t_stack **stack_a, t_stack **stack_b);
void	sort_large(t_stack **stack_a, t_stack **stack_b);

int		is_sorted(t_stack *stack);
void	push_swap(t_stack **stack_a, t_stack **stack_b);

#endif
