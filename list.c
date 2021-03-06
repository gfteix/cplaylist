#include "node.h"
#include "list.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int isEmpty(struct Node* head){
    if(head == NULL){
        return 1;
    }
    return 0;
}

void sortById(struct Node** head){
    if(isEmpty(*head)){
        printf("\nLista vazia.");
        return;
    }
    int swapped;
    struct Node* current = *head;
    struct Node* next;
    while(current && current->next){
        next = current->next;
        while(next){
            swapped =0;
            if(current->id > next->id){
                swapped =1;
                const struct Node* aux_current_prev = current->prev;
                const struct Node* aux_current_next = current->next;
                if(current->prev != NULL){
                    current->prev->next = next;
                }
                if(current->next != NULL && current->next != next){
                    current->next->prev = next;
                }
                if(next->prev != NULL && next->prev != current){
                    next->prev->next = current;
                }
                if(next->next != NULL){
                    next->next->prev = current;
                }
                if(next->prev != current){
                    current->prev = next->prev;
                }else{
                    current->prev = next;
                }
                current->next = next->next;
                next->prev = (struct Node*) aux_current_prev;
                if(aux_current_next != next){
                    next->next = (struct Node*)aux_current_next;
                }else{
                    next->next = current;
                }
                if(current == (*head)){
                    (*head) = next;
                }
            }
            if(swapped==1){
                current = next;
            }
            next = next->next;
        }
        current = current->next;
    }

    system("clear");
    list(*head);
}

void sortByTitle(struct Node** head){
    if(isEmpty(*head)){
        printf("\nLista vazia.");
        return;
    }
    int swapped;
    struct Node* current = *head;
    struct Node* next;
    while(current && current->next){
        next = current->next;
        while(next){
            swapped =0;
            if(strcmp(current->title, next->title)>0){
                swapped = 1;
                const struct Node* aux_current_prev = current->prev;
                const struct Node* aux_current_next = current->next;
                if(current->prev != NULL){
                    current->prev->next = next;
                }
                if(current->next != NULL && current->next != next){
                    current->next->prev = next;
                }
                if(next->prev != NULL && next->prev != current){
                    next->prev->next = current;
                }
                if(next->next != NULL){
                    next->next->prev = current;
                }
                if(next->prev != current){
                    current->prev = next->prev;
                }else{
                    current->prev = next;
                }
                current->next = next->next;
                next->prev = (struct Node*) aux_current_prev;
                if(aux_current_next != next){
                    next->next = (struct Node*)aux_current_next;
                }else{
                    next->next = current;
                }
                if(current == (*head)){
                    (*head) = next;
                }
            }
            if(swapped==1){
                current = next;
            }
            next = next->next;
        }
        current = current->next;
    }
    system("clear");
    list(*head);
}


struct Node* returnItem (struct Node* head, int id){
    struct Node* aux = head;

    while(aux->id != id){
        aux = aux->next;
    }

    return aux;
}

int insertAtBegin(struct Node** head, char title[], int id){

    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

    new_node->prev = NULL;
    new_node->id = id;
    //se a lista estiver vazia o ponteiro head apontar?? para o novo elemento
    // e o atributo next do novo elemento recebe NULL
    strcpy(new_node->title, title);
    if(isEmpty(*head)){
        (*head) = new_node;
        new_node->next = NULL;
        system("clear");
        return 1;
    }

    new_node->next = (*head);
    (*head)->prev = new_node;
    (*head) = new_node;

    system("clear");
    return 1;
}

int insert(struct Node* item, int id){
    char title_aux[256];
    printf("\nDigite o nome da musica: ");
    scanf("%s", title_aux);

    struct Node * new_node = (struct Node*) malloc(sizeof(struct Node));

    strcpy(new_node->title, title_aux);
    new_node->id = id;
    new_node->prev = item;
    new_node->next = item->next;

    if(item->next != NULL){
        item->next->prev = new_node;
    }
    item->next = new_node;

    system("clear");
    return 1;
}
int insertAtEnd(struct Node** head, char title[], int id){


    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->next = NULL;
    new_node->id = id;

    strcpy(new_node->title, title);

    if(*head == NULL){
        new_node->prev = NULL;
        (*head) = new_node;
        system("clear");
        return 1;
    }

    struct Node* last = (*head);

    while(last->next != NULL){
       last = last->next;
    }

    last->next = new_node;
    new_node->prev = last;

    system("clear");
    return 1;
}

void list(struct Node* head){

    system("clear");
    if(isEmpty(head)){
        printf("\nPlaylist vazia");
        return;
    }
    printf("\n*** Playlist ***\n");
    struct Node* aux = head;
    while(aux != NULL){
        printf("[%d]", aux->id);
        printf(" %s ", aux->title);
        aux = aux->next;
    }


}

int removeItem(struct Node** head, struct Node* item){

    if((*head) == item){
        (*head) = item->next;
    }
    //se  o elemento a ser deletado n??o ?? o ??ltimo
    //o atributo prev (anterior) do elemento ap??s o item a ser excluido recebe o elemento anterior ao item a ser excluido
    if(item->next != NULL){
        item->next->prev = item->prev;
    }
    //se o elemento a ser deletado n??o ?? o primeiro:
    //o antributo next (pr??ximo) do elemento anterior recebe o atribudo next (pr??ximo) do elemento a ser deletado.
    if(item->prev != NULL){
        item->prev->next = item->next;
    }
    free(item);
    system("clear");
    printf("\n Musica removida.");
    
    return 1;
}

void savePlaylist(struct Node* head){
    struct Node* item = head;
    FILE *f_playlist;
    f_playlist = fopen("playlist.dat", "wb+");

    while(item != NULL){
        fwrite(item, sizeof(struct Node), 1, f_playlist);
        item = item->next;
    }
    fclose(f_playlist);
}
int readingPlaylist(struct Node** head){
    FILE * f_playlist;
    int new_count=0;
    if ((f_playlist = fopen("playlist.dat", "ab+")) == NULL)
	{
		printf("File open error\n ");
		return -1;
	}
    struct Node* item = (struct Node*)malloc(sizeof(struct Node));

    while(fread(item, sizeof(struct Node), 1, f_playlist)){
        if(item){
		if(item->id > new_count){
            		new_count = item->id;
		}
            	insertAtEnd(head, item->title, item->id);
        }
    }
    system("clear");
    list(*head);

    return new_count+1;
}

void deleteList(struct Node** head){
    struct Node* current = (*head);
    struct Node* next = NULL;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    (*head) = NULL;
}

