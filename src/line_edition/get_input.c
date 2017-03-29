/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 10:19:38 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/29 17:19:24 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include "term_config.h"

void	print_line(char *line)
{
	while (*line)
	{
		if (*line == '\n')
			ft_putchar_fd(' ', 0);
		else
			ft_putchar_fd(*line, 0);
		line++;
	}
}

void	insert_char(t_line *line, int key)
{
	if (line->length + 1 >= MAX_CMD_LEN)
		return ;
	ft_memmove(line->cmd + line->cursor + 1, line->cmd + line->cursor,
			MAX_CMD_LEN - line->cursor - 1);
	line->cmd[line->cursor] = key;
	line->length++;
	line->cursor++;
	tputs(tgetstr("im", NULL), 1, &tc_putc);
	if (key != '\n')
		ft_putchar_fd(key, STDIN_FILENO);
	tputs(tgetstr("ei", NULL), 1, &tc_putc);
}

void	delete_char(t_line *line, int key)
{
	if (key == 127 && !line->cursor)
		return ;
	if (key == 127)
		cursor_to_left(line);
	if (line->cursor == line->length)
		return ;
	ft_memmove(line->cmd + line->cursor, line->cmd + line->cursor + 1,
			MAX_CMD_LEN - line->cursor - 1);
	line->length--;
	tputs(tgetstr("cd", NULL), 0, &tc_putc);
	print_line(line->cmd + line->cursor);
	set_curpos(line);
}
