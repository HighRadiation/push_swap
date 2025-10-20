/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boksuz <boksuz@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:35:20 by boksuz            #+#    #+#             */
/*   Updated: 2025/10/20 17:35:21 by boksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct s_stack	t_stack;

int		ft_atoi(const char *str);
void	ft_putstr(char *str);
void	error_exit(void);

int		has_duplicates(t_stack *stack);
void	index_stack(t_stack **stack);

int		get_min(t_stack *stack);
int		get_max(t_stack *stack);
int		get_min_index(t_stack *stack);

#endif
