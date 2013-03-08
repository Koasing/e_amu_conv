/*
 Class "CardUtil" : Convert NFC-V TagID to Human-readable code
                    Useful for "e-Amusement" service.

 NO ONE PROVIDES WARRANTY.
 Use this software AT YOUR OWN RISK.

 This software is ABSOLUTELY free.
 If you paid money, please contact seller to get refund.

 If you use this software as a part of commercial product,
 please provide free download link for this software.
 */
#include "CardUtil.h"

/* STATIC ARRAYS INITIALIZATION */
const char * const CardUtil::m_str = "0123456789ABCDEFGHJKLMNPRSTUWXYZ"; // 32 chars. I, O, Q, V skipped.

const unsigned int CardUtil::m_table0_0[64] = {
	0x02080008, 0x02082000, 0x00002008, 0x00000000, 0x02002000, 0x00080008, 0x02080000, 0x02082008,
	0x00000008, 0x02000000, 0x00082000, 0x00002008, 0x00082008, 0x02002008, 0x02000008, 0x02080000,
	0x00002000, 0x00082008, 0x00080008, 0x02002000, 0x02082008, 0x02000008, 0x00000000, 0x00082000,
	0x02000000, 0x00080000, 0x02002008, 0x02080008, 0x00080000, 0x00002000, 0x02082000, 0x00000008,
	0x00080000, 0x00002000, 0x02000008, 0x02082008, 0x00002008, 0x02000000, 0x00000000, 0x00082000,
	0x02080008, 0x02002008, 0x02002000, 0x00080008, 0x02082000, 0x00000008, 0x00080008, 0x02002000,
	0x02082008, 0x00080000, 0x02080000, 0x02000008, 0x00082000, 0x00002008, 0x02002008, 0x02080000,
	0x00000008, 0x02082000, 0x00082008, 0x00000000, 0x02000000, 0x02080008, 0x00002000, 0x00082008
};
const unsigned int CardUtil::m_table0_1[64] = {
	0x08000004, 0x00020004, 0x00000000, 0x08020200, 0x00020004, 0x00000200, 0x08000204, 0x00020000,
	0x00000204, 0x08020204, 0x00020200, 0x08000000, 0x08000200, 0x08000004, 0x08020000, 0x00020204,
	0x00020000, 0x08000204, 0x08020004, 0x00000000, 0x00000200, 0x00000004, 0x08020200, 0x08020004,
	0x08020204, 0x08020000, 0x08000000, 0x00000204, 0x00000004, 0x00020200, 0x00020204, 0x08000200,
	0x00000204, 0x08000000, 0x08000200, 0x00020204, 0x08020200, 0x00020004, 0x00000000, 0x08000200,
	0x08000000, 0x00000200, 0x08020004, 0x00020000, 0x00020004, 0x08020204, 0x00020200, 0x00000004,
	0x08020204, 0x00020200, 0x00020000, 0x08000204, 0x08000004, 0x08020000, 0x00020204, 0x00000000,
	0x00000200, 0x08000004, 0x08000204, 0x08020200, 0x08020000, 0x00000204, 0x00000004, 0x08020004
};
const unsigned int CardUtil::m_table0_2[64] = {
	0x80040100, 0x01000100, 0x80000000, 0x81040100, 0x00000000, 0x01040000, 0x81000100, 0x80040000,
	0x01040100, 0x81000000, 0x01000000, 0x80000100, 0x81000000, 0x80040100, 0x00040000, 0x01000000,
	0x81040000, 0x00040100, 0x00000100, 0x80000000, 0x00040100, 0x81000100, 0x01040000, 0x00000100,
	0x80000100, 0x00000000, 0x80040000, 0x01040100, 0x01000100, 0x81040000, 0x81040100, 0x00040000,
	0x81040000, 0x80000100, 0x00040000, 0x81000000, 0x00040100, 0x01000100, 0x80000000, 0x01040000,
	0x81000100, 0x00000000, 0x00000100, 0x80040000, 0x00000000, 0x81040000, 0x01040100, 0x00000100,
	0x01000000, 0x81040100, 0x80040100, 0x00040000, 0x81040100, 0x80000000, 0x01000100, 0x80040100,
	0x80040000, 0x00040100, 0x01040000, 0x81000100, 0x80000100, 0x01000000, 0x81000000, 0x01040100
};
const unsigned int CardUtil::m_table0_3[64] = {
	0x04010801, 0x00000000, 0x00010800, 0x04010000, 0x04000001, 0x00000801, 0x04000800, 0x00010800,
	0x00000800, 0x04010001, 0x00000001, 0x04000800, 0x00010001, 0x04010800, 0x04010000, 0x00000001,
	0x00010000, 0x04000801, 0x04010001, 0x00000800, 0x00010801, 0x04000000, 0x00000000, 0x00010001,
	0x04000801, 0x00010801, 0x04010800, 0x04000001, 0x04000000, 0x00010000, 0x00000801, 0x04010801,
	0x00010001, 0x04010800, 0x04000800, 0x00010801, 0x04010801, 0x00010001, 0x04000001, 0x00000000,
	0x04000000, 0x00000801, 0x00010000, 0x04010001, 0x00000800, 0x04000000, 0x00010801, 0x04000801,
	0x04010800, 0x00000800, 0x00000000, 0x04000001, 0x00000001, 0x04010801, 0x00010800, 0x04010000,
	0x04010001, 0x00010000, 0x00000801, 0x04000800, 0x04000801, 0x00000001, 0x04010000, 0x00010800
};
const unsigned int CardUtil::m_table0_4[64] = {
	0x00000400, 0x00000020, 0x00100020, 0x40100000, 0x40100420, 0x40000400, 0x00000420, 0x00000000,
	0x00100000, 0x40100020, 0x40000020, 0x00100400, 0x40000000, 0x00100420, 0x00100400, 0x40000020,
	0x40100020, 0x00000400, 0x40000400, 0x40100420, 0x00000000, 0x00100020, 0x40100000, 0x00000420,
	0x40100400, 0x40000420, 0x00100420, 0x40000000, 0x40000420, 0x40100400, 0x00000020, 0x00100000,
	0x40000420, 0x00100400, 0x40100400, 0x40000020, 0x00000400, 0x00000020, 0x00100000, 0x40100400,
	0x40100020, 0x40000420, 0x00000420, 0x00000000, 0x00000020, 0x40100000, 0x40000000, 0x00100020,
	0x00000000, 0x40100020, 0x00100020, 0x00000420, 0x40000020, 0x00000400, 0x40100420, 0x00100000,
	0x00100420, 0x40000000, 0x40000400, 0x40100420, 0x40100000, 0x00100420, 0x00100400, 0x40000400
};
const unsigned int CardUtil::m_table0_5[64] = {
	0x00800000, 0x00001000, 0x00000040, 0x00801042, 0x00801002, 0x00800040, 0x00001042, 0x00801000,
	0x00001000, 0x00000002, 0x00800002, 0x00001040, 0x00800042, 0x00801002, 0x00801040, 0x00000000,
	0x00001040, 0x00800000, 0x00001002, 0x00000042, 0x00800040, 0x00001042, 0x00000000, 0x00800002,
	0x00000002, 0x00800042, 0x00801042, 0x00001002, 0x00801000, 0x00000040, 0x00000042, 0x00801040,
	0x00801040, 0x00800042, 0x00001002, 0x00801000, 0x00001000, 0x00000002, 0x00800002, 0x00800040,
	0x00800000, 0x00001040, 0x00801042, 0x00000000, 0x00001042, 0x00800000, 0x00000040, 0x00001002,
	0x00800042, 0x00000040, 0x00000000, 0x00801042, 0x00801002, 0x00801040, 0x00000042, 0x00001000,
	0x00001040, 0x00801002, 0x00800040, 0x00000042, 0x00000002, 0x00001042, 0x00801000, 0x00800002
};
const unsigned int CardUtil::m_table0_6[64] = {
	0x10400000, 0x00404010, 0x00000010, 0x10400010, 0x10004000, 0x00400000, 0x10400010, 0x00004010,
	0x00400010, 0x00004000, 0x00404000, 0x10000000, 0x10404010, 0x10000010, 0x10000000, 0x10404000,
	0x00000000, 0x10004000, 0x00404010, 0x00000010, 0x10000010, 0x10404010, 0x00004000, 0x10400000,
	0x10404000, 0x00400010, 0x10004010, 0x00404000, 0x00004010, 0x00000000, 0x00400000, 0x10004010,
	0x00404010, 0x00000010, 0x10000000, 0x00004000, 0x10000010, 0x10004000, 0x00404000, 0x10400010,
	0x00000000, 0x00404010, 0x00004010, 0x10404000, 0x10004000, 0x00400000, 0x10404010, 0x10000000,
	0x10004010, 0x10400000, 0x00400000, 0x10404010, 0x00004000, 0x00400010, 0x10400010, 0x00004010,
	0x00400010, 0x00000000, 0x10404000, 0x10000010, 0x10400000, 0x10004010, 0x00000010, 0x00404000
};
const unsigned int CardUtil::m_table0_7[64] = {
	0x00208080, 0x00008000, 0x20200000, 0x20208080, 0x00200000, 0x20008080, 0x20008000, 0x20200000,
	0x20008080, 0x00208080, 0x00208000, 0x20000080, 0x20200080, 0x00200000, 0x00000000, 0x20008000,
	0x00008000, 0x20000000, 0x00200080, 0x00008080, 0x20208080, 0x00208000, 0x20000080, 0x00200080,
	0x20000000, 0x00000080, 0x00008080, 0x20208000, 0x00000080, 0x20200080, 0x20208000, 0x00000000,
	0x00000000, 0x20208080, 0x00200080, 0x20008000, 0x00208080, 0x00008000, 0x20000080, 0x00200080,
	0x20208000, 0x00000080, 0x00008080, 0x20200000, 0x20008080, 0x20000000, 0x20200000, 0x00208000,
	0x20208080, 0x00008080, 0x00208000, 0x20200080, 0x00200000, 0x20000080, 0x20008000, 0x00000000,
	0x00008000, 0x00200000, 0x20200080, 0x00208080, 0x20000000, 0x20208000, 0x00000080, 0x20008080
};

