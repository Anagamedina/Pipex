/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:36:49 by anamedin          #+#    #+#             */
/*   Updated: 2024/09/02 11:38:00 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_conver(char *format, va_list args)
{
	int	count;

	count = 0;
	if (*format == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (*format == 's')
		count += ft_print_string(va_arg(args, char *));
	else if (*format == 'p')
	{
		if (ft_print_string("0x") == -1)
			return (-1);
		count += 2;
		count += ft_hex(va_arg(args, unsigned long), 'p');
	}
	else if (*format == 'd' || *format == 'i')
		count += ft_putnbr(va_arg(args, int));
	else if (*format == 'u')
		count += ft_unsignedint(va_arg(args, unsigned int));
	else if (*format == 'x')
		count += ft_hex(va_arg(args, unsigned int), 'x');
	else if (*format == 'X')
		count += ft_hex(va_arg(args, unsigned int), 'X');
	else if (*format == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(char const *format, ...)
{
	va_list	args;
	size_t	i;
	int		total_chars;
	char	*ptr;

	i = 0;
	total_chars = 0;
	va_start(args, format);
	ptr = (char *)format;
	while (ptr[i] != '\0' && total_chars != -1)
	{
		if (ptr[i] == '%')
		{
			total_chars += ft_conver(&ptr[i + 1], args);
			i++;
		}
		else
		{
			total_chars += ft_putchar(ptr[i]);
		}
		i++;
	}
	va_end(args);
	return (total_chars);
}

/*int main() {
    printf("> -  -  -  -  -  -  -  -  -  -  -  -  -  -  - <\n");

<<<<<<< HEAD
    // %c - Imprime un solo carácter
=======
    // %c - Print a single character
>>>>>>> e1159302857cead8a2d972e9b0370aa80d82e191
    ft_printf("BYANA --> %c \n", 'A');
    printf("ORIGI --> %c \n", 'A');
	printf(">\n -  -  -  -  -  -  -  -  -  -  -  -  -  -  - <\n");

<<<<<<< HEAD
    // %s - Imprime una string
    ft_printf("BYANA --> %s \n", "Hola mundo");
    printf("ORIGI --> %s \n", "Hola mundo");
	printf(">\n -  -  -  -  -  -  -  -  -  -  -  -  -  -  - <\n");

    // %p - Imprime un puntero en formato hexadecimal
    char str[] = "Ejemplo";
=======
    // %s - Print a string
    ft_printf("BYANA --> %s \n", "Hello world");
    printf("ORIGI --> %s \n", "Hello world");
	printf(">\n -  -  -  -  -  -  -  -  -  -  -  -  -  -  - <\n");

    // %p - Print a pointer in hexadecimal format
    char str[] = "Example";
>>>>>>> e1159302857cead8a2d972e9b0370aa80d82e191
    void *ptr = &str;
    ft_printf("BYANA --> %p \n", ptr);
    printf("ORIGI --> %p \n", ptr);
	printf(">\n -  -  -  -  -  -  -  -  -  -  -  -  -  -  - <\n");

<<<<<<< HEAD
   // %d - Imprime un número decimal (base 10)
=======
    // %d - Print a decimal number (base 10)
>>>>>>> e1159302857cead8a2d972e9b0370aa80d82e191
    int num = 42;
    ft_printf("BYANA --> %d \n", num);
    printf("ORIGI --> %d \n", num);
	printf(">\n -  -  -  -  -  -  -  -  -  -  -  -  -  -  - <\n");

<<<<<<< HEAD
    // %i - Imprime un entero en base 10
=======
    // %i - Print an integer in base 10
>>>>>>> e1159302857cead8a2d972e9b0370aa80d82e191
    ft_printf("BYANA --> %i \n", num);
    printf("ORIGI --> %i \n", num);
	printf(">\n -  -  -  -  -  -  -  -  -  -  -  -  -  -  - <\n");

<<<<<<< HEAD
    // %u - Imprime un número decimal sin signo
=======
    // %u - Print an unsigned decimal number (base 10)
>>>>>>> e1159302857cead8a2d972e9b0370aa80d82e191
    unsigned int uns_num = 100;
    ft_printf("BYANA --> %u \n", uns_num);
    printf("ORIGI --> %u \n", uns_num);
	printf(">\n -  -  -  -  -  -  -  -  -  -  -  -  -  -  - <\n");

<<<<<<< HEAD
    // %x - Imprime un número hexadecimal en minúsculas
=======
    // %x - Print a hexadecimal number in lowercase
>>>>>>> e1159302857cead8a2d972e9b0370aa80d82e191
    ft_printf("BYANA --> %x \n", num);
    printf("ORIGI --> %x \n", num);
	printf(">\n -  -  -  -  -  -  -  -  -  -  -  -  -  -  - <\n");

<<<<<<< HEAD
    // %X - Imprime un número hexadecimal en mayúsculas
=======
    // %X - Print a hexadecimal number in uppercase
>>>>>>> e1159302857cead8a2d972e9b0370aa80d82e191
    ft_printf("BYANA --> %X \n", num);
    printf("ORIGI --> %X \n", num);
	printf("> \n -  -  -  -  -  -  -  -  -  -  -  -  -  -  - <\n");

<<<<<<< HEAD
    // %% - Imprime el símbolo del porcentaje
    ft_printf("BYANA --> %% \n");
    printf("ORIGI --> %% \n");

    printf("> -  -  -  -  -  -  -  -  -  -  -  -  -  -  - <\n"); 
    return 0;
}*/

//////////////////////////////////////////////////
/*int main(void)
{
	ft_printf("BYANA --> d: %d\n", 10);
    printf("ORIGI --> d: %d\n", 10);
	return (0);
=======
    // %% - Print the percentage symbol
    ft_printf("BYANA --> %% \n");
    printf("ORIGI --> %% \n");

    printf("> -  -  -  -  -  -  -  -  -  -  -  -  -  -  - <\n");
    return 0;
>>>>>>> e1159302857cead8a2d972e9b0370aa80d82e191
}*/
