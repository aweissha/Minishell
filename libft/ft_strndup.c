/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:21:30 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/14 14:17:40 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	strnlen(char *s1, size_t n)
{
	size_t	str_len;

	str_len = ft_strlen(s1);
	if (str_len < n)
		return (str_len);
	else
		return (n);
}

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	len;
	char	*new_str;

	len = strnlen((char *)s1, n);
	new_str = malloc(len + 1);
	if (new_str == NULL)
		return (NULL);
	ft_strncpy(new_str, s1, len);
	new_str[len] = '\0';
	return (new_str);
}
