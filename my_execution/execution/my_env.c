
#include "../../minishell.h"

t_environ *making_the_environ_struct(void)
{
    extern char **environ;
    t_environ *s_environ;
    t_environ *new;
    
    s_environ = NULL;
    
    int count ;
    
    int i;
    count = 0;
    
    if(environ)
    {
        i = 0;
        while(environ[i])
        {
            new = ft_lstnew_environ(environ[i]);
            ft_lstadd_back_environ(&s_environ, new);
            i++;
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
        if(current->value)
        {
            printf("%s", current->var);
            printf("=");
            printf("%s", current->value);
            printf("\n");
        }
        current= current->next;
    }
    
}