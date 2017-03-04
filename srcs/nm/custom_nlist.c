/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_nlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 18:09:12 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/04 18:09:24 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

t_custom_nlist		*alloc_custom(void)
{
	if(!(g_customs = (struct s_custom_nlist*) \
		malloc(sizeof(struct s_custom_nlist))))
		return (NULL);
	g_customs->content = NULL;
	g_customs->type = 0;
	g_customs->addr = 0;
	g_customs->next = NULL;
	g_customs->prev = NULL;
	return (g_customs);
}

t_custom_nlist		*get_custom_nlist(void)
{
	if (g_customs)
		return (g_customs);
	else
		return (alloc_custom());
}

void	add_custom_x64(t_custom_nlist *customs, struct nlist_64 *nlist, char *c)
{
	struct s_custom_nlist	*new;

	if(!(new = (struct s_custom_nlist*) \
		malloc(sizeof(struct s_custom_nlist))))
		return ;
	new->content = c;
	new->type = nlist->n_type;
	new->addr = nlist->n_value;
	new->next = NULL;
	new->prev = NULL;

	while (customs->next)
		customs = customs->next;
	customs->next = new;
	new->prev = customs;
}

void	add_custom_x32(t_custom_nlist *customs, struct nlist *nlist, char *c)
{
	struct s_custom_nlist	*new;

	if(!(new = (struct s_custom_nlist*) \
		malloc(sizeof(struct s_custom_nlist))))
		return ;
	new->content = c;
	new->type = nlist->n_type;
	new->addr = nlist->n_value;
	new->next = NULL;
	new->prev = NULL;

	while (customs->next)
		customs = customs->next;
	customs->next = new;
	new->prev = customs;
}

void	replace_custom_data(t_custom_nlist *first, t_custom_nlist *second)
{
	char		*data;
	uint32_t	type;
	uint64_t	addr;

	data = first->content;
	type = first->type;
	addr = first->addr;
	first->content = second->content;
	first->type = second->type;
	first->addr = second->addr;
	second->content = data;
	second->type = type;
	second->addr = addr;
}

void	range_customs_by_ascii(void)
{
	t_custom_nlist *customs;

	customs = get_custom_nlist();
	t_custom_nlist *tmp = customs->next;
	t_custom_nlist *tmp_2 = NULL;

	while (tmp)
	{
		tmp_2 = tmp->next;
		while (tmp_2)
		{
			if (tmp->content[1] > tmp_2->content[1])
				replace_custom_data(tmp, tmp_2);
			tmp_2 = tmp_2->next;
		}
		tmp = tmp->next;
	}
}