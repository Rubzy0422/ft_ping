/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeaddrinfo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcoetzer <rcoetzer@student.wethinkcode.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:40:47 by rcoetzer          #+#    #+#             */
/*   Updated: 2020/10/08 12:41:25 by rcoetzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

void	ft_freeaddrinfo(struct addrinfo *head)
{
	struct addrinfo	*tmp;

	while (head != NULL)
	{
		tmp = head->ai_next;
		free(head);
		head = tmp;
	}
}