const unsigned int CardUtil::m_table1[3][32] =
{
	{
		0x20d0d03c, 0x868ecb41, 0xbcd89c84, 0x4c0e0d0d, 0x84fc30ac, 0x4cc1890e, 0xfc5418a4, 0x02c50f44,
		0x68acb4e0, 0x06cd4a4e, 0xcc28906c, 0x4f0c8ac0, 0xb03ca468, 0x884ac7c4, 0x389490d8, 0xcf80c6c2,
		0x58d87404, 0xc48ec444, 0xb4e83c50, 0x498d0147, 0x64f454c0, 0x4c4701c8, 0xec302cc4, 0xc6c949c1,
		0xc84c00f0, 0xcdcc49cc, 0x883c5cf4, 0x8b0fcb80, 0x703cc0b0, 0xcb820a8d, 0x78804c8c, 0x4fca830e
	},
	{
		0x80d0f03c, 0x8ec84f8c, 0x98c89c4c, 0xc80d878f, 0x54bc949c, 0xc801c5ce, 0x749078dc, 0xc3c80d46,
		0x2c8070f0, 0x0cce4dcf, 0x8c3874e4, 0x8d448ac3, 0x987cac70, 0xc0c20ac5, 0x288cfc78, 0xc28543c8,
		0x4c8c7434, 0xc50e4f8d, 0x8468f4b4, 0xcb4a0307, 0x2854dc98, 0x48430b45, 0x6858fce8, 0x4681cd49,
		0xd04808ec, 0x458d0fcb, 0xe0a48ce4, 0x880f8fce, 0x7434b8fc, 0xce080a8e, 0x5860fc6c, 0x46c886cc
	},
	{
		0xd01098a4, 0xce090b8c, 0x1044cc2c, 0x86898e0f, 0xd0809c3c, 0x4a05860f, 0x54b4f80c, 0x4008870e,
		0x1480b88c, 0x0ac8854f, 0x1c9034cc, 0x08444c4e, 0x0cb83c64, 0x41c08cc6, 0x1c083460, 0xc0c603ce,
		0x2ca0645c, 0x818246cb, 0x0408e454, 0xc5464487, 0x88607c18, 0xc1424187, 0x284c7c90, 0xc1030509,
		0x40486c94, 0x4603494b, 0xe0404ce4, 0x4109094d, 0x60443ce4, 0x4c0b8b8d, 0xe054e8bc, 0x02008e89
	}
};

