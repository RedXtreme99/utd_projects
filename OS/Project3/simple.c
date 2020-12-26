/**
 * simple.c
 *
 * A simple kernel module. 
 * 
 * To compile, run makefile by entering "make"
 *
 * Operating System Concepts - 10th Edition
 * Copyright John Wiley & Sons - 2018
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
// Includes for list structures and macros and kalloc and kfree
#include <linux/list.h>
#include <linux/slab.h>

// Birthday structure that contains day, month, year,
// and a structure to hold each list_head structure with pointers to the
// next and previous entries in the doubly linked circular list
struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;
};

// Initialize birthday_list to be the head of the list
static LIST_HEAD(birthday_list);

/* This function is called when the module is loaded. */
int simple_init(void)
{
	// Initialize birthday struct pointers and i for loop control
	struct birthday *person, *ptr;
   int i;

   printk(KERN_INFO "Loading Module\n");

	// Loop through and create five birthday structs to insert into the list
	// Memory is allocated with kmalloc
	// INIT_LIST_HEAD initializes the list member struct in each birthday
	// Each person's birthday is added to the tail of the birthday list
	for(i = 1; i <= 5; i++)
	{
		person = kmalloc(sizeof(*person), GFP_KERNEL);
		person->day = i*4;
		person->month = i*2;
		person->year = 2000;
		INIT_LIST_HEAD(&person->list);
		list_add_tail(&person->list, &birthday_list);
	}

	// Iterate through the birthday list and print each birthday
	// ptr points to each element of birthday_list sequentially
	list_for_each_entry(ptr, &birthday_list, list)
	{
		printk(KERN_INFO "Birth date: %d\nBirth month: %d\nBirth year: %d\n",
			ptr->day, ptr->month, ptr->year);
	}

	return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	// Initialize birthday struct pointers
	struct birthday *ptr, *next;

	printk(KERN_INFO "Removing Module\n");

	// Print each birthday as we remove them
	// ptr points to the current birthday, and next points to the next
	// birthday, which is necessary as we free the memory allocated
	// to each current birthday
	list_for_each_entry_safe(ptr, next, &birthday_list, list)
	{
		printk(KERN_INFO "Removing birthday %d/%d/%d\n", ptr->day, ptr->month, ptr->year);
		list_del(&ptr->list);
		kfree(ptr);
	}

	// Iterate through the list and print each date
	// Should print nothing if everything was properly removed
	list_for_each_entry(ptr, &birthday_list, list)
	{
		printk(KERN_INFO "Birth date: %d\nBirth month: %d\nBirth year: %d\n",
			ptr->day, ptr->month, ptr->year);
	}
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
