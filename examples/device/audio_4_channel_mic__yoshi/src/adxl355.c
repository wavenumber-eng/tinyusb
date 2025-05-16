#include "adxl355.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_lpspi_edma.h"
#include "app.h"
#include "fsl_lpspi.h"
#include "board.h"


#if defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT
#include "fsl_dmamux.h"
#endif

#define TRANSFER_SIZE       10     /* Transfer dataSize */
#define TRANSFER_BAUDRATE   500000U /* Transfer baudrate - 500k */

#define DRDY_ISR            GPIO3_IRQHandler
#define DRDY_IRQn           GPIO3_IRQn


uint8_t masterRxData[TRANSFER_SIZE];
uint8_t masterTxData[TRANSFER_SIZE];

AT_NONCACHEABLE_SECTION_INIT(lpspi_master_edma_handle_t g_m_edma_handle) = {0};

volatile bool trigger_spi_transfer = false;
volatile uint32_t drdy_ctr = 0;


void ADLX_355__spi_init(void)
{
    uint32_t srcClock_Hz;
    lpspi_master_config_t masterConfig;

    /*Master config*/
    LPSPI_MasterGetDefaultConfig(&masterConfig);
    masterConfig.baudRate = TRANSFER_BAUDRATE;
    masterConfig.whichPcs = EXAMPLE_LPSPI_MASTER_PCS_FOR_INIT;
    masterConfig.pcsToSckDelayInNanoSec        = 0;
    masterConfig.lastSckToPcsDelayInNanoSec    = 0;
    masterConfig.betweenTransferDelayInNanoSec = 0;
    
    srcClock_Hz = LPSPI_MASTER_CLK_FREQ;
    LPSPI_MasterInit(EXAMPLE_LPSPI_MASTER_BASEADDR, &masterConfig, srcClock_Hz);
}


void ADXL355__TxRx(uint32_t length, uint8_t *txData, uint8_t *rxData)
{
    lpspi_transfer_t masterXfer;

    /*Start master transfer*/
    masterXfer.txData   = txData;
    masterXfer.rxData   = rxData;
    masterXfer.dataSize = length;
    masterXfer.configFlags = EXAMPLE_LPSPI_MASTER_PCS_FOR_TRANSFER | kLPSPI_MasterPcsContinuous | kLPSPI_MasterByteSwap;

    LPSPI_MasterTransferBlocking(EXAMPLE_LPSPI_MASTER_BASEADDR, &masterXfer);
}

void ADXL355_WriteRegister(uint8_t Reg, uint8_t Value)
{

    masterTxData[0] = (Reg << 1);
    masterTxData[1] = Value;
    ADXL355__TxRx(2,&masterTxData[0],&masterRxData[0]);
}

uint8_t ADXL355_ReadRegister(uint8_t Reg)
{
    masterTxData[0] = (Reg << 1) + 1;
    masterTxData[1] = 0;
    ADXL355__TxRx(2,&masterTxData[0],&masterRxData[0]);
    return masterRxData[1];
}



void ADXL355__init(void)
{
    ADLX_355__spi_init();

    ADXL355_WriteRegister(ADXL33X_RESET,0x52);
    ADXL355_WriteRegister(ADXL33X_POWER_CTL,0);
    ADXL355_WriteRegister(ADXL33X_RANGE,0x80 | 3);   

    masterTxData[0] = (ADXL33X_XDATA3<<1) + 1;
    NVIC_EnableIRQ(DRDY_IRQn);
}

void DRDY_ISR(void)
{
    if(GPIO_GpioGetInterruptFlags(GPIO3) & (1U << 0U))
    {
        drdy_ctr++;
        trigger_spi_transfer = true;
        GPIO_GpioClearInterruptFlags(GPIO3, 1U << 0U);
    }

    SDK_ISR_EXIT_BARRIER;
}


void ADXL355__crunch()
{
    if(trigger_spi_transfer)
    {
        ADXL355__TxRx(10, &masterTxData[0], &masterRxData[0]);
        trigger_spi_transfer = false;
    }
}