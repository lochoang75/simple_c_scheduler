FLAGS= -Wall
GCC= gcc

all: simple_scheduler
clean: 
	rm -rf coffee_task.o
	rm -rf task_queue.o
	rm -rf task_scheduler.o
	rm -rf simple_scheduler
	rm -rf *.gch

coffee_task.o: coffee_task.h coffee_task.c 
	$(GCC) $(FLAGS) -c $^

task_queue.o: coffee_task.o task_queue.h task_queue.c
	$(GCC) $(FLAGS) -c $^

task_schedule.o: task_schedule.o coffee_task.o task_schedule.c
	$(GCC) $(FLAGS) -c $^

simple_scheduler: coffee_task.o task_queue.o task_schedule.o main.c
	$(GCC) $(FLAGS) $^ -o $@
