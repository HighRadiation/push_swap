/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boksuz <boksuz@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:35:20 by boksuz            #+#    #+#             */
/*   Updated: 2025/10/20 17:35:21 by boksuz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

// count_words, it will control the seperator which is that is 'char c'. 
static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

/* word_len, it will count the length of string with a while, 
if it see an seperator it will stop. */
static int	word_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

/* Copy the string, you know the length of string. */
static char	*word_dup(const char *s, int len)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

/* free, it is going to start from last word to free (ex.index 4,3,2..) */
static void	free_split(char **split, int i)
{
	while (i > 0)
		free(split[--i]);
	free (split);
}

/* ft_split a string into an array of words using a seperator character. */
char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		words;
	int		len;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (words--)
	{
		while (*s == c)
			s++;
		len = word_len(s, c);
		result[i] = word_dup(s, len);
		if (!result[i])
			return (free_split(result, i), NULL);
		s += len;
		i++;
	}
	result[i] = NULL;
	return (result);
}

/* Free the entire split array */
void	free_split_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
