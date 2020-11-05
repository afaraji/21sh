/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 20:58:13 by afaraji           #+#    #+#             */
/*   Updated: 2020/10/29 20:58:17 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"
#include <stdarg.h>

void	handle_percent(int fd, char **format, va_list args, int *i)
{
	char	*str;
	int		nbr;
	char	*ptr;

	ptr = *format;
	if (*ptr == 's')
	{
		str = va_arg(args, char *);
		ft_putstr_fd(str, fd);
		*i += ft_strlen(str);
	}
	else if (**format == 'd')
	{
		nbr = va_arg(args, int);
		ft_putnbr_fd(nbr, fd);
		*i += ft_ilen(nbr);
	}
}

int		ft_print(int fd, char *format, ...)
{
	va_list	arguments;
	int		count;

	count = 0;
	va_start(arguments, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			handle_percent(fd, &format, arguments, &count);
			format++;
		}
		else if (*format != '%')
		{
			write(fd, &(*format), 1);
			count++;
			format++;
		}
	}
	va_end(arguments);
	return (count);
}
