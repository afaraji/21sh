/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:00:18 by sazouaka          #+#    #+#             */
/*   Updated: 2020/01/13 22:00:20 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PLUS 1
#define MINUS 2
#define MULT 3
#define DIV 4
#define O_PAR 5
#define C_PAR 6
#define	NUM 0

typedef struct 			s_operator
{ 
	int					type;
	int					value;
	struct s_operator	*left;
	struct s_operator	*right;
	struct s_operator	*parent;
}						t_operator;

t_operator	*add_node(int type, t_operator **parent)
{
	t_operator *node;

	node = (t_operator *)malloc(sizeof(t_operator));
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	if(*parent)
		node->parent = *parent;
	else
		node->parent = NULL;
	return (node);
}

void	parse(char *str)
{
	int i = 0;
	t_operator *head = add_node(-42, NULL);
	t_operator *node = head;

	while (str[i])
	{
		char c = str[i];
		if (c == '(')
		{
			node->left =
		}
		i++;
	}
	

	return;
}

int	main(int ac, char **av)
{ 
	int i = 0;
	parse(av[1]);
	

	return (0);
}
