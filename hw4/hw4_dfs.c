#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>
#include <linux/list.h>

void dfs(struct task_struct *p, char* buf){
	struct task_struct *child_task = NULL;
	struct task_struct *tmp = NULL;
	int pid;

	list_for_each_entry_safe(child_task, tmp, &(p->children), sibling) {

		pid = child_task->pid;
		get_task_comm(buf, child_task);
		printk(KERN_INFO "pid: %d | pname: %s | state: %d\n", pid, buf, (int)child_task->state);

		if(!list_empty(&(child_task->children))){
			dfs(child_task, buf);
		}
	}
}

int ken_init(void){
	struct task_struct *p = NULL;

	char buf[16] = "";
	int pid;

    p = &init_task;

	get_task_comm(buf, p);
	pid = p->pid;
	printk(KERN_INFO "pid: %d | pname: %s | state: %d\n", pid, buf, (int)p->state);

    dfs(p, buf);

	return 0;
}

void ken_exit(void) {
}

module_init(ken_init);
module_exit(ken_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("OS_HW4_DFS");
MODULE_AUTHOR("BKC");