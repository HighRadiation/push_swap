/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
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

/* 
** Parse arguments - handles both "./push_swap 4 2 1" and "./push_swap "4 2 1""
** Returns a NULL-terminated array of strings
*/
char	**parse_arguments(int argc, char **argv)
{
	char	**args;

	if (argc == 2)
	{
		// Single argument case - split by spaces (handles "4 2 1")
		args = ft_split(argv[1], ' ');
		if (!args || !args[0])
		{
			if (args)
				free_split_array(args);
			return (NULL);
		}
		return (args);
	}
	else
	{
		// Multiple arguments - skip argv[0] (program name)
		return (&argv[1]);
	}
}
