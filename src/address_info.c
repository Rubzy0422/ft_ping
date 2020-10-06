/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   address_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcoetzer <rcoetzer@student.wethinkcode.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:06:58 by rcoetzer          #+#    #+#             */
/*   Updated: 2020/10/06 22:22:53 by rcoetzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

void *handelerrcode(int errcode, const char *hostname)
{
	if (errcode == -2)
	printf("%s:%s: Name or service not known\n", PROG_NAME, hostname);
	// -3 Temporary failure in name resolution
	else if (errcode == -3)
	printf("%s:%s: Temporary failure in name resolution\n", PROG_NAME, hostname); 
	return (NULL);
}

char *dns_lookup(const char *host)
{
	struct addrinfo hints;
	struct addrinfo *res;
	int errcode;
	char addrstr[100];
	void *ptr;

	ft_bzero(&hints, sizeof (hints));
	hints.ai_flags = 0;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;
	errcode = getaddrinfo(host, NULL, &hints, &res);
	if (errcode != 0)
		return handelerrcode(errcode, host);
	inet_ntop(res->ai_family, res->ai_addr->sa_data, addrstr, NI_MAXHOST);
	if (res->ai_family == AF_INET)
		ptr = &((struct sockaddr_in *) res->ai_addr)->sin_addr;
	 inet_ntop (res->ai_family, ptr, addrstr, NI_MAXHOST);
	g_env.addr_con = res->ai_addr;
	return ft_strdup(addrstr);
}

// Resolves the reverse lookup of the hostname 
char* reverse_dns_lookup(char *ip_addr) 
{ 
	struct sockaddr_in ip4addr;
	
	memset(&ip4addr, 0, sizeof(struct sockaddr_in));
	ip4addr.sin_family = AF_INET;
	ip4addr.sin_port = htons(0);
	inet_pton(AF_INET, ip_addr, &ip4addr.sin_addr);
	char host[NI_MAXHOST], service[NI_MAXSERV];
	int s = getnameinfo((struct sockaddr *) &ip4addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV);
	if (s == 0)
		return strdup(host);
	return NULL;
}