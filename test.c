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

#include "parse.h"

char		*read_number(char *str)
{
	int i;
	
	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		i++;
	}
	if(i == 0)
		return (NULL);
	return (ft_strsub(str, 0, i));
}

char		*read_word(char *str)
{
	int i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		i++;
	}
	if (i == 0)
		return (NULL);
	return (ft_strsub(str, 0, i));	
}

t_redirect		*rediriction(t_list_token *tokens)
{
	if (!_OR(tokens->type, GRT, GRTGRT, SMLSML, SML))
		return (NULL);
	
}

int main(int ac, char **av)
{
	//printf("++-->[%s]\n", read_number(av[1]));
	printf("++%s-->[%s]\n", av[1],read_word(av[1]));
	return 0;
}