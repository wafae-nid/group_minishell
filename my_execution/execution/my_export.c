
#include "../../minishell.h"

static int ft_is_a_numb(char c)
{
    if(c >= '0' && c <= '9')
        return(1);
    else
        return(0);
}
static int is_while_space(char c)
{
    if((c > 8 && c <= 13) || c == ' ')
        return(1);
    return(0);
}


static int valid_position_export(char *str)
{
    int i;

    i = 0;
    
    if(!str)
        return(-1);
    while(str[i])
    {
        if(((str[i] == '=') && ((i == 0) || is_while_space(str[i-1])) )|| ((str[i] =='+') && ((i ==0) || is_while_space(str[i-1]))))
            return(0);
        i++; 
    }
    return(1);
}

static int var_name_end(char *str)
{
    int i;

    i = 0;
    if(!str)
        return(-1);
    while(str[i])
    {
        if(str[i]=='+' && str[i+1] == '=' && i!=0)
        {
            // i--;
            return(i);
        }
        else if(str[i] == '=' && i!= 0)
        {
            // i--;
            return(i);
        }
        i++;
    }
    return(i);
}

static int valid_var_name(char *str, int count)
{
    int i;
    if(!str)
    {
        return(-1);
    }
    if(ft_is_a_numb(str[0]))
    {

        return(0);
    }
    i = 0;
    while(i < count)
    {
        if((!ft_is_a_numb(str[i]) && !ft_isalpha(str[i])) && str[i] != '_')
        {
            return(0);
        }
        i++;
    }
    return(1);
    
}
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

int is_the_var_in_environ(char *variable, t_environ *environ)
{
    t_environ *current = environ;
   while(current)
   {
       
       if(!strcmp(current->var ,variable))
       {
           return(1);
       }
       current = current->next;
   }
   return(0);
}

static void replace_node(t_environ **new, t_environ **environ)
{
    t_environ *tmp;
    t_environ *current;
    
    char *new_value;
    
    tmp = (*environ);
    while(tmp)
    {
        if((tmp->next) && !strcmp((tmp->next)->var, (*new)->var))
        {
            current = tmp;
            tmp = (tmp->next)->next;
            if(!strcmp((*new)->operator, "+="))
            {
                new_value = ft_strjoin((current->next)->value, (*new)->value);
                if(!new_value)
                    return;
                (*new)->value = new_value;
            }
            (*new)->next = tmp;
            current->next = *new;
            break;
        }
        tmp=tmp->next;     
    }
}

static void handling_new_changes(t_environ **new, t_environ **environ)
{
    char *new_value;
    char *new_operator;
    

    if(!((*new)->value))
        return;
    else if(!ft_strcmp((*new)->operator, "+=") && !strcmp((*new)->value,""))
        return;
    replace_node(new, environ); 
}

static int input_struct_handling(char *arg)
{
    int var_name_end_;
    int i;
    
        if(!arg)
            return(1);
        i = 0;
        while(arg[i])
        {
            var_name_end_=(var_name_end(arg));
            if(!valid_var_name(arg, var_name_end_))
            {
                printf("syntax error!");
                    return(1);
            }
            i++;
        }
        return(0);
 
}
static void make_export_struct(char **command, t_environ **environ)
{
    t_environ *new;
    t_environ *current;
    int count ;
    int i;
    
   (1&& (count = 0), (i = 1 ));
    if(command)
    {
        while(command[i])
        {
            if(valid_position_export(command[i]))
            {
                if(input_struct_handling(command[i]))
                    i++;
                new = ft_lstnew_environ(command[i]);
                if(is_the_var_in_environ(new->var, *environ))
                    handling_new_changes(&new, environ);
                else 
                ft_lstadd_back_environ(environ, new);
            }
            else
                printf("syntax error!");
            i++;
        }
    }
}


static void export_no_arg(t_environ **environ)
{
    t_environ *current;

    current = (*environ);
    while(current)
    {
        printf("declare -x ");
        printf("%s", current->var);
        if(current->value)
        {
            printf("=");
            printf("\"%s\"", current->value);
        }
        printf("\n");
        current = current->next;
    }
}
void export_parssing(char **command, t_environ **environ)
{
    int i;
    t_environ *current;

    if(command)
    {
        i = 1;
        if(!command[1])
        {
            export_no_arg(environ);
            return;
        }
        // while(command[i])
        // {
        //     if(valid_position_export(command[i]))
        //     {
        //         if(input_struct_handling(command[i]))
        //             return;
        //     }
        //     else 
        //     {
        //         printf("syntax error!");
        //     } 
            // i++; 
        make_export_struct(command,environ);
        
    }
}

