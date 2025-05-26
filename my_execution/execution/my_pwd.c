
#include "../../minishell.h"

static int is_valid_pwd(char **command)
{
    if (!ft_strcmp(command[1],"-p") || !ft_strcmp(command[1],"--p" ) || !ft_strcmp(command[1],"---p"))
        return(0);
    else
        return(1);
}

void  pwd_execution(char **command)
{
    char *PWD;

    if (command[1] && !is_valid_pwd(command))
    {
        printf("error msg");
        return;
    }
    PWD = getcwd(NULL,0);
    if(!PWD )
        perror("problem finding current directory");
    else
        printf("%s\n", PWD);
    
}