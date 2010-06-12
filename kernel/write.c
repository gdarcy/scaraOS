#include <scaraOS/kernel.h>
#include <scaraOS/task.h>
#include <scaraOS/vfs.h>
#include <scaraOS/fcntl.h>
#include <arch/mm.h>

int _sys_write(unsigned int handle, const char *buf, size_t count)
{
	struct file *fd;
	struct task *me;
	char *kbuf;

	if ( handle == 1 ) {
		return _sys_write_stdout(handle, (void *)buf, count);
	}

	kbuf = strdup_from_user(buf, UACCESS_KERNEL_OK);
	if ( NULL == kbuf )
		return -1; /* EFAULT or ENOMEM */

	me = __this_task;
	fd = fdt_entry_retr(me->fd_table, handle);
	if ( NULL == fd )
		return -1; /* EMAXFILE */
	return kernel_write(fd, kbuf, count);
}

int kernel_write(struct file *file, const char *buf, size_t count)
{
	printk("write: not yet implemented\n");
	return -1;
}
