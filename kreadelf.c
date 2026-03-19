#include <stdio.h>
#include <string.h>


void magic_bytes(char *arr){
	char magic_numbers[4];
	char elf_sign[4] = {0x7F,0x45,0x4C,0x46};
	int cmp = 1;

	for(int i = 0; i < 4; i++){
		magic_numbers[i] = arr[i];
	}

	printf("magic bytes: ");
	for(int i = 0; i < sizeof(magic_numbers)/sizeof(magic_numbers[0]);i++){
        	printf(" %x",magic_numbers[i]);
                if(magic_numbers[i] != elf_sign[i]){
                	cmp = 0;
               	}
        }
	if(cmp != 0){
        	printf("\nfiletype: ELF");
        }

}


void arch(char *arr){
	if(arr[4] == 0x01){
       		printf("\narchitecture: 32-bit");
        }
       	else if(arr[4] == 0x02){
        	printf("\narchitecture: 64-bit");
        }
        else{
        	printf("\ncan't recognize architecture");
        }
}

int main(int argc, char *argv[]){
	FILE *file;
	char e_ident[16];
	int cmp;

	if(argv[1] !=  NULL){
		file = fopen(argv[1], "rb");
		if(file != NULL){
			
			fread(e_ident,1,16,file);
			
			magic_bytes(e_ident);

			arch(e_ident);

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
