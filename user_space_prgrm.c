#include <sys/socket.h>
#include <linux/netlink.h>
#include <sys/types.h>
#include <stdio.h>


int main()
{
	int fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_USER_SPACE_COMM);
}


