/**
 * \file colorList.c
 * Contains all colorList related data structures and operations.
 * \author Simon Wietrich
 * \author Pierre Genthon
 * \author Celestin Caumes
 * \author Camille Schnell
 **/

#include <stdio.h>
#include <stdlib.h>

#include "colorList.h"

struct colorNode {
    char val;
    ColorNode* next;
};

struct colorList {
    ColorNode* head;
    ColorNode* current;
};

/**
 * \fn ColorList* ColorListCreate()
 * \brief Initialises an empty color list.
 * \return Initialized empty color list
 */
ColorList* ColorListCreateEmpty(){
	ColorList *list = malloc(sizeof(ColorList));
	list->head = NULL;
	list->current = NULL;

	return list;
}
/**
 * \fn void ColorListPush(ColorList* list, char color)
 * \brief Adds an element with value of parameter color to the end of the list
 * \param list The list to which the element will be added
 * \param color The value of the element to add
 */
void ColorListPush(ColorList* list, char color){
	ColorNode *node = malloc(sizeof(ColorNode));
	node->val = color;
	node->next = NULL;

    if (list->head == NULL) {
        list->head = node;
        list->current = node;
        return;
    }

    ColorNode* current = list->head;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = node;
}

/**
 * \fn size_t ColorListSize(ColorList* list)
 * \brief Return the number of element of the list.
 * @param list The list to get the size of.
 * @return The number of element of the list.
 */
size_t ColorListSize(ColorList* list){
    ColorNode* current = list->head;
    if (current == NULL)
        return 0;

    size_t s = 1;

    while (current->next != NULL) {
        s++;
        current = current->next;
    }
    return s;
}

/**
 * \fn void ColorListForward(ColorList* l, char* element)
 * \brief Assigns the value of current element,
 * or NULL if the end of the list has been reached through the param element.
 * Also sets the current element to the next element on the list.
 * @param l The list to get the next element of.
 * @param element A pointer that will be value assigned the value of the current element of the list.
 * @return true as long as the list end has not been reached, false otherwise.
 */
bool ColorListForward(ColorList* l, char* element){
	if (l->current == NULL) {
		element = NULL;
		return false;
	}
	else {
		*element = (l->current)->val;
		(l->current) = (l->current)->next;
		return true;
	}
}

void ColorNodesClean(ColorNode* n) {
    if (n->next == NULL)
        return;
    
    ColorNodesClean(n->next);
    free(n->next);
}

/**
 * \fn void ColorListClean(ColorList* l)
 * \brief Free the list elements form the memory
 * @param l The list to remove the elements from.
 * 
 */
void ColorListClean(ColorList* l){
    if (l->head == NULL)
        return;

    ColorNodesClean(l->head);
}

/**
 * \fn void ColorListDestroy(ColorList* l)
 * \brief Free the list and its elements form the memory
 * @param l The list to remove from memory
 */
void ColorListDestroy(ColorList* l){
	ColorListClean(l);
	free(l);
}

/**
 * \fn colorListCopy(ColorList* src, ColorList* dst)
 * \brief Cleans dst list and copy src list elements into dst.
 * @param src The list to copy from.
 * @param dst The list to copy to.
 */
void ColorListCopy(ColorList* src, ColorList* dst){
    ColorNode* current = src->head;

    while(current != NULL) {
        ColorListPush(dst, current->val);
        current = current->next;
    }

    current = dst->head;

    while(current != NULL) {
        current = current->next;
    }
}

void ColorListPrint(ColorList* l) {
    ColorNode* current = l->head;
    puts("\n [ ");

    while(current != NULL) {
        printf("%c, ", current->val);
        current = current->next;
    }
    puts("] \n");
}

