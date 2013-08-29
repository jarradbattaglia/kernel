#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct {
	unsigned char firstInstruction[3];  // This is often a jump instruction to the boot sector code itself
	unsigned char OEM[8];  		
	unsigned char numBytesPerSector[2];
	unsigned char numSectorsPerCluster[1];
	unsigned char numReservedSectors[2];
	unsigned char numCopiesFAT[1];
	unsigned char numEntriesRootDir[2];
	unsigned char numSectors[2];
	unsigned char mediaDescriptor[1];
	unsigned char numSectorsInFAT[2];
	unsigned char numSectorsPerTrack[2];
	unsigned char numSides[2];
	unsigned char numHiddenSectors[2];
	unsigned char bootstrap[480];
	unsigned char signature[2];
} FATHEAD;

typedef struct {
	unsigned char name[13];
	unsigned char stuff[19];
} ENTRY;

int LITTLE_ENDIAN = 1;
int BIG_ENDIAN = 0;

int read_int(unsigned char* source, int bytes, int endian) {
	int data = 0;
	if(endian == LITTLE_ENDIAN) { 
		for(int i = bytes-1; i >= 0; i--) {
			data = data | source[i] << (8*i);
		}
	} else { 
		for(int i = 0; i < bytes; i++) {
			data = data | source[i] << (8*(bytes-i-1));
		}
	}
	return data;
}

int main() {

	int fd = open("samplefat.bin",O_RDONLY);

	FATHEAD fh, fh2;
	ENTRY entry;

	read(fd, &fh, sizeof(fh));
	
	printf("OEM: %s\n", fh.OEM);	
	printf("Media descriptor: %x\n", read_int(fh.mediaDescriptor, 1, BIG_ENDIAN));
	printf("# of bytes per sector: %d\n", read_int(fh.numBytesPerSector, 2, LITTLE_ENDIAN));
	printf("# of sectors per cluster: %d\n", read_int(fh.numSectorsPerCluster, 1, BIG_ENDIAN));
	printf("# of reserved sectors: %d\n", read_int(fh.numReservedSectors, 2, BIG_ENDIAN));	
	printf("# of FAT: %d\n", read_int(fh.numCopiesFAT, 1, BIG_ENDIAN));
	printf("# of root directory entires: %d\n", read_int(fh.numEntriesRootDir, 2, LITTLE_ENDIAN));	
	printf("# of sectors: %d\n", read_int(fh.numSectors, 1, BIG_ENDIAN));
	printf("# of sectors per FAT: %d\n", read_int(fh.numSectorsInFAT, 2, LITTLE_ENDIAN));
	printf("# of sectors per track: %d\n", read_int(fh.numSectorsPerTrack, 2, LITTLE_ENDIAN));
	printf("# of sides: %d\n", read_int(fh.numSides, 2, LITTLE_ENDIAN));
	printf("# of hidden sectors: %d\n", read_int(fh.numHiddenSectors, 2, LITTLE_ENDIAN));
	//printf("%s\n",entry.name);	
	//printf("%s\n",fh.numBytesPerSector);BYE
	return 1;
	
}


