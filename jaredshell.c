#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sched.h>
#include <sys/types.h>


#define SIZEOFSTACK 1024*1024
#define BUFFER 1024
int status;
int checkbuiltin(char **cmds);
void builtin_CLONE(char **cmds);
int takecommand();

void checkexecutable(char **cmds)
{
  int childstatus;
  pid_t pid = fork();
  if(pid == -1)
  {
    fprintf(stderr, "%s\n", "Sorry, forking failed");
  }
  else if(pid == 0)
  {
    if (execvp(cmds[0], cmds) == -1)
    {
      fprintf(stderr, "%s\n", "Either the command failed to execute or it was not located on disk");
    }
    exit(0);
  }
  else
  {
    wait(NULL);
    return;
  }

}
void builtin_dog()
{

      fprintf(stderr, "\n  __      _");
      fprintf(stderr, "\no'')}____//");
      fprintf(stderr, "\n `_/      )");
      fprintf(stderr, "\n (_(_/-(_/");
      return;

}
void initShell()
{
  fprintf(stderr, "\nHowdy pardner, welcome to Matt and Jared's shell\n");
}
void builtin_exit()
{
    fprintf(stderr, "\nExiting. Thanks for using our shell!\n");
    exit(1);
    return;
}

int builtin_cd(char **cmds)
{

  if(cmds[1] == NULL)
  {
    fprintf(stderr, "\nExpected second argument");
  }
  else
  {
    if (chdir(cmds[1]) != 0)
    {
      fprintf(stderr, "\nDirectory doens't exist");

    }
  }

  return 1;
}

void builtin_help()
{
  fprintf(stderr, "\nHere are the list of commands that are supported:");
  fprintf(stderr, "\ncd");
  fprintf(stderr, "\nhelp");
  fprintf(stderr, "\nexit");
  fprintf(stderr, "\ndog");
  fprintf(stderr, "\nclone");

  return;
}
int childfunct(void *args)
{
  system("sh");
  return 0;
}

char *read_line(void)
{
  char *str = NULL;
  int position = 0, x = 0;
  ssize_t buffersize = 0;
  getline(&str, &buffersize, stdin);
  if(str[strlen(str) - 1] == '\n')/*slightly messy way to remove newline character */
  {
    str[strlen(str) - 1] = 0;
  }
  return str;
}

char **parse_line(char *line)
{
  /*fprintf(stderr, "\n%s", line);  used for testing */
  int x = 0, y = 0;
  char **tokens = malloc(4048);
  char *token;
  token = strtok(line, " \t\n");
  while(token != NULL)
  {
    tokens[x] = token;
  /*  fprintf(stderr, "\n%d%s", x, tokens[x]);  used for testing */
    x++;
    token = strtok(NULL, " ");
  }

  tokens[x] = NULL;
/*  while(y < x)/* used for testing
  {
    fprintf(stderr, "\n%s", tokens[y]);/* used for testing
    y++;
  }*/
  return tokens;

}

int checkbuiltin(char **cmds)
{

  int i = 6, x;
  char *listofcommands[i];
  listofcommands[0] = "exit";
  listofcommands[1] = "cd";
  listofcommands[2] = "help";
  listofcommands[3] = "dog";
  listofcommands[4] = "clone";


/*  while((strcmp(cmds[0], listofcommands[x]) != 0) && x <= 3)
  {
    x++;
    fprintf(stderr, "\nloop");/* used for testing
  }*/
  for (x = 0; x < i; x++)
  {
    if(strcmp(cmds[0], listofcommands[x]) == 0)
    {

        x++;
        break;
    }
  }
/*   fprintf(stderr, "\ncheckbuiltin2"); used for testing */
/*  fprintf(stderr, "\n%d", x);  used for testing */

  switch(x)
  {
    case 1:
    /*    fprintf(stderr, "\nexit");  used for testing */
        builtin_exit();
        return 1;
        break;
    case 2:
    /*    fprintf(stderr, "\ncd");  used for testing */
        builtin_cd(cmds);
        return 1;
        break;
    case 3:
    /*    fprintf(stderr, "\nhelp");  used for testing */
        builtin_help();
        return 1;
        break;
    case 4:
    /*    fprintf(stderr, "\ndog");  used for testing */
        builtin_dog();
        return 1;
        break;
    case 5:
        builtin_CLONE(cmds);
        return 1;
        break;
    default:
      break;
    }
    return 0;
}
int takecommand()
{
  char *line;
  char **cmds;
  initShell();
  line = read_line();
  cmds = parse_line(line);
  if(cmds[0]== NULL)
  {
    fprintf(stderr, "\nNo commands entered");
    return 1;
  }

/*  while(cmds[y] != NULL)/* used for testing
  {
    fprintf(stderr, "\n%s", cmds[y]);/* used for testing
    y++;
  }*/
  int ran = checkbuiltin(cmds);
  if (ran == 0)
  {
    checkexecutable(cmds);
  }
  free(line);
  free(cmds);
  return 1;

}
void builtin_CLONE(char **cmds)
{
  int flag;
  if(cmds[1] == NULL)
  {
    fprintf(stderr, "\nNote: you may enter a paramter following clone to flag a namespace.\n Ex: CLONE_NEWUSER\n");
    flag = SIGCHLD;
  }
  else if (strcmp(cmds[1], "CLONE_NEWNET") == 0)
  {
    flag = CLONE_NEWNET;
  }
  else if (strcmp(cmds[1], "CLONE_NEWNS") == 0)
  {
    flag = CLONE_NEWNS;
  }
  else if (strcmp(cmds[1], "CLONE_NEWIPC") == 0)
  {
    flag = CLONE_NEWIPC;
  }
  else if (strcmp(cmds[1], "CLONE_NEWUSER") == 0)
  {
    flag = CLONE_NEWUSER;
  }
  else if (strcmp(cmds[1], "CLONE_NEWUTS") == 0)
  {
    flag = CLONE_NEWUTS;
  }
  else
  {
    flag = SIGCHLD;
  }

  pid_t p = clone(childfunct, malloc(4096) + 4096, SIGCHLD|flag, NULL);
  /*fprintf(stderr, "\nparent pid: %d", getpid());*/
  if (p==-1)
  {
    fprintf(stderr, "\nError creating clone");
    return;
  }
  /*fprintf(stderr, "\nchild pid: %d", p);*/
  waitpid(p, NULL, 0);
  return;
}

int main()
{
  fprintf(stderr, "Type 'help' for a list of available commands");
  status = 0;
  do {

    int x = takecommand();

  } while(status == 0);

  return 0;

}
