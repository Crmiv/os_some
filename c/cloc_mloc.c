//define void*calloc(size_t nmemb,size_t size)
//equal malloc(nmemb *size)
//caloc fun init all the memory 0

struct test
{
	int a[10];
	char b[20];
}

fun{
	struct test *ptr=calloc(sizeof(struct test),10);
}

//get page size
#include<unistd.h>
size_t getpagesize(void)
{
	//return an int type
	getpagesize();
}
#include<unistd.h>
#include<sys/mman.h>


//define mem mapping

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/mman.h>

main()
{
	int fd;
	void *start;
	struct stat sb;
	fd=open("/etc/passwd",O_RDONLY);
	fstat(fd,&sb);
	start=mmap(NULL,sb.st_size,PROT_READ,MAP_PRIVATE,fd,0);
	if(start==MAP_FAILED)
		return;
	munma(start,sb.st_size);
	closed(fd);
}
