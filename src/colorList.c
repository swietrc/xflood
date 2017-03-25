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
 * \return initialized empty color list
 */
ColorList* ColorListCreateEmpty(){
    // TODO implement that
}
/**
 * \fn void ColorListPush(ColorList* list, char color)
 * \brief Adds an element with value of parameter color to the end of the list
 * \param list The list to which the element will be added
 * \param color The value of the element to add
 */
void ColorListPush(ColorList* list, char color){
    // TODO implement that
}

/**
 * \fn size_t ColorListSize(ColorList* list)
 * \brief Return the number of element of the list.
 * @param list The list to get the size of.
 * @return The number of element of the list.
 */
size_t ColorListSize(ColorList* list){
    // TODO implement that
}

/**
 * \fn void ColorListForward(ColorList* l, char* element)
 * \brief Assigns the value of current element,
 * or NULL if the end of the list has been reached through the param element.
 * Also sets the current element to the next element on the list.
 * @param l The list to get the next element of.
 * @param element A pointer that will be value assigned the value of the current element of the list.
 */
void ColorListForward(ColorList* l, char* element){
    // TODO implement that
}

/**
 * \fn void ColorListClean(ColorList* l)
 * \brief Free the list elements form the memory
 * @param l The list to remove the elements from.
 */
void ColorListClean(ColorList* l){
    // TODO implement that
}

/**
 * \fn void ColorListDestroy(ColorList* l)
 * \brief Free the list and its elements form the memory
 * @param l The list to remove from memory
 */
void ColorListDestroy(ColorList* l){
    // TODO implement taht
}

/**
 * \fn colorListCopy(ColorList* src, ColorList* dst)
 * \brief Cleans dst list and copy src list elements into dst.
 * @param src The list to copy from.
 * @param dst The list to copy to.
 */
void colorListCopy(ColorList* src, ColorList* dst){
    // TODO implement taht
}