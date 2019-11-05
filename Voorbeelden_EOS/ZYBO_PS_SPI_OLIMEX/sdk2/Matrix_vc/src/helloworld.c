#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xplatform_info.h"
#include "xspips.h"
//#include "font.h"
#include "lcd8x8rgb.h"

#define MATRIX_SPI_SELECT_1	0x01
#define MATRIX_SPI_SELECT_0	0x00

#define SPI_DEVICE_ID		XPAR_XSPIPS_0_DEVICE_ID

#ifndef TESTAPP_GEN
static XSpiPs SpiInstance;
#endif

// SPI	= MIO10 MIO11 MIO12
// SS[0] = MIO13

int main()
{
	XSpiPs_Config *SpiConfig;
	u16 SpiDeviceId= SPI_DEVICE_ID;
	XSpiPs *SpiInstancePtr;
	int Status;
    init_platform();

    SpiInstancePtr = &SpiInstance;

    print("Demo Appplication by Vincent Claes\n\r");
    /*
    	 * Initialize the SPI driver so that it's ready to use
    	 */
    	SpiConfig = XSpiPs_LookupConfig(SpiDeviceId);
    	if (NULL == SpiConfig) {
    		return XST_FAILURE;
    	}

    	Status = XSpiPs_CfgInitialize(SpiInstancePtr, SpiConfig,
    					SpiConfig->BaseAddress);
    	if (Status != XST_SUCCESS) {
    		return XST_FAILURE;
    	}

    	/*
    	 * Perform a self-test to check hardware build
    	 */
    	Status = XSpiPs_SelfTest(SpiInstancePtr);
    	if (Status != XST_SUCCESS) {
    		return XST_FAILURE;
    	}
    	/*
    	 * Set the SPI device as a master with manual start and manual
    	 * chip select mode options
    	 */

    	/* XSpiPs_SetOptions(SpiInstancePtr, XSPIPS_MANUAL_START_OPTION | \
    				XSPIPS_MASTER_OPTION | XSPIPS_FORCE_SSELECT_OPTION); */


    	/*
    	 * 	#define XSPIPS_MASTER_OPTION				0x00000001U  /**< Master mode option
		* 	#define XSPIPS_CLK_ACTIVE_LOW_OPTION		0x00000002U  /**< Active Low Clock option
			#define XSPIPS_CLK_PHASE_1_OPTION			0x00000004U  /**< Clock Phase one option
			#define XSPIPS_DECODE_SSELECT_OPTION		0x00000008U  /**< Select 16 slaves Option
			#define XSPIPS_FORCE_SSELECT_OPTION			0x00000010U /**< Force Slave Select
			#define XSPIPS_MANUAL_START_OPTION			0x00000020U /**< Manual Start mode option
    	 *
    	 *
    	 *
    	 */
    	 XSpiPs_SetOptions(SpiInstancePtr, XSPIPS_MASTER_OPTION | XSPIPS_CLK_PHASE_1_OPTION |\
    			XSPIPS_FORCE_SSELECT_OPTION);

    		/*
    		 * Set the SPI device pre-scalar to divide by 8
    		 */
    	XSpiPs_SetClkPrescaler(SpiInstancePtr, XSPIPS_CLK_PRESCALE_256);
    		/*
    			 * Set the matrix chip select
    			 */
    	//u8 WriteData = 0x88;
    	u8 WriteData[24];
    	WriteData[0]	=0b11111111;
    	WriteData[1]	=0b11111111;
    	WriteData[2]	=0b11111111;
    	WriteData[4]	=0b10111101;
    	WriteData[5]	=0b10111101;
    	WriteData[6]	=0b10111101;
    	WriteData[7]	=0b11011011;
    	WriteData[8]	=0b11011011;
    	WriteData[9]	=0b11011011;
    	WriteData[10]	=0b11100111;
    	WriteData[11]	=0b11100111;
    	WriteData[12]	=0b11100111;
    	WriteData[13]	=0b11111011;
    	WriteData[14]	=0b11111011;
    	WriteData[15]	=0b11111011;
    	WriteData[16]	=0b11111101;
    	WriteData[17]	=0b11111101;
    	WriteData[18]	=0b11111101;
    	WriteData[19]	=0b11111110;
    	WriteData[20]	=0b11111110;
    	WriteData[21]	=0b11111110;
    	WriteData[22]	=0b11111111;
    	WriteData[23]	=0b11111111;
    	u32 ChipSelect = MATRIX_SPI_SELECT_0;
    	XSpiPs_SetSlaveSelect(SpiInstancePtr, ChipSelect);
    	XSpiPs_PolledTransfer(SpiInstancePtr, WriteData, NULL, sizeof(WriteData));
    cleanup_platform();
    return 0;
}
