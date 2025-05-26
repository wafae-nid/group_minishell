/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_empty_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:31:38 by zatalbi           #+#    #+#             */
/*   Updated: 2025/05/24 19:41:22 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_cmdcase(t_list **list, t_list **head, char *str)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp != *head && tmp->next != *head)
		tmp = tmp->next;
	if (tmp == *head)
		*list = (*head)->next;
	else if (tmp->next == *head)
		tmp->next = (*head)->next;
	tmp = *head;
	*head = (*head)->next;
	return (ft_lstdelone(tmp, ft_free_token), free(str), 1);
}

int	ft_empty_token(t_list **list, t_list **head, char *str, int ptype)
{
	int	v;

	v = -1;
	while (((t_token *)(*head)->content)->token[++v])
	{
		if (((t_token *)(*head)->content)->token[v] == '\''
			|| ((t_token *)(*head)->content)->token[v] == '"')
			return (0);
	}
	if (!*str && ptype < INRED)
		return (ft_cmdcase(list, head, str));
	else if (!*str && ptype >= INRED)
		return (ft_putstr_fd("minishell: ", 2),
			ft_putstr_fd(((t_token *)(*head)->content)->token, 2),
			ft_putendl_fd(": ambiguous redirect", 2), *head = NULL,
			ft_lstclear(list, ft_free_token), free(str), 1);
	return (0);
}
