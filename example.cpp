#include "ioq.hpp" // used for asynchronous io
#include "tcp.h" // used for tcp abstractions

#include "ioq.cpp"
#include "tcp.c"

#include <cstdio>

// a very simple callback function which takes
// a file descriptor
// a malloc() buffer and the len
void callback(int fd, void* buf, int len)
{
	/*
		example function which performs some kind
		of processing on the buffer.
	*/
	
	// lets say the buffer did not read in enough,
	// or something else happened
	
	// the function can re-register itself, and
	// can also pass in a pointer to where the old
	// buffer started, and the presize of the buffer
	if(error == true)
		nonseq_read(fd, buf, len, len + 8192, callback);
	
	// finish processing
	
	free(buf);
}


int main()
{	
	int tcp_lifd = make_tcp_listener(80); // make a listening socket on port 80
	if(tcp_lifd == -1)
	{
		printf("error allocating listening socket\n");
		return -1;
	}
	
	const int max = 8192;
	
	while(1)
	{
		int client_fd = wait_for_connection(tcp_lifd); // waits for a client conn
		
		nonseq_read(client_fd, max, callback); // queues a read, and callback
	}
}

/*
	special notes:
	if nonseq_read detects that an error occurred with the read,
	it will automatically free the buffer it is using to read into.
	if it detects an error, it will still call the callback function,
	but pass NULL into the buf argument, and will pass 0 in the len.
*/
