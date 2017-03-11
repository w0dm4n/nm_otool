/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_x64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 06:52:14 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/11 06:52:15 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

static char		st_set_upper(char c, struct nlist_64 symbol)
{
	if ((symbol.n_type & N_EXT) && c != ' ')
		return (ft_toupper(c));
	return (c);
}

static char		st_find_char(struct segment_command_64 *segment,
		unsigned int index)
{
	struct section_64			*sect;

	sect = (struct section_64 *)((char *)segment
			+ sizeof(struct segment_command_64));
	sect += index;
	if (!ft_strcmp(segment->segname, "__DATA")
			&& !ft_strcmp(sect->sectname, "__bss"))
		return ('b');
	if (!ft_strcmp(segment->segname, "__DATA")
			&& !ft_strcmp(sect->sectname, "__data"))
		return ('d');
	if (!ft_strcmp(segment->segname, "__TEXT")
			&& !ft_strcmp(sect->sectname, "__text"))
		return ('t');
	return ('s');
}

static char		st_find_char_obj(struct segment_command_64 *segment,
		unsigned int index)
{
	struct section_64			*sect;

	sect = (struct section_64 *)((char *)segment
			+ sizeof(struct segment_command_64));
	sect += index;
	if (!ft_strcmp(segment->segname, "__DATA")
			|| !ft_strcmp(sect->sectname, "__bss"))
		return ('b');
	if (!ft_strcmp(segment->segname, "__DATA")
			|| !ft_strcmp(sect->sectname, "__data"))
		return ('d');
	if (!ft_strcmp(segment->segname, "__TEXT")
			|| !ft_strcmp(sect->sectname, "__text"))
		return ('t');
	return ('s');
}

char			st_find(struct nlist_64 symbol, void *buf, int obj)
{
	struct load_command			*cmd;
	struct mach_header_64		*header;
	struct segment_command_64	*segment;
	unsigned int				i;
	unsigned int				n;

	header = (struct mach_header_64 *)buf;
	i = 0;
	n = 0;
	cmd = (struct load_command *)(((char *)buf)
			+ sizeof(struct mach_header_64));
	while (i < header->ncmds)
	{
		if (cmd->cmd == LC_SEGMENT_64)
		{
			segment = (struct segment_command_64 *)cmd;
			if ((n + segment->nsects) >= symbol.n_sect)
				return ((obj == 1) ? FIND_OBJ_X64 : FIND_ALL_X64);
			n += segment->nsects;
		}
		cmd = (struct load_command *)(((char *)cmd) + cmd->cmdsize);
		++i;
	}
	return ('s');
}

char			get_symbol_x64(struct nlist_64 symbol, void *buf, t_file *file)
{
	if ((symbol.n_type & N_TYPE) == N_SECT)
	{
		if (file->filetype != 1)
			return (st_set_upper(st_find(symbol, buf, 0), symbol));
		else
			return (st_set_upper(st_find(symbol, buf, 1), symbol));
	}
	if ((symbol.n_type & N_TYPE) == N_UNDF)
	{
		if (symbol.n_value == 0)
			return (st_set_upper('u', symbol));
		else
			return (st_set_upper('c', symbol));
	}
	if ((symbol.n_type & N_TYPE) == N_ABS)
		return (st_set_upper('a', symbol));
	if ((symbol.n_type & N_TYPE) == N_INDR)
		return (st_set_upper('i', symbol));
	return ('X');
}
