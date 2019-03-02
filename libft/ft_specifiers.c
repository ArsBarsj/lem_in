/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifiers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 17:36:38 by artemiy           #+#    #+#             */
/*   Updated: 2019/01/09 22:04:34 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

int			get_width(char **fmt)
{
	int	width;

	width = ft_atoi(*fmt);
	while (**fmt && ft_isdigit(**fmt))
		(*fmt)++;
	return (width);
}

int			get_precition(char **fmt)
{
	int			precition;

	if (**fmt == '.')
	{
		while (**fmt && **fmt == '.')
			(*fmt)++;
		precition = ft_atoi(*fmt);
		while (**fmt && ft_isdigit(**fmt))
			(*fmt)++;
		return (precition);
	}
	return (-1);
}

int			get_length(char **fmt)
{
	char		*length;
	int			l_len;

	l_len = get_length_len(*fmt);
	if (!(length = ft_strsub(*fmt, 0, l_len)))
		return (0);
	*fmt += l_len;
	if (!ft_strcmp(length, "hh"))
		l_len = 1;
	else if (!ft_strcmp(length, "h"))
		l_len = 2;
	else if (!ft_strcmp(length, "l"))
		l_len = 3;
	else if (!ft_strcmp(length, "ll"))
		l_len = 4;
	else if (!ft_strcmp(length, "L"))
		l_len = 4;
	else if (!ft_strcmp(length, "z"))
		l_len = 5;
	else if (!ft_strcmp(length, "j"))
		l_len = 6;
	free(length);
	return (l_len);
}

void		ft_spec_init(t_specifier **sp)
{
	(*sp)->flags = NULL;
	(*sp)->length = 0;
	(*sp)->precition = -1;
	(*sp)->width = 0;
	(*sp)->specifier = '\0';
}

t_specifier	*create_specifier2(char **fmt)
{
	t_specifier	*sp;
	t_flags		*flags;
	int			length;

	if (!(sp = (t_specifier *)malloc(sizeof(t_specifier))))
		handle_error(0, NULL);
	ft_spec_init(&sp);
	flags = init_flags();
	while (**fmt && ft_strchr("0123456789-+ #.lhjzL", **fmt))
	{
		while (**fmt && ft_strchr(" -+0#", **fmt))
			ft_set_flag(fmt, flags);
		length = get_length(fmt);
		if (sp->length < length)
			sp->length = length;
		ft_set_width(fmt, sp);
		if (**fmt == '.')
			sp->precition = get_precition(fmt);
	}
	ft_checknset_flags(fmt, flags, sp);
	normalize_spec(&sp);
	if (!sp->flags)
		handle_error(0, &sp);
	return (sp);
}
