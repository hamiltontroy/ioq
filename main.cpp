/*
	here is a description of the below function call;
	
	io_queue is an object that abstracts away asynchronous io.
	this call tells the io_queue object to register a read.
	
	fd is a file description that supports the read() system call.
	
	MAX_COUNT is an integer that caps size of the internal vector buffer
	 which will hold the bytes read from fd.
	 
	callback_function is a function which will be called when the io
	 operation finishes. This function will be executed in whatever
	 thread of execution calls it.
	
	callback_args is a struct which will hold the additional arguments that
	 the callback function will take.
*/
// side_read(io_queue, fd, MAX_COUNT, callback_function, callback_args);

/*
	side_read will add a job to the io_queue;
	a thread running a loop will "scan" the io_queue for
	if a job is ready.
	
	if a job is ready, io_queue will return a struct to the
	calling thread which will allow the calling thread to
	 then look through the struct and pass arguments to whatever
	 function is referenced in the struct, and call the referenced
	 function.
*/

struct callback_args
{
	// this will contain any further arguments for the callback function
};

// note, only the 23 bytes of metadata for vectors are copied.
// the actual internal buffer for the vectors is uncopied
void callback(int fd, std::vector<std::byte> buffer, struct callback_args args = {})
{
	// this function is going to do processing on the buffer or something
}

// example program

struct callback_args
{
	// this will contain any further arguments for the callback function
};

// a function which may or may not want any further arguments
void callback(int fd, std::vector<std::byte> buffer, struct callback_args args = {})
{
	// this function is going to do processing on the buffer or something
}

// there should only be one io_medium per program.
// it can be defined globally, or inside main() it does not matter.
ioq::io_medium medium;

int main()
{
	// do file opening and checking
	// get file descriptor
	
	int fd;
	// assign fd the files' file descriptor
	const int MAX_COUNT = 8192;
	
	// notice how there is no callback args argument?
	// that is because sometimes one is not needed.
	side_read(medium, fd, MAX_COUNT, callback);
	
	// at this point, the os has started a read on the
	// file descriptor. Once the read is complete, a
	// procedure can occur where the callback function
	// can be called.
	
	// now run a loop to check if an io operation has finished
	// and if one has, lets execute the callback function for the finished job.
	
	while(1)
	{
		bool is_ready = medium.ready();
		if(is_ready == false)
			continue;
		
		is_ready = false; // reset the flag.
		
		// get the next ready job
		struct work_info job_info;
		job_info = medium.get_work();
		
		// check if there was an io failure on the job
		bool io_failed = io_failure(job_info);
		if(io_failed == true)
			continue;
		
		do_work(job_info); // does whatever job is inside of job_info		
		// do_work in this scenario program will call the function called callback().
	}
	
}