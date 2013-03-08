#include <iostream>
#include <string>
#include "CardUtil.h"

int main(int argc, char **argv)
{
	char *e = new char[17];
	memcpy(e, "E00401001234ABCD", 17);

	std::cout << " Hex Code : " << e << std::endl;

	CardUtil::Usercode(e);

	std::cout << "Card Code : " << e << std::endl;

	delete[] e;
	return 0;
}
