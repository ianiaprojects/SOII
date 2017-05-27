/***
* displayMenu()   : displays a menu of existent arguments
* travereseDir()  : travereses a directory recursively
* executeProgram(): milestone1 and milestone2 requirements
*
***/

#include "util.h"

void executeProgram(int argc, char* argv[])
{

    int param;
    int option_index = 0;

    // milestone1
    int depth  = 1;
    char* path = "./";
    //milestone2
    long* userid      = NULL;
    long* groupid     = NULL;
    char* permisiuni  = NULL;
    long long* dimMax = NULL;
    long long* dimMin = NULL;

    static struct option long_options[] = {
        {"max-depth",   required_argument, 0, 'h'},
        {"directory",   required_argument, 0, 'd'},

        {"userid",      required_argument, 0, 'u'},
        {"groupid",     required_argument, 0, 'g'},
        {"permisiuni",  required_argument, 0, 'p'},
        {"dim-max",     required_argument, 0, 'M'},
        {"dim-min",     required_argument, 0, 'm'},

        {"meniu-info",  no_argument      , 0, 'i'},
        {0,             0,                 0,   0}
    };

   while ((param = getopt_long(argc, argv, "h:d:u:g:p:M:m:i",
            long_options, &option_index))!= -1) {
       switch (param) {

         case 'h':
                  depth = atoi(optarg);
                  break;
         case 'd':
                  path = optarg;
                  break;
        case 'u':
                  userid  = (long*)malloc(sizeof(long));
                  *userid = atol(optarg);
                  break;
        case 'g':
                  groupid  = (long*)malloc(sizeof(long));
                  *groupid = atol(optarg);
                  break;
        case 'p':
                  permisiuni = optarg;
                  break;
        case 'M':
                  dimMax  = (long long*)malloc(sizeof(long long));
                  *dimMax = atoll(optarg);
                  break;
        case 'm':
                  dimMin  = (long long*)malloc(sizeof(long long));
                  *dimMin = atoll(optarg);
                  break;

         case 'i':
                  displayMenu();
                  exit(0);
       default:
            printf("Argument not found: %c\n", param);
            break;
        }
    }
    printf("%s,%d\n", path, depth);
    travereseDir(path, depth, userid, groupid, permisiuni, dimMax, dimMin);

    free(userid);
    free(groupid);
    free(permisiuni);
    free(dimMin);
    free(dimMax);
    exit(EXIT_SUCCESS);
}

// Traverse in depth, recursively a directory
void travereseDir(char* dirName, int depth, long *userid,
                                            long *groupid,
                                            char *permisiuni,
                                            long long *dimMax,
                                            long long *dimMin)
{
  struct dirent *entry; // used to read dirs
  DIR *dirPointer;      // used to enter dirs

  if(depth < 1)
  return ;

  if(!(dirPointer = opendir(dirName)))
  {
    perror("Eroare la deschidere director");
    return;
  }
  chdir(dirName); // enter directory

  while(NULL != (entry = readdir(dirPointer)))
  {
    if(entry->d_type == DT_DIR)
    {
      if((strcmp(entry->d_name, "..") != 0) && (strcmp(entry->d_name, ".") != 0))
      {
          checkDisplay(entry->d_name, userid, groupid, permisiuni, dimMax, dimMin);
          travereseDir(entry->d_name, depth-1, userid, groupid, permisiuni, dimMax, dimMin);
      }
    }
    else
    {
        checkDisplay(entry->d_name, userid, groupid, permisiuni, dimMax, dimMin);
        fprintf(stdout, "\n" );
    }
  }

  chdir("../");
  closedir(dirPointer);
}

// Display instructions
void displayMenu()
{
  printf("MENIU:\n");
  printf("Parametrii:\n");
  printf("--max-depth  / -h [parametru] : specifica adancimea maxima a cautarii recursive in document\n");
  printf("--directory  / -d [parametru] : specifica fisierul(documentul)\n");
  printf("--userid     / -u [parametru] : cautare dupa id-ul utilizatorului\n");
  printf("--groupid    / -g [parametru] : cautare dupa grupulul asociat fisierului\n");
  printf("--permisiuni / -p [parametru] : cauta fisierele ce au setate anumite permisiuni(ex: rwxrwxrwx)\n");
  printf("--dim-max    / -M [parametru] : cauta fisiere ce au dimensiunea maxima de ___ bytes(B)\n");
  printf("--dim-min    / -m [parametru] : cauta fisiere ce au dimensiunea minima de ___ bytes(B)\n");
  printf("--meniu-info / -i             : afiseaza meniul\n");
}

// Check options and display milestone1 info if ok
void checkDisplay(char *path, long *userid,
                              long *groupid,
                              char *permisiuni,
                              long long *dimMax,
                              long long *dimMin)
{
      struct stat fStat;
      if(lstat(path, &fStat) < 0)
      {
          printf("Eroare la fStat!");
          return;
      }

      bool check = true;

      if(userid != NULL && *userid != (long)fStat.st_uid)
          check = false;

      if(groupid != NULL && *groupid != (long)fStat.st_gid)
          check = false;

      if(permisiuni != NULL)
          check = checkPerm(fStat, permisiuni);

      if(dimMax != NULL && *dimMax < (long long)fStat.st_size)
          check = false;

      if(dimMin != NULL && *dimMin > (long long)fStat.st_size)
          check = false;

      if(check)
          displayPathInfo(path);
}

// Check if the path permissions match the argumet
bool checkPerm(struct stat fStat, char* permisiuni)
{
      if(strlen(permisiuni) != 9)
        return false;

      if(
        ((fStat.st_mode & S_IRUSR) == (permisiuni[0] == 'r' ? S_IRUSR : false)) &&
        ((fStat.st_mode & S_IWUSR) == (permisiuni[1] == 'w' ? S_IWUSR : false)) &&
        ((fStat.st_mode & S_IXUSR) == (permisiuni[2] == 'x' ? S_IXUSR : false)) &&

        ((fStat.st_mode & S_IRGRP) == (permisiuni[3] == 'r' ? S_IRGRP : false)) &&
        ((fStat.st_mode & S_IWGRP) == (permisiuni[4] == 'w' ? S_IWGRP : false)) &&
        ((fStat.st_mode & S_IXGRP) == (permisiuni[5] == 'x' ? S_IXGRP : false)) &&

        ((fStat.st_mode & S_IROTH) == (permisiuni[6] == 'r' ? S_IROTH : false)) &&
        ((fStat.st_mode & S_IWOTH) == (permisiuni[7] == 'w' ? S_IWOTH : false)) &&
        ((fStat.st_mode & S_IXOTH) == (permisiuni[8] == 'x' ? S_IXOTH : false))
        )
        return true;

      return false;
}
