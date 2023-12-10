/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:52:31 by lferro            #+#    #+#             */
/*   Updated: 2023/10/15 10:04:01 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strlen(needle) > len)
		return (NULL);
	if (ft_strlen(needle) == 0)
		return ((char *)&haystack[i]);
	while (i < ft_strlen(haystack) && i < len)
	{
		while (haystack[i + j] == needle[j] && i + j < len)
		{
			if (needle[j + 1] == 0)
				return ((char *)&haystack[i]);
			j++;
		}
		j = 0;
		i++;
	}
	return (NULL);
}

// int main(void)
// {
// 	char *s1 = "lorem ipsum dolor sit amet";
// 	char *s2 ="ipsumm";
// 	int n = 30;
// 	if (ft_strnstr(s1, s2, n) != NULL)
// 		printf("%s\n", ft_strnstr(s1, s2, n));
// 	else
// 		printf("NULL\n");
// 	if (ft_strnstr(s1, s2, n) != NULL)
// 		printf("%s\n", strnstr(s1, s2, n));
// 	else
// 		printf("NULL\n");
// 	return (0);
// }
