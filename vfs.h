#ifndef VFS_H_
#define VFS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_FILE_QTY 10

struct fileStructure {
	char fname[30];
	char fcontent[100];
};

int fs_write(char* fname, char* databuf);
long int fs_get_file_size(const char* fname);
int fs_read(const char* fname, char* databuf);
int fs_ls(char** arr_str);
void fs_init(void);
int fs_if_file_exists(const char* fname);


#endif /* VFS_H_ */