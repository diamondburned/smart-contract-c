#include "types.h"
#include "wasm.h"
#include "vector.h"
#include "utils.h"

struct Parameters {
	uint64 round_idx;
	uint8  round_id[32];
	uint8  transaction_id[32];
	uint8  sender[32];
	uint64 amount;
};

struct Parameters* parameters_load() {
	int payload_len = _payload_len();
	uint8* payload_bytes;
	vector_grow(payload_bytes, payload_len);

	_payload((char*)payload_bytes);

	struct Parameters* p = NULL;
	uint64* ptr = 0;

	p->round_idx = readuint64(payload_bytes, ptr);
	p->round_id = vector_read(payload_bytes, ptr, 32 * sizeof(uint8));
	p->transaction_id = vector_read(payload_bytes, ptr, 32 * sizeof(uint8))
}
