/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boksuz <boksuz@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:35:20 by boksuz            #+#    #+#             */
/*   Updated: 2025/10/20 17:35:21 by boksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_stack	t_stack;

int		check_args(char **argv);
int		is_valid_number(char *str);
int		check_int_overflow(char *str);
char	**parse_arguments(int argc, char **argv);
t_stack	*create_stack_from_args(char **args);

#endif
