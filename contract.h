#include "types.h"

struct Contract;
void contract_write_to(struct Contract* c, uint8* buf);
struct Contract* contract_read_from(uint8* buf, uint64* pos);
