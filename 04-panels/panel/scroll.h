#pragma once 

#include <M5Unified.h>

int scrollOffSet = 0;
// voor swipe detectie
int touchStartY = 0;
int scrollStartOffSet = 0;
bool isDragging = false;

// grenzen waarbinnen je mag scrollen
int minScrollOffSet = 0;
int maxScrollOffSet = 110;

void handleScroll();