/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 15:15:48 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/04 15:15:49 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	close_and_free(struct s_file *file)
{
	close(file->fd);
	free(file->stat_data);
	free(file);
}

void	do_64(struct s_file *file)
{
	struct mach_header_64	*header_64;

	file->is_x64 = TRUE;
	header_64 = get_x64(file);
	check_swap_x64(header_64);
	if ((header_64->filetype < 3 && header_64->filetype > 0) \
		|| header_64->filetype == 6)
	{
		file->filetype = header_64->filetype;
		read_x64(header_64, file);
	}
	else
		print_not_object();
	close_and_free(file);
}

void	do_32(struct s_file *file)
{
	struct mach_header		*header_32;

	header_32 = get_x32(file);
	check_swap_x32(header_32);
	if ((header_32->filetype < 3 && header_32->filetype > 0) \
		|| header_32->filetype == 6)
	{
		file->filetype = header_32->filetype;
		read_x32(header_32, file);
	}
	else
		print_not_object();
	close_and_free(file);
}

void	do_fat(struct s_file *file)
{
	void					*ptr;
	struct fat_arch			*arch;
	struct mach_header_64	*header;

	file->is_fat = TRUE;
	ptr = get_ptr(file);
	arch = ptr + sizeof(struct fat_header) + sizeof(struct fat_arch);
	header = ptr + swap_int32(arch->offset);
	if (is_magic_64(header->magic))
		read_fat_x64(file, header, ptr);
	close_and_free(file);
}
