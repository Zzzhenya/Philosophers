# Modified version of Edsger Dijkstra's Dining philosophers problem


## Compile and run


	cd philo && make

	./philo 



## FAQ ( Asked by me from myself )

1) Why mutex for printing to stdout?

	To print action timestamps in order of calling printf. printf is a threadsafe reentrant function. A mutex to print to stdout helps to keep the stdout print requests to printf in a queue.


2) Why a mutex for is_alive == true check (philo->mtx_status) before each routine cycle and before each print ? 

	To stop as soon as the monitor updates the status of the thread, without printing any
	messages that occur within the same milli second but after the philo is killed.

3) Why update_ready from main process and check_ready from all threads before starting the cyclic routine?

	To make sure all threads are already created in order to start simultaneously. We don't have control over how much time the kernal would take to create threads. Without a ready flag, some threads may take a long time to get created, by which time the monitor may assume the thread is already hungry based on the recorded start time.


4) Why are return values of mutex_lock and mutex_unlock functions not caught and checked to handle errors? 

	I don't know how to handle this with current scope/allowed functions. If a mutex_lock or unlock function returns an error there must be something seriously wrong with the kernal or hardware.


5) Why the input configuration 50 410 200 200 fail on a computer that has 8 cores (16 threads) (e.g. Core i7 vPro)?

	A computer with 8 cores can run upto a maximum of 16 threads concurrently. With the odd-even logic, for the 50 philosophers configuration with 410 life-time, for philosophers to not strave to death, at least 25 threads should to run concurrently. The kernal schedules maximum of random 16 (usually less than 16) threads first and the the other 9 threads wait until the kernal schedules them. Because the life-time defined for the configuration is too low, the monitor detects them as hungry and kill the threads to terminate the simulation. 

	In such a computer, 410 200 200 configuration could safely work upto 20 philosophers (where no. of philosophers is an even number and there are no other resource intensive processes running in parallel).


6) Why a custom sleep function is used without passing the converted milliseconds to usleep(usec)?

	usleep function from unistd.h only gurantees to suspends the calling thread for at least usec microseconds. There is no gurantee that the suspension would not be more than this. In addition to this, if usec is greater than or equal to 1000000 the behaviour of the function( whether it returns EINVAL) is system dependant. Therefore a cyclic 500 microsecond usleep against the start time is used to suspend the thread.


7) Fork status mutexes locked for the duration of eating vs. fork status mutexes locked and released when checking/updating the fork status (spin lock). What are the costs?

	While one thread has locked a shared resource/ critical section protected by a mutex, if the other threads require to lock the resource at the same time, the other threads are blocked and stay in waiting. Blocked threads are sent to sleep by the kernal. As soon as the thread that has already aquired the mutex unlocks it, the kernal wakes a waiting thread which aquires the mutex lock. 

	When multiple threads are trying to acquire the same mutex lock, the time taken to sending to sleep and waking up threads can add up and significantly slow down the task.

	On the other hand, if multiple threads are locking and unlocking a mutex to check/update the status of critical section in a loop, the thread will be active and waste CPU cycles.

