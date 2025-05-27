
#include "../../minishell.h"

static int is_valid_pwd(char **command)
{
    if (!ft_strcmp(command[1],"-p") || !ft_strcmp(command[1],"--p" ) || !ft_strcmp(command[1],"---p"))
        return(0);
    else
        return(1);
}

void  pwd_execution(char **command, char **PWD)
{
    char *pwd;

    if (command[1] && !is_valid_pwd(command))
    {
        printf("error msg");
        return;
    }
    pwd=getcwd(NULL,0);
    if(!pwd)
        printf("%s\n",*PWD);
    else
        printf("%s\n", pwd);
    
}