/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 15:08:19 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/04 15:08:20 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void		print_usage(void)
{
	ft_putstr("Usage : ./ft_otool <object file> (print the text section)\n");
}

void		print_not_object(void)
{
	ft_putstr("./ft_otool: The file was not recognized as");
	ft_putstr(" a valid object file.\n");
}

int			check_file(struct s_file *file)
{
	if (fstat(file->fd, file->stat_data) < 0)
	{
		print_usage();
		return (FALSE);
	}
	if (!S_ISREG(file->stat_data->st_mode))
	{
		print_not_object();
		return (FALSE);
	}
	return (TRUE);
}
