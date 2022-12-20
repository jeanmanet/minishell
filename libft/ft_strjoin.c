/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:56:56 by jmanet            #+#    #+#             */
/*   Updated: 2022/03/30 16:39:39 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{	
	size_t	size;
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(*str) * (size + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{	
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
