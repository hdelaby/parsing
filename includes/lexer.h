/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 11:25:10 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/28 17:07:02 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include "shell.h"

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
	t_dlist	**hist;
}				t_token;

typedef struct	s_lextab
{
	char	key;
	void	(*p)(t_token *tok, t_list **tokens_lst);
}				t_lextab;

/*
** lexer.c
*/

void	end_token(t_token *tok, t_list **lst);
t_list	*lex_cmd(char *cmd, t_sh *sh);

/*
** Handlers
*/

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

/*
** lexing_tools.c
*/

int		is_line_empty(char *str);

#endif
