/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 23:14:10 by afaraji           #+#    #+#             */
/*   Updated: 2020/02/11 23:14:15 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

int sig;

void	signal_callback_handler(int signum)
{
	if (signum == 2)
	{
		printf("ctrl-c\n");
		sig = 1;
	}
}


int main()
{
	int buff;
	sig = 0;
	signal(SIGINT, &signal_callback_handler);
	struct termios term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON | ECHO | ISIG );
	tcsetattr(0, TCSANOW, &term);
	while (1)
	{
		buff = 0;
		if (sig)
			break;
		int ret = read(0, &buff, 4);
		if (sig)
			break;
		printf("==+[%d]+[%X]==\n", ret, buff);
		if (buff == 0x9)
			sig = 1;
		if (sig)
			break;
	}
	sig = 0;
	return (0);
}