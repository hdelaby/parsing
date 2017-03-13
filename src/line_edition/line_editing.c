/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 09:51:53 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/13 11:14:20 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include "ft_printf.h"
#include "history.h"
#include "keys.h"
#include <curses.h>

/*
** "\e[6n" corresponds to escape sequence to get cursor position. It writes
** on stdin an input of type ^[[1;1R that we then parse.
*/

void	get_cursor_start_pos(t_line *line)
{
	char	answer[20];
	int		i;

	ft_putstr_fd("\e[6n", 0);
	ft_bzero(answer, 20);
	i = read(0, answer, 20);
	answer[i] = 0;
	i = 2;
	line->start.row = ft_atoi(answer + i);
	while (ft_isdigit(answer[i]))
		i++;
	line->start.col = ft_atoi(answer + i + 1);
}

void	match_hist(int key_pressed, t_line *line)
{
	int						i;
	static struct s_keyhist	keyhist[2] = {
		{KEY_UP, &old_hist_entry},
		{KEY_DOWN, &new_hist_entry}
	};

	i = 0;
	while (i < 2)
		if (key_pressed == keyhist[i++].key)
			keyhist[i - 1].p(line, &(line->hist));
}

void	match_move(int key_pressed, t_line *line)
{
	int						i;
	static struct s_keymove	keymove[8] = {
		{KEY_RIGHT, &cursor_to_right},
		{KEY_LEFT, &cursor_to_left},
		{KEY_HOME, &cursor_to_home},
		{KEY_END, &cursor_to_end},
		{KEY_SRIGHT, &goto_next_word},
		{KEY_SLEFT, &goto_prev_word},
		{KEY_SPREVIOUS, &goto_prev_line},
		{KEY_SNEXT, &goto_next_line}
	};

	i = 0;
	while (i < 8)
		if (key_pressed == keymove[i++].key)
			keymove[i - 1].p(line);
}

void	input_loop(t_line *line)
{
	int		key_pressed;

	ft_getwinsz(&line->winsz);
	while (42)
	{
		ft_getwinsz(&line->winsz);
		key_pressed = get_key();
		if (line->start.row + line->cursor / line->winsz.col > line->winsz.row)
			line->start.row--;
		match_move(key_pressed, line);
		/* match_hist(key_pressed, line); */
		if (key_pressed > 31 && key_pressed < 127)
			insert_char(line, key_pressed);
		if (key_pressed == KEY_DC || key_pressed == 127)
			delete_char(line, key_pressed);
		if (key_pressed == KEY_CTRLL)
		{
			tputs(tgoto(tgetstr("SF", NULL), 0, line->start.row - 1)
					, 1, &tc_putc);
			line->start.row = 1;
			set_curpos(line);
		}
		if (key_pressed == '\n' || !key_pressed)
		{
			insert_char(line, key_pressed);
			break ;
		}
	}
}

char	*line_editing(void)
{
	t_line	line;
	char	*str;

	str = NULL;
	if (!isatty(STDIN_FILENO))
		while (get_next_line(STDIN_FILENO, &str) > 0)
			return (str);
	raw_term_mode();
	ft_bzero(&line, sizeof(line));
	line.hist = retrieve_history();
	line.hist_size = ft_dlstsize(line.hist);
	get_cursor_start_pos(&line);
	input_loop(&line);
	cursor_to_end(&line);
	default_term_mode();
	ft_putchar_fd('\n', 0);
	/* append_history(line.cmd); */
	ft_dlstdelstr(&line.hist);
	return (ft_strdup(line.cmd));
}
