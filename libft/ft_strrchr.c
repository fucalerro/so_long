/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:14:18 by lferro            #+#    #+#             */
/*   Updated: 2023/10/12 08:26:28 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char		*last_char;
	const char	ch = c;
	size_t		i;

	i = 0;
	last_char = NULL;
	while (i <= ft_strlen(s))
	{
		if (s[i] == ch)
			last_char = (char *)&s[i];
		i++;
	}
	return (last_char);
}
