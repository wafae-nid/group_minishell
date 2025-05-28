/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:20:27 by zatalbi           #+#    #+#             */
/*   Updated: 2025/05/28 20:35:05 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*str;

	size = ft_strlen(s1) + 1;
	str = (char *)malloc(size);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, size);
	return (str);
}
