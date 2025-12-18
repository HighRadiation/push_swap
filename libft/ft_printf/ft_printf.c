/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boksuz <boksuz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:14:35 by boksuz            #+#    #+#             */
/*   Updated: 2025/07/24 18:05:16 by boksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		total;

	total = 0;
	if (!format)
		return (0);
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			total += ft_format((int)(*(++format)), &args);
			format++;
		}
		else
			total += ft_putchar(*format++);
	}
	va_end(args);
	return (total);
}
