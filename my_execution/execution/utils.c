
#include "../../minishell.h"

static int count_lengh_value_str_export(char *str)
{
    int i;

    int count;
    
    i = 0;
    count = 0;
    if(!str)
        return(-1);
    if(str[i] && (str[i] == '=' || str[i] == '+'))
    {
        if(str[i] && str[i]=='=')
            i++;
        i++; 
    }
    while(str[i])
    {
        i++;
        count++;
    }
    return(count);
   
    
}

static int count_lengh_var_str_export(char *str)
{
    int i ;
    
    i = 0;
    while(str[i] &&(str[i] != '=' && str[i]!= '+'))
    {
        i++;
    }
    return (i);  
}
 static void fill_in_environ(char *str,char ***splited_export_char)
{
    int i;
    int j;
    
    i = 0;
    while(str[i] && str[i] != '=' && str[i] != '+')
    {
        
        (*splited_export_char)[0][i] = str[i];
        i++;
    }
    (*splited_export_char)[0][i] = '\0';
    j = 0;
    if(str[i] == '=' || str[i] == '+')
    {
        if(str[i] == '+')
        {
            (*splited_export_char)[1][j]='+';
            i++;
            j++;
        }
        (*splited_export_char)[1][j]='=';
        i++;
        j++;
    }
    if((*splited_export_char)[1])
        (*splited_export_char)[1][j]='\0';
    j = 0;
    while(str[i])
    {
        (*splited_export_char)[2][j]=str[i];
        j++;
        i++;
    }
    if((*splited_export_char)[2])
        (*splited_export_char)[2][j] = '\0';
}


static char  **split_environ(char *str)
{
    char **splited_export_char;
    int  lengh_of_var_str;
    int lengh_of_var_value;
    
    if(!str)
        return(NULL);

    lengh_of_var_str = count_lengh_var_str_export(str);
    lengh_of_var_value = count_lengh_value_str_export((str + lengh_of_var_str));
    splited_export_char = (char **)malloc(4*sizeof(char *));
    if(!splited_export_char)
        return(NULL);
    splited_export_char[0] =(char *)malloc((size_t)(lengh_of_var_str + 1));
    if(str[lengh_of_var_str] == '=')
        splited_export_char[1] = (char *)malloc((size_t)(2));
    else if(str[lengh_of_var_str] == '+')
        splited_export_char[1] = (char *)malloc((size_t)(3));
    else
    {
        splited_export_char[1] = NULL;
        splited_export_char[2] = NULL;
        fill_in_environ(str,&splited_export_char);
        return(splited_export_char);
    }
    splited_export_char[2]= (char *)malloc((size_t)(lengh_of_var_value + 10));
    splited_export_char[3] = NULL ;
    if(!splited_export_char[0] || !splited_export_char[1] || !splited_export_char[2])
        return(NULL);
    fill_in_environ(str,&splited_export_char);
     return(splited_export_char);
}


t_environ  *ft_lstnew_environ(char *str)
{
	t_environ	*newnode;
    char       **splited_export;

	newnode = (t_environ *)malloc(sizeof(t_environ));
	if (!newnode)
		return (NULL);
    // if(!strcmp(str, ""))
    // {
    //     newnode->var =NULL;
    //     newnode->operator= NULL;
    //     newnode->value= NULL;
    //     newnode->next = NULL;
    // }
    // else
    // {
    splited_export = split_environ(str);
    if(!splited_export)
        return(NULL);
    else
    {
	    newnode->var =splited_export[0];
        newnode->operator= splited_export[1];
        newnode->value= splited_export[2];
	    newnode->next = NULL;
        return(newnode);
    }
}
void	ft_lstadd_back_environ(t_environ **lst, t_environ *new)
{
	t_environ	*temp;

	if (new == NULL)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while ((temp)->next != NULL)
	{
		(temp) = (temp)->next;
	}
	(temp)->next = new;
}
// void make_export_struct(char **splited_arg, t_environ **environ)
// {
//     t_environ *new;
//     t_environ *current;
//     int count ;
//     int i;
    
    
    
//    (1&& (count = 0), (i = 0 ));
//     if(splited_arg)
//     {
//         while(splited_arg[i])
//         {
//             new = ft_lstnew_environ(splited_arg[i]);
//             if(is_the_var_in_environ(new->var, *environ))
//             {
//                 handling_new_changes(&new, environ);
//             }
//             else 
//             {
//                 ft_lstadd_back_environ(environ, new);
//             }   
//             i++;
//         }
//         // current = *environ;
//         // while(current)
//         // {
//         //     printf("%s\n", current->var);
//         //     current= current->next;
//         // }  
//     }
// }
