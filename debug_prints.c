/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_prints.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 23:36:12 by afaraji           #+#    #+#             */
/*   Updated: 2020/10/29 23:36:21 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	print_set_with_typ(void)
{
	t_variable	*node;

	node = g_var.var;
	fprintf(ttt, "\n++++++++++++++++++++++++\n");
	while (node)
	{
		fprintf(ttt, "%d:%s=%s\n", node->env, node->key, node->value);
		node = node->next;
	}
	fprintf(ttt, "++++++++++++++++++++++++\n");
		
}