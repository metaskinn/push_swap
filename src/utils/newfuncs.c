/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newfuncs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: metaskin <metaskin@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 16:35:00 by metaskin          #+#    #+#             */
/*   Updated: 2026/03/15 17:35:08 by metaskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	mt_strcmp(const char *s1, const char *s2)
{
	size_t	idx;

	idx = 0;
	while (s1[idx] && s2[idx] && s1[idx] == s2[idx])
		idx++;
	return ((unsigned char)s1[idx] - (unsigned char)s2[idx]);
}
