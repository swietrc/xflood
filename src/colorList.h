
#ifndef XFLOOD_COLORLIST_H
#define XFLOOD_COLORLIST_H

typedef struct colorList ColorList;

ColorList* ColorListCreateEmpty();
void ColorListPush(ColorList* list, char color);
size_t ColorListSize(ColorList* l);
bool ColorListForward(ColorList* l, char* element);
void ColorListClean(ColorList* l);
void ColorListDestroy(ColorList* l);
void colorListCopy(ColorList* src, ColorList* dst);

#endif //XFLOOD_COLORLIST_H
