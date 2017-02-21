/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 08:56:41 by hdelaby           #+#    #+#             */
/*   Updated: 2017/02/21 09:23:05 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#include "ft_printf.h"

void	end_token(t_token *tok, t_list **tokens_lst)
{
	t_list *new_node;

	tok->str[tok->str_i] = '\0';
	if (*tok->str)
	{
		new_node = ft_lstnew(tok->str, ft_strlen(tok->str) + 1);
		if (tok->is_pipe)
			new_node->content_size = 1;
		else if (tok->is_iredir)
			new_node->content_size = 2;
		else if (tok->is_oredir)
			new_node->content_size = 3;
		else
			new_node->content_size = 4;
		ft_lstaddback(tokens_lst, new_node);
	}
	ft_bzero(tok->str, MAX_TOKEN_LEN);
	tok->is_pipe = 0;
	tok->is_iredir = 0;
	tok->is_oredir = 0;
	tok->is_quoted = 0;
	tok->str_i = 0;
}

void	match_table(char c, t_token *tok, t_list **tokens_lst)
{
	int							i;
	static struct s_parsingtab	ptab[5] = {
		{' ', &handle_space},
		/* {'\'', &handle_squote} */
		{'\"', &handle_dquote},
		/* {'\"', &handle_squote} */
		{'|', &handle_pipe},
		{'<', &handle_iredir},
		{'>', &handle_oredir}
	};

	i = 0;
	while (i < 5)
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

void	parse_cmd(char *cmd)
{
	t_list	*tokens_lst;
	t_token tok;

	ft_bzero(&tok, sizeof(t_token));
	while (cmd[tok.cmd_i])
	{
		match_table(cmd[tok.cmd_i], &tok, &tokens_lst);
		tok.cmd_i++;
	}
	end_token(&tok, &tokens_lst);
	while (tokens_lst)
	{
		ft_printf("%s %d\n", tokens_lst->content, tokens_lst->content_size);
		tokens_lst = tokens_lst->next;
	}
}

int		main(void)
{
	char *cmd = "ls -l|cat 2> mdr > redir";
	parse_cmd(cmd);
}
