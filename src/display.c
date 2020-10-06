/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcoetzer <rcoetzer@student.wethinkcode.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:07:06 by rcoetzer          #+#    #+#             */
/*   Updated: 2020/10/06 17:45:36 by rcoetzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

void		stats(t_env *env)
{
	gettimeofday(&env->time.program_end, NULL);
	printf("\n--- %s ping statistics ---\n",env->hostname);
	printf("%lu packets transmitted, %lu received,",
	env->icmp_seqNum, env->icmp_recieved);
	printf("%.3f%% packet loss, time %f ms\n",
	(double)((env->icmp_sent - env->icmp_recieved) / env->icmp_sent) * 100,
	ft_timediff(env->time.program_start, env->time.program_end));
	free(env->ip_addr);
}

void	display_help(void)
{
	printf("Usage\n");
	printf("ping [options] <destination>\n");
	printf("Options:\n");
	printf("\t<destination>\tdns name or ip address\n");
	printf("\t-h\t\tprint help and exit\n");
	printf("\t-v\t\tverbose output\n");
	printf("\t-V\t\tprint version and exit\n");
	exit(0);
}