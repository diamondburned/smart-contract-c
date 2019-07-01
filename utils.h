#include "types.h"
// This compiles with emcc
#include "vector.h"

// Generic read function to read a vector. `size' takes in the size of each
// element in a vector, and the length header is assumed to be `uint32'.
uint8* vector_read(uint8* src, uint64* from, int size);

// _write function writes just about anything but a vector.
void _write(uint8* dst, void* interface);

// vector_write function, which writes the length and the content
void vector_write(uint8* dst, uint8* content);

// _atoi converts unsigned char* to int
// https://golang.org/src/strconv/atoi.go?s=5007:5039#L192
int _atoi(uint8* string);

#define READER(T)                                  \
    T read##T(uint8* src, uint64* from) {          \
        /* Create a new uint8 buffer */            \
        uint8* buf = 0;                            \
        /* Pre-alloc the size */                   \
        vector_grow(buf, sizeof(T));               \
        /* Write the T to the buffer */            \
        for (unsigned int i = 0; i < sizeof(T); i++) { \
            vector_append(buf, src[i + *from]);    \
        };                                         \
                                                   \
        /* Land of the unsafes */                  \
        T ret = *(uint64*)buf;                     \
        /* Bump up the ptr */                      \
        *from += sizeof(T);                        \
        return ret;                                \
    }

READER(uint64);
#undef READER
