// MonoLib.cpp : Defines the exported functions for the DLL application.
//

#include "../stdafx.h"
#include "MonoLib.h"


// This is an example of an exported variable
MONOLIB_API int nMonoLib=0;

// This is an example of an exported function.
MONOLIB_API int fnMonoLib(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see MonoLib.h for the class definition
CMonoLib::CMonoLib()
{
    return;
}
