/*
 * ePing
 *
 *
 * Using the Internet Control Message Protocol (ICMP) "ECHO" facility,
 * measure round-trip-delays and packet loss across network paths.
 *
*/

//TODO remove this when debugging is done
#include <iostream>

/*
*
* Imports
*
*/
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/file.h>
#include <sys/time.h>
#include <sys/signal.h>
#include <sys/unistd.h>

#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#if __unix__
#include <arpa/inet.h>
#include <time.h>

#elif __WINDOWS__
#include <windows.h>
#include <winsock2.h>
#endif

/*
	IP HEADER
*/
struct tagIPHeader
{
	u_char versionHeaderLength;
	u_char typeOfService;
	short totalLength;
	short ID;
	short flagsFragOff;
	u_char timeToLive;
	u_char protocol;
	u_short checksum;
	struct in_addr sourceIPAddress;
	struct in_addr destinationIPAddress;
};
/*
	Address Info Struct
*/

// struct addrinfo {
	// int ai_flags; // AI_Passive
	// int ai_family; // Inet? Inet6? Unspecified?
	// int ai_socktype; // Stream or Datagram: SOCK_STREAM or SOCK_DIAGRAM
	// int ai_protocol; //
	// size_t ai_addrlen;  // Size of ai_addr in bytes
	// struct sockaddr *ai_addr; // other struct
	// char *ai_canonname; //full canonical hostname
	// struct addrinfo *ai_next; // linked list, next node
// };




/* 
	ICMP HEADER 
*/
struct tagICMPHeader{
	u_char type;
	u_char code;
	u_short checksum;
	u_short identifier;
	u_short sequenceNumber;
};

tagICMPHeader icmpHeader;
struct tagICMPEchoRequest{
	tagICMPHeader icmpHeader;
	time_t time;
	//char charfillData[REQ_DATASIZE];
	char charfillData[3];
};
/*
	Initialize Structs
*/
tagICMPEchoRequest ICMPEchoRequest;
addrinfo addressInfo;
tagIPHeader IPHeader;
struct sockaddr whereto;
// Variable to see if the packet was sent
int sent;


/*

	Checksum()

	Taken from Mike Musss' version of ping.c
	from the public domain
*/
static int checksum(u_short *addr, int len)
{
        register int nleft = len;
        register u_short *w = addr;
        register int sum = 0;
        u_short answer = 0;

        /*
         * Our algorithm is simple, using a 32 bit accumulator (sum), we add
         * sequential 16 bit words to it, and at the end, fold back all the
         * carry bits from the top 16 bits into the lower 16 bits.
         */
        while (nleft > 1)  {
                sum += *w++;
                nleft -= 2;
        }

        /* mop up an odd byte, if necessary */
        if (nleft == 1) {
                *(u_char *)(&answer) = *(u_char *)w ;
                sum += answer;
        }

        /* add back carry outs from top 16 bits to low 16 bits */
        sum = (sum >> 16) + (sum & 0xffff);     /* add hi 16 to low 16 */
        sum += (sum >> 16);                     /* add carry */
        answer = ~sum;                          /* truncate to 16 bits */
        return(answer);
}


/*

	ping()

*/
void ping(int socketDescriptor,int REQ_DATASIZE)
{

	printf("Mark 1 ping\n");
	register struct tagICMPHeader *icmpHeader;
	// Fill in some data to send
	printf("Mark 2 ping\n");
	memset(ICMPEchoRequest.charfillData, ' ', REQ_DATASIZE);

	// Save tick count when sent (milliseconds)
	// echoRequest.time = gettime ...;

	// Compute checksum
	ICMPEchoRequest.icmpHeader.checksum = checksum((u_short *)icmpHeader, 30);
	printf("Mark 3 ping\n");
	
	sent = sendto(socketDescriptor, ICMPEchoRequest.charfillData, 30, 0, &whereto, sizeof(struct sockaddr));
	printf("Mark 4 ping\n");
	
	// Increment sequence number
	ICMPEchoRequest.icmpHeader.sequenceNumber++;
	printf("PING");

	
}



