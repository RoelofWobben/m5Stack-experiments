#include "scroll.h"
#include "panel.h"

int scrollOffSet = 0;
// voor swipe detectie
int touchStartY = 0;
int scrollStartOffSet = 0;
bool isDragging = false;

// grenzen waarbinnen je mag scrollen
int minScrollOffSet = 0;
int maxScrollOffSet = 110;

void handleScroll() {

  if (M5.Touch.getCount() == 0) {
    isDragging = false;
    return;
  }

  auto detail = M5.Touch.getDetail(0);

  if (detail.wasPressed()) {
    touchStartY = detail.y;
    scrollStartOffSet = scrollOffSet;
    isDragging = true;
  }

  if (isDragging && detail.isDragging()) {
    int deltaY = detail.y - touchStartY;
    int newOffSet = scrollStartOffSet - deltaY;
    newOffSet = constrain(newOffSet, minScrollOffSet, maxScrollOffSet);

    if (newOffSet != scrollOffSet) {
      scrollOffSet = newOffSet;
      drawPanels();
    }
  }
}

