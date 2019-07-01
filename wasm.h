// These functions are injected at contract upload time into the wasm.
// https://github.com/perlin-network/wavelet/blob/master/contract.go#L71
unsigned long _payload_len();
void _payload(char* out);
void _log(char* content, unsigned long len);
void _result(char* result, unsigned long len);
void _send_transaction(
	char tag, 
	char* payload, 
	unsigned long payload_len
);
long _verify_ed25519(
	char* pubkey, unsigned long pubkey_len,
	char* data,   unsigned long data_len,
	char* sig,    unsigned long sig_len
);
long _hash_blake2b_256(
	char* data, unsigned long data_len,
	char* out,  unsigned long out_len
);
long _hash_blake2b_512(
	char* data, unsigned long data_len,
	char* out,  unsigned long out_len
);
long _hash_sha256(
	char* data, unsigned long data_len,
	char* out,  unsigned long out_len
);
long _hash_sha512(
	char* data, unsigned long data_len,
	char* out,  unsigned long out_len
);
