# philosophers

42 school [subject](https://cdn.intra.42.fr/pdf/pdf/68462/en.subject.pdf).

A C project that makes particular use of mutexes, semaphores, threads and processes via forks.

To learn more about the learned theory, read the comments inside the code.

## Usage 

Go into folder related to philo one, two or three and `make` to create the executable.

Examples of tests using the executable.
```
./philo_one 6 1000 2000 2000 5 //Verify rapid death
./philo_one 3 8000 2000 2000 //Infinity
./philo_one 2 8000 3000 3000 5 | grep "is eating" | wc -l //verify eat count feature
./philo_one 7 8000 3000 3000 1 //verify eat count feature
./philo_one 20 15000 2000 2000 10 //test chronological time
./philo_one 4 410 200 200 //Should not die, by correction pdf 
// 410 dies occasionaly, because 420 never dies seems to be related to free memory space that can slow down the program and cause occosional death of philospher

//Test 0 philos, 0 different times, test with negative values, test with letters
//Can behave differently on different OSs
```

If certain semaphores are blocked, you can unblock them `gcc unlink_semaphore.c && ./a.out`.
