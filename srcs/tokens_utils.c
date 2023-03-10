/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:07:26 by jmanet            #+#    #+#             */
/*   Updated: 2023/03/10 09:04:25 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Fonction pour créer un nouveau maillon avec le token donné
t_token_node	*create_token_node(char *token, int state) {
    // Allouer de la mémoire pour le nouveau maillon
    t_token_node *new_node = malloc(sizeof(t_token_node));
    if (new_node == NULL) {
        fprintf(stderr, "Erreur : Impossible d'allouer de la mémoire pour un nouveau maillon\n");
        exit(1);
    }

    // Allouer de la mémoire pour le token et le copier dans le nouveau maillon
    new_node->token = malloc(strlen(token) + 1);
    if (new_node->token == NULL) {
        fprintf(stderr, "Erreur : Impossible d'allouer de la mémoire pour le token\n");
        exit(1);
    }
    strcpy(new_node->token, token);

    if (state == LEX_DQUOTE)
        new_node->q_state = S_IN_DQUOTE;
    else if (state == LEX_SQUOTE)
        new_node->q_state = S_IN_SQUOTE;
    else
        new_node->q_state = S_NOT_IN_QUOTE;

    // Initialiser les pointeurs next et prev à NULL
    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;
}

// Fonction pour ajouter un nouveau maillon à la fin de la liste
void	add_token_node(t_token_node **list_head, char *token, int state) {
    // Créer le nouveau maillon
    t_token_node *new_node = create_token_node(token, state);

    // Si la liste est vide, le nouveau maillon devient la tête de liste
    if (*list_head == NULL) {
        *list_head = new_node;
        return;
    }

    // Trouver le dernier maillon de la liste
    t_token_node *current_node = *list_head;
    while (current_node->next != NULL) {
        current_node = current_node->next;
    }

    // Ajouter le nouveau maillon à la fin de la liste
    current_node->next = new_node;
    new_node->prev = current_node;
}

// Fonction pour afficher tous les tokens dans la liste
void	print_tokens(t_token_node *list_head)
{
    t_token_node *current_node = list_head;
    while (current_node != NULL)
    {
        printf("[%s] ", current_node->token);
        if (current_node->q_state == S_IN_SQUOTE)
                printf("-> IN_SQUOTE \n");
        if (current_node->q_state == S_IN_DQUOTE)
                printf("-> IN_DQUOTE \n");
        if (current_node->q_state == S_NOT_IN_QUOTE)
                printf("-> NOT_IN_QUOTE \n");
        current_node = current_node->next;
    }
    printf("fin de la liste\n\n");
}
