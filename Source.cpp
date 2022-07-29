#include "Calculator.h"

const string SERVER = "";
const string NAME = "";
const string PASSWORD = "";
int main()
{
	Calculator G(SERVER, NAME, PASSWORD);
	G.run();
	return 0;
}