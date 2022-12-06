#include <unistd.h>

int main(){
	// 1 = descriptorul stdout folosit de printf
	write(1, "Hello World\n", 12);
	
	return 0;}
