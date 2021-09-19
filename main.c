#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//const char* ENTRY_FORMAT_OUT = "(%s,%s,%s,%s)\n";

typedef struct Entry
{
  char *name;
  char *email;
  char *password;
  char *description;
  char *url;
} Entry;

void createEntry()
{
  Entry *e;
  FILE *fp;
  char *p = malloc(1024);

  e = (Entry *)malloc(sizeof(Entry));
  fp = fopen("myentries.txt", "ab");

  //Obligatory field

  printf("Enter your Name\n");
  scanf("%s", p);
  e->name = (char *)malloc(sizeof(p));
  strcpy(e->name, p);
  fflush(stdin);

  //Obligatory field

  printf("Enter you username/email\n");
  scanf("%s", p);
  e->email = (char *)malloc(sizeof(p));
  strcpy(e->email, p);
  fflush(stdin);

  //Obligatory field

  printf("Enter your password\n");
  scanf("%s", p);
  fflush(stdin);
  e->password = (char *)malloc(sizeof(p));
  strcpy(e->password, p);

  //Must fix optinal sections
  printf("Enter a description *Optional Press '0' to skip\n");
  scanf("%s", p);
  if(*p == '0'){
    printf("No description added\n");
  } else{
    e->description = (char *)malloc(sizeof(p));
    strcpy(e->description, p);
  }

  //printf("Description: %s\n", p);
  

  printf("Enter a url *Optional Press '0' to skip\n");
  scanf("%s",p);
  if (*p == '0'){
    printf("No Url added\n");

  } else{
    e->url = (char *)malloc(sizeof(p));
    strcpy(e->url, p);
  }
  

  fwrite(e, sizeof(Entry), 1, fp);

  fclose(fp);
}

void listEntries()
{
  Entry *e;
  e = (Entry *)malloc(sizeof(Entry));

  FILE *fp;
  fp = fopen("myentries.txt", "rb");

  while(fread(e,sizeof(Entry),1,fp)){
    if(!feof(fp)){
       printf("Username: %s Username/email: %s Password: %s Description: %s Url: %s \n", e->name, e->email, e->password, e->description, e->url);

    }
  }

  // if (fp != NULL)
  // {
  //   while(!feof(fp)){
  //     fread(e, sizeof(Entry), 1, fp);
  //     printf("Username: %s Username/email: %s Password: %s Description: %s Url: %s \n", e->name, e->email, e->password, e->description, e->url);
  //   }
    
  //   fclose(fp);
  // }
  //printf("Username: %s Username/email: %s Password: %s Description: %s Url: %s \n", e->name, e->email, e->password, e->description, e->url);
}

int main()
{

  int option;

  do
  {
    printf("1.Create New Entry\n");
    printf("2.Delete Entry\n");
    printf("3.View all entries\n");
    printf("4.Select an entry\n");
    printf("0.Exit Program\n");

    printf("Enter your choice : ");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
      createEntry();
      break;
    case 2:
      //delete()
      break;
    case 3:
      listEntries();
    }

  } while (option != 0);

  return 0;
};
