/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:07:13 by jmanet            #+#    #+#             */
/*   Updated: 2023/04/30 11:39:16 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_variable(t_lst_var **head, char *name, char *value)
{
	t_lst_var	*new_var;
	t_lst_var	*current;

	new_var = malloc(sizeof(t_lst_var));
	new_var->name = strdup(name);
	new_var->value = strdup(value);
	new_var->previous = NULL;
	new_var->next = NULL;

	if (*head == NULL)
		*head = new_var;
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_var;
		new_var->previous = current;
	}
}

void	remove_variable(t_lst_var **head, char *name)
{
	t_lst_var	*current;

	current = *head;
	if (*head == NULL)
		return ;
	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
		{
			if (current->previous != NULL)
				current->previous->next = current->next;
			else
				*head = current->next;
			if (current->next != NULL)
				current->next->previous = current->previous;
			free(current->name);
			free(current->value);
			free(current);
			return ;
		}
		current = current->next;
	}
}

void	edit_variable(t_lst_var **head, char *name, char *new_value)
{
	t_lst_var	*current;

	current = *head;
	if (*head == NULL)
		return ;
	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
		{
			free(current->value);
			current->value = ft_strdup(new_value);
		}
		current = current->next;
	}
}

void	free_variables(t_lst_var **head)
{
	t_lst_var	*current;
	t_lst_var	*next;

	current = *head;
	next = NULL;
	while (current != NULL)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
	*head = NULL;
}

void	print_variables(t_lst_var *head)
{
	t_lst_var	*current;

	current = head;
	while (current != NULL)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}

