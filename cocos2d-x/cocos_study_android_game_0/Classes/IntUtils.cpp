#include "IntUtils.h"

int IntUtils::ClampI(int value, int min, int max)
{
	return value < min ? min : value>max ? max : value;
}
