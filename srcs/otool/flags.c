/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 08:19:17 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/11 08:19:18 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

int		has_flags(char f, char *flags)
{
	int i;

	i = 0;
	while (flags[i])
	{
		if (flags[i] == f)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int		authorized_flags(char f)
{
	int i;

	i = 0;
	while (OTOOL_FLAGS[i])
	{
		if (OTOOL_FLAGS[i] == f)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

char	*new_flags(char n, char *flags)
{
	int i;

	i = 0;
	while (flags[i])
		i++;
	flags[i++] = n;
	flags[i] = '\0';
	return (flags);
}

char	*add_flags(char *to_add, char *flags)
{
	int i;

	i = 1;
	while (to_add[i])
	{
		if (authorized_flags(to_add[i]) \
			&& has_flags(to_add[i], flags) == FALSE)
			flags = new_flags(to_add[i], flags);
		i++;
	}
	return (flags);
}

char	*get_flags(char **argv)
{
	int		i;
	char	*flags;

	i = 1;
	if (!(flags = ft_strnew(4096)))
		return (NULL);
	while (argv[i])
	{
		if (argv[i][0] == '-')
			flags = add_flags(argv[i], flags);
		i++;
	}
	return (flags);
}
