/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 08:56:41 by hdelaby           #+#    #+#             */
/*   Updated: 2017/02/18 11:37:32 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	end_token(t_token *tok, t_list **tokens_lst)
{
	ft_lstaddback(tokens_lst, ft_lstnew(tok->str, ft_strlen(tok->str) + 1));
	ft_bzero(tok->str, MAX_TOKEN_LEN);
	tok->str_i = 0;
}

void	parse_cmd(char *cmd)
{
	t_list	*tokens_lst;
	t_token tok;

	ft_bzero(&tok, sizeof(t_token));
	while (cmd[tok.cmd_i])
	{
		if (cmd[tok.cmd_i] > 32)
			tok.str[tok.str_i++] = cmd[tok.cmd_i];
		else
			end_token(&tok, &tokens_lst);
		tok.cmd_i++;
	}
	tok.str[tok.str_i] = 0;
	end_token(&tok, &tokens_lst);
	ft_putlst(tokens_lst);
}

int		main(void)
{
	char *cmd = "Hello this is a command";
	
	parse_cmd(cmd);
}
