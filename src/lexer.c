/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 09:24:31 by hdelaby           #+#    #+#             */
/*   Updated: 2017/02/23 09:27:39 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void		end_token(t_token *tok, t_list **lst)
{
	t_list *new_node;

	tok->str[tok->index] = '\0';
	if (*tok->str)
	{
		new_node = ft_lstnew(tok->str, ft_strlen(tok->str) + 1);
		new_node->content_size = tok->type;
		ft_lstaddback(lst, new_node);
	}
	ft_bzero(tok->str, MAX_TOKEN_LEN);
	tok->index = 0;
	tok->type = 0;
}

static void	match_table(char c, t_token *tok, t_list **tokens_lst)
{
	int							i;
	static struct s_parsingtab	ptab[6] = {
		{' ', &handle_space},
		{'\'', &handle_quote},
		{'\"', &handle_dquote},
		{'|', &handle_pipe},
		{'<', &handle_iredir},
		{'>', &handle_oredir}
	};

	i = 0;
	while (i < 6)
	{
		if (c == ptab[i].key)
		{
			ptab[i].p(tok, tokens_lst);
			return ;
		}
		i++;
	}
	handle_other(tok, tokens_lst, c);
}

t_list		*lex_cmd(char *cmd)
{
	t_token	tok;
	t_list	*lst;

	ft_bzero(&tok, sizeof(tok));
	tok.cmd = cmd;
	while (*tok.cmd)
		match_table(*tok.cmd++, &tok, &lst);
	end_token(&tok, &lst);
	return (lst);
}
