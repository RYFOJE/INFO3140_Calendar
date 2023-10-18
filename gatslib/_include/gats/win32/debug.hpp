#pragma once
/*	gats/win32/debug.hpp

	Installs Microsoft specific debugging services.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.08.25
	C++ 17 version.

Version 2019.01.19
	Production version.

Version 2015.01.01
	Alpha release.

=============================================================

Copyright 2015-21, Garth Santor & Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor/Trinh Han, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor/Trinh Han
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
=============================================================*/


// Setup DBG environment
#if defined(_DEBUG) && defined(_WIN32)
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>
#endif

// Create a dbg version of new that provides more information
#if defined(_DEBUG) && defined(_WIN32)
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif
