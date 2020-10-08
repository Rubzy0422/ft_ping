/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcoetzer <rcoetzer@student.wethinkcode.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 06:19:44 by rcoetzer          #+#    #+#             */
/*   Updated: 2020/10/08 12:50:45 by rcoetzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

void	init_ICMP(t_env *env)
{
	struct timeval tv_out; 
	
	tv_out.tv_sec = RECV_TIMEOUT;
	tv_out.tv_usec = 0;
	gettimeofday(&env->time.program_start, NULL);
	if (setsockopt(env->sockfd, SOL_IP, IP_TTL, &env->ttl, 
	sizeof(env->ttl)) != 0) 
	{ 
		printf("\nSetting socket options to TTL failed!\n"); 
		return;
	}
	else
		setsockopt(env->sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv_out,
		sizeof tv_out); 
}

void	send_echo(t_env *env)
{
	struct ping_pkt pckt;
	int i;
	ssize_t size;

	ft_bzero(&pckt, sizeof(pckt)); 
	pckt.hdr.type = ICMP_ECHO;
	pckt.hdr.code = 0;
	pckt.hdr.un.echo.id = getpid();
	env->pid = pckt.hdr.un.echo.id;
	i = 0;
	while(i++ < (int)sizeof(pckt.msg)-1) 
		pckt.msg[i] = i+'0';
	pckt.msg[i] = 0;
	strcpy(env->pkt.msg, pckt.msg);
	pckt.hdr.un.echo.sequence = env->icmp_seqNum;
	pckt.hdr.checksum = checksum(&pckt, sizeof(pckt));
	gettimeofday(&env->time.echo_start, NULL);
	size = sendto(env->sockfd, &pckt.hdr, sizeof(pckt), 0,
		(struct sockaddr *)env->addr_con, sizeof(struct sockaddr));
	if (PING_PKT_SIZE != size)
		printf("%s: sendmsg: Network is unreachable\n", P_NAME);
	else
		env->icmp_seqNum++;
}

void	recieve_echo(t_env *env)
{
	struct msghdr	msg;
	struct iovec	iov;
	struct icmphdr *hdr;
	unsigned char	iov_base[84];
	ssize_t			ret;

	ft_bzero(&msg, sizeof(msg));
	ft_bzero(&iov, sizeof(iov));
	msg.msg_name = env->addr_con;
	msg.msg_namelen = env->addrlen;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	iov.iov_base = &iov_base;
	iov.iov_len = 84;

	gettimeofday(&env->time.echo_end, NULL);
	ret = recvmsg(env->sockfd, &msg, MSG_DONTWAIT);
	if (ret > 0)
	{
		hdr = (struct icmphdr *)((void *)iov_base + sizeof(struct ip));
		if (hdr->un.echo.sequence >= env->icmp_recieved)
		{
			env->icmp_recieved++;
			validate_packet(hdr, ret, env);
		}
	}
}

unsigned short checksum(void *b, int len)
{
	unsigned short *buf = b; 
	unsigned int sum=0; 
	unsigned short result; 

	for ( sum = 0; len > 1; len -= 2 )
		sum += *buf++; 
	if ( len == 1 ) 
		sum += *(unsigned char*)buf; 
	sum = (sum >> 16) + (sum & 0xFFFF); 
	sum += (sum >> 16); 
	result = ~sum; 
	return result; 
} 