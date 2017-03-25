<<<<<<< HEAD
#ifndef XFLOOD_COLORLIST_H
#define XFLOOD_COLORLIST_H

typedef struct colorList ColorList;

ColorList* ColorListCreateEmpty();
void ColorListPush(ColorList* list, char color);
size_t ColorListSize(ColorList* l);
void ColorListForward(ColorList* l, char* element);
void ColorListClean(ColorList* l);
void ColorListDestroy(ColorList* l);
void colorListCopy(ColorList* src, ColorList* dst);

=======
//
// Created by scrip on 25/03/17.
//

#ifndef XFLOOD_COLORLIST_H
#define XFLOOD_COLORLIST_H

>>>>>>> 3c8d251e43ed04b3c95c64c6ca85df507b81c641
#endif //XFLOOD_COLORLIST_H
