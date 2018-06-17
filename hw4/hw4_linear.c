#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

int ken_init(void){
	struct task_struct *p = NULL;
	char buf[16] = "";
    int pid;

	for_each_process(p){
		get_task_comm(buf, p);
		pid = p->pid;
		printk(KERN_INFO "pid: %d | pname: %s | state: %d\n", pid, buf, (int)p->state);
	}

	return 0;
}

void ken_exit(void) {

}

module_init(ken_init);
module_exit(ken_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("OS_HW4_LINEAR");
MODULE_AUTHOR("BKC");