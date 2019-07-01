#include "vector.h"
#include "wasm.h"
#include "types.h"
#include "utils.h"

enum TransactionTag{TagNop, TagTransfer, TagContract, TagStake};

struct Transfer {
	uint8  destination[32];
	uint64 amount;

	uint8* func_name;
	uint8* func_params;
};

struct Transfer* transfer_read_from(uint8* buf, uint64* needle) {
	struct Transfer* t;

	// Read the destionation
	for (int i = 0; i < 32; i++) {
		t->destination[i] = buf[i + *needle];
	};

	// Move the pointer over the destination
	*needle += 32;

	// Read the amount
	uint8* amount = _read(buf, needle, sizeof(uint64));
	t->amount = (uint64)amount;

	// Read the gas limit
	if (*needle < vector_len(buf)) {
		// Apparently you do nothing with this?
		_read(buf, needle, sizeof(uint64));
	}

	if (*needle < vector_len(buf)) {
		t->func_name = _read(buf, needle, sizeof(uint64));
	}

	if (*needle < vector_len(buf)) {
		t->func_params = _read(buf, needle, sizeof(uint64));
	}

	return t;
};

void transfer_write_to(struct Transfer* t, uint8* buf) {
	// Grow the buffer array to be as large as [32]uint8
	vector_grow(buf, sizeof(uint8) * 32);

	// Write the destination
	for (int i = 0; i < 32; i++) {
		vector_append(buf, t->destination[i]);
	};

	// Write the amount
	vector_resize(buf, vector_len(buf) + 4);
	vector_append(buf, (char)&t->amount);

	// If func_name and func_params is not empty
	if (vector_len(t->func_name) > 0 && vector_len(t->func_params) > 0) {
		int name_len = vector_len(t->func_name);
		int params_len = vector_len(t->func_params);

		// Grow the array to be as large as both the name and params
		vector_resize(buf, vector_len(buf) + name_len + params_len);

		for (int i = 0; i < name_len; i++) {
			vector_write(buf, t->func_name);
		};

		for (int i = 0; i < params_len; i++) {
			vector_append(buf, t->func_params[i]);
		};
	};
};

enum TransactionTag transfer_tag(struct Transfer* t) {
	return TagTransfer;
};

void transfer_send_transaction(struct Transfer* t) {
	uint8* payload = NULL;
	transfer_write_to(t, payload);

	_send_transaction(transfer_tag(t), (char*)payload, vector_len(payload));

	// bruh moment
	vector_free(payload);
};
