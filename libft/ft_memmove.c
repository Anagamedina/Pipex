/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:05:19 by anamedin          #+#    #+#             */
/*   Updated: 2024/09/21 17:56:13 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_ptr;
	unsigned char	*src_ptr;

	dst_ptr = (unsigned char *) dst;
	src_ptr = (unsigned char *) src;
	if (!dst && !src)
		return (NULL);
	if (len == 0)
		return (dst);
	if (src < dst)
	{
		while (len-- > 0)
			dst_ptr[len] = src_ptr[len];
	}
	else
	{
		while (len-- > 0)
			*dst_ptr++ = *src_ptr++;
	}
	return (dst);
}
/*
#include <stdio.h>
#include <string.h>

int main(void)
{
    char str[11] = "12345abcde";
    char str_src[14] = "hellooooooooo";

    // Copiamos 5 bytes desde str (inicio "12345") a str + 5 (sobre "abcde")
    ft_memmove(str + 1, str_src, 14);

    printf("%s\n", str);  // Salida esperada: "1234512345"

    return 0;
}
*/
