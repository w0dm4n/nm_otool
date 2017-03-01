/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 19:05:35 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/01 19:05:36 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

int						is_magic_64(uint32_t magic)
{
	return (magic == MH_MAGIC_64 || magic == MH_CIGAM_64);
}

int						is_x64(t_file *file)
{
	struct mach_header	*mach_header;

	if(!(mach_header = (struct mach_header*)ft_mmap(file->fd, \
		sizeof(struct mach_header))))
		return -1;
	return (is_magic_64(mach_header->magic));
}

struct mach_header_64	*get_x64(t_file *file)
{
	struct mach_header_64	*mach_header_64;

	if(!(mach_header_64 = (struct mach_header_64*)ft_mmap(file->fd, \
		sizeof(struct mach_header_64))))
		return (NULL);
	return (mach_header_64);
}

struct mach_header		*get_x32(t_file *file)
{
	struct mach_header		*mach_header;

	if(!(mach_header = (struct mach_header*)ft_mmap(file->fd, \
		sizeof(struct mach_header))))
		return (NULL);
	return (mach_header);
}