/*

	listen()

*/
void listen(int socketDescriptor)
{
	// Setting some flags needed for select()
	readfds.fd_count = 1; // Set # of sockets (I **think**)
	readfds.fd_array[0] = raw; // Should be the sets of socket descriptors
	timeout.tv_sec = 5; // timeout period, seconds (added second, if that matters)
	timeout.tv_usec = 0; // timeuot period, microseconds 1,000,000 micro = second
	
	char buf[512];
	
	// The following are functions we will probably need to use later
	// On second thought, we recieve (ping) packets one at a time, not as a set. We may not need these after all.
	// FD_SET(int fd, fd_set *set);		Add fd to the set
	// FD_CLR(int fd, fd_set *set);		Remove fd to the set
	// FD_ISSET(int fd, fd_set *set);	Returns trye if fd is in the set(probably won't use this one)
	// FD_ZERO(fd_set *set);			Clears all entries from the set

	rv = select(socketDescriptor + 1, &readfds, NULL, NULL, &timeout);
	case(rv) 
	{
		case -1:
			printf("Something terrible has happened! Error in select()");
		case 0:
			printf("I'm tired of waiting. Timeout occurred. Either timeout is too short or packet took too long to reply.");
		default:
			printf("(I think) this means we have a reply!");
			if(FD_ISSET(socketDescriptor, &readfds) {
				recvfrom(socketDescriptor, buf, sizeof buf, 0, 
			}
	}
	
	// Get the info out of it
	
	// Was it an error packet? Uh oh!
	
	/* Lost packets: was this packet in order with the sequence? */
	
 	
}


/*

	report()

*/
void report()
{
	// Any missing packets?
	// Delays for each packet
	// Print it!
	

}




/*
	buildPing()
*/

void buildPing(int REQ_DATASIZE, int seq){
	ICMPEchoRequest.icmpHeader.type='8';
	ICMPEchoRequest.icmpHeader.code='0';
	ICMPEchoRequest.icmpHeader.sequenceNumber=seq;
	#if __unix__
	time(&ICMPEchoRequest.time);
	#elif __WINDOWS__
	ICMPEchoRequest.time=time(NULL);
	#endif
	IPHeader.protocol=1;
	// IPHeader.versionHeaderLength=4;
	IPHeader.timeToLive = 64;//Recommended value, according to the internet.
	IPHeader.versionHeaderLength=0b01000101;
	printf("Buildping finished\n");
}

/*

	main()

*/
char *argv[2];
int main(int argc, const char** argv){
	printf("main() begin\n");
	const char* destination="8.8.8.8";
	char hostName[128];
	printf("mark\n");
	if((gethostname(hostName, sizeof hostName))==NULL)
	{
		printf("gethostname error: returned null\n");
	}
	printf("mark\n");
	hostent *hostIP;
	printf("mark\n");
	hostIP=gethostbyname(hostName);
	printf("mark4\n");
	struct in_addr destIP;
	struct in_addr srcIP;
	std::cout<<sizeof(srcIP)<<std::endl;
	IPHeader.sourceIPAddress=srcIP;
	IPHeader.destinationIPAddress=destIP;
	std::cout<<sizeof(IPHeader.sourceIPAddress)<<std::endl;
	#if __unix__
	printf("Mark 4.5\n");
	inet_pton(AF_INET,hostIP->h_name,&srcIP);
	printf("Mark 5\n");
	if(inet_pton(AF_INET,destination,&IPHeader.destinationIPAddress)!=1){
		// int error=WSAGetLastError();
		// printf((char*)error);
		//Add error message, etc.
		printf("inet_pton error");
	}
	#elif __WINDOWS__

	printf("Mark 5\n");
	if(InetPton(2,destination,&IPHeader.destinationIPAddress)!=1){
		int error=WSAGetLastError();
		printf((char*)error);
	}

	InetPton(2,hostIP,*IPHeader.sourceIPAddress);
	#endif
	printf("Mark 6\n");
	int seq=0;
	int REQ_DATASIZE=10;
	int inSocketDescriptor;
	int outSocketDescriptor;
	
	printf("Mark 7\n");
	inSocketDescriptor=socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	printf("Mark 8\n");
	outSocketDescriptor=socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	// Grab arguments from command line and set flags
	// Number of Pings
	// Packet Size
	buildPing(REQ_DATASIZE,seq);
	ping(outSocketDescriptor,REQ_DATASIZE);
	listen(inSocketDescriptor);
	report();
	printf("main() end\n");

}
