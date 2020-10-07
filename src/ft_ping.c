/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcoetzer <rcoetzer@student.wethinkcode.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 22:32:54 by rcoetzer          #+#    #+#             */
/*   Updated: 2020/10/07 08:47:59 by rcoetzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

char 	*parse_args(int argc, char **argv, t_env *env)
{
	int		i;
	int		x;
	char	*str_destAddr;
	
	i = 0;
	x = 0;
	str_destAddr = NULL;
	while (++i < argc)
		if (argv[i][x] == '-')
			while (argv[i][x++])
			{
				if (argv[i][x] == 'v')
					env->verbose = true;
				if (argv[i][x] == 'h' || argv[i][x] == 'H')
					display_help();
				if (!ft_strchr("vhH",argv[i][x]))
					display_help();
			}
		else 
			str_destAddr = argv[i]; 
	return str_destAddr;
}

void		ping_loop(t_env *env)
{
	struct timeval	s_time;
	time_t			lst_time;

	lst_time = 0;
	init_ICMP(env);
	while (env->pingloop)
	{
		gettimeofday(&s_time, NULL);
		if (s_time.tv_sec >= lst_time + 1)
		{
			lst_time = s_time.tv_sec;
			send_echo(env);
			env->icmp_seqNum++;
		}
		recieve_echo(env);
	}
	stats(env);
}

void InterruptHandler() 
{
	g_env.pingloop=false;
}

int main(int argc, char *argv[]) 
{
	start_env(argc, argv);
	g_env.hostname = parse_args(argc, argv, &g_env);
	g_env.ip_addr = dns_lookup(g_env.hostname);
	g_env.reverse_hostname = reverse_dns_lookup(g_env.hostname, g_env.ip_addr);
	
	if(g_env.ip_addr == NULL) 
		return 0;
	printf("PING %s (%s) %d(%d) bytes of data.\n", g_env.hostname,
	g_env.ip_addr, 56, 84);
	signal(SIGINT, InterruptHandler);
	g_env.sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if(g_env.sockfd >= 0)
		ping_loop(&g_env);
	return 0;
}

void	start_env(int argc, char **argv)
{
	g_env.addrlen = sizeof(g_env.addr_con);
	g_env.verbose = false;
	g_env.pingloop = true;
	g_env.icmp_sent = 0;
	g_env.icmp_seqNum = 0;
	g_env.icmp_recieved = 0;
	g_env.ttl = 64;

	if (getuid()) {
		printf("You must be root to execute this program\n");
		exit(0);
	}
	if (argc <= 1) {
		printf("%s: usage error: Destination address required\n", argv[0]);
		exit(0);
	}
}