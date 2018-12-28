#ifndef CONSTANTS_H_
#define CONSTANTS_H_

/* version information */
#define JCRL_VERSION_MAJOR 0
#define JCRL_VERSION_MINOR 33
#define JCRL_vERSION_PATCH 0

/* status codes */
#define JCRL_ERR_OK 0
#define JCRL_ERR_NULL_PARAM 1
#define JCRL_ERR_IMPOSSIBLE 2
#define JCRL_ERR_SYS_MEM_ALLOC 3
#define JCRL_ERR_UNINITIALISED 4
#define JCRL_ERR_OUT_OF_BOUNDS 5
#define JCRL_ERR_NOT_FOUND 6

/* Map implementation */
#define JCRL_MAP_INIT_NUM_BUCKETS 256
#define JCRL_MAP_LOAD_THRESHOLD 0.75
#define JCRL_MAP_GROWTH_FACTOR 2

#endif // CONSTANTS_H_
