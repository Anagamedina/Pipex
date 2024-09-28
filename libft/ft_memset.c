/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:19:05 by anamedin          #+#    #+#             */
/*   Updated: 2024/09/21 18:06:19 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	ch;
	unsigned char	*str;

	ch = c;
	str = b;
	while (len--)
		*str++ = ch;
	return (b);
}

/*int	main(void)
{
	char str[] = "hola Ana";

	char *result = ft_memset(str, 'a', 5);
	printf("%s\n", (char *)result);

	return (0);
}*/
