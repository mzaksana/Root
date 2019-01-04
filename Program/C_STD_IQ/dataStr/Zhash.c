/*
* 
*
* Writer: Muammar Zikri Aksana
*/

/* This is a collection of programs that computes the CRC-32 checksum.
Probably only the first three, and maybe the fourth (CRC32d) are of any
interest. The others are just experiments that did not result in
anything useful. More comments are at the bottom of this file. */

// ---------------------------- reverse --------------------------------

// Reverses (reflects) bits in a 32-bit word.
unsigned reverse(unsigned x)
{
	x = ((x & 0x55555555) << 1) | ((x >> 1) & 0x55555555);
	x = ((x & 0x33333333) << 2) | ((x >> 2) & 0x33333333);
	x = ((x & 0x0F0F0F0F) << 4) | ((x >> 4) & 0x0F0F0F0F);
	x = (x << 24) | ((x & 0xFF00) << 8) |
	    ((x >> 8) & 0xFF00) | (x >> 24);
	if (x < 0)
		x *= -1;
	return x;
}

// ----------------------------- crc32a --------------------------------

/* This is the basic CRC algorithm with no optimizations. It follows the
logic circuit as closely as possible. */

unsigned int crc32a(char *message)
{
	int i, j;
	unsigned int byte, crc;

	i = 0;
	crc = 0xFFFFFFFF;
	while (message[i] != 0)
	{
		byte = message[i];    // Get next byte.
		byte = reverse(byte); // 32-bit reversal.
		for (j = 0; j <= 7; j++)
		{ // Do eight times.
			if ((int)(crc ^ byte) < 0)
				crc = (crc << 1) ^ 0x04C11DB7;
			else
				crc = crc << 1;
			byte = byte << 1; // Ready next msg bit.
		}
		i = i + 1;
	}
	return reverse(~crc);
}

/* The code above computes, in several ways, the cyclic redundancy check
usually referred to as CRC-32. This code is used by IEEE-802 (LAN/MAN
standard), PKZip, WinZip, Ethernet, and some DOD applications.

I investigated this because an early reviewer of Hacker's Delight
suggested that I might try to find some trick to speed up the
calculation of the CRC checksum. I have tried and don't see any way to
speed it up, over the standard table lookup method, which does one table
lookup per byte of message. The table size is 256 32-bit words. One
could do two bytes at a time with a table of size 65536 words, but
that's not very interesting. Not interesting, but maybe useful on a
machine with a large data cache, so the code is shown above.

This file contains eight routines for doing the CRC-32 calculation, and
a simple test driver main program.

For references, there are a few web sites, and the book "Numerical
Recipes in Fortran, The Art of Scientific Computing," by William H.
Press, Saul A. Teukolsky, William T. Vetterling, and Brian P. Flannery,
Cambridge University Press, 1992 (2nd ed.), pps 888-894.

Another book reference is "Computer Networks," by Andrew S. Tanenbaum,
second edition, pages 208-212.

Another reference, which serves as a good introduction to the subject,
and which I found very well-written and interesting, is:

Peterson, W.W. and Brown, D.T. "Cyclic Codes for Error Detection." In
Proceedings of the IRE, January 1961, 228-235.

The web site http://www.ciphersbyritter.com/ARTS/CRCMYST.HTM by Terry
Ritter is a good intro. This material also appeared as "The Great CRC
Mystery," in Dr. Dobb's Journal of Software Tools, February 1986, 26-34
and 76-83. He gives several more references.

There are other programs for computing CRC-32 at the PC Magazine web
site http://www.createwindow.com/programming/crc32/.

This code is not in Hacker's Delight, although a few of the simpler
programs may be included in a future edition. */

//###############################################################################3
// MORE hash function

// size_t precision = 2; //change the precision with this
// size_t hash(const char *str)
// {
// 	return (*(size_t *)str) >> precision;
// }

// unsigned hashZ(char *str)
// {
// 	unsigned hash = 5381;
// 	int c;

// 	while (c = *str++)
// 		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

// 	return hash;
// }

#include <stdint.h>

#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && \
    __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define _le64toh(x) ((uint64_t)(x))
#elif defined(_WIN32)
/* Windows is always little endian, unless you're on xbox360
   http://msdn.microsoft.com/en-us/library/b0084kay(v=vs.80).aspx */
#define _le64toh(x) ((uint64_t)(x))
#elif defined(__APPLE__)
#include <libkern/OSByteOrder.h>
#define _le64toh(x) OSSwapLittleToHostInt64(x)
#else

/* See: http://sourceforge.net/p/predef/wiki/Endianness/ */
#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
#include <sys/endian.h>
#else
#include <endian.h>
#endif
#if defined(__BYTE_ORDER) && defined(__LITTLE_ENDIAN) && \
    __BYTE_ORDER == __LITTLE_ENDIAN
#define _le64toh(x) ((uint64_t)(x))
#else
#define _le64toh(x) le64toh(x)
#endif

#endif

#define ROTATE(x, b) (uint64_t)(((x) << (b)) | ((x) >> (64 - (b))))

#define HALF_ROUND(a, b, c, d, s, t) \
	a += b;                         \
	c += d;                         \
	b = ROTATE(b, s) ^ a;           \
	d = ROTATE(d, t) ^ c;           \
	a = ROTATE(a, 32);

#define DOUBLE_ROUND(v0, v1, v2, v3)     \
	HALF_ROUND(v0, v1, v2, v3, 13, 16); \
	HALF_ROUND(v2, v1, v0, v3, 17, 21); \
	HALF_ROUND(v0, v1, v2, v3, 13, 16); \
	HALF_ROUND(v2, v1, v0, v3, 17, 21);

uint64_t siphash24(const void *src, unsigned long src_sz, const char key[16])
{
	const uint64_t *_key = (uint64_t *)key;
	uint64_t k0 = _le64toh(_key[0]);
	uint64_t k1 = _le64toh(_key[1]);
	uint64_t b = (uint64_t)src_sz << 56;
	const uint64_t *in = (uint64_t *)src;

	uint64_t v0 = k0 ^ 0x736f6d6570736575ULL;
	uint64_t v1 = k1 ^ 0x646f72616e646f6dULL;
	uint64_t v2 = k0 ^ 0x6c7967656e657261ULL;
	uint64_t v3 = k1 ^ 0x7465646279746573ULL;

	while (src_sz >= 8)
	{
		uint64_t mi = _le64toh(*in);
		in += 1;
		src_sz -= 8;
		v3 ^= mi;
		DOUBLE_ROUND(v0, v1, v2, v3);
		v0 ^= mi;
	}

	uint64_t t = 0;
	uint8_t *pt = (uint8_t *)&t;
	uint8_t *m = (uint8_t *)in;
	switch (src_sz)
	{
	case 7:
		pt[6] = m[6];
	case 6:
		pt[5] = m[5];
	case 5:
		pt[4] = m[4];
	case 4:
		*((uint32_t *)&pt[0]) = *((uint32_t *)&m[0]);
		break;
	case 3:
		pt[2] = m[2];
	case 2:
		pt[1] = m[1];
	case 1:
		pt[0] = m[0];
	}
	b |= _le64toh(t);

	v3 ^= b;
	DOUBLE_ROUND(v0, v1, v2, v3);
	v0 ^= b;
	v2 ^= 0xff;
	DOUBLE_ROUND(v0, v1, v2, v3);
	DOUBLE_ROUND(v0, v1, v2, v3);
	return (v0 ^ v1) ^ (v2 ^ v3);
}