//-------------------------------------------------------------------
//	celsius.c
//
//	This module creates a pseudo-file named '/proc/celsius' that 
//	shows users the CPU-temperatures (on an Intel-x86 platform).
//
//	NOTE: Developed and tested using Linux kernel version 3.0.4.
//
//	programmer: ALLAN CRUSE
//	written on: 17 MAR 2012
//-------------------------------------------------------------------

#include <linux/module.h>	// for init_module() 
#include <linux/proc_fs.h>	// for create_proc_read_entry() 

#define TjMax 100		// maximum operating temperature 

char modname[] = "celsius";	// name used for our pseudo-file
unsigned int	cpucount = 0;	// for count of the actual CPUs 

void inc_cpucount( void *dummy )
{
	asm("	push	%rax		");
	asm("	mov	$1, %eax	");
	asm("	xadd	%eax, cpucount	");
	asm("	pop	%rax		");	
}


void read_therm_status( void *dummy )
{
	unsigned int	status;	

	get_cpu();	// disable preemption	

	asm("	push	%rax		");
	asm("	push	%rbx		");
	asm("	push	%rcx		");
	asm("	push	%rdx		");

	// read value in 'IA32_THERM_STAT' Model-Specific Register
	asm("	mov	$0x19C, %ecx	");
	asm("	rdmsr			");
	asm("	mov	%%eax, %0 " : "=m" (status) : : "ax" );

	asm("	pop	%rdx		");
	asm("	pop	%rcx		");
	asm("	pop	%rbx		");
	asm("	pop	%rax		");

	*(int *)dummy = status;

	put_cpu();	// reenable preemption
}


int my_proc_read( char *buf, char **start, off_t off, int count, 
						 int *eof, void *data ) 
{
	int		i, celsius, len = 0;

	len += sprintf( buf+len, "\n %u CPUs detected \n", cpucount );
	
	for (i = 0; i < cpucount; i++)
		{
		unsigned int 	status = 0;
		smp_call_function_single( i, read_therm_status, &status, 1 ); 
		celsius = TjMax - ((status >> 16)&0x7F);

		len += sprintf( buf+len, "\n cpu%-2d ", i+1 );
		len += sprintf( buf+len, "thermal_status = %08X ", status );
		if ( celsius == TjMax ) continue;
		len += sprintf( buf+len, " %4d-degrees (celsius)", celsius );
		}
	len += sprintf( buf+len, "\n\n" );
	return	len;
}


static int __init celsius_init( void )
{
	int	i;

	printk( "<1>\nInstalling \'%s\' module ", modname );
	printk( "(NR_CPUS = %u) \n", NR_CPUS );

	// detect and report the actual number of logical CPUs
	for (i = 0; i < NR_CPUS; i++)
		smp_call_function_single( i, inc_cpucount, NULL, 1 );
	printk( "<1>Detected %u actual processors \n", cpucount );

	// setup the pseudo-file for reporting temperatures to a user
	create_proc_read_entry( modname, 0, NULL, my_proc_read, NULL );
	return	0;  //SUCCESS
}


static void __exit celsius_exit(void )
{
	remove_proc_entry( modname, NULL );
	printk( "<1>Removing \'%s\' module\n", modname );
}

module_init( celsius_init );
module_exit( celsius_exit );
MODULE_LICENSE("GPL"); 

