#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include<linux/slab.h>

typedef struct student {
  int ID;
  int Year;
  int Month;
  int Day;
  struct list_head node_student;
} student_d;


struct list_head group;

student_d *make_node(int id, int y, int m, int d) {
  student_d *stu = NULL;

  if ((stu = kmalloc(sizeof(struct student), GFP_KERNEL)) == NULL) {
    return NULL; /* Failed to allocate memory. */
  }

  stu->ID = id;
  stu->Year = y;
  stu->Month = m;
  stu->Day = d;

  return stu;
}

int ken_init(void){
  
  student_d *stu = NULL;

  printk(KERN_INFO "Loading Module\n");

  INIT_LIST_HEAD(&group);
  
  if((stu = make_node(106062540, 1996, 1, 6)) == NULL){
    printk(KERN_INFO "Failed to creat 2540.\n");  
  }
  list_add_tail(&stu->node_student, &group);

  if((stu = make_node(106062899, 1997, 2, 7)) == NULL){
    printk(KERN_INFO "Failed to creat 2899.\n");  
  }
  list_add_tail(&stu->node_student, &group);

 
  if((stu = make_node(106062569, 1998, 3, 8)) == NULL){
    printk(KERN_INFO "Failed to creat 2569.\n");  
  }
  list_add_tail(&stu->node_student, &group);


  if((stu = make_node(106061359, 1999, 4, 9)) == NULL){
    printk(KERN_INFO "Failed to creat 1359.\n");  
  }
  list_add_tail(&stu->node_student, &group);

  if((stu = make_node(106054893, 1995, 5, 10)) == NULL){
    printk(KERN_INFO "Failed to creat 4893.\n");  
  }
  list_add_tail(&stu->node_student, &group);

  printk(KERN_INFO "Group created successfully.\n");

  list_for_each_entry(stu, &group, node_student) {
    printk(KERN_INFO "%d, %d-%d-%d.", stu->ID, stu->Day, stu->Month, stu->Year);
  }

  printk(KERN_INFO "Succeeded in initializing.\n");

  return 0;
}

void ken_exit(void) {
  student_d *stu = NULL;
  student_d *tmp = NULL;

  printk(KERN_INFO "Removing Module.\n");
 

  list_for_each_entry_safe(stu, tmp, &group, node_student) {
    
    list_del(&stu->node_student);
    kfree(stu);

  }

  printk(KERN_INFO "Removing Module succeeded.\n");

}

module_init(ken_init);
module_exit(ken_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("OS HW1");
MODULE_AUTHOR("BKC");

