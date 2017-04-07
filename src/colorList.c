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
    colorNode* next;
};

struct colorList {
    colorNode* head;
    colorNode* current;
};

/**
 * \fn ColorList* ColorListCreate()
 * \brief Initialises an empty color list.
 * \return Initialized empty color list
 */
ColorList* ColorListCreateEmpty(){
	colorList *list = malloc(sizeof(struct ColorList));
	list->head = NULL;
	lits->current = NULL;
	return list;
}
/**
 * \fn void ColorListPush(ColorList* list, char color)
 * \brief Adds an element with value of parameter color to the end of the list
 * \param list The list to which the element will be added
 * \param color The value of the element to add
 */
void ColorListPush(ColorList* list, char color){
	ColorNode *node = malloc(sizeof(struct ColorNode));
	node->val = color;
	node->next = NULL;
	list->current = node;
	(list->head)->next = node;
}

/**
 * \fn size_t ColorListSize(ColorList* list)
 * \brief Return the number of element of the list.
 * @param list The list to get the size of.
 * @return The number of element of the list.
 */
size_t ColorListSize(ColorList* list){
	ColorList *l1 = l;
	if ((l1->head)->next == NULL) {
		return 0;
	}
	else {
		l1->head = (l1->head)->next;
		return 1 + ColorListSize(l1);
	}
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
	if ((l->current)->next == NULL) {
		element = NULL;
		return false;
	}
	else {
		element = (l->current)->val;
		(l->current) = (l->head)->next;
		return true;
	}
}

/**
 * \fn void ColorListClean(ColorList* l)
 * \brief Free the list elements form the memory
 * @param l The list to remove the elements from.
 */
void ColorListClean(ColorList* l){
	if ((l->head)->next == NULL) {
		free(l->head);
	}
	else {
		free(l->head);
		(l->head) = (l->head)->next;
		ColorListClean(l);
	}
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
void colorListCopy(ColorList* src, ColorList* dst){
	ColorListClean(dst);
	while(dst->head != NULL) {
		dst->head = src->head;
		src->head = (src->head)->next;
		dst->head = (dst->head)->next;
	}
}
