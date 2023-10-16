/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:19:16 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/16 18:20:45 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_dollar_expansion(char **ptmp, t_info *info)
{
	char	*res;
	char	*key;
	char	*tmp;

	res = NULL;
	key = NULL;
	tmp = *ptmp;
	tmp++;
	if (*tmp == '?')
	{
		res = ft_itoa(info->status);
		tmp++;
	}
	else if (ft_isalpha(*tmp) || *tmp == '_' || ft_isdigit(*tmp))
	{
		key = get_envp_key(tmp);
		res = get_envp_value(info->envp_lst, key);
		if (!res)
			res = ft_strdup("");
		tmp += ft_strlen(key);
		free(key);
	}
	*ptmp = tmp;
	return (res);
}

static int	get_new_len(char *str, t_info *info)
{
	char	*tmp;
	int		len;
	char	*res;

	res = NULL;
	tmp = str;
	len = 0;
	while (*tmp)
	{
		if (*tmp == '$' && is_valid_dollar_followup(*(tmp + 1)))
		{
			res = handle_dollar_expansion(&tmp, info);
			len += ft_strlen(res);
			free(res);
		}
		else
		{
			len++;
			tmp++;
		}
	}
	return (len);
}

static char	*process_string_value(t_token *token,
			t_info *info, char *tmp, int *current_len)
{
	char	*new_str;
	char	*res;

	new_str = (char *)malloc(token->len + 1);
	if (!new_str)
		return (NULL);
	new_str[token->len] = '\0';
	while (*tmp)
	{
		if (*tmp == '$' && is_valid_dollar_followup(*(tmp + 1)))
		{
			res = handle_dollar_expansion(&tmp, info);
			if (res)
				append_to_buffer(new_str, res, current_len);
		}
		else
		{
			new_str[*current_len] = *tmp;
			(*current_len)++;
			tmp++;
		}
	}
	return (new_str);
}

static char	*get_new_value(t_token *token, t_info *info)
{
	char	*new_str;
	char	*tmp;
	int		current_len;

	current_len = 0;
	tmp = token->value;
	new_str = process_string_value(token, info, tmp, &current_len);
	free(token->value);
	return (new_str);
}

void	expansion(t_info *info)
{
	t_token	*tmp;

	tmp = info->token_lst;
	while (tmp != NULL)
	{
		if (tmp->key == TOKEN_WORD || tmp->key == TOKEN_EXP_FIELD)
		{
			tmp->len = get_new_len(tmp->value, info);
			tmp->value = get_new_value(tmp, info);
		}
		tmp = tmp->next;
	}
}