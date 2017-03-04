/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 15:27:50 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/04 15:28:17 by frmarinh         ###   ########.fr       */
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
