#include "scaraOS.h"

int main(int argc, char **argv)
{
	static const char * const hello_world = "Hello World!\n";

	if ( _write(STDOUT_FILENO, hello_world, strlen(hello_world)) <= 0 )
		return EXIT_FAILURE;
	_write(STDOUT_FILENO, (void *)0xdeadbeef, 20);

	switch(vfork()) {
	case -1:
		_write(STDOUT_FILENO, "Fork failed!\n", 13);
		break;
	case 0:
		break;
	default:
		_exec("/bin/cpuhog-b");
		return EXIT_FAILURE;
	}

	_exec("/bin/cpuhog-a");
	return EXIT_FAILURE;
}
