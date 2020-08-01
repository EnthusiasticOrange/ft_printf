/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 23:51:49 by mjuli             #+#    #+#             */
/*   Updated: 2020/07/31 20:29:56 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	process_format(t_arg_info *arg)
{
	if (arg->type == 's')
		process_string(arg);
	else if (arg->type == 'c')
		process_char(arg);
	else if (arg->type == '%')
		arg->result += write(1, "%", 1);
	else
		process_numbers(arg);
}

int			ft_printf(const char *format, ...)
{
	t_arg_info		arg;

	arg.result = 0;
	va_start(arg.ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (!*format)
				return (-1);
			if (!process_arg(&arg, &format))
				return (-1);
			process_format(&arg);
		}
		else
			arg.result += write(1, format, 1);
		format++;
	}
	va_end(arg.ap);
	return (arg.result);
}
