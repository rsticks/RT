/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 17:01:52 by daron             #+#    #+#             */
/*   Updated: 2020/03/05 16:41:39 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		kill_all(char *message)
{
	perror(message);
	exit(1);
}

void	kill_error(char *message, int string_number)
{
	kill_all(ft_strjoin_del(ft_strjoin(ft_strjoin("ERROR: ", message),
			" String number "), ft_itoa(string_number), 'R'));
}
