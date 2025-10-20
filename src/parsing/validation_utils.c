/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boksuz <boksuz@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:35:20 by boksuz            #+#    #+#             */
/*   Updated: 2025/10/20 17:35:21 by boksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "ft_string.h"
#include "parsing.h"

/* Check if a string is a valid integer */
int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/* Check for integer overflow */
int	check_int_overflow(char *str)
{
	long	num;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	num = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		num = num * 10 + (str[i] - '0');
		if (num * sign > 2147483647 || num * sign < -2147483648)
			return (0);
		i++;
	}
	return (1);
}

/* Check all arguments for validity */
int	check_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!is_valid_number(argv[i]))
			return (0);
		if (!check_int_overflow(argv[i]))
			return (0);
		i++;
	}
	return (1);
}
