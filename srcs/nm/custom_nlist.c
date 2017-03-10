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
#include <stdio.h>

t_custom_nlist		*get_custom_nlist(void)
{
	if (g_customs)
		return (g_customs);
	else
	{
		if (!(g_customs = (struct s_custom_nlist*)\
		malloc(sizeof(struct s_custom_nlist))))
			return (NULL);
		g_customs->content = NULL;
		g_customs->type = 0;
		g_customs->addr = 0;
		g_customs->next = NULL;
		g_customs->prev = NULL;
		g_customs->sect = 0;
		return (g_customs);
	}
}

void				add_custom_x64(t_custom_nlist *customs,\
	struct nlist_64 *nlist, char *c)
{
	struct s_custom_nlist	*new;

	if (nlist->n_type == 60)
		return ;
	if (!(new = (struct s_custom_nlist*)\
		malloc(sizeof(struct s_custom_nlist))))
		return ;
	new->content = c;
	new->type = nlist->n_type;
	new->addr = nlist->n_value;
	new->next = NULL;
	new->prev = NULL;
	new->sect = nlist->n_sect;
	/*if (!ft_strcmp(c, "__ZZ14bundle_versionvE13BundleVersion"))
	{
		printf("nsect: %d, ntype: %d\n", new->sect, new->type);
		exit(0);
	}*/
	if (authorized_type(new->type))
	{
		while (customs->next)
			customs = customs->next;
		customs->next = new;
		new->prev = customs;
	}
}

void				add_custom_x32(t_custom_nlist *customs,\
	struct nlist *nlist, char *c)
{
	struct s_custom_nlist	*new;

	if (!(new = (struct s_custom_nlist*)\
		malloc(sizeof(struct s_custom_nlist))))
		return ;
	new->content = c;
	new->type = nlist->n_type;
	new->addr = nlist->n_value;
	new->next = NULL;
	new->prev = NULL;
	new->sect = nlist->n_sect;
	if (authorized_type(new->type))
	{
		while (customs->next)
			customs = customs->next;
		customs->next = new;
		new->prev = customs;
	}
}

void				replace_custom_data(t_custom_nlist *first,\
	t_custom_nlist *second)
{
	char		*data;
	uint32_t	type;
	uint64_t	addr;
	uint8_t		sect;

	data = first->content;
	type = first->type;
	addr = first->addr;
	sect = first->sect;
	first->content = second->content;
	first->type = second->type;
	first->addr = second->addr;
	first->sect = second->sect;
	second->content = data;
	second->type = type;
	second->addr = addr;
	second->sect = sect;
}

void				range_customs_by_ascii(void)
{
	t_custom_nlist *customs;
	t_custom_nlist *tmp;
	t_custom_nlist *tmp_2;

	customs = get_custom_nlist();
	tmp = customs->next;
	tmp_2 = NULL;
	while (tmp)
	{
		tmp_2 = tmp->next;
		while (tmp_2)
		{
			if (ft_strcmp(tmp->content, tmp_2->content) > 0)
				replace_custom_data(tmp, tmp_2);
			tmp_2 = tmp_2->next;
		}
		tmp = tmp->next;
	}
}
