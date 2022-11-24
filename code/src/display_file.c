#include <dirent.h>
#include <stdio.h>

int main()
{
	DIR *d;
	struct dirent *dir;
	d=opendir("."); //open existing directory
	if(d)
	{
		while((dir=readdir(d)) != NULL)
		{
			printf("%s\n",dir->d_name);
		}
		
	closedir(d); //close current directory
	}	
	return 0;
}

