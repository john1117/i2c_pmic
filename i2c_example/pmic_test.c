#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>

const char *filename = "/dev/i2c-0";

int main(int argc, char **argv) {
	int file;
	char buf[255] = {0};
	int i, j;
	int cnt = 0;
	int addr = 0b00110010;

	if ((file = open(filename,O_RDWR)) < 0) {
		printf("Failed to open the bus.");
		exit(1);
	}

	if (ioctl(file,I2C_SLAVE,addr) < 0) {
		printf("Failed to acquire bus access and/or talk to slave.\n");
		exit(1);
	}

	if (argc > 1) {
		buf[0] = (int)strtol(argv[1], NULL, 16);
		buf[1] = (int)strtol(argv[2], NULL, 16);
		if (write(file,buf,2) < 1) {
			printf("Failed to write to the i2c bus.\n");
		}
	}

	if (read(file,buf,255) < 0) {
		printf("Failed to read from the i2c bus.\n");
	} else {
			printf("    ");
		for (i = 0; i < 16; i++)
			printf(" %x ", i);
		printf("\n");
		for (i = 0; i < 16; i++) {
			printf("%x : ", i);
			for (j = 0; j < 16; j++) {
	    			printf("%02x ", buf[cnt++]);
			}
			printf("\n");
		}
	}

	return 0;
}
