#include <stdbool.h>
#include <stdlib.h>

struct vec {
	unsigned int capacity;
	unsigned int size;
	void **data;
};

int vector_new(struct vec *v) {
	void **data = calloc(2, sizeof(*data));
	if (!data) {
		return false;
	}

	v->capacity  = 2;
	v->size		 = 0;
	v->data		 = data;

	return true;
}

void vector_free(struct vec *v) {
	for (size_t i = 0; i < v->size; ++i) {
		free(v->data[i]);
	}

	free(v->data);
}

int vector_grow(struct vec* v, int size) {
	v->size += size;

	if (v->size >= v->capacity) {
		v->capacity += v->size - v->capacity;

		void **tmp = realloc(v->data, v->capacity * sizeof(*tmp));
		if (!tmp) {
			return false;
		}

		v->data = tmp;
	}

	return true;
}

int vector_append(struct vec* v, void* thing) {
	if (v->size >= v->capacity) {
		v->capacity *= 2;

		void **tmp = realloc(v->data, v->capacity * sizeof(*tmp));
		if (!tmp) {
			return 1;
		}

		v->data = tmp;
	}

	v->data[v->size++] = thing;
	return true;
}

unsigned int vector_len(struct vec* v) {
	return v->size;
}
