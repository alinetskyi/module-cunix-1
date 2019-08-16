#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "hash.c"

/// GLOBAL VARS
hashtable_t *env;
/////////////

char *lsh_read_line()
{
  char *line = NULL;
  ssize_t bufsize = 0;  
  getline(&line, &bufsize, stdin);
  return line;
}

char *remove_spaces(char **line_t) 
{
    int i = 0, j = 0;
    char *line = *line_t;
    int flag = 0;
    while (line[i] != '\n')
    {   
	if ((flag == 0) && (line[i] == '"')) 
	{
	    flag = 1;
	}   else
	{	
	    if ((flag == 1) && (line[i] == '"')) 
	    {
	        flag = 0;
	    }
	}	    
        if (line[i] != ' ') 
	{
	    line[j] = line[i];
	    j++;
	} else {
	    if ((flag) || ((j != 0) && (line[j - 1] != ' ')))  
	    {
	        line[j] = line[i];
		j++;
	    } 
	}
	i++;
    }
    if (line[j - 1] == ' ') 
    {
        j--;
    }
    line[j] = '\0';
    return line;
}

int print_variable(char *line)
{
    printf("LOLOL   %s 1\n",line);
    void *data = hash_get(env,line);
    printf("%p\n",data);
}

int run_exit(char *line) 
{
   if (*line == '\0') 
   {
       return 0;
   }
   return -1;
}

int run_pwd(char *line) 
{
   if (*line == '\0') 
   {
       char my_cwd[1024];
       getcwd(my_cwd, 1024);
       printf("%s\n", my_cwd);
       return 1;
   }
   return -1;
}

void change_pwd()
{
    char my_cwd[1024];
    getcwd(my_cwd, 1024);
    printf("%s\n",my_cwd);
    hash_set(env, "pwd" , "lol");
    //printf("%s\n",hash_get(env,"pwd"));
}

int run_cd(char *line) 
{
    if (chdir(line) != 0) {
        printf("Path not found!\n");
    } else {
        change_pwd();
    } 
    return 1;
}


int run_echo(char *line) 
{   
    if (line[0] == '$') 
    {
       line++;
       print_variable(line);
       return 1;
    }	    
    if (line[0] == '"') 
    {
        line++;
    }
    while ((*line != '"') && (*line != '\0'))
    {
        printf("%c",*line);
	line++;
    }
    line++;
    if (*line != '\0') 
    {
        line+=2;
	printf(" ");
	run_echo(line);
    } else 
    {
        printf("\n");
    }
    return 1;
}


int run_export(char *line)  // Now line points to new variable's name 
{
    int i = 0;
    char *name = line;
    char *value;
    while (line[i] != '\0') 
    {
        if (line[i] == '=') 
	{
	    line[i] = '\0';
	    value = line + i + 2;
	}
	i++;
    }
    line[i - 1] = '\0';
    hash_set(env,name,value);
    return 1;     
}

int run_env()
{
    print_table(env);
    return 1;        
}

int run_command(char *line) 
{   	
    if (strstr(line, "exit") == line) 
    {   
        return run_exit(line + 4);
    } 
    if (strstr(line,"pwd") == line) 
    {
	return run_pwd(line + 3);    
    } 
    if (strstr(line,"env") == line) 
    {
	return run_env();  
    }
    if (strstr(line,"cd ") == line) 
    {   
	return run_cd(line +3);
    }
    if (strstr(line,"echo ") == line) 
    {    
        return run_echo(line + 5);
    }
    if (strstr(line,"export ") == line)
    {
	return run_export(line + 7);
    } 
    return -1;
}

int lsh_execute(char *line) {
    int status;
    if (*line == '\n') 
    {
        return 1;
    }
    line = remove_spaces(&line);
    status = run_command(line);  // -1 for bad command, 0 for exit, 1 if all OK
    if (status == -1) {
        printf("Unknown command!\n");
    }
    return status;
}

int mainloop() 
{
    char *line;
    int status;    
    while (1) 
    {
        printf("$_>");
        line = lsh_read_line();
	status = lsh_execute(line);
	if (status == 0) {
	    return 0;
	}	
    } 
}

int main() 
{   int status;
    env = hash_create(10);
    change_pwd();   
    status = mainloop();
   if (status == 0) 
    {
	hash_destroy(env);    
        return 0;	
    }
}
