/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:56:35 by lferro            #+#    #+#             */
/*   Updated: 2023/10/17 13:25:07 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	dest_len;
	size_t	i;

	dest_len = ft_strlen(dest);
	i = 0;
	while (i < n && src[i])
	{
		if (dest_len + i < n - 1)
		{
			dest[dest_len + i] = src[i];
			i++;
		}
		else
			break ;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d_len;
	size_t	s_len;

	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	ft_strncat(dst, src, size);
	if (size < d_len)
		return (s_len + size);
	return (d_len + s_len);
}

// int main() {
//     char d1[5] = "abc";
// 	char d2[5] = "abc";

//     const char *s = "456789";
//     size_t n = 6;

//     size_t r1 = strlcat(d1, s, n);
//     size_t r2 = ft_strlcat(d2, s, n);

//     printf("na len:	%zu\n", r1);
//     printf("na str:	%s\n", d1);

// 	printf("ft len:	%zu\n", r2);
//     printf("ft str:	%s\n", d2);

//     return (0);
// }
