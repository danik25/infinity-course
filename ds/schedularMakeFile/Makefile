OBJECTS = scheduler.o scheduler_test.o uid.o pq.o sorted_list.o \
			dl_list.o task.o


sched : $(OBJECTS)
	cc -o sched $(OBJECTS)

scheduler.o : scheduler.c scheduler.h
	cc -c scheduler.c

scheduler_test.o : scheduler_test.c scheduler.h task.h
	cc -c scheduler_test.c

uid.o : uid.c uid.h
	cc -c uid.c

pq.o : pq.c pq.h sorted_list.h
	cc -c pq.c

sorted_list.o : sorted_list.c sorted_list.h dl_list.h
	cc -c sorted_list.c

dl_list.o : dl_list.c dl_list.h
	cc -c dl_list.c

task.o : task.c task.h uid.h
	cc -c task.c

.PHONY : clean
clean : 
	rm sched $(OBJECTS)