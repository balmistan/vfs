#include "vfs.h"

void print_list(void){
	char **arr_str;
	int i=0;
	int file_qty = 0;
	
	arr_str = malloc(sizeof(char*) * MAX_FILE_QTY);

	file_qty = fs_ls(arr_str);
	printf("%s\n", "----------------------FILE LIST-----------------------------");
	while( i < file_qty ){
		printf("\t%s\n", arr_str[i]);
		i++;
	}
	printf("%s\n", "------------------------------------------------------------");
}

/**
 * @brief main function used for testing
 */
int main(int argc, char *argv[]){	
	char fname[30], buf[100], choice;
	int issue;
	fs_init();
	print_list();
	while(1){
		printf("\n\n");
		printf("1. Create a new file or modify its content \n");
		printf("2. Read the contents of a file \n");
		printf("3. Exit \n\n");
		printf("Type your choice: ");
		choice = getchar(); 
		while(getchar()!='\n');
		switch(choice){
			case '1':
				fputs("\nEnter the file name:  ", stdout);
				fgets(fname, 29, stdin);
				fname[strlen(fname) - 1] = '\0';
				fputs("\nEnter the contents of the file:  ", stdout);
				fgets(buf, 99, stdin);
				buf[strlen(buf) - 1] = '\0';
				issue = fs_write(fname, buf);
				print_list();
				if(issue == -1)
					printf("%s %s\n\n", "error write to file: ", fname);	
				break;  
			case '2':
				printf("\nEnter the file name: ");
				fgets(fname, 29, stdin);
				fname[strlen(fname) - 1] = '\0';
				issue = fs_read(fname, buf);
				print_list();
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
