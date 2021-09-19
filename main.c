#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//const char* ENTRY_FORMAT_OUT = "(%s,%s,%s,%s)\n";

typedef struct Entry
{
  char name[20];
  char email[15];
  char password[20];
  char description[50];
  char url[20];
} Entry;



void createEntry()
{
  Entry *e;
  FILE *fp;
  char *p = malloc(1024);

  e = (Entry *)malloc(sizeof(Entry));
  fp = fopen("myentries.bin", "ab");

  //Obligatory field

  printf("Enter Entry name\n");
  scanf("%s", p);
  //e->name = (char *)malloc(sizeof(p));
  strcpy(e->name, p);
  fflush(stdin);

  //Obligatory field

  printf("Enter you username/email\n");
  scanf("%s", p);
  //e->email = (char *)malloc(sizeof(p));
  strcpy(e->email, p);
  fflush(stdin);

  //Obligatory field

  printf("Enter your password or press 'R' to create random password\n");
  scanf("%s", p);
  //e->password = (char *)malloc(sizeof(p));
  strcpy(e->password, p);
  fflush(stdin);


  printf("Enter a description *Optional Press '0' to skip\n");
  scanf("%s", p);
  if(*p == '0'){
    printf("No description added\n");
  } else{
    //e->description = (char *)malloc(sizeof(p));
    strcpy(e->description, p);
    fflush(stdin);

  }

  //printf("Description: %s\n", p);
  

  printf("Enter a url *Optional Press '0' to skip\n");
  scanf("%s",p);
  if (*p == '0'){
    printf("No Url added\n");

  } else{
    //e->url = (char *)malloc(sizeof(p));
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
  fp = fopen("myentries.bin", "rb");


  while(fread(e,sizeof(Entry),1,fp)){
    
       printf("Entry Name: %s\n\n", e->name);

    
  }
  fclose(fp);
}


  void selectedEntry(char *name){
    Entry *e;
    e = (Entry *)malloc(sizeof(Entry));
    int value;

    FILE *fp;
    fp = fopen("myentries.bin", "rb");
    while(fread(e,sizeof(Entry),1,fp)){
         value=strcmp(e->name,name);  
      if(value == 0){
       printf("Username: %s Username/email: %s Password: %s Description: %s Url: %s \n", e->name, e->email, e->password, e->description, e->url);

      }
    
  }
  fclose(fp);

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


int main()
{

  int option;
  char *nameEntry = malloc(1024);

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
      break;
    case 4:
    printf("Enter entry name: \n");
    scanf("%s", nameEntry);
      selectedEntry(nameEntry);
    }
    


  } while (option != 0);

  return 0;
};
