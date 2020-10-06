/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcoetzer <rcoetzer@student.wethinkcode.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 11:08:18 by rcoetzer          #+#    #+#             */
/*   Updated: 2020/10/06 22:33:40 by rcoetzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

double ft_timediff(struct timeval s, struct timeval e)
{
	double seconds;
	double micro;

	seconds = (double)((e.tv_sec - s.tv_sec))*1000;
	micro = (double)((e.tv_usec - s.tv_usec)) / 1000;
	return (double)(seconds + micro);
}