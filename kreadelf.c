#include <stdio.h>
#include <string.h>
#include <time.h>


void magicBytes(char *arr){
	char magic_numbers[4];
	char elf_sign[4] = {0x7F,0x45,0x4C,0x46};
	int cmp = 1;

	for(int i = 0; i < 4; i++){
		magic_numbers[i] = arr[i];
	}

	printf("magic bytes:\t\t");
	for(int i = 0; i < sizeof(magic_numbers)/sizeof(magic_numbers[0]);i++){
        	printf("%x ",magic_numbers[i]);
                if(magic_numbers[i] != elf_sign[i]){
                	cmp = 0;
               	}
        }
	if(cmp != 0){
        	printf("\nfiletype:\t\tELF");
        }
	printf("\n");

}


void arch(char *arr){
	printf("architecture:\t\t");
	if(arr[4] == 0x01){
       		printf("32-bit");
        }
       	else if(arr[4] == 0x02){
        	printf("64-bit");
        }
        else{
        	printf("N/A");
        }
	printf("\n");
}

void endian(char *arr){
	printf("endianness:\t\t");
	if(arr[5] == 0x00){
		printf("big endian");
	}
	else if(arr[5] == 0x01){
		printf("little endian");
	}
	else{
		printf("N/A");
	}
	printf("\n");
}


int main(int argc, char *argv[]){
	FILE *file;
	char e_ident[16];
	int cmp;
	char options[] = {'m','a','e'};
	float runtime;
	
	if(argc > 1){
		if(argc >= 3){
			file = fopen(argv[2], "rb");
		}
		else{
			file = fopen(argv[1], "rb");
		}
		if(file != NULL){
			fread(e_ident,1,16,file);
			if(argv[1][1] == options[0]){
				magicBytes(e_ident);
			}
			else if(argv[1][1] == options[1]){
				arch(e_ident);
			}
			else if(argv[1][1] == options[2]){
				endian(e_ident);
			}
			else{
				magicBytes(e_ident);
				arch(e_ident);
				endian(e_ident);
			}

		}	
		else{
			fprintf(stderr,"no file given...");
			runtime = (float)clock() / CLOCKS_PER_SEC;
        		printf("\n\nruntime:\t\t%f ms", runtime*1000);
			return -1;
		}
	}
	else{
		fprintf(stderr,"no argument given...");
		runtime = (float)clock() / CLOCKS_PER_SEC;
        	printf("\n\nruntime:\t\t%f ms", runtime*1000);
		return -1;
	}

	runtime = (float)clock() / CLOCKS_PER_SEC;
	printf("\n\nruntime:\t\t%f ms", runtime*1000);
	
	return 0;
}
