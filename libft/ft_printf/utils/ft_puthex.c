/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boksuz <boksuz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:36:28 by boksuz            #+#    #+#             */
/*   Updated: 2025/07/24 17:54:36 by boksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	ft_puthex(unsigned long n, char *upper)
{
	int		len;

	len = 0;
	if (n >= 16)
		len += ft_puthex(n / 16, upper);
	len += ft_putchar(upper[n % 16]);
	return (len);
}
