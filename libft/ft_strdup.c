/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boksuz <boksuz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:19:46 by boksuz            #+#    #+#             */
/*   Updated: 2025/06/18 18:13:45 by boksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*str1;
	size_t	len;

	len = ft_strlen(str);
	str1 = (char *)malloc(len + 1);
	if ((str1) == NULL)
		return (NULL);
	ft_memcpy(str1, str, len + 1);
	return (str1);
}
