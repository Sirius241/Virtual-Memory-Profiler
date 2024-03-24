# Virtual-Memory-Profiler
A Virtual Memory Profiler is a vital tool for analyzing and optimizing the utilization of virtual memory in software. It provides insights into memory usage patterns, potential leaks, and optimization opportunities. ​
Implementation:
memwatch.c

gcc -o memwatch memwatch.c -lrt

./memwatch <pid>

OUTPUT:

![img2](https://github.com/Sirius241/Virtual-Memory-Profiler/assets/130964012/0b552c4d-ae97-4a3c-8822-97afa6ca8a56)

pagefault.c

gcc -o pagefault pagefault.c

./pagefault <pid/command name>

OUTPUT:

![Screenshot 2024-02-15 072045](https://github.com/Sirius241/Virtual-Memory-Profiler/assets/130964012/580c6804-964b-4cfc-ad5d-44f936e99b30)

vp.c

(To obtain data in csv format for dashboard or graph creation,follow the below steps for execution)

gcc -o vp vp.c

![Screenshot 2024-03-09 232011](https://github.com/Sirius241/Virtual-Memory-Profiler/assets/130964012/966cdeed-d32f-4ad5-a1fd-ba55b074f159)

mem_map.c

gcc -o mm mem_map.c

./mm <pid>

OUTPUT:

![Screenshot 2024-03-24 115529](https://github.com/Sirius241/Virtual-Memory-Profiler/assets/130964012/1fd4db43-8e80-4688-8861-506c8286c22c)
