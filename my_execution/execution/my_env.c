
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
        // if(current->value)
        // {
            printf("%s", current->var);
            if(current->value)
            {
                printf("=");
                printf("%s", current->value);
            }
            printf("\n");
        // }
        current= current->next;
    }
    
}