/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:07:20 by ydembele          #+#    #+#             */
/*   Updated: 2025/05/12 15:01:34 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newnode_head;
	void	*temp;
	t_list	*new_list;
	t_list	*current;

	if (!lst || !f || !del)
		return (NULL);
	newnode_head = NULL;
	current = lst;
	while (current != NULL)
	{
		temp = f(current->content);
		new_list = ft_lstnew(temp);
		if (!new_list)
		{
			del(temp);
			ft_lstclear(&newnode_head, del);
			return (0);
		}
		ft_lstadd_back(&newnode_head, new_list);
		current = current->next;
	}
	return (newnode_head);
}
/*int main()
{
	#include <string.h>
	char tab[50][50] = {"je", "suis", "la", "mec"};
	t_list * l =  ft_lstnew(tab);
	for (int i = 1; i < 4; ++i)
			ft_lstadd_back(&l, ft_lstnew(tab + i));
	t_list * tmp = l;
	for (int i = 0; i < 4; ++i)
	{
			printf("p%sp, x%dx\n",(char *)tmp->content, i);
			tmp = (t_list *)tmp->next;
	}
	ft_lstclear(&tmp, free);
}*/