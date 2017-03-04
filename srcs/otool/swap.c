/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 19:24:24 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/01 19:24:27 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

static int				should_swap_bytes(uint32_t magic)
{
	return (magic == MH_CIGAM || magic == MH_CIGAM_64);
}

void					swap_mach_header_x32(struct mach_header *mh)
{
	mh->magic = swap_int32(mh->magic);
	mh->cputype = swap_int32(mh->cputype);
	mh->cpusubtype = swap_int32(mh->cpusubtype);
	mh->filetype = swap_int32(mh->filetype);
	mh->ncmds = swap_int32(mh->ncmds);
	mh->sizeofcmds = swap_int32(mh->sizeofcmds);
	mh->flags = swap_int32(mh->flags);
}

void					swap_mach_header_x64(struct mach_header_64 *mh)
{
	mh->magic = swap_int32(mh->magic);
	mh->cputype = swap_int32(mh->cputype);
	mh->cpusubtype = swap_int32(mh->cpusubtype);
	mh->filetype = swap_int32(mh->filetype);
	mh->ncmds = swap_int32(mh->ncmds);
	mh->sizeofcmds = swap_int32(mh->sizeofcmds);
	mh->flags = swap_int32(mh->flags);
	mh->reserved = swap_int32(mh->reserved);
}

void					check_swap_x64(struct mach_header_64 *header)
{
	if (should_swap_bytes(header->magic))
		swap_mach_header_x64(header);
}

void					check_swap_x32(struct mach_header *header)
{
	if (should_swap_bytes(header->magic))
		swap_mach_header_x32(header);
}
