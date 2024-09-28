/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:47:29 by anamedin          #+#    #+#             */
/*   Updated: 2024/09/24 13:20:57 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	*f(void *content)
{
    int *original = (int *)content;
    int *duplicated = (int *)malloc(sizeof(int));
    if (!duplicated)
        return NULL;
    *duplicated = *original * 2;
    return (duplicated);
}*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	void	*tmp;
	t_list	*result;

	if (!lst)
		return (0);
	new_lst = NULL;
	while (lst != NULL)
	{
		tmp = f(lst->content);
		result = ft_lstnew(tmp);
		if (!result)
		{
			del(tmp);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, result);
		lst = lst->next;
	}
	return (new_lst);
}

/*void ft_free(t_list **lst)
{
	t_list *tmp;

	while (*lst != NULL)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp->content);
		free(tmp);
	}
}

int main(void)
{
    t_list *lista = ft_lstnew(strdup(""));
    t_list *node1 = ft_lstnew(strdup("10"));
    t_list *node2 = ft_lstnew(strdup("25"));
    t_list *node3 = ft_lstnew(strdup("40"));
    t_list *node4 = ft_lstnew(strdup("75"));

    // Creamos lista
    lista->next = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;

    // Recorremos lista antes de la función
    t_list *tmp = lista;
    int i = 0;
    while (tmp != NULL)
    {
        printf("nodo[%d]: %s\n", i, (char *)tmp->content);
        tmp = tmp->next;
        i++;
    }

    // Llamamos a la función
    t_list *new_lst = ft_lstmap(lista, &multiply, ft_free);
    if (!new_lst)
    {
        printf("Error al mapear la lista.\n");
        return 1;
    }

    // Recorremos la nueva lista
    tmp = new_lst;
    i = 0;
    while (tmp != NULL)
    {
        printf("nuevo nodo[%d]: %d\n", i, *(int *)(tmp->content));
        tmp = tmp->next;
        i++;
    }

    // Liberamos memoria
    ft_free(&lista);
    ft_free(&new_lst);

    return 0;
}*/
