#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>

#include "../src/colorList.h"

void test_ColorList_ColorListCreateEmpty() {
  ColorList* cl = ColorListCreateEmpty();
  CU_ASSERT_PTR_NOT_NULL(cl);

  ColorListDestroy(cl);
}

void test_ColorList_ColorListPush() {
  ColorList* cl = ColorListCreateEmpty();
  ColorListPush(cl, 'R');
  char color;
  ColorListForward(cl, &color);

  CU_ASSERT(color == 'R');
}

void test_ColorList_ColorListSize() {
  ColorList* cl = ColorListCreateEmpty();
  // Adding 5 elements...
  ColorListPush(cl, 'R');
  ColorListPush(cl, 'R');
  ColorListPush(cl, 'R');
  ColorListPush(cl, 'R');
  ColorListPush(cl, 'R');

  CU_ASSERT(ColorListSize(cl) == 5);

  ColorListDestroy(cl);
}

void test_ColorList_ColorListForward() {
  ColorList* cl = ColorListCreateEmpty();
  // Adding 3 elements...
  ColorListPush(cl, 'R');
  ColorListPush(cl, 'G');
  ColorListPush(cl, 'B');

  char color;
  ColorListForward(cl, &color);
  CU_ASSERT(color == 'R');
  ColorListForward(cl, &color);
  CU_ASSERT(color == 'G');
  ColorListForward(cl, &color);
  CU_ASSERT(color == 'B');

  ColorListDestroy(cl);
}

void test_ColorList_ColorListCopy() {
  ColorList* src = ColorListCreateEmpty();
  // Adding 3 elements...
  ColorListPush(src, 'R');
  ColorListPush(src, 'G');
  ColorListPush(src, 'B');

  ColorList* dst = ColorListCreateEmpty();
  ColorListCopy(src, dst);

  // Check if dst contains correct elements
  char color;
  ColorListForward(dst, &color);
  CU_ASSERT(color == 'R');
  ColorListForward(dst, &color);
  CU_ASSERT(color == 'G');
  ColorListForward(dst, &color);
  CU_ASSERT(color == 'B');

  ColorListDestroy(src);
  ColorListDestroy(dst);
}


void addAllColorListTests(){
    CU_pSuite pSuite = CU_add_suite("ColorList elementary data structure and operations on them", NULL, NULL);

    CU_add_test(pSuite, "ColorListCreateEmpty() should return a non null pointer", test_ColorList_ColorListCreateEmpty);
    CU_add_test(pSuite, "ColorListPush() should correctly add a new element at the end of the list", test_ColorList_ColorListPush);
    CU_add_test(pSuite, "ColorListSize() should return the number of elements in the list", test_ColorList_ColorListSize);
    CU_add_test(pSuite, "ColorListForward() should give the current element of the list", test_ColorList_ColorListForward);
    CU_add_test(pSuite, "ColorListCopy() should correctly copy the source list into the destination list", test_ColorList_ColorListCopy);
}
