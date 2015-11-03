#include <stdio.h>
#include <stdlib.h>
#include <png.h>

#include "../../include/graphic.h"

#if defined(GDEBUG)

const char *color_type_str(const size_t type) {
  const char *msg;
  switch(type) {
    case PNG_COLOR_TYPE_GRAY: msg = "Grayscale";        break;
    case PNG_COLOR_TYPE_GA:   msg = "Grayscale(Alpha)"; break;
    case PNG_COLOR_TYPE_RGB:  msg = "Color(RGB)";       break;
    case PNG_COLOR_TYPE_RGBA: msg = "Color(RGBA)";      break;
    default: msg = "Otherwise"; break;
  }
  return msg;
}

#endif
