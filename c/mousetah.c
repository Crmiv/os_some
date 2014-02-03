#include<stdio.h>
#include<stdlib.h>
#include<linux/input.h>
#include<fcntl.h>
#include<sys/time.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

int main(int argc,char **argv)
{
	int fd,retval;
	char buf[6];
	fd_set readfds;
	struct timeval tv;
	fd = open("/dev/input/mice", O_RDONLY);
	if(fd<0)
	{
		exit(1);
	}
	else{
		//success
	}

	while(1)
	{
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		FD_ZERO(&readfds);
		FD_SET(fd, &readfds);

		retval = select(fd+1,&readfds,NULL,NULL,&tv);
		if(retval==0)
		{
			printf("time out!");
		}
		if(FD_ISSET(fd,&readfds)){
			//read mouse data
			if(read(fd,buf,6) <= 0)
			{
				continue;
			}
			printf("%d %d %d %d",(buf[0] & 0x07), buf[1], buf[2], buf[3]);
		}
	}
	close(fd);
	return 0;

}
