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

class CardUtil
{
public:
	static void Usercode(char *cardno);

protected:
	static const char * const m_str;

	static const unsigned int m_table0_0[64];
	static const unsigned int m_table0_1[64];
	static const unsigned int m_table0_2[64];
	static const unsigned int m_table0_3[64];
	static const unsigned int m_table0_4[64];
	static const unsigned int m_table0_5[64];
	static const unsigned int m_table0_6[64];
	static const unsigned int m_table0_7[64];
	static const unsigned int m_table1[3][32];

	static void Calc(unsigned int *arg1, unsigned int *arg2, int mode);
};
