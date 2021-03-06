#ifndef XFLOOD_COLORLIST_H
#define XFLOOD_COLORLIST_H

#include <stdbool.h>

typedef struct colorNode ColorNode;
typedef struct colorList ColorList;

ColorList* ColorListCreateEmpty();
void ColorListPush(ColorList* list, char color);
size_t ColorListSize(ColorList* l);
bool ColorListForward(ColorList* l, char* element);
void ColorListReset(ColorList* l);
void ColorListClean(ColorList* l);
void ColorListDestroy(ColorList* l);
void ColorListCopy(ColorList* src, ColorList* dst);
bool ColorListIsIn(ColorList* l, char color);
void ColorListPrint(ColorList*);

#endif //XFLOOD_COLORLIST_H
