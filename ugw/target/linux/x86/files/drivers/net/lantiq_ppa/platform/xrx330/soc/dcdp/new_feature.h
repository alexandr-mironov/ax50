
#ifndef __NEW_FEATURE_H_
#define __NEW_FEATURE_H_

    #ifdef __LITTLE_ENDIAN
        #include "new_feature_le.h"
    #else
        #include "new_feature_be.h"
    #endif
#endif

