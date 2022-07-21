#include "vfs.h"


struct fileStructure virtualFileSystem[MAX_FILE_QTY]; //struct and MAX_FILE_QTY are defined in vfs.f



long int fs_get_file_size(const char* fname){
	for (int i=0; i<MAX_FILE_QTY; i++){
		   if (!strcmp(fname, virtualFileSystem[i].fname)){    
		       return strlen(virtualFileSystem[i].fcontent);
		   }
		}
		   return -1;
}


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
int fs_read(const char* fname, char* databuf){
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
/*void fs_ls(char **arr_str){
	int count = 1; 
	arr_str[0] = NULL;
	for (int i=0; i<MAX_FILE_QTY; i++){
	   if (strcmp(virtualFileSystem[i].fname, "")){
		arr_str[count -1] = realloc(arr_str[count - 1], (strlen(virtualFileSystem[i].fname) +1 )* sizeof(char));
		strcpy(arr_str[count -1], virtualFileSystem[i].fname);
		arr_str[count] = NULL;
		count ++;
	   }
	}
	return;
}
*/
int fs_ls(char** arr_str){
	int count = 0;           //array index
	int file_qty = 0;        //quantity of file with filename != ""
	int len = 0;             //length of filename
	
	while (count < MAX_FILE_QTY){
	   if (len = strlen(virtualFileSystem[file_qty].fname)>0){
		arr_str[count] = (char*)realloc(arr_str[count], (len + 1 )* sizeof(char));
		strcpy(arr_str[count], virtualFileSystem[file_qty].fname);
		file_qty++;
	   }//if close
	   count ++;
	}//while close
	return file_qty;
}

void fs_init() {
 fs_write(strdup("hello"), strdup("This is the content in file hello."));
 return;
}

int fs_if_file_exists(const char* fname){
	for (int i=0; i<MAX_FILE_QTY; i++){
		   if (!strcmp(fname, virtualFileSystem[i].fname)){   
		       return 0;
		   }
		}
	return -ENOENT;
}
