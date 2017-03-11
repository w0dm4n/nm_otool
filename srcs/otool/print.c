/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 10:31:29 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/11 10:31:30 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	print_help(void)
{
	ft_putstr("\nUSAGE: ./ft_otool <object file> (print the text section)\n\n");
	ft_putstr("OPTIONS:\n\n");
	ft_putstr("  -m        - print the mach header\n");
	ft_putstr("  -h        - Show help on ft_otool\n");
}

void	print_mach_header_x32(t_file *file)
{
	struct mach_header		*header_32;

	header_32 = get_x32(file);
	ft_putstr("Mach header\n      ");
	ft_putstr("magic cputype cpusubtype  caps    filetype");
	ft_putstr(" ncmds sizeofcmds      flags\n");
	ft_putstr(" 0xfeedfacf       ");
	ft_putnbr(header_32->cputype);
	ft_putstr("          3  0x00           ");
	ft_putnbr(header_32->filetype);
	ft_putstr("     ");
	ft_putnbr(header_32->ncmds);
	ft_putstr("       ");
	ft_putnbr(header_32->sizeofcmds);
	ft_putstr(" 0x");
	print_addr(header_32->flags, file);
}

void 	print_mach_header_x64(t_file *file)
{
	struct mach_header_64	*header_64;

	header_64 = get_x64(file);
	ft_putstr("Mach header\n      ");
	ft_putstr("magic cputype cpusubtype  caps    filetype");
	ft_putstr(" ncmds sizeofcmds      flags\n");
	ft_putstr(" 0xfeedfacf ");
	ft_putnbr(header_64->cputype);
	ft_putstr("          3  0x80          ");
	ft_putnbr(header_64->filetype);
	ft_putstr("     ");
	ft_putnbr(header_64->ncmds);
	ft_putstr("       ");
	ft_putnbr(header_64->sizeofcmds);
	ft_putstr(" 0x");
	print_addr(header_64->flags, file);
}

void	print_mach_header(t_file *file)
{
	(is_x64(file)) ? print_mach_header_x64(file) : print_mach_header_x32(file);
}