inline unsigned int ROR32(unsigned int t, unsigned char s)
{
	// Rotate Right 32bit. or "Circular Shift Right"
	return (t << (32 - s)) | (t >> s);
}
inline unsigned int ROL32(unsigned int t, unsigned char s)
{
	// Rotate Left 32bit. or "Circular Shift Left"
	return (t << s) | (t >> (32 - s));
}

void CardUtil::Calc(unsigned int *a, unsigned int *b, int mode)
{
	unsigned int temp;

	temp = ((*a >> 4) ^ *b) & 0x0F0F0F0F;
	*a ^= temp << 4;
	*b ^= temp;

	temp = (*b >> 16) ^ (*a & 0x0000FFFF);
	*b ^= temp << 16;
	*a ^= temp;

	temp = ((*a >> 2) ^ *b) & 0x33333333;
	*a ^= temp << 2;
	*b ^= temp;

	temp = ((*b >> 8) ^ *a) & 0x00FF00FF;
	*b ^= temp << 8;
	*a = ROR32(*a ^ temp, 1);

	temp = (*a ^ *b) & 0x55555555;
	*a ^= temp;
	*b = ROR32(*b ^ temp, 1);

	if(mode == 0 || mode == 2) {
		for(int pos = 2; pos <= 30; pos += 4) {
			temp = m_table1[mode][pos - 2] ^ *b;
			*a ^= m_table0_3[(temp >>  2) & 0x3F];
			*a ^= m_table0_2[(temp >> 10) & 0x3F];
			*a ^= m_table0_1[(temp >> 18) & 0x3F];
			*a ^= m_table0_0[(temp >> 26)       ];

			temp = ROL32(m_table1[mode][pos - 1] ^ *b, 4);
			*a ^= m_table0_7[(temp >>  2) & 0x3F];
			*a ^= m_table0_6[(temp >> 10) & 0x3F];
			*a ^= m_table0_5[(temp >> 18) & 0x3F];
			*a ^= m_table0_4[(temp >> 26)       ];

			temp = m_table1[mode][pos] ^ *a;
			*b ^= m_table0_3[(temp >>  2) & 0x3F];
			*b ^= m_table0_2[(temp >> 10) & 0x3F];
			*b ^= m_table0_1[(temp >> 18) & 0x3F];
			*b ^= m_table0_0[(temp >> 26)       ];

			temp = ROL32(m_table1[mode][pos + 1] ^ *a, 4);
			*b ^= m_table0_7[(temp >>  2) & 0x3F];
			*b ^= m_table0_6[(temp >> 10) & 0x3F];
			*b ^= m_table0_5[(temp >> 18) & 0x3F];
			*b ^= m_table0_4[(temp >> 26)       ];
		}
	}

	if(mode == 1) {
		for(int pos = 30; pos >= 2; pos -= 4) {
			temp = ROL32(m_table1[mode][pos + 1] ^ *b, 4);
			*a ^= m_table0_7[(temp >>  2) & 0x3F];
			*a ^= m_table0_6[(temp >> 10) & 0x3F];
			*a ^= m_table0_5[(temp >> 18) & 0x3F];
			*a ^= m_table0_4[(temp >> 26)       ];

			temp = m_table1[mode][pos] ^ *b;
			*a ^= m_table0_3[(temp >>  2) & 0x3F];
			*a ^= m_table0_2[(temp >> 10) & 0x3F];
			*a ^= m_table0_1[(temp >> 18) & 0x3F];
			*a ^= m_table0_0[(temp >> 26)       ];

			temp = ROL32(m_table1[mode][pos - 1] ^ *a, 4);
			*b ^= m_table0_7[(temp >>  2) & 0x3F];
			*b ^= m_table0_6[(temp >> 10) & 0x3F];
			*b ^= m_table0_5[(temp >> 18) & 0x3F];
			*b ^= m_table0_4[(temp >> 26)       ];

			temp = m_table1[mode][pos - 2] ^ *a;
			*b ^= m_table0_3[(temp >> 2) & 0x3F];
			*b ^= m_table0_2[(temp >> 10) & 0x3F];
			*b ^= m_table0_1[(temp >> 18) & 0x3F];
			*b ^= m_table0_0[(temp >> 26)       ];
		}
	}

	*a = ROL32(*a, 1);

	temp = (*a ^ *b) & 0x55555555;
	*a ^= temp;
	*b = ROL32(*b ^ temp, 1);

	temp = ((*a >> 8) ^ *b) & 0x00FF00FF;
	*a ^= temp << 8;
	*b ^= temp;

	temp = ((*b >> 2) ^ *a) & 0x33333333;
	*b ^= temp << 2;
	*a ^= temp;

	temp = (*a >> 16) ^ (*b & 0x0000FFFF);
	*a ^= temp << 16;
	*b ^= temp;

	temp = ((*b >> 4) ^ *a) & 0x0F0F0F0F;
	*b ^= temp << 4;
	*a ^= temp;

	return;
}

