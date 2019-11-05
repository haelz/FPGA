
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "WS2812.h"
#include "xparameters.h"
#include "xil_io.h"
#include "sleep.h"

#define WS2812ADR XPAR_WS2812_0_S00_AXI_BASEADDR


u16 result;

int main()
{
    init_platform();
    int i=0;
    WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG0_OFFSET, 0x0000FF);
    WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG1_OFFSET, 0x000100);
    WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG2_OFFSET, 0x000000);
    WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG3_OFFSET, 0x0100F0);
    WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG4_OFFSET, 0x010F00);

	for(;;){
    printf("Looping :%d....\n\r", i);
    WS2812_mWriteReg(WS2812ADR,WS2812_S00_AXI_SLV_REG2_OFFSET, i);
    if (i>25000)
    	i=0;
    else i++;

    /*
    result =  HCSR04_SENSOR_mReadReg(XPAR_HCSR04_SENSOR_0_S00_AXI_BASEADDR,HCSR04_SENSOR_S00_AXI_SLV_REG0_OFFSET);
    printf("Reg0: %d\n\r", result);
    result =  HCSR04_SENSOR_mReadReg(XPAR_HCSR04_SENSOR_0_S00_AXI_BASEADDR,HCSR04_SENSOR_S00_AXI_SLV_REG1_OFFSET);
        printf("Reg1: %d\n\r", result);
	result =  HCSR04_SENSOR_mReadReg(XPAR_HCSR04_SENSOR_0_S00_AXI_BASEADDR,HCSR04_SENSOR_S00_AXI_SLV_REG2_OFFSET);
		printf("Reg2: %d\n\r", result);
		*/

	//result =  WS2812_mReadReg(XPAR_HCSR04_SENSOR_0_S00_AXI_BASEADDR,HCSR04_SENSOR_S00_AXI_SLV_REG3_OFFSET);
		//printf("%d cm\n\r", result);
		//usleep(500);

	}

    cleanup_platform();
    return 0;
}