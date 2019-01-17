#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int8_t write_buf[1024];
int8_t read_buf[1024];

int main()
{
	int fd;
	int option;
	printf("*********Created by Spanidea**************\n");
		
	fd = open("/dev/my_device", O_RDWR);
	if(fd < 0)
	{
		printf("Can not able to open device file\n");
		return 0;
	}
	
	while(1)
	{
		printf("*****************************************\n");
		printf("\t1.Read\n");
		printf("\t2.Write\n");
		printf("\t3.Exit\n");
		printf("Please Enter your option : \n");
		scanf("%d",&option);
		switch(option)
		{
			case 1:
				printf("Data reading\n");
				read(fd,read_buf,1024);
				printf("Done \n");
				printf("Data : %s\n",read_buf);
				break;
			case 2:
				printf("Enter the string to write :\n");
				scanf(" %[^\t\n]s",write_buf);
				printf("Data Writng ...\n");
				write(fd,write_buf,strlen(write_buf)+1);
				printf("Done...\n");
				break;
			case 3:
				close(fd);
				printf("Program exit\n");
				return 0;
				break;
			default:
				printf("please provide proper option.\n");
				break;
		}

		printf("*****************************************\n");
	}
	return 0;
}
