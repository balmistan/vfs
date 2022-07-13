
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_QTY 10

struct fileStructure {
	char fname[30];
	char fcontent[100];
};


/**
 * @brief Returns the pointer to the array of structures of type fileStructure. The first call declares the array and initializes the various fields with empty strings.
**/
struct fileStructure* getVirtualFileSystem(){
	static struct fileStructure* virtualFileSystem = NULL;
	if(!virtualFileSystem){
		virtualFileSystem = (struct fileStructure*) malloc(MAX_FILE_QTY * sizeof(struct fileStructure));
		for(int i=0; i<MAX_FILE_QTY; i++){
			strcpy(virtualFileSystem[i].fname, "");
			strcpy(virtualFileSystem[i].fcontent, "");
			}	
	}
	return virtualFileSystem;
}

/**
 * @brief Create a virtual file if it doesn't already exist or overwrite its contents.
 * @param fname pointer to file name
 * @param buf pointer to the buffer from which to read the content to be written to the virtual file
 * @return amount of bytes written or -1 on error.
**/
int fs_write(char* fname, char* buf){
	struct fileStructure* virtualFileSystem = getVirtualFileSystem();
	//content override if file exists
	for (int i=0; i<MAX_FILE_QTY; i++){
		if(!strcmp(fname, virtualFileSystem[i].fname)){
    		strcpy(virtualFileSystem[i].fcontent, buf);
    		return strlen(buf);
  	 	}
	}
	//create file if it doesn't exists
	for (int i=0; i<MAX_FILE_QTY; i++){
  		 if (!strcmp(virtualFileSystem[i].fname, "")){
		  	strcpy(virtualFileSystem[i].fname, fname);
   			strcpy(virtualFileSystem[i].fcontent, buf);
    		return strlen(buf);
   			}
	}
	return -1;
}

/**
 * @brief Reads the contents of a virtual file
 * @param fname pointer to file name
 * @param buf pointer to the buffer into which to place the content read from the virtual file
 * @return amount of bytes read or -1 on error
**/
int fs_read(char* fname, char* buf){
	struct fileStructure* virtualFileSystem = getVirtualFileSystem();
	for (int i=0; i<MAX_FILE_QTY; i++){
	   if (!strcmp(fname, virtualFileSystem[i].fname)){
	    strcpy(buf, virtualFileSystem[i].fcontent);
	    return strlen(buf);
	   }
	}
	   return -1;
}
/**
 * @brief It prints the file list
 */
void fs_ls(void){
	struct fileStructure* virtualFileSystem = getVirtualFileSystem();
	printf("%s\n", "----------------------FILE LIST-----------------------------");
	for (int i=0; i<MAX_FILE_QTY; i++){
	   if (strcmp(virtualFileSystem[i].fname, "")){
		printf("\t%s\n", virtualFileSystem[i].fname);
	   }
	}
	printf("%s\n", "------------------------------------------------------------");
}


/**
 * @brief main function used for testing
 */
int main(int argc, char *argv[]){	
	char fname[30], buf[100], choice;
	while(1){
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
				if(fs_write(fname, buf )== -1)
					printf("%s %s\n", "error write to file: ", fname);
				break;  
			case '2':
				printf("\nEnter the file name: ");
				fgets(fname, 29, stdin);
				fname[strlen(fname) - 1] = '\0';
				if(fs_read(fname, buf)==-1)
					printf("%s %s\n", "error read file: ", fname);
				else
					printf("%s %s:  %s\n\n", "string in ", fname, buf );
				break;
			case '3':
				fputs("\nGoodbye!\n\n", stdout);
				exit(0);               
			default: 
				break;
		}//switch close
		fs_ls();
	}//while close
}//main close
