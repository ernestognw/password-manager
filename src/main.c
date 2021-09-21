#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

FILE *f;

//Entry object
typedef struct Entry
{
  char name[100];
  char email[100];
  char password[51];
  char description[150];
  char url[150];
} Entry;

//random password generator
char *genPassword(int passSize)
{
  char *password = malloc(passSize * sizeof(char));
  for (int i = 0; i < passSize; i++)
  {
    password[i] = 33 + (random() % 90);
  }
  return password;
}

//Create master password
int createPassword()
{
  char password[51];
  printf("Crear password: ");
  scanf("%s", password);

  f = fopen("password.bin", "wb");
  fwrite(password, 51, 1, f);
  fclose(f);
  system("clear");
  return 0;
}

void listEntries()
{
  Entry *e;
  e = (Entry *)malloc(sizeof(Entry));

  FILE *fp;
  if (access("myentries.bin", F_OK) != 0)
  {
    printf("There are no entries. \n");
    return;
  }
  fp = fopen("myentries.bin", "rb");

  while (fread(e, sizeof(Entry), 1, fp))
  {
    printf("=========== ENTRIES ===========\n");
    printf("- %s\n", e->name);
  }
  fclose(fp);
}

void createEntry()
{
  Entry *e;
  FILE *fp;
  char *p = malloc(1024), *r;
  int passSize;

  e = (Entry *)malloc(sizeof(Entry));
  fp = fopen("myentries.bin", "ab");

  // Required field

  printf("Name entry: ");
  scanf("%s", p);
  strcpy(e->name, p);
  fflush(stdin);

  // Required field

  printf("Username/Email: ");
  scanf("%s", p);
  strcpy(e->email, p);
  fflush(stdin);

  // Required field

  printf("Enter your password (press 'R' to create random one): ");
  scanf("%s", p);
  if (*p == 'R' || *p == 'r')
  {
    printf("Enter the password size (min 6, max 30): ");
    scanf("%d", &passSize);
    r = genPassword(passSize);
    strcpy(e->password, r);
    free(r); //free password variable from genPassword
    fflush(stdin);
  }
  else
  {
    strcpy(e->password, p);
    fflush(stdin);
  }

  printf("Enter a description (Press '0' to skip): ");
  scanf("%s", p);
  if (*p == '0')
    printf("No description added \n");
  else
  {
    strcpy(e->description, p);
    fflush(stdin);
  }

  printf("Enter a URL (Press '0' to skip): ");
  scanf("%s", p);
  if (*p == '0')
    printf("No URL added \n");
  else
    strcpy(e->url, p);

  fwrite(e, sizeof(Entry), 1, fp);

  fclose(fp);
}

void selectedEntry(char *name)
{
  Entry *e;
  e = (Entry *)malloc(sizeof(Entry));
  int value;

  FILE *fp;
  if (access("myentries.bin", F_OK) != 0)
  {
    printf("Specified entry does not exists. \n");
    return;
  }
  fp = fopen("myentries.bin", "rb");
  while (fread(e, sizeof(Entry), 1, fp))
  {
    value = strcmp(e->name, name);
    if (value == 0)
    {
      printf("Entry: %s\n", e->name);
      printf("Username/Email: %s\n", e->email);
      printf("Password: %s\n", e->password);
      printf("Description: %s\n", e->description);
      printf("URL: %s\n", e->url);
    }
  }
  fclose(fp);
}

void deleteEntry(char *name)
{
  Entry *e;
  e = (Entry *)malloc(sizeof(Entry));
  FILE *fp;
  FILE *temp;
  if (access("myentries.bin", F_OK) != 0)
  {
    printf("Specified entry does not exists. \n");
    return;
  }
  fp = fopen("myentries.bin", "rb");
  temp = fopen("tmp.bin", "wb");
  while (fread(e, sizeof(Entry), 1, fp))
  {
    if (strcmp(e->name, name) == 0)
      printf("A record with requested name found and deleted.\n\n");
    else
      fwrite(e, sizeof(Entry), 1, temp);
  }
  fclose(fp);
  fclose(temp);

  remove("myentries.bin");
  rename("tmp.bin", "myentries.bin");
}

void menuEntries()
{
  int option;
  char *nameEntry = malloc(1024);
  srand(time(NULL));

  do
  {
    printf("=========== MENU ===========\n");
    printf("1. Create new entry\n");
    printf("2. Delete entry\n");
    printf("3. View all entries\n");
    printf("4. Select an entry\n");
    printf("0. Exit\n\n");

    printf("Enter your choice: ");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
      createEntry();
      break;
    case 2:
      printf("Enter entry name to delete: ");
      scanf("%s", nameEntry);
      printf("\n");
      deleteEntry(nameEntry);
      break;
    case 3:
      printf("\n");
      listEntries();
      break;
    case 4:
      printf("Enter entry name: ");
      scanf("%s", nameEntry);
      printf("\n");
      selectedEntry(nameEntry);
    }

  } while (option != 0);
}

//Check master password inputed to stored one
void confirmPassword()
{

  char password[15];
  char master_password[15];
  char entradas[1000];

  //Si esto existe, quiere decir que si hay una
  //master password
  if (access("password.bin", F_OK) == 0)
  {
    //pido por esa master password
    printf("Introducir password: ");
    scanf("%s", password);
    //Abro el archivo para ver ver si lo que hay dentro  == password introducida
    f = fopen("password.bin", "rb");
    // Lo que hay (master password FILE .bin) lo voy a  en master_password
    fscanf(f, "%s", master_password);
    //Tengo que cerrar el archivo
    fclose(f);
    system("clear");

    if (strcmp(password, master_password) == 0)
      menuEntries();
    else
    {
      printf("Incorrect password. Try again. \n");
      //esto es lo mismo que un return -1;
      exit(EXIT_FAILURE);
    }
  }
  else
  {
    createPassword();
    confirmPassword();
  }
}

int main()
{
  confirmPassword();

  return 0;
};
