// Basil El-Hindi
// CS 4348.HON
// Project 4
// dining.c

// Kernel module includes
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/list.h>
#include <linux/delay.h>  // msleep()
#include <linux/random.h> // get_random_bytes()
#include <linux/kthread.h> 
#include <linux/semaphore.h>
#include <linux/slab.h>
#include <linux/sched.h> // task_struct

// Struct to start threads
static struct task_struct *philosopher_thread;

// Struct to hold times for each eating cycle for
// philosopher thread to output on exit
struct eating_cycle{
	int philosopher_num;
	int hunger_time;
	int eating_time;
	struct list_head list;
};

// Shared resource and locks
int food = 30;
struct semaphore forks[7];
struct semaphore eat;

// Function prototype
int philosopher_run(void *data);

// Philosopher thread function, data holds philosopher number
int philosopher_run(void* data)
{
	// Number that indicates which philosopher this is
	int num = (int)data;
	// Pointers to output eating cycles
	struct eating_cycle *ptr, *next;
	// Initialize output list for each thread
	static LIST_HEAD(out_list);
	do
	{
		unsigned int rand;
		// Struct to hold info for this eating cycle
		struct eating_cycle *cycle;
		cycle = kmalloc(sizeof(*cycle), GFP_KERNEL);
		cycle->philosopher_num = num;
		// Sleep between 2 and 4 seconds
		get_random_bytes(&rand, sizeof(unsigned int));
		if(rand < 0)
		{
			printk(KERN_ERR "Failed to get random number");
			return 1;
		}
		rand = rand % 3 + 2;
		// Store hunger time
		cycle->hunger_time = rand;
		msleep(rand * 1000);
		// Try to acquire forks. To prevent deadlocks, odd philosophers grab to the
		// right first, even philosophers grab to the left first. Fork 1 is to the 
		// right of philosopher 1 and left of philosopher 7.
		if(num%2 == 1)
		{
			down(&forks[num]);
			down(&forks[(num+1) % 7]);
			// Since food is a shared resource, make sure only one philosopher thread
			// can decrement food at a time
			down(&eat);
			// If we take a bite, sleep for 1-3 seconds and start again
			if(food > 0)
			{
				food = food - 1;
        		up(&eat);
				printk(KERN_INFO "Bite taken by philosopher %d\n", num);
				get_random_bytes(&rand, sizeof(unsigned int));
				if(rand < 0)
				{
					printk(KERN_ERR "Failed to get random number");
					return 1;
				}
				rand = rand % 3 + 1;
				// Record eating time
				cycle->eating_time = rand;
				msleep(rand * 1000);
			}
			// If there is no food left, output the time spent waiting and resting
			// for each eating cycle and exit the thread
			else
			{
				printk(KERN_INFO "");
				up(&eat);
				up(&forks[num]);
				up(&forks[(num+1) % 7]);
				// Free memory since struct will not enter list
				kfree(cycle);
				break;
			}
			up(&forks[num]);
			up(&forks[(num+1) % 7]);
		}
		else
		{
			down(&forks[(num+1) % 7]);
			down(&forks[num]);
			down(&eat);
			if(food > 0)
			{
				food = food - 1;
        		up(&eat);
				printk(KERN_INFO "Bite taken by philosopher %d\n", num);
				get_random_bytes(&rand, sizeof(unsigned int));
				if(rand < 0)
				{
					printk(KERN_ERR "Failed to get random number");
					return 1;
				}
				rand = rand % 3 + 1;
				cycle->eating_time = rand;
				msleep(rand * 1000);
			}
			else
			{
				printk(KERN_INFO "");
				up(&eat);
				up(&forks[(num+1) % 7]);
				up(&forks[num]);
				kfree(cycle);
				break;
			}
			up(&forks[(num+1) % 7]);
			up(&forks[num]);
		}
		// Add this eating cycle to the end of the output list
		INIT_LIST_HEAD(&cycle->list);
		list_add_tail(&cycle->list, &out_list);
	} while(true);
	// When there is no more food and the philosopher exits, print its
	// hunger and eating time for each cycle and free the memory before
	// the thread terminates
	printk(KERN_INFO "Food finished, philosopher %d exiting\n", num);
	list_for_each_entry_safe(ptr, next, &out_list, list)
	{
		if(ptr->philosopher_num == num)
		{
			printk(KERN_INFO "Philosopher %d waited for %d before eating for %d time\n", 
				ptr->philosopher_num, ptr->hunger_time, ptr->eating_time);
			list_del(&ptr->list);
			kfree(ptr);
		}
	}
	return 0;
}

/* This function is called when the module is loaded. */
int dining_init(void)
{
	int i;
	char name[12] = "Philosopher ";

   printk(KERN_INFO "Loading Module\n");

	// Initialize semaphores and spawn the 7 philosopher threads
	sema_init(&eat, 1);
	for(i = 0; i < 7; i++)
	{
		sema_init(&forks[i], 1);
		name[11] = i;
		philosopher_thread = kthread_run(philosopher_run, (void*)i, name);
		if(philosopher_thread)
		{
			printk(KERN_INFO "Thread %d started\n", i);
		}
		else
		{
			printk(KERN_ERR "Error starting thread");
		}
	}
	return 0;
}

/* This function is called when the module is removed. */
void dining_exit(void) {
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( dining_init );
module_exit( dining_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
