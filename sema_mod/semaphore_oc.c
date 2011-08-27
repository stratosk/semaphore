#include <linux/init.h>
#include <linux/module.h>

<<<<<<< HEAD

=======
>>>>>>> semaphore/master
extern void s5pv210_change_high_1200(void);
extern void s5pv210_change_high_1000(void);

static int oc_init(void)
{
	printk(KERN_INFO "Overcloking enabled\n");
	s5pv210_change_high_1200();
	
	return 0;
}

static void oc_exit(void)
{
	printk(KERN_INFO "Overclocking disabled\n");
	s5pv210_change_high_1000();
}

module_init(oc_init);
module_exit(oc_exit);

MODULE_AUTHOR("stratosk");
MODULE_DESCRIPTION("Semaphore overcloking");
MODULE_LICENSE("GPL");
