#include <bits/stdc++.h>

#include <stdlib.h>
#include <unistd.h>
// #include <glob.h>
#include <dirent.h>
#include <sys/types.h>
using namespace std;

void list_files(const char* path=".") {
   DIR *dr;
   struct dirent *en;
   dr = opendir(path); //open all directory
   if (dr) {
      while ((en = readdir(dr)) != NULL) {
         cout<<" "<<en->d_name<<endl; //print all directory name
      }
      closedir(dr); //close all directory
   }
}
