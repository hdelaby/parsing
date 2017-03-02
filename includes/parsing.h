/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 11:40:42 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/02 09:32:07 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "ast.h"

# define MAX_TOKEN_LEN 256

# define WORD	1
# define DIGIT	2
# define PIPE	3
# define OREDIR	4
# define IREDIR	5
# define SEMICO	6
# define EOL	7
# define END	8

typedef struct	s_token
{
	char	str[MAX_TOKEN_LEN];
	char	*cmd;
	int		index;
	int		type;
}				t_token;

struct			s_parsingtab
{
	char	key;
	void	(*p)(t_token *tok, t_list **tokens_lst);
};

typedef struct	s_cmdlist
{
	int					type;
	t_list				*args;
	t_list				*redir;
	struct s_cmdlist	*next;
}				t_cmdlist;

/*
** parser.c
*/

t_ast	*parser(t_list *tok);

/*
** lexer.c
*/

void	end_token(t_token *tok, t_list **lst);
t_list	*lex_cmd(char *cmd);

void	handle_pipe(t_token *tok, t_list **tokens_lst);
void	handle_semicolon(t_token *tok, t_list **tokens_lst);
void	handle_eol(t_token *tok, t_list **tokens_lst);
void	handle_space(t_token *tok, t_list **tokens_lst);
void	handle_dquote(t_token *tok, t_list **tokens_lst);
void	handle_quote(t_token *tok, t_list **lst);
void	handle_backsh(t_token *tok, t_list **tokens_lst);
void	handle_iredir(t_token *tok, t_list **tokens_lst);
void	handle_oredir(t_token *tok, t_list **tokens_lst);
void	handle_other(t_token *tok, t_list **tokens_lst, char key);

#endif
