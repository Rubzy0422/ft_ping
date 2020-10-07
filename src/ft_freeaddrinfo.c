/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeaddrinfo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcoetzer <rcoetzer@student.wethinkcode.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:22:44 by rcoetzer          #+#    #+#             */
/*   Updated: 2020/10/07 09:07:13 by rcoetzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

void ft_freeaddrinfo(struct addrinfo *aihead)
{
	struct addrinfo	*ai, *ainext;

	ai = aihead;
	while (ai != NULL) {
		if (ai->ai_addr != NULL)
			free(ai->ai_addr);

		if (ai->ai_canonname != NULL)
			free(ai->ai_canonname);

		ainext = ai->ai_next;
		free(ai);
		ai = ainext;
	}
}