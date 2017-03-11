/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 19:44:58 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/04 18:13:48 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

t_file			*get_file_struct(char *name, char *flags)
{
	struct s_file	*file;

	if (!(file = (struct s_file*)malloc(sizeof(struct s_file))))
		return (NULL);
	file->file_name = name;
	if ((file->fd = open(file->file_name, O_RDONLY)) == -1)
		return (NULL);
	if (!(file->stat_data = (struct stat*)malloc(sizeof(struct stat))))
		return (NULL);
	file->is_x64 = FALSE;
	file->is_fat = FALSE;
	file->flags = flags;
	return (file);
}

static void		get_content(char *name, char *flags)
{
	struct s_file			*file;

	if (!(file = get_file_struct(name, flags)))
	{
		print_usage();
		return ;
	}
	if (!check_file(file))
		return ;
	if (is_universal(file))
		do_fat(file);
	else
		(is_x64(file)) ? do_64(file) : do_32(file);
}

void			do_current(char *current, char **argv, int i, int argc)
{
	char	*flags;

	flags = get_flags(argv);
	if (count_file(argv) >= 2)
	{
		ft_putstr(current);
		ft_putstr(":\n");
	}
	get_content(current, flags);
	if ((i + 1) < argc && count_file(argv) > 1)
		ft_putstr("\n");
}

int				main(int argc, char **argv)
{
	int		i;

	i = 1;
	if (has_flags('h', get_flags(argv)))
	{
		print_help();
		return (0);
	}
	if (argc >= 2)
	{
		if (count_file(argv) > 1)
			ft_putstr("\n");
		while (argv[i])
		{
			if (argv[i][0] != '-' || argv[i][1] == 'h')
				do_current(argv[i], argv, i, argc);
			i++;
		}
	}
	else
		print_usage();
	return (0);
}
