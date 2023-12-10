#include "testing.h"

// Control debug mode
static bool debugEnabled = true;

bool isDebugEnabled() {
	return debugEnabled;
}

void setDebugEnabled( bool enable ) {
	debugEnabled = enable;
}
