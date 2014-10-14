
#include<stdio.h>
#include <dirent.h>
void usage();
void remove_test_dir(char *path,char *newDir);
void create_test_dir(char *path,char *newDir);
int main(int argc, char *ARGV[])  {
int i=0;
char ch;
char target_path[]="/tmp";
char newDir[]="C-test";
int target_path_index=0;
int cdir_path_index=0;
int rdir_path_index=0;
int len_of_target_path=0;
	for(i=1;i<argc;i++)  {
		if(!strcmp(ARGV[i],"-target") || !strcmp(ARGV[i],"-t"))  { // if switch is -t[arget]
			target_path_index=++i;				   // hold the count of next arg
		}
        else if(!strcmp(ARGV[i],"-create") || !strcmp(ARGV[i],"-c"))  { // if switch is -t[arget]
			cdir_path_index=++i;				   // hold the count of next arg
		}
        else if(!strcmp(ARGV[i],"-remove") || !strcmp(ARGV[i],"-r"))  { // if switch is -t[arget]
			rdir_path_index=++i;				   // hold the count of next arg
		}
		else{
			if(!strcmp(ARGV[i],"-usage") || !strcmp(ARGV[i],"-u")); 
			else
			printf("Invalid usage: %s??\n",ARGV[i]);   // if switch is other than -t[arget] or -u[sage]
			usage();
			return 0;
		}
	}

	printf("target = %s dir = %s\n",ARGV[target_path_index],ARGV[cdir_path_index]);

    if(!target_path_index || (target_path_index && !cdir_path_index && !rdir_path_index)) {
	   printf("Invalid usage: -dir <DIR_NAME> option missing\n");
	   return 0;
	}

	if(cdir_path_index) create_test_dir(ARGV[target_path_index],ARGV[cdir_path_index]);
	if(rdir_path_index) remove_test_dir(ARGV[target_path_index],ARGV[rdir_path_index]);
	
return 0;
}

// function that checks for "/" at the end of path and creates the directory
void create_test_dir(char *path, char *newDir)  {
int len_of_target_path=strlen(path);
int len_of_dir_path=strlen(newDir);
char *p1 = (char *) malloc (len_of_target_path * sizeof(char)) ;
char *p2;
   len_of_dir_path++;
   strcpy(p1,path);
   
   p2 = (char *) realloc (p1, len_of_dir_path*sizeof (char));
   if ( p2 != NULL ) { //realloc was successful
      p1=NULL;
   }
   strcat(p2,"/");
   strcat(p2,newDir);
   printf("Creating Directory = %s\n",p2);
   if(! mkdir(p2,0777)) 
   	  printf("created directory\n");
   else
   	  printf("can't create dir\n");
}

//function that removes all the test files created in the C-test directory and also deletes the C-test directory
void remove_test_dir(char *path, char *newDir)  {
DIR *dir;
struct dirent *content;
int len_of_target_path=strlen(path);
int len_of_dir_path=strlen(newDir);
char *p1 = (char *) malloc (len_of_target_path * sizeof(char)) ;
char *p2;
   len_of_dir_path++;
   strcpy(p1,path);
   
   p2 = (char *) realloc (p1, len_of_dir_path*sizeof (char));
   if ( p2 != NULL ) { //realloc was successful
      p1=NULL;
   }
   strcat(p2,"/");
   strcat(p2,newDir);

   printf("Remove dir %s\n",p2);
   if ((dir = opendir(p2)) == NULL) {
      printf("ERROR: unable to read the contents in dir %s\n", p2);
      return;
   }
   while ((content = readdir(dir)) != NULL)
   	  remove(content->d_name);
      closedir(dir);
      rmdir(p2);
   }

// help function
void usage() {
printf("-- C-test.c is a c program that creates the directory to run the tests and removes it up on completion of the test\n");
printf("Valid switch options are:\n\n");
printf("\t-t[arget]  <TARGET_PATH>   must needed option\n");
printf("\t-c[reate]  <New_dir_name>\n");
printf("\t-r[remove] <Remove_dir>\n");
printf("\t-u[sage]  -- help command\n");
}

