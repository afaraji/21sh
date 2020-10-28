/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:13:41 by afaraji           #+#    #+#             */
/*   Updated: 2020/02/10 16:14:17 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"
#include <stdarg.h>

void		handle_percent(char **format, va_list args, int *i)
{
	**format++;
	if (**format == 's')
	{
		//
	}
	else if (**format == 'd')
	{
		//
	}
	
}

int		my_print(int fd, char *format, ...)
{
	va_list	arguments;
	int		number_of_printed_characters;

	number_of_printed_characters = 0;
	va_start(arguments, format);
	printf("===[%s]===\n", format);
	while (*format)
	{
		if (*format == '%')
			handle_percent(&format, arguments, &number_of_printed_characters);
		else if (*format != '%')
		{
			write(fd, *format, 1);
			number_of_printed_characters++;
			format++;
		}
	}
	va_end(arguments);
	return (number_of_printed_characters);
}

int main()
{
	my_print(1, "hello this is test of myprintf\n");
}