#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>


struct task_struct *task;
struct task_struct *task_child;
struct list_head *list;
int inp_pid = -1;
module_param(inp_pid, int, S_IRUSR | S_IWUSR);
/* This function is called when the module is loaded. */
int JonesLKM_init(void)
{
       printk(KERN_INFO "Loading Module\n");
       
       for_each_process( task ){
       if(task->pid > inp_pid){
       	printk(KERN_INFO "PROCESS		PID	STATE	PRIO	ST_PRIO	NORM_PRIO\n");
       	printk(KERN_INFO "%-16s %d 	%d	%d	%d	%d\n", task->comm, task->pid,  task->__state, task->prio, task->static_prio, task->normal_prio);
       	
       	list_for_each(list, &task->children){
       		
       		task_child = list_entry(list, struct task_struct, sibling);
       		
       		printk(KERN_INFO "CHILD\n");
       		printk(KERN_INFO "%-16s %d 	%d	%d	%d	%d\n",task_child->comm, task_child->pid, task_child->__state, task_child->prio, task_child->static_prio, task_child->normal_prio);
       	}
       	printk(KERN_INFO "PARENT\n");
       	printk(KERN_INFO "%-16s %d 	%d	%d	%d	%d\n",task->real_parent->comm, task->real_parent->pid,  task->real_parent->__state, task->real_parent->prio, task->real_parent->static_prio, task->real_parent->normal_prio);
       	printk(KERN_INFO " \n");
       	}
       }
       printk(KERN_ALERT "TEST: param = %d", inp_pid);

       return 0;
}

/* This function is called when the module is removed. */
void JonesLKM_exit(void) {
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( JonesLKM_init );
module_exit( JonesLKM_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("JonesLKM Module to iterate through all processes/child processes whose PID is greater than int input by user");
MODULE_AUTHOR("ndjone12");
