/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:06:48 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/05/29 00:05:26 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_environ *making_the_environ_struct(void)
{
    extern char **environ;
    t_environ *s_environ;
    int flag;
    t_environ *new;
    int i;

    (1 && (s_environ = NULL),(flag = 0));
    if(environ)
    {
        i = 0;
        while(environ[i])
        {
            if(!ft_strcmp(environ[i], PATH))
                flag = 1;
            new = ft_lstnew_environ(environ[i]);
            ft_lstadd_back_environ(&s_environ, new);
            i++;
        }
        if(!flag)
        {
            new = ft_lstnew_environ(PATH);
            ft_lstadd_back_environ(&s_environ, new);
        }
        return(s_environ);
    }
    else  
        return(NULL);
}

void executing_env(t_environ **environ)
{
    t_environ *current;

    if (*environ == NULL)
        return;
    current = *environ;
    while(current)
    {
        printf("%s", current->var);
        if(current->value)
        {
            printf("=");
            printf("%s", current->value);
        }
        printf("\n");
        current= current->next;
    }   
}