#pragma once

#include "Metadata.h"

struct Test
{
	Declare_Struct(Test)

	Define_Field(1, int, a)

	Define_Field(2, double, b)

	Define_Field(3, string, c)

	Define_Metadata(3)
};
