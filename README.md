# multithreading
Testing and Implementing Multithreading and Synchronization

Program Overview
The developed program manages a queuing system where customers and their service types are obtained from a text file. These customers are then placed in a dynamically allocated queue. The system includes four tellers who provide services to the customers based on their service types. A log file is created to record various information, including customer arrival time, response time, completion time, as well as teller information such as start time, termination time, and the total number of customers served.


Synchronization Mechanisms
To ensure proper synchronization and prevent race conditions or memory overwriting, the program implements the following synchronization mechanisms:
Mutex Lock: A Pthread Mutex lock is used to ensure mutual exclusion when accessing the shared resources, specifically the customer queue and the r_log file. The mutex lock ensures that only one thread can access these resources at a time, preventing 	conflicts and maintaining data integrity.
Condition Variable: A Pthread Condition variable is utilized for thread synchronization. It is employed in conjunction with the mutex lock to enable threads to wait for specific conditions to be met before proceeding. In this program, the condition variable is used to signal the teller threads to wake up and begin servicing 	customers when a customer enters the queue.


Thread Roles and Resource Access
The program involves multiple threads that access shared resources in a coordinated manner:
Customer Threads: Each customer thread accesses the customer queue to enqueue themselves. They acquire the mutex lock to ensure mutual exclusivity when accessing the shared queue. After enqueuing, he threads waits for a specific time interval before enqueuing the next customer. Additionally, the mutex lock is utilized when appending to the r_log file to avoid conflicts when multiple threads 	attempt to write to the file simultaneously.
Teller Threads: Teller threads access both the customer queue and the r_log file. They acquire the mutex lock to ensure exclusive 	access to these shared resources. The teller threads continuously check if there are any customers in the queue. If customers are present, a customer is dequeued from the queue, and the thread performs the required service based on the customer's service type. 	After completing the service, the thread appends the relevant information to the r_log file while holding the mutex lock.


Conclusion
In conclusion, the developed program successfully implements synchronization mechanisms using Pthread Mutex locks and Pthread Condition variables. These mechanisms ensure proper access to shared resources and prevent race conditions and memory overwriting. 
