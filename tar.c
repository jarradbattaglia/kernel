#include <stdio.h>
#include <stdlib.h>

//for some reason will only output all files after the scond one, and does first one correctly
//seems to be problem with null values and counting them
typedef struct  {
	char name[100];
	char mode[8];
	char uid[8];
	char gid[8];
	char size[12];
	char mtime[12];
	char chksum[8];
	char typeflag;
	char linkname[100];
	char magic[6];
	char version[2];
	char uname[32];
	char gname[32];
	char devmajor[8];
	char devminor[8];
	char prefix[155];
} posix_header;

void print_file_headers( posix_header* header) {
	printf("Name: %s\n", header->name);
    printf("Mode: %s\n", header->mode);
    printf("UID: %s\n", header->uid);
    printf("GID : %s\n", header->gid);
    printf("Size: %s\n", header->size);
    printf("MTime: %s\n", header->mtime);
    printf("Checksum: %s\n", header->chksum);
    printf("UName: %s\n", header->uname);
    printf("GName: %s\n", header->gname);
    printf("\n");
}

int main(int argc, char *argv[]) {
	if(argc < 2) {
		printf("There is less than one argument, please enter in form of ./tar filename");
		return 1;
	}
	FILE *fp;
	fp = fopen(argv[1], "r");
	//read file in, and offset in header
	int current_offset = 0;
	//how big is header (500 charachters)
	int header_offset = 500;
	int nulls = 0;
	int c;
	int file_count = 0;
	int file_started = 0;
	//each content will be able to hold up to 2000 charachers (my limit)
	char* content = (char*)malloc(sizeof(char)*2000);
	int length;
	//first read in file
	posix_header tar_header;

	while(c != EOF) {
		//read each character one at a time so we can add to each buffer and then contents
		//first get all null characters from front
		c = getc(fp);
		if(current_offset < header_offset) 
		{
			if(current_offset < 100) {
				file_started = 1;
				tar_header.name[current_offset] = c;		
			}
			else if(current_offset < 108) {
				tar_header.mode[current_offset-100]=c;
			}
			else if(current_offset < 116) {
				tar_header.uid[current_offset-108]=c;
			}
			else if(current_offset < 124) {
				tar_header.gid[current_offset-116]=c;
			}
			else if(current_offset < 136) {
				tar_header.size[current_offset-124]=c;
			}
			else if(current_offset < 148) {
				tar_header.mtime[current_offset-136]=c;
			}
			else if(current_offset < 156) {
				tar_header.chksum[current_offset-148]=c;
			}
			else if(current_offset < 157) {
				tar_header.typeflag = c;
			}
			else if(current_offset < 257) {
				tar_header.linkname[current_offset-157]=c;
			}
			else if(current_offset < 263) {
				tar_header.magic[current_offset-257]=c;
			}
			else if(current_offset < 265) {
				tar_header.version[current_offset-263]=c;
			}
			else if(current_offset < 297) {
				tar_header.uname[current_offset-265]=c;
			}
			else if(current_offset < 329) {
				tar_header.gname[current_offset-297]=c;
			}
			else if(current_offset < 337) {
				tar_header.devmajor[current_offset-329]=c;
			}
			else if(current_offset < 345) {
				tar_header.devminor[current_offset-337]=c;
			}
			else {
				tar_header.prefix[current_offset-345]=c;
			}
		}
		else if(current_offset == header_offset)
		{
			//pretty much header is done and are now at file content start
			file_count++;
			length =0;
		}
		else 
		{
			//if valid character put in content array then this is the files contents
			if(c) {
				//only store 2000 but keep on going till end of file or reach null delimiter
				if(length < 2000) {
					content[length] = c;
					length++;
				}				
			}
		}
		//keep track of number of nulls
		if(c == NULL) {
			nulls++;
		} else {
			//at certain point, there are a certain amount of nulls to also declare file done
			//hit a non null again
			if(nulls > 207) {
				current_offset = 0;
				file_started = 0;
				//probably got next files character
				ungetc(c,fp);
				//now write file to disk
				FILE* efp;
				print_file_headers(&tar_header);
				efp = fopen(tar_header.name, "w");
				int i=0;
				while(i < length) {
					fprintf(efp,"%c",content[i]);
					i++;
				}
				fclose(efp);
				printf("Created %s\n", tar_header.name);
				posix_header test;
				tar_header = test;
				content = (char*)malloc(sizeof(char)*2000);
			}
			nulls = 0;

		}
		if(file_started == 1) {
			current_offset++;
		}
	}
	
	//now that all files are read, try to extract them
	//create file to extract
	fclose(fp);
	printf("%d files created\n", file_count);
	//close tar file
	return 0;		
	
}
