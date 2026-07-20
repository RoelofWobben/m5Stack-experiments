#pragma once 

#include <M5Unified.h>

extern int scrollOffSet;
// voor swipe detectie
extern int touchStartY;
extern int scrollStartOffSet;
extern bool isDragging;

// grenzen waarbinnen je mag scrollen
extern int minScrollOffSet;
extern int maxScrollOffSet;

void handleScroll();