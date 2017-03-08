/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 15:27:50 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/08 16:43:02 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void		*get_ptr(t_file *file)
{
	return (ft_mmap(file->fd, file->stat_data->st_size));
}

void		*get_text_section(int index, char *ptr)
{
	return (ptr + index);
}

uint32_t	swap_int32(uint32_t x)
{
	return ((uint32_t)((((uint32_t)(x) & 0xff000000) >> 24) | \
		(((uint32_t)(x) & 0x00ff0000) >> 8) | \
		(((uint32_t)(x) & 0x0000ff00) << 8) | \
		(((uint32_t)(x) & 0x000000ff) << 24)));
}

void		*ft_mmap(int fd, size_t size)
{
	return (mmap(0, size, PROT_READ, \
		MAP_SHARED, fd, 0));
}

void		print_space(int space)
{
	while (space != 0)
	{
		ft_putchar(' ');
		space--;
	}
}

int			authorized_type(int type)
{
	return (type == 66 || type == 1 || type == 14 || type == 15);
}


void		print_glob_by_type(int type)
{
	if (type == 6)
		ft_putstr(" S ");
	else
		ft_putstr(" D ");
}
