/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 19:03:43 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/10 19:03:44 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void		print_glob(int type)
{
	if (type == 6)
		ft_putstr(" S ");
	else
		ft_putstr(" D ");
}

void		print_symbol(t_custom_nlist *current, t_file *file)
{
	if ((int)current->sect == 8 && current->type == 15)
		print_glob(file->filetype);
	else if (((int)current->sect == 12 && current->type == 14) ||
		((int)current->sect == 14 && current->type == 30))
		ft_putstr(" d ");
	else if (((int)current->sect == 13 && current->type == 14) ||
		(((int)current->sect == 15 && current->type == 14)))
		ft_putstr(" b ");
	else if (((int)current->sect == 5 && current->type == 14) ||
		((int)current->sect == 16 && current->type == 30) ||
		((int)current->sect == 4 && current->type == 14) ||
		((int)current->sect == 6 && current->type == 30) ||
		((int)current->sect == 12 && current->type == 30))
		ft_putstr(" s ");
	else if (current->type == 1)
		ft_putstr(" U ");
	else if (current->type == 14 || \
		((int)current->sect == 1 && current->type == 30))
		ft_putstr(" t ");
	else if ((int)current->sect == 1 && current->type == 15)
		ft_putstr(" T ");
	else if (((int)current->sect == 12 && current->type == 15) ||
		((int)current->sect == 7 && current->type == 15))
		ft_putstr(" D ");
}
