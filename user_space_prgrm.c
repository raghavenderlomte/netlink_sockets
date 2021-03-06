#include <sys/socket.h>
#include <unistd.h>
#include <linux/netlink.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct sockaddr_nl src_addr,dest_addr;
struct iovec iov;
struct msghdr msg;
struct nlmsghdr *nlh;
int ret=0;
int main()
{
	int fd = socket(AF_NETLINK, SOCK_RAW, 31);
	if(fd == -1)
	{
		perror("socket error\n");
		return -1;
	}
	while(1)
	{
	sleep(3);

	memset(&src_addr, 0, sizeof(src_addr));
	src_addr.nl_family = AF_NETLINK;
	src_addr.nl_pid = getpid();
	src_addr.nl_groups = 0;
	ret = bind (fd,(struct sockaddr *)&src_addr, sizeof(src_addr));
	if(ret < 0 )
	{
		perror("bind error\n");
		return -1;
	}
	memset(&dest_addr, 0, sizeof(dest_addr));
	dest_addr.nl_family = AF_NETLINK;
	dest_addr.nl_pid = 0;
	dest_addr.nl_groups = 0;
	nlh=(struct nlmsghdr *)malloc(NLMSG_SPACE(1024));
	nlh->nlmsg_len = NLMSG_SPACE(1024);
	nlh->nlmsg_pid = getpid();
	nlh->nlmsg_flags = 0;
		strcpy(NLMSG_DATA(nlh), "Hello You");
	iov.iov_base = (void *)nlh;
	iov.iov_len = nlh->nlmsg_len;
	msg.msg_name= (void *)&dest_addr;
	msg.msg_namelen=sizeof(dest_addr);
	msg.msg_iov=&iov;
	msg.msg_iovlen = 1;
	ret =sendmsg(fd, &msg, 0);
	if(ret == -1)
	{
		perror("sendmsg error\n");
		return -1;
	}
	ret =recvmsg(fd, &msg, 0);
	if(ret == -1)
	{
		perror("recvmsg error\n");
		return -1;
	}
	printf("data from kernel %s\n",NLMSG_DATA(nlh));
	}
	close(fd);
	return 0;

	

}


