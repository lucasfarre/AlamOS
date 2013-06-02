

#ifndef _temp_
#define _temp_

/* Intel® 64 and IA-32 Architectures
    Software Developer’s Manual */
                                    
#define IA32_THERM_STATUS 0x19C
#define IA32_TEMPERATURE_TARGET 0x1a2
#define IA32_PACKAGE_THERM_STATUS 0x1b1

int Get_Bits_Value(unsigned long val,int highbit, int lowbit);
int Read_Thermal_Status_CPU(int cpu_num);

#endif
