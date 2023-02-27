/*
	main operations are reading and writing on 
	file descriptors.
	
	when an io operation completes a callback function
	can be called.
	
	The callback function can take the 
	basic: (file descriptor, buffer, buflen) combo.
	
	ex:
	void callback(int fd, void* buffer, int buflen);
	
	the super low level stuff will be written in C,
	and the typical C++ stuff will come with useful
	function overloads.
	
	coread(int fd, void (*callback)(int, void*, int), int max);
	
	cowrite(int fd, void* buf, int len, void (*callback)(int, void*, int));
	
	// what a callback will look like
	// void callback(int fd, void* buffer, int buflen);
	
	cowrite will write to a file descriptor, then call the callback with the
	normal parameters of (int, void*, int). if nothing else needs
	to be processed after the write, the callback will probably just
	be a free() wrapper.
*/

void coread(int, void (*)(int, void*, int), int);
//coread(int fd, void (*callback)(int, void*, int), int max);

void cowrite(int, void*, int, void (*)(int, void*, int));
//cowrite(int fd, void* buf, int len, void (*callback)(int, void*, int));

// what a callback will look like
// void callback(int fd, void* buffer, int buflen);