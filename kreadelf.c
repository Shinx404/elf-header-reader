#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]){
	FILE *file;
	char magic_numbers[4];
	char elf_sign[4] = {0x7F,0x45,0x4C,0x46};
	int cmp = 1;

	if(argv[1] !=  NULL){
		file = fopen(argv[1], "rb");
		if(file != NULL){
			
			fread(magic_numbers,sizeof(int),4,file);
			
			printf("filetype: ");
			for(int i = 0; i < sizeof(magic_numbers)/sizeof(magic_numbers[0]);i++){
				printf(" %x",magic_numbers[i]);
				if(magic_numbers[i] != elf_sign[i]){
					cmp = 0;
				}
			}
			if(cmp != 0){
				printf("\nthis is an ELF!");
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
