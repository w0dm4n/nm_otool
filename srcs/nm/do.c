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

void				close_and_free(struct s_file *file)
{
	close(file->fd);
	free(file->stat_data);
	free(file);
}

void				do_64(struct s_file *file)
{
	struct mach_header_64	*header_64;

	header_64 = get_x64(file);
	check_swap_x64(header_64);
	file->is_x64 = TRUE;
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

void				do_32(struct s_file *file)
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

void				do_fat(struct s_file *file)
{
	void					*ptr;
	struct fat_arch			*arch;
	struct mach_header_64	*header_64;
	struct fat_header		*fat;

	fat = (struct fat_header*)get_ptr(file);
	file->is_fat = TRUE;
	ptr = get_ptr(file);
	arch = get_arch_x64(swap_int32(fat->nfat_arch), \
		(ptr + sizeof(struct fat_header)), ptr);
	if (arch != NULL)
	{
		header_64 = ptr + swap_int32(arch->offset);
		if ((header_64->filetype < 3 && header_64->filetype > 0) \
		|| header_64->filetype == 6)
			read_fat_x64(file, header_64, ptr);
	}
	else
		do_fat_32(NULL, ptr, file, fat);
	close_and_free(file);
}
