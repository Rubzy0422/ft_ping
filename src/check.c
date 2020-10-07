/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcoetzer <rcoetzer@student.wethinkcode.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 00:37:59 by alex              #+#    #+#             */
/*   Updated: 2020/10/07 08:48:55 by rcoetzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	validate_packet(struct icmphdr *hdr2, int bytes, t_env *env)
{
	unsigned short cksum;

	cksum = hdr2->checksum;
	hdr2->checksum = 0;
	hdr2->checksum = checksum((unsigned short *)hdr2, 64);
	if (env->verbose)
	{
		if (bytes != 84)
			printf("Icomplete packet.\n");
		if (hdr2->un.echo.id != env->pid)
			printf("Bad id.\n");
		if (hdr2->checksum != cksum)
			printf("Checksum fail.\n");
	}
	check_type(hdr2, env);
}

void	check_type(struct icmphdr *hdr, t_env *env)
{
	if (hdr->type == ICMP_TIME_EXCEEDED)
	{
		printf("64 bytes from %s: icmp_seq=%ld Time to live exceeded\n",
			env->reverse_hostname, env->icmp_seqNum);
		return;
	}
	else
	{
		if (hdr->type != ICMP_ECHOREPLY)
		{
			if (env->verbose)
			{
				printf("Bad icmp type: %d\n", hdr->type);
				return;
			}
		}
	}
	printf("%d bytes from %s (%s): icmp_seq=%ld ttl=%d time=%.3f\n", 64,
		env->reverse_hostname , env->ip_addr, env->icmp_seqNum, env->ttl,
		ft_timediff(env->time.echo_start, env->time.echo_end));
}