/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:31:38 by zatalbi           #+#    #+#             */
/*   Updated: 2025/05/23 22:34:39 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_numcpy(char *str, int n)
{
	if (n == -2147483648)
	{
		str = ft_numcpy(str, n / 10);
		*str++ = -(n % 10) + '0';
	}
	else if (n < 0)
	{
		*str++ = '-';
		str = ft_numcpy(str, -n);
	}
	else if (n > 9)
	{
		str = ft_numcpy(str, n / 10);
		*str++ = n % 10 + '0';
	}
	else if (n >= 0 && n <= 9)
		*str++ = n + '0';
	return (str);
}

static size_t	ft_envcpy(char **dst, char *src, int flag)
{
	size_t	v;
	char	*env;

	v = 0;
	if (src[v] == '$' && ++v)
		*dst += ft_strlcpy(*dst, "$$", 3);
	else if (!ft_isalnum(src[v]) && src[v] != '_' && ((src[v] != '\''
				&& src[v] != '"') || flag))
		*(*dst)++ = *(src - 1);
	while (ft_isalnum(src[v]) || src[v] == '_')
		v++;
	env = ft_getenv(src, v);
	while (env && *env)
		*(*dst)++ = *env++;
	return (v);
}

static size_t	ft_dqcase(char **dst, char *src, int status, int flag)
{
	size_t	v;

	v = 0;
	while (src[++v] != '"')
	{
		if (!flag && src[v] == '$')
		{
			if (src[++v] == '"' && --v)
				*(*dst)++ = src[v];
			else if (src[v] == '?')
				*dst = ft_numcpy(*dst, status);
			else
				v += ft_envcpy(dst, &src[v], 0) - 1;
		}
		else
			*(*dst)++ = src[v];
	}
	return (v);
}

void	ft_expand_token(char *dst, char *src, int status, int flag)
{
	size_t	v;

	v = 0;
	while (src[v])
	{
		if ((flag | 0b01) == 0b01 && src[v] == '\'')
		{
			while (src[++v] != '\'')
				*dst++ = src[v];
		}
		else if ((flag | 0b01) == 0b01 && src[v] == '"')
			v += ft_dqcase(&dst, &src[v], status, flag);
		else if ((flag | 0b10) == 0b10 && src[v] == '$' && src[v + 1] == '?'
			&& ++v)
			dst = ft_numcpy(dst, status);
		else if ((flag | 0b10) == 0b10 && src[v] == '$' && ++v)
			v += ft_envcpy(&dst, &src[v], flag) - 1;
		else
			*dst++ = src[v];
		if (src[v])
			v++;
	}
	*dst = '\0';
}
