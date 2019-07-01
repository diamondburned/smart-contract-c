#include "vector.h"
#include "types.h"
#include "utils.h"

uint8* vector_read_size(uint8* src, uint)

// Generic read function to read a vector. `size' takes in the size of each
// element in a vector, and the length header is assumed to be `uint32'.
uint8* vector_read(uint8* src, uint64 *from, int size) {
	uint8* dst = NULL;

	// Read the first few bytes for the vector size.
	int len = _atoi(_read(src, from, sizeof(uint32)));

	// Grow the slice to the length
	vector_grow(dst, len*size);

	// Read the whole vector by multiplying the vector length with the size of
	// one vector element.
	for (int i = 0; i < len*size; i++) {
		vector_append(dst, src[*from + i]);
	};

	*from += (uint64)size;

	return dst;
};

// _write function writes just about anything but a vector.
void _write(uint8* dst, void* interface) {
	vector_grow(dst, sizeof(*interface));
	vector_append(dst, (uint8)interface);
};

// vector_write function, which writes the length and the content
void vector_write(uint8* dst, uint8* content) {
	// Rust's Vec.len() returns usize, which is 4 on 32-bit
	// smart-contract-rs compiles wasm 32-bit
	uint32 size = vector_len(content);

	// Grow the array to have the length and the body
	vector_grow(dst, vector_len(content) + sizeof(uint32));

	// Write the size header
	vector_append(dst, (uint8)&size);

	// Write the body
	for (int i = 0; i < vector_len(content); i++) {
		vector_append(dst, content[i]);
	};
};

int _atoi(uint8* string) {
	int n;
	for (int i = 0; i < vector_len(string); i++) {
		string[i] -= '0';
		if (string[i] > 9) {
			return n;
		}

		n = n*10 + (int)string[i];
	};

	return n;
};
