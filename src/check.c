/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcoetzer <rcoetzer@student.wethinkcode.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 00:37:59 by alex              #+#    #+#             */
/*   Updated: 2020/10/08 13:16:01 by rcoetzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
 
void	validate_packet(struct icmphdr *hdr, int bytes, t_env *env)
{
	unsigned short cksum;

	cksum = hdr->checksum;
	hdr->checksum = 0;
	hdr->checksum = checksum((unsigned short *)hdr, 64);
	if (env->verbose)
	{
		if (bytes != 84)
			printf("Icomplete packet.\n");
		if (hdr->un.echo.id != env->pid)
			printf("Bad id.\n");
		if (hdr->checksum != cksum)
			printf("Checksum fail.\n");	
	}
	if (check_type(hdr, env))
	printf("%d bytes from %s (%s): icmp_seq=%d ttl=%d time=%.3f ms\n", 64,
	env->reverse_hostname , env->ip_addr, hdr->un.echo.sequence + 1, env->ttl,
	ft_timediff(env->time.echo_start, env->time.echo_end));
}

bool	check_type(struct icmphdr *hdr, t_env *env)
{
	if (hdr->type == ICMP_TIME_EXCEEDED)
	{
		printf("64 bytes from %s: icmp_seq=%d Time to live exceeded\n",
			env->reverse_hostname, hdr->un.echo.sequence + 1);
		return false;
	}
	else
	{
		if (env->verbose)
			{
				if (hdr->type != ICMP_ECHOREPLY && 
				ft_strcmp(env->ip_addr, "127.0.0.1"))
				{
					printf("Bad icmp type: %d\n", hdr->type);
					return false;
				}	
			}
	}
	return true;
}