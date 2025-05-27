
#include "../../minishell.h"

static  void changing_nodes(t_environ **environ, char *var , char *new_value)
{
	t_environ *tmp;
	
	tmp = (*environ);

	while(tmp)
	{
		if(!strcmp(tmp->var, var))
			tmp->value = ft_strdup(new_value);
		tmp = tmp->next;
	}
}

static void  cd_oldpwd(t_environ **environ, char **PWD, char **OLDPWD)
{
	t_environ *current;
	char *old_pwd;
	old_pwd = *PWD;

	if(!chdir(*OLDPWD))
	{
		changing_nodes(environ,"OLDPWD", *PWD);
		changing_nodes(environ,"PWD", *OLDPWD);
		*PWD = ft_strdup(*OLDPWD);
		*OLDPWD = ft_strdup(old_pwd);
		printf("%s\n", *PWD);
	}
	else
		printf("error!");
}
static int is_home_set(t_environ **environ)
{
	t_environ *current;

	current = (*environ);
	while(current)
	{
		if(!strcmp(current->var,"HOME"))
		{
			if(!(current->value))
			{
				printf("home is unset\n");
				return(0);
			}
			if(!strcmp(current->value, ""))
			{
				printf("home is set but empty\n");
				return(0);
			}
			return(1);
			break;
		}
		current=current->next;
	}
	printf("home is unset\n");
	return(0);
}

static void cd_home(t_environ **environ, char **PWD, char **OLDPWD)
{
    char *HOME;
	t_environ *current;
	int flag;

	flag =is_home_set(environ);
	if(flag ==0)
		return;
    HOME=getenv("HOME");
	if(!chdir(HOME))
	{
		*OLDPWD = ft_strdup(*PWD);
		changing_nodes(environ, "OLDPWD",*PWD);
		*PWD = ft_strdup(HOME);
		changing_nodes(environ,"PWD", HOME);
	}
	else
		printf("error!");
}
static char *get_deleted_path_gain(char *PWD, char *new)
{
	char *deleted_path;

	char *pwd_for_path;
	pwd_for_path = ft_strjoin(PWD, "/");
	if(!pwd_for_path)
		return (NULL);
	deleted_path = ft_strjoin(pwd_for_path, new);
	if(!deleted_path)
		return(NULL);
	else
		return(deleted_path);
}
static void new_path_cd(t_environ **environ, char *new, char **PWD, char **OLDPWD)
{
    char *new_path;
	
	if(!chdir(new))
	{
		new_path = getcwd(NULL,0);
		if(!new_path)
		{
			printf("getcwd cant reach directory \n");
			new_path = get_deleted_path_gain(*PWD, new);
		}
		*OLDPWD = ft_strdup(*PWD);
		changing_nodes(environ, "OLDPWD",*PWD);
		*PWD = new_path;
		changing_nodes(environ,"PWD", new_path);
	}
	else
	{
		printf("chdir error");
		return;
	}
}

static char *telda_full_path(char *telda_path)
{
	char *telda_full_path;
	
	if(!telda_path ||!(*telda_path))
		return(NULL);
	telda_full_path = ft_strjoin("/home/wnid-hsa", telda_path + 1);
	if(!telda_full_path)
		return(NULL);
	else
		return(telda_full_path);
}
		
void cd_execution(char **command, char **PWD, t_environ **environ, char **OLDPWD)
{
	char *telda_path;
	
    if((command)[2])
    {
        printf("too many arguments");
        return;
    }
	else if((command)[1] && !strcmp((command)[1],"-"))
        cd_oldpwd(environ ,PWD,OLDPWD);
	else if (((command)[1] && !strcmp((command)[1], "~")) || (command)[1]== NULL)
    	cd_home(environ, PWD, OLDPWD);
	else if (command[1][0] == '~' )
	{
		telda_path = telda_full_path(command[1]);
		if(!telda_path)
			return;
		new_path_cd(environ,telda_path,PWD, OLDPWD);
	}
	else
        new_path_cd(environ,(command)[1],PWD, OLDPWD);
}