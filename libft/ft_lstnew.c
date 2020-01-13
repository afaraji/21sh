/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 02:47:37 by afaraji           #+#    #+#             */
/*   Updated: 2018/10/24 08:19:38 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *tmp;

	if (!(tmp = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	tmp->next = NULL;
	if (!content)
	{
		tmp->content = NULL;
		tmp->content_size = 0;
		return (tmp);
	}
	if (!(tmp->content = malloc(content_size)))
	{
		free(tmp);
		return (NULL);
	}
	ft_memcpy(tmp->content, content, content_size);
	tmp->content_size = content_size;
	return (tmp);
}
