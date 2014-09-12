// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

//#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here
#include "../apache_1.3.42/src/include/httpd.h"
#include "../apache_1.3.42/src/include/http_log.h"
#include "../apache_1.3.42/src/include/http_config.h"
#include "../apache_1.3.42/src/include/http_protocol.h"
#include "../apache_1.3.42/src/include/http_main.h"
#undef strtoul /* from "httpd.h" */

