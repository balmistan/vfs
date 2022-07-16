
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_QTY 10

struct fileStructure {
	char fname[30];
	char fcontent[100];
}virtualFileSystem[MAX_FILE_QTY];


/**
 * @brief Create a virtual file if it doesn't already exist. Overwrite its contents if it exists.
 * @param fname pointer to file name
 * @param databuf is a pointer to the buffer from which to read the content to be written to the virtual file
 * @return 0 on SUCCESS or -1 on ERROR.
**/
int fs_write(char* fname, char* databuf){
	//content override if file exists
	for (int i=0; i<MAX_FILE_QTY; i++){
		if(!strcmp(fname, virtualFileSystem[i].fname)){
    		strcpy(virtualFileSystem[i].fcontent, databuf);
    		return 0;
  	 	}
	}
	//create file if it doesn't exists
	for (int i=0; i<MAX_FILE_QTY; i++){
  		 if (!strcmp(virtualFileSystem[i].fname, "")){
		  	strcpy(virtualFileSystem[i].fname, fname);
   			strcpy(virtualFileSystem[i].fcontent, databuf);
    		return 0;
   			}
	}
	return -1;
}


/**
 * @brief Reads the contents of a virtual file
 * @param fname pointer to file name
 * @param databuf is a pointer to the array to receive data read from virtual file
 * @return 0 on SUCCESS or -1 on error
**/
int fs_read(char* fname, char* databuf){
	for (int i=0; i<MAX_FILE_QTY; i++){
	   if (!strcmp(fname, virtualFileSystem[i].fname)){   
	       strcpy(databuf, virtualFileSystem[i].fcontent);
	       return 0;
	   }
	}
	   return -1;
}


/**
 * @brief It prints the file list
 */
void fs_ls(void){
	printf("%s\n", "----------------------FILE LIST-----------------------------");
	for (int i=0; i<MAX_FILE_QTY; i++){
	   if (strcmp(virtualFileSystem[i].fname, "")){
		printf("\t%s\n", virtualFileSystem[i].fname);
	   }
	}
	printf("%s\n", "------------------------------------------------------------");
}









// ############################  TEST FUNCTION  ################################# 


/**
 * @brief main function used for testing
 */
int main(int argc, char *argv[]){	
	char fname[30], buf[100], choice;
	int issue;
	while(1){
		printf("\n\n");
		printf("1. Create a new file or modify its content \n");
		printf("2. Read the contents of a file \n");
		printf("3. Exit \n\n");
		printf("Type your choice: ");
		choice = getchar(); 
		while(getchar()!='\n');
		//getchar();
		switch(choice){
			case '1':
				fputs("\nEnter the file name:  ", stdout);
				fgets(fname, 29, stdin);
				fname[strlen(fname) - 1] = '\0';
				fputs("\nEnter the contents of the file:  ", stdout);
				fgets(buf, 99, stdin);
				buf[strlen(buf) - 1] = '\0';
				issue = fs_write(fname, buf);
				fs_ls();
				if(issue == -1)
					printf("%s %s\n\n", "error write to file: ", fname);	
				break;  
			case '2':
				printf("\nEnter the file name: ");
				fgets(fname, 29, stdin);
				fname[strlen(fname) - 1] = '\0';
				issue = fs_read(fname, buf);
				fs_ls();
				if(issue == -1)
					printf("%s %s\n\n", "error read file: ", fname);
				else
					printf("%s %s:  %s\n\n", "string in ", fname, buf );
				break;
			case '3':
				fputs("\nGoodbye!\n\n", stdout);
				exit(0);               
			default: 
				break;
		}//switch close
		
	}//while close
}//main close
