/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:04:59 by zatalbi           #+#    #+#             */
/*   Updated: 2024/11/09 15:31:06 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	v;

	if (s == NULL || f == NULL)
		return ;
	v = 0;
	while (s[v] != '\0')
	{
		f(v, &s[v]);
		v++;
	}
}
