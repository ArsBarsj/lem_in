/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_spec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 17:16:20 by artemiy           #+#    #+#             */
/*   Updated: 2019/01/08 19:41:31 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

void	print_specifier(t_specifier *sp, int *counter)
{
	char	*width;

	if (sp->width > 0 || (sp->precition > 0 && sp->specifier != '%'))
	{
		if (sp->flags->zero)
			width = ft_fillstr(sp->width > sp->precition ?
					sp->width : sp->precition, '0');
		else
			width = ft_fillstr(sp->width > sp->precition ?
					sp->width : sp->precition, ' ');
		if (sp->flags->minus)
			width[0] = sp->specifier;
		else
			width[ft_strlen(width) - 1] = sp->specifier;
		ft_putstr(width);
		*counter += ft_strlen(width);
		free(width);
	}
	else
	{
		ft_putchar(sp->specifier);
		*counter += 1;
	}
}