unsigned int parseUInt(const char *in)
{
	union { unsigned char c[4]; unsigned int i; } t;

	for(int i=0; i<4; i++) {
		char h = in[6-2*i], l = in[6-2*i+1];

		if('0' <= h && h <= '9') t.c[i] = h - '0';
		if('a' <= h && h <= 'F') t.c[i] = h - 'a' + 10;
		if('A' <= h && h <= 'F') t.c[i] = h - 'A' + 10;

		t.c[i] = t.c[i] << 4;

		if('0' <= l && l <= '9') t.c[i] |= l - '0';
		if('a' <= l && l <= 'F') t.c[i] |= l - 'a' + 10;
		if('A' <= l && l <= 'F') t.c[i] |= l - 'A' + 10;
	}

	return t.i;
}

void copyUIntToByteArray(const unsigned int in, unsigned char *out)
{
	union { unsigned char c[4]; unsigned int i; } t;

	t.i = in;
	out[0] = t.c[0];
	out[1] = t.c[1];
	out[2] = t.c[2];
	out[3] = t.c[3];

	return;
}

void CardUtil::Usercode(char *cardno)
{
	// Validation
	unsigned int high_bits = parseUInt(cardno);
	unsigned int low_bits  = parseUInt(cardno+8);
	if ((high_bits & 0xFFFF0000) != 0xE0040000) return;

	// Convert to Usercode
	Calc(&high_bits, &low_bits , 0);
	Calc(&low_bits , &high_bits, 1);
	Calc(&high_bits, &low_bits , 2);

	// Split 5 bit chunk
	unsigned char *bits = new unsigned char[8];
	copyUIntToByteArray(high_bits, bits  );
	copyUIntToByteArray(low_bits , bits+4);

	unsigned char *outputCode = new unsigned char[16];
	for(int i = 0; i < 16; i++) outputCode[i] = 0;

	for(int i = 0; i < 0x40; i++) {
		int currentPos = i / 5;
		unsigned char currentBit = (bits[i >> 3] >> (7 - (i & 0x07))) & 0x01;
		outputCode[currentPos] |= currentBit << (currentPos * 5 - i + 4);
	}

	// Xor encode
	outputCode[13] = 1;
	outputCode[0] ^= 1;
	for(int i=1; i<14; i++) outputCode[i] ^= outputCode[i-1];

	// Checksum
	outputCode[14] = 1;
	unsigned int checksum = 0;

	for(int i=0; i<15; i++) checksum += outputCode[i] * ((i - (i / 3) * 3) + 1);
	while (checksum > 0x1f) checksum = (checksum & 0x1f) + (checksum >> 5);

	outputCode[15] = (unsigned char)checksum;    // 16th code : checksum

	// convert to human-readable code
	for(int i=0; i<16; i++) cardno[i] = m_str[outputCode[i]];
	cardno[16] = 0;

	// Cleanup
	delete[] bits;
	delete[] outputCode;

	return;
}
