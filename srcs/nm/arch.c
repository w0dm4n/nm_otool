/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 19:13:12 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/14 19:13:12 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

int					is_fat(uint32_t magic)
{
	return (magic == FAT_MAGIC || magic == FAT_CIGAM);
}

struct fat_arch		*get_arch_x64(int arch_count, void *first, void *ptr)
{
	struct fat_arch			*arch;
	struct mach_header_64	*tmp_header;
	int						i;

	arch = NULL;
	i = 0;
	if (arch_count > 100)
		return (first);
	while (arch_count > 0)
	{
		if (i > 0)
			arch = first + (sizeof(struct fat_arch) * i);
		else
			arch = (struct fat_arch*)first;
		tmp_header = ptr + swap_int32(arch->offset);
		if (is_magic_64(tmp_header->magic))
			return (arch);
		arch_count--;
		i++;
	}
	return (NULL);
}

struct fat_arch		*get_arch_x32(int arch_count, void *first, void *ptr)
{
	struct fat_arch			*arch;
	struct mach_header		*tmp_header;
	int						i;

	arch = NULL;
	i = 0;
	if (arch_count > 100)
		return (first);
	while (arch_count > 0)
	{
		if (i > 0)
			arch = first + (sizeof(struct fat_arch) * i);
		else
			arch = (struct fat_arch*)first;
		tmp_header = ptr + swap_int32(arch->offset);
		if (is_magic_32(tmp_header->magic))
			return (arch);
		arch_count--;
		i++;
	}
	return (NULL);
}

void				do_fat_32(struct mach_header *header_32, \
	void *ptr, t_file *file, struct fat_header *fat)
{
	struct fat_arch			*arch;

	arch = get_arch_x32(swap_int32(fat->nfat_arch), \
		(ptr + sizeof(struct fat_header)), ptr);
	if (arch != NULL)
	{
		header_32 = ptr + swap_int32(arch->offset);
		if ((swap_int32(header_32->filetype) < 3 && \
			swap_int32(header_32->filetype) > 0) \
			|| (swap_int32(header_32->filetype) == 6))
			read_fat_x32(file, header_32, ptr);
	}
}
