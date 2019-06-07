#ifndef _MINIFB_H_
#define _MINIFB_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "Types.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MFB_RGB(r, g, b) (((uint)r) << 16) | (((uint)g) << 8) | b
#define MFB_ARGB(a, r, g, b) (((uint)a) << 24) | (((uint)r) << 16) | (((uint)g) << 8) | b

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Create a window that is used to display the buffer sent into the mfb_update function, returns 0 if fails
int mfb_open(const char* name, int width, int height);

// Update the display. Input buffer is assumed to be a 32-bit buffer of the size given in the open call
// Will return -1 when ESC key is pressed (later on will return keycode and -1 on other close signal) 
int mfb_update(void* buffer);

// Close the window
void mfb_close();

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

#endif
