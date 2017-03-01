/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_x64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 19:53:00 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/01 19:53:02 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"
#include <stdio.h>

void	*get_ptr(t_file *file)
{
	return (ft_mmap(file->fd, file->stat_data->st_size));
}

void	read_x64(struct mach_header_64 *header, t_file *file)
{
	int							i;
	struct load_command			*cmd;
	void						*ptr;
	struct segment_command_64	*segment;
	struct section_64			*section;

	ptr = get_ptr(file) + sizeof(struct mach_header_64);
	i = 0;
	segment = NULL;
	section = NULL;
	while (i < header->ncmds)
	{
		cmd = (struct load_command*)ptr;
		if (cmd->cmd == LC_SEGMENT_64)
		{
			segment = (struct segment_command_64*)ptr;
			section = ptr + sizeof(struct segment_command_64);
			if (ft_strcmp(segment->segname, "__TEXT") == 0)
			{
				printf("%p segname: %s, cmdsize: %d, filesize: %llu, addr: %llx, offset: %llu\n", ptr, segment->segname, cmd->cmdsize, \
				 segment->filesize, section->addr, section->offset);
			}
		}
		ptr += cmd->cmdsize;
		i++;
	}
}
