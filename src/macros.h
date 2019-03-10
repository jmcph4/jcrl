#ifndef MACROS_H_
#define MACROS_H_

#define PASS_UP_ON_FAIL(x) if(x != JCRL_ERR_OK) \
{\
    return res;\
}

/* Allows integral types to be stored in ADT */
#define G_INT(x) (void*)(uintptr_t)(x)

#endif /* MACROS_H_ */

