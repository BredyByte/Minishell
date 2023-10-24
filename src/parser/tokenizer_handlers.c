/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:24:51 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/24 13:02:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quotes(char **str)
{
	char	quote_char;
	char	*start;

	quote_char = **str;
	start = ++(*str);
	while (**str && **str != quote_char)
		(*str)++;
	if (**str == quote_char)
	{
		if (quote_char == '"')
			fill_in_lex(TOKEN_EXP_FIELD, ft_strndup(start, *str - start));
		else if (quote_char == '\'')
			fill_in_lex(TOKEN_FIELD, ft_strndup(start, *str - start));
	}
	else
	{
		printf("Davyd: Error Quotes.\n");
		exit(1);
	}
}

void	handle_redirections(char **str)
{
	if (**str == '>')
	{
		if (ft_strncmp(*str, ">>", 2) == 0)
		{
			fill_in_lex(TOKEN_REDIR_APPEND, ">>");
			(*str)++;
		}
		else
			fill_in_lex(TOKEN_REDIR_OUT, ">");
	}
	else if (**str == '<')
	{
		if (ft_strncmp(*str, "<<", 2) == 0)
		{
			fill_in_lex(TOKEN_REDIR_INSOURCE, "<<");
			(*str)++;
		}
		else
			fill_in_lex(TOKEN_REDIR_IN, "<");
	}
}

void	handle_words(char **str)
{
	char	*start;

	if (!ft_is_special_char(**str) || (**str == '&' && *(*str + 1) != '&'))
	{
		start = *str;
		while (*(*str + 1) && (!ft_is_special_char(*(*str + 1)) || (**str == '&'
					&& *(*str + 1) != '&')) && !ft_isspace(*(*str + 1)))
			(*str)++;
		fill_in_lex(TOKEN_WORD, ft_strndup(start, *str + 1 - start));
	}
}

void	handle_space(char **str)
{
	char	*start;

	start = *str;
	while (ft_isspace(*(*str + 1)))
		(*str)++;
	fill_in_lex(TOKEN_SEP, ft_strndup(start, *str + 1 - start));
}
