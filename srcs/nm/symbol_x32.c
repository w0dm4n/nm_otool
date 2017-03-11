/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_x32.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 06:52:06 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/11 06:52:07 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

static char			st_set_upper_x32(char c, struct nlist symbol)
{
	if ((symbol.n_type & N_EXT) && c != ' ')
		return (ft_toupper(c));
	return (c);
}

static char			st_find_char_x32(struct segment_command *segment,
		unsigned int index)
{
	struct section			*sect;

	sect = (struct section *)((char *)segment
			+ sizeof(struct segment_command));
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

static char			st_find_char_x32_obj(struct segment_command *segment,
		unsigned int index)
{
	struct section			*sect;

	sect = (struct section *)((char *)segment
			+ sizeof(struct segment_command));
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

char				st_find_x32(struct nlist symbol, void *buf, int obj)
{
	struct load_command			*cmd;
	struct mach_header			*header;
	struct segment_command		*segment;
	unsigned int				i;
	unsigned int				n;

	header = (struct mach_header *)buf;
	i = 0;
	n = 0;
	cmd = (struct load_command *)(((char *)buf)
			+ sizeof(struct mach_header));
	while (i < header->ncmds)
	{
		if (cmd->cmd == LC_SEGMENT)
		{
			segment = (struct segment_command *)cmd;
			if ((n + segment->nsects) >= symbol.n_sect)
				return ((obj) ? FIND_OBJ_X32 : FIND_ALL_X32);
			n += segment->nsects;
		}
		cmd = (struct load_command *)(((char *)cmd) + cmd->cmdsize);
		++i;
	}
	return ('s');
}

char				get_symbol_x32(struct nlist symbol, void *buf, t_file *file)
{
	if ((symbol.n_type & N_TYPE) == N_SECT)
	{
		if (file->filetype != 1)
			return (st_set_upper_x32(st_find_x32(symbol, buf, 0), symbol));
		else
			return (st_set_upper_x32(st_find_x32(symbol, buf, 1), symbol));
	}
	if ((symbol.n_type & N_TYPE) == N_UNDF)
	{
		if (symbol.n_value == 0)
			return (st_set_upper_x32('u', symbol));
		else
			return (st_set_upper_x32('c', symbol));
	}
	if ((symbol.n_type & N_TYPE) == N_ABS)
		return (st_set_upper_x32('a', symbol));
	if ((symbol.n_type & N_TYPE) == N_INDR)
		return (st_set_upper_x32('i', symbol));
	return ('X');
}
