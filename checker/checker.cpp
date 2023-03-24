#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
	registerChecker("cat", argc, argv);
	compareRemainingLines();
}
