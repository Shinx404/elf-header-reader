#include <stdio.h>

int main(int argc, char *argv[]){
	FILE *file;
	char magic_numbers[4][2];
	char elf_sign[4][2] = {"7F","45","4C","46"};
	char *str;

	if(argv[1] !=  NULL){
		file = fopen(argv[1], "rb");
		if(file != NULL){
			fread(magic_numbers,sizeof(int),4,file);
			
			printf("filetype: ");
			for(int i = 0; i < sizeof(magic_numbers)/sizeof(magic_numbers[0]);i++){
				printf(" %s",magic_numbers[i]);
			}
		}	
		else{
			fprintf(stderr,"no file given...");
			return -1;
		}
	}
	else{
		fprintf(stderr,"no argument given...");
		return -1;
	}

	return 0;
}
