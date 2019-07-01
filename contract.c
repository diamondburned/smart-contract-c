#include "types.h"
#include "vector.h"
#include "utils.h"

struct Contract {
	uint8* payload;
	uint8* code;
};

void contract_write_to(struct Contract* c, uint8* buf) {
	// Write a zero gas fee
	vector_append(buf, (uint64)0);

	vector_write(buf, c->payload);
	vector_write(buf, c->code);
};

struct Contract* contract_read_from(uint8* buf, uint64* pos) {
	struct Contract* c = NULL;
	c->payload = vector_read(buf, pos, sizeof(uint8));
	c->code = vector_read(buf, pos, sizeof(uint8));

	return c;
};

