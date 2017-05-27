#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>

//Homework1
void displayMilestone1(int argc, char* argv[]);
void displayPathInfo  (char *path);
int isPath            (char *path);

//Homework2 & Homework3
void executeProgram(int argc, char* argv[]);
void travereseDir(char* dirName, int depth, long *userid,
                                            long *groupid,
                                            char *permisiuni,
                                            long long *dimMax,
                                            long long *dimMin);
void checkDisplay(char* path, long *userid,
                              long *groupid,
                              char *permisiuni,
                              long long *dimMax,
                              long long *dimMin);
bool checkPerm(struct stat fStat, char* permisiuni);
void displayMenu();
