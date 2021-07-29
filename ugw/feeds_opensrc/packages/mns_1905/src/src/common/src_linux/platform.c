/*
 *  Broadband Forum BUS (Broadband User Services) Work Area
 *  
 *  Copyright (c) 2017, Broadband Forum
 *  Copyright (c) 2017, MaxLinear, Inc. and its affiliates
 *  
 *  Redistribution and use in source and binary forms, with or
 *  without modification, are permitted provided that the following
 *  conditions are met:
 *  
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  
 *  2. Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials
 *     provided with the distribution.
 *  
 *  3. Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products
 *     derived from this software without specific prior written
 *     permission.
 *  
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 *  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 *  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  
 *  The above license is used as a license under copyright only.
 *  Please reference the Forum IPR Policy for patent licensing terms
 *  <https://www.broadband-forum.org/ipr-policy>.
 *  
 *  Any moral rights which are necessary to exercise under the above
 *  license grant are also deemed granted under this license.
 */

#include "platform.h"

#include <stdlib.h>      // free(), malloc(), ...
#include <string.h>      // memcpy(), memcmp(), ...
#include <stdio.h>       // printf(), ...
#include <stdarg.h>      // va_list
#include <sys/time.h>    // gettimeofday()
#include <syslog.h>
#ifndef _FLAVOUR_X86_WINDOWS_MINGW_
#    include <pthread.h> // mutexes, pthread_self()
#endif



////////////////////////////////////////////////////////////////////////////////
// Private functions, structures and macros
////////////////////////////////////////////////////////////////////////////////

// *********** libc stuff ******************************************************

// We will use this variable to save the instant when "PLATFORM_INIT()" was
// called. This way we sill be able to get relative timestamps later when
// someone calls "PLATFORM_GET_TIMESTAMP()"
//
static struct timeval tv_begin;

// The following variable is used to set which "PLATFORM_PRINTF_DEBUG_*()"
// functions should be ignored:
//
//   0 => Only print ERROR messages
//   1 => Print ERROR and WARNING messages
//   2 => Print ERROR, WARNING and INFO messages
//   3 => Print ERROR, WARNING, INFO and DETAIL messages
//
static int verbosity_level = 2;

// Mutex to avoid STDOUT "overlaping" due to different threads writing at the
// same time.
//
#ifndef _FLAVOUR_X86_WINDOWS_MINGW_
pthread_mutex_t printf_mutex = PTHREAD_MUTEX_INITIALIZER;
#endif

// Color codes to print messages from different threads in different colors
//
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#ifndef _FLAVOUR_X86_WINDOWS_MINGW_
#    define ENABLE_COLOR (1)
#else
#    define ENABLE_COLOR (0)
#endif

char *_enableColor(void)
{
#if ENABLE_COLOR
    static pthread_t  first_thread = 0;

    if (0 == first_thread)
    {
        first_thread = pthread_self();
    }

    if (pthread_self() == first_thread)
    {
        return KWHT;
    }
    else
    {
        static char  *aux[] = {KRED, KGRN, KYEL, KBLU, KMAG, KCYN, KWHT};
        return aux[(pthread_self()-first_thread) % 6];
    }
#else
    return "";
#endif
}

char *_disableColor(void)
{
#if ENABLE_COLOR
    return KNRM;
#else
    return "";
#endif
}


////////////////////////////////////////////////////////////////////////////////
// Platform API: libc stuff
////////////////////////////////////////////////////////////////////////////////

void *PLATFORM_MALLOC(INT32U size)
{
    void *p;

    p = malloc(size);

    if (NULL == p)
    {
        syslog(LOG_CRIT,"%s","ERROR: Out of memory!\n");
        exit(1);
    }

    return p;
}


void PLATFORM_FREE(void *ptr)
{
    return free(ptr);
}


void *PLATFORM_REALLOC(void *ptr, INT32U size)
{
    void *p;

    p = realloc(ptr, size);

    if (NULL == p)
    {

        syslog(LOG_CRIT,"%s","ERROR: Out of memory!\n");
        exit(1);
    }

    return p;
}

void *PLATFORM_MEMSET(void *dest, INT8U c, INT32U n)
{
    return memset(dest, c, n);
}

void *PLATFORM_MEMCPY(void *dest, const void *src, INT32U n)
{
    return memcpy(dest, src, n);
}

