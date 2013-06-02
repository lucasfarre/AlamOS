#include "../../include/drivers/temp.h"

///////////////////////////////////////READ TEMPERATURE////////////////////////////////////////////
//
//int Get_Bits_Value(unsigned long val,int highbit, int lowbit){ 
        //unsigned long data = val;
        //int bits = highbit - lowbit + 1;
        //if(bits<64){
            //data >>= lowbit;
            //data &= (1ULL<<bits) - 1;
        //}
        //return(data);
//}
//
 //a nice document to read is 322683.pdf from intel
//int Read_Thermal_Status_CPU(int cpu_num){
        //int error_indx;
        //unsigned long val= get_msr_value(cpu_num,IA32_THERM_STATUS,63,0,&error_indx);
        //int digital_readout = Get_Bits_Value(val,23,16);
        //bool thermal_status = Get_Bits_Value(val,32,31);
//
        //val= get_msr_value(cpu_num,IA32_TEMPERATURE_TARGET,63,0,&error_indx);
        //int PROCHOT_temp = Get_Bits_Value(val,23,16);
    //
        //temperature is prochot - digital readout
        //if (thermal_status)
          //return(PROCHOT_temp - digital_readout);
        //else
          //return(-1);
//}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
