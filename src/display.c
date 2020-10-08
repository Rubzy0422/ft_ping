/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcoetzer <rcoetzer@student.wethinkcode.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:07:06 by rcoetzer          #+#    #+#             */
/*   Updated: 2020/10/08 12:32:51 by rcoetzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

void		stats(t_env *env)
{
	double num;

	num = ((env->icmp_seqNum - env->icmp_recieved) * 100.00 / env->icmp_seqNum);
	gettimeofday(&env->time.program_end, NULL);
	printf("\n--- %s ping statistics ---\n",env->hostname);
	printf("%u packets transmitted, %u received, ",
	env->icmp_seqNum, env->icmp_recieved);
	printf("%.2f%% packet loss, time %.3f ms\n", num, 
	ft_timediff(env->time.program_start, env->time.program_end));
	free(env->ip_addr);
	free(env->reverse_hostname);
}

void	display_help(void)
{
	printf("Usage\n");
	printf("ping [options] <destination>\n");
	printf("Options:\n");
	printf("\t<destination>\tdns name or ip address\n");
	printf("\t-h\t\tprint help and exit\n");
	printf("\t-v\t\tverbose output\n");
	exit(0);
}