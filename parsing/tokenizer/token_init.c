/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:17:27 by keteo             #+#    #+#             */
/*   Updated: 2025/07/22 15:17:27 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	token_init(char ***token)
{
	*token = malloc((sizeof(char *) * MAX_TOKEN));
	if (!*token)
		return (0);
	return (1);
}