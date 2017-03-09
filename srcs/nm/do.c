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
	if (!is_fat(header_32->magic))
	{
		if ((header_32->filetype < 3 && header_32->filetype > 0) \
			|| header_32->filetype == 6)
		{
			file->filetype = header_32->filetype;
			read_x32(header_32, file);
		}
		else
			print_not_object();
	}
	else
	{
		void *ptr = get_ptr(file);
		//struct fat_header *test = (struct fat_header*)ptr;
		//ft_putnbr(swap_int32(test->nfat_arch));
		struct fat_arch *arch = ptr + sizeof(struct fat_header) + sizeof(struct fat_arch);
		//ft_putstr("\n");
		//ft_putnbr(swap_int32(arch->offset));
		struct mach_header_64 *header = ptr + swap_int32(arch->offset);
		if (is_magic_64(header->magic))
		{
			file->is_x64 = TRUE;
			file->filetype = header->filetype;
			int							i;
			struct load_command			*cmd;
			struct segment_command_64	*segment;
			struct symtab_command		*symtab;

			ptr = (void*)header + sizeof(struct mach_header_64);
			i = 0;
			segment = NULL;
			symtab = NULL;
			while (i < (int)header->ncmds)
			{
				cmd = (struct load_command*)ptr;
				if (cmd->cmd == LC_SYMTAB)
				{
					read_universal((void*)header + sizeof(struct mach_header_64), (struct symtab_command*)cmd, file, (void*)header);
				}
				ptr += cmd->cmdsize;
				i++;
			}
		}
		/*struct mach_header_64	*header_64 = malloc(sizeof(struct mach_header_64));
		header_64->magic = swap_int32(header_32->magic);
		header_64->cputype = swap_int32(header_32->cputype);
		header_64->cpusubtype = swap_int32(header_32->cpusubtype);
		header_64->filetype = (swap_int32(header_32->filetype) - 1);
		header_64->ncmds = swap_int32(header_32->ncmds);
		header_64->sizeofcmds = swap_int32(header_32->sizeofcmds);
		header_64->flags = swap_int32(header_32->flags);

		printf("Filetype: %d, ncmds:%d, sizeofcmds:%d\n", header_64->filetype, header_64->ncmds, header_64->sizeofcmds);
		file->filetype = header_64->filetype;
		read_x64(header_64, file);*/
	}
	close_and_free(file);
}
