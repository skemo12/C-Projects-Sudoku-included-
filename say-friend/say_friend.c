#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>

#define AES_BLOCK_SIZE	16

static void print_hex(const unsigned char *msg, size_t len)
{
	size_t i;

	for (i = 0; i < len; i++)
		printf("\\x%02x", msg[i]);
}

static const unsigned char enc[] = "\x39\x08\xe4\xbf\xb4\x13\x82\x54\x03\x98\xc9\x8e\xbc\x1b\x30\x65\xe4\x26\xea\x7b\x9c\x1e\xfb\x46\x5d\xa3\xc5\xa9\x46\x75\x8b\xc0";

int main(void)
{
	char key_buf[32];
	unsigned char *in;
	unsigned char *key;
	AES_KEY enc_key;
	size_t in_size, key_size;
	unsigned char *out;
	size_t i;

	printf("Say friend and enter: ");
	fgets(key_buf, 32, stdin);
	if (key_buf[strlen(key_buf)-1] == '\n')
		key_buf[strlen(key_buf)-1] = '\0';

	in_size = (sizeof(enc) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
	if (in_size < sizeof(enc))
		in_size += AES_BLOCK_SIZE;
	key_size = (strlen(key_buf) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
	if (key_size < strlen(key_buf))
		key_size += AES_BLOCK_SIZE;

	in = malloc(in_size);
	key = malloc(key_size);
	out = malloc(in_size);
	memset(in, 0, in_size);
	memset(key, 0, key_size);
	memset(out, 0, key_size);
	memcpy(in, enc, sizeof(enc));
	memcpy(key, key_buf, strlen(key_buf));

	AES_set_decrypt_key(key, key_size * 8, &enc_key);
	for (i = 0; i < in_size; i += AES_BLOCK_SIZE)
		AES_decrypt(in+i, out+i, &enc_key);

	print_hex(out, in_size);
	puts("");

	return 0;
}
