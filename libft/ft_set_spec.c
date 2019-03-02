/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_spec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 21:51:30 by fkuhn             #+#    #+#             */
/*   Updated: 2019/01/09 21:51:38 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_set_flag(char **fmt, t_flags *flags)
{
	if (**fmt == ' ')
		flags->space = 1;
	else if (**fmt == '-')
		flags->minus = 1;
	else if (**fmt == '+')
		flags->plus = 1;
	else if (**fmt == '0')
		flags->zero = 1;
	else if (**fmt == '#')
		flags->cage = 1;
	(*fmt)++;
}

void	ft_checknset_flags(char **fmt, t_flags *flags, t_specifier *sp)
{
	if (flags->minus)
		flags->zero = 0;
	if (flags->plus)
		flags->space = 0;
	sp->flags = flags;
	sp->specifier = **fmt ? **fmt : '\0';
	if (**fmt)
		(*fmt)++;
}

void	ft_set_width(char **fmt, t_specifier *sp)
{
	if (sp->width == 0)
		sp->width = get_width(fmt);
	else
	{
		while (ft_isdigit(**fmt))
			(*fmt)++;
	}
}
