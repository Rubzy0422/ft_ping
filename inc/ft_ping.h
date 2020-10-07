#ifndef FT_PING_H
#define FT_PING_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <netinet/in.h> 
#include <netinet/ip_icmp.h>  
#include <fcntl.h> 
#include <signal.h>

#include <libft.h>

#define PING_PKT_SIZE 64 
#define PORT_NO 0
#define PING_SLEEP_RATE 1000000
#define RECV_TIMEOUT 1
#define PROG_NAME "ft_ping"

typedef enum
{
					false,
					true
}					bool;

typedef struct		ping_pkt 
{
	struct icmphdr hdr; 
	char msg[PING_PKT_SIZE -sizeof(struct icmphdr)]; 
}					ping_pkt; 


typedef struct 		s_time
{
	struct timeval	echo_start;
	struct timeval	echo_end;
	struct timeval	program_start;
	struct timeval	program_end;
}					t_time;

typedef struct		s_env
{
	int				sockfd; 
	char			*ip_addr;
	char			*reverse_hostname;
	char			*hostname;
	struct			sockaddr *addr_con; 
	int				addrlen; 
	char			net_buf[NI_MAXHOST];
	unsigned long	icmp_seqNum;
	unsigned long	icmp_sent;
	unsigned long	icmp_recieved;
	t_time			time;
	bool			verbose;
	bool			pingloop;
	ping_pkt		pkt;
	unsigned int	ttl;
	pid_t			pid;
}					t_env;

t_env 				g_env;
void				start_env(int argc, char **argv);
uid_t				getuid(void);
char				*dns_lookup(const char *host);
char* 				reverse_dns_lookup(char *hostname, char *s_ipv4_addr);
void				send_ping(int ping_sockfd, struct sockaddr_in *ping_addr, 
					char *ping_dom, char *ping_ip, char *rev_host);
void				intHandler(int dummy);
void				init_ICMP(t_env *env);
void				send_echo(t_env *env);
void				recieve_echo(t_env *env);
void				display_help(void);
void				stats(t_env *env);
unsigned short		checksum(void *buffer, int size);
double 				ft_timediff(struct timeval s, struct timeval e);
void				ft_freeaddrinfo(struct addrinfo *aihead);
void				validate_packet(struct icmphdr *hdr2, int bytes,
					t_env *env);
void				check_type(struct icmphdr *hdr, t_env *env);
#endif