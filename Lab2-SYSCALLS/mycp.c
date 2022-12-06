#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>	// pt readonly, writeonly...
#include <errno.h>	// pt tratarea erorilor
#include <unistd.h>	// read, write, close

int main( int argc, char* argv[]){

	ssize_t ret_in, ret_out;
	char buffer[4096];
	
	if(argc != 3){
		perror("Numar de argumente invalid");
		return errno;
		}
		
	// deschid fisierul de input reading only
	int input = open(argv[1], O_RDONLY);
	if(input == -1){
		perror("Eroare la deschiderea fisierului de input");
		return errno;
		}
	
	//deschid fisierul de output write only/create daca nu exista
	int output = open(argv[2], O_WRONLY | O_CREAT, 0644);	//owner:R&W, other:R
	if (output == -1){
		perror("Eroare la deschiderea fisierului de output");
		return errno;
		}
		
	while((ret_in = read(input, &buffer, 4096))){
		ret_out = write(output, &buffer, (ssize_t) ret_in);
		//returneaza nr de bytes scrisi
		if (ret_out != ret_in){
			perror("Eroare la scrierea in fisierul de output");
			return errno;
			}
		}
	
	close(input);
	close(output);
	
	return 0;
}