INT8U PLATFORM_MEMCMP(const void *s1, const void *s2, INT32U n)
{
    int aux;

    aux = memcmp(s1, s2, n);

    if (0 == aux)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

INT32U PLATFORM_STRLEN(const char *s)
{
    return strlen(s);
}

char *PLATFORM_STRDUP(const char *s)
{
    return strdup(s);
}

char *PLATFORM_STRNCAT(char *dest, const char *src, INT32U n)
{
    return strncat(dest, src, n);
}

void PLATFORM_SNPRINTF(char *dest, INT32U n, const char *format, ...)
{
    va_list arglist;

    va_start( arglist, format );
    vsnprintf( dest, n, format, arglist );
    va_end( arglist );

    return;
}

void PLATFORM_VSNPRINTF(char *dest, INT32U n, const char *format, va_list ap)
{
    vsnprintf( dest, n, format, ap);

    return;
}

void PLATFORM_PRINTF(const char *format, ...)
{
    va_list arglist;

#ifndef _FLAVOUR_X86_WINDOWS_MINGW_
    pthread_mutex_lock(&printf_mutex);
#endif

    va_start( arglist, format );
    vsyslog( LOG_DEBUG,format, arglist );
    va_end( arglist );

#ifndef _FLAVOUR_X86_WINDOWS_MINGW_
    pthread_mutex_unlock(&printf_mutex);
#endif

    return;
}

void PLATFORM_PRINTF_DEBUG_SET_VERBOSITY_LEVEL(int level)
{
    verbosity_level = level;
}

void PLATFORM_PRINTF_DEBUG_ERROR(const char *format, ...)
{
    va_list arglist;
    INT32U ts;

    if (verbosity_level < 0)
    {
        return;
    }

    ts = PLATFORM_GET_TIMESTAMP();

#ifndef _FLAVOUR_X86_WINDOWS_MINGW_
    pthread_mutex_lock(&printf_mutex);
#endif

    syslog(LOG_ERR,"%s", _enableColor());
    syslog(LOG_ERR,"[%03d.%03d] ", ts/1000, ts%1000);
    syslog(LOG_ERR,"%s","ERROR   : ");
    va_start( arglist, format );
    vsyslog(LOG_ERR, format, arglist );
    va_end( arglist );
    syslog(LOG_ERR,"%s", _disableColor());

#ifndef _FLAVOUR_X86_WINDOWS_MINGW_
    pthread_mutex_unlock(&printf_mutex);
#endif

    return;
}

void PLATFORM_PRINTF_DEBUG_WARNING(const char *format, ...)
{
    va_list arglist;
    INT32U ts;

    if (verbosity_level < 1)
    {
        return;
    }

    ts = PLATFORM_GET_TIMESTAMP();

#ifndef _FLAVOUR_X86_WINDOWS_MINGW_
    pthread_mutex_lock(&printf_mutex);
#endif

    syslog(LOG_WARNING,"%s", _enableColor());
    syslog(LOG_WARNING,"[%03d.%03d] ", ts/1000, ts%1000);
    syslog(LOG_WARNING,"%s","WARNING : ");
    va_start( arglist, format );
    vsyslog(LOG_WARNING, format, arglist );
    va_end( arglist );
    syslog(LOG_WARNING,"%s", _disableColor());

#ifndef _FLAVOUR_X86_WINDOWS_MINGW_
    pthread_mutex_unlock(&printf_mutex);
#endif

    return;
}

void PLATFORM_PRINTF_DEBUG_INFO(const char *format, ...)
{
    va_list arglist;
    INT32U ts;

    if (verbosity_level < 2)
    {
        return;
    }

    ts = PLATFORM_GET_TIMESTAMP();

#ifndef _FLAVOUR_X86_WINDOWS_MINGW_
    pthread_mutex_lock(&printf_mutex);
#endif

    syslog(LOG_INFO,"%s", _enableColor());
    syslog(LOG_INFO,"[%03d.%03d] ", ts/1000, ts%1000);
    syslog(LOG_INFO,"%s","INFO    : ");
    va_start( arglist, format );
    vsyslog( LOG_INFO,format, arglist );
    va_end( arglist );
    syslog(LOG_INFO,"%s", _disableColor());
    
#ifndef _FLAVOUR_X86_WINDOWS_MINGW_
    pthread_mutex_unlock(&printf_mutex);
#endif

    return;
}

void PLATFORM_PRINTF_DEBUG_DETAIL(const char *format, ...)
{
    va_list arglist;
    INT32U ts;

    if (verbosity_level < 3)
    {
        return;
    }

    ts = PLATFORM_GET_TIMESTAMP();

#ifndef _FLAVOUR_X86_WINDOWS_MINGW_
    pthread_mutex_lock(&printf_mutex);
#endif

    syslog(LOG_DEBUG,"%s", _enableColor());
    syslog(LOG_DEBUG,"[%03d.%03d] ", ts/1000, ts%1000);
    syslog(LOG_DEBUG,"%s","DETAIL  : ");
    va_start( arglist, format );
    vsyslog(LOG_DEBUG, format, arglist );
    va_end( arglist );
    syslog(LOG_DEBUG,"%s", _disableColor());

#ifndef _FLAVOUR_X86_WINDOWS_MINGW_
    pthread_mutex_unlock(&printf_mutex);
#endif

    return;
}

INT32U PLATFORM_GET_TIMESTAMP(void)
{
    struct timeval tv_end;
    INT32U diff;

    gettimeofday(&tv_end, NULL);

    diff = (tv_end.tv_usec - tv_begin.tv_usec) / 1000 + (tv_end.tv_sec - tv_begin.tv_sec) * 1000;

    return diff;
}


////////////////////////////////////////////////////////////////////////////////
// Platform API: Initialization functions
////////////////////////////////////////////////////////////////////////////////

INT8U PLATFORM_INIT(void)
{

    // Call "_timeval_print()" for the first time so that the initialization
    // time is saved for future reference.
    //
    gettimeofday(&tv_begin, NULL);

    return 1;
}





