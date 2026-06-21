#include "adc.h"

//直流变量
extern uint16_t dataBufferA[1];
extern uint16_t dataBufferB[1];
extern volatile bool bgetConvStatus;

//交流变量
extern uint16_t adc_buff[FFT_LENGTH];//存放ADC采集的数据
extern volatile bool AdcConvEnd;//用来检测ADC是否采集完毕 0：没有采集完毕 1：采集完毕，在stm32f1xx_it里的DMA完成中断进行修改

/* The control table used by the uDMA controller.  This table must be aligned
 * to a 1024 byte boundary. */
#if defined(__ICCARM__)
#pragma data_alignment=1024
uint8_t pui8ControlTable[1024];
#elif defined(__TI_ARM__)
#pragma DATA_ALIGN(pui8ControlTable, 1024)
uint8_t pui8ControlTable[1024];
#else
uint8_t pui8ControlTable[1024] __attribute__ ((aligned(1024)));
#endif

void ADC0SS3_IRQHandler(void)
{
    uint32_t getIntStatus;

    /* Get the interrupt status from the ADC */
    getIntStatus = MAP_ADCIntStatusEx(ADC0_BASE, true);

    /* If the interrupt status for Sequencer-3 is set the
     * clear the status and read the data */
    if((getIntStatus & ADC_INT_DMA_SS3) == ADC_INT_DMA_SS3)
    {
        /* Clear the ADC interrupt flag. */
        MAP_ADCIntClearEx(ADC0_BASE, ADC_INT_DMA_SS3);

        /* Reconfigure the channel control structure and enable the channel */
        MAP_uDMAChannelTransferSet(UDMA_CH17_ADC0_3 | UDMA_PRI_SELECT,
                                   UDMA_MODE_BASIC,
                                   (void *)&ADC0->SSFIFO3, (void *)&dataBufferA,
                                   sizeof(dataBufferA)/2);

        MAP_uDMAChannelEnable(UDMA_CH17_ADC0_3);
    }
}

void ADC1SS3_IRQHandler(void)
{
    uint32_t getIntStatus;

    /* Get the interrupt status from the ADC */
    getIntStatus = MAP_ADCIntStatusEx(ADC1_BASE, true);

    /* If the interrupt status for Sequencer-3 is set the
     * clear the status and read the data */
    if((getIntStatus & ADC_INT_DMA_SS3) == ADC_INT_DMA_SS3)
    {
        /* Clear the ADC interrupt flag. */
        MAP_ADCIntClearEx(ADC1_BASE, ADC_INT_DMA_SS3);

        /* Reconfigure the channel control structure and enable the channel */
        MAP_uDMAChannelTransferSet(UDMA_CH27_ADC1_3 | UDMA_PRI_SELECT,
                                   UDMA_MODE_BASIC,
                                   (void *)&ADC1->SSFIFO3, (void *)&dataBufferB,
                                   sizeof(dataBufferB)/2);

        MAP_uDMAChannelEnable(UDMA_CH27_ADC1_3);

        /* Set conversion flag to true */
        bgetConvStatus = true;
    }
}

void adc_init()
{
//  Enable Periph Clk----------------------------------------------------------
    /* Enable the clock to GPIO Port E and wait for it to be ready */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)))
    {
    }                       

    /* Configure PE3 as ADC input channel */
    MAP_GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3 | GPIO_PIN_2);

    /* Enable the clock to ADC-1 and wait for it to be ready */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
    while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_ADC1)))
    {
    }                       
//  Enbale ADC1------------------------------------------------------------------
    /* Configure Sequencer 3 to sample the analog channel : AIN0. The
     * end of conversion and interrupt generation is set for AIN0 */
    MAP_ADCSequenceStepConfigure(ADC1_BASE, 3, 0, ADC_CTL_CH0 | ADC_CTL_IE |  ADC_CTL_END);
    //MAP_ADCSequenceStepConfigure(ADC1_BASE, 3, 0, ADC_CTL_CH1 | ADC_CTL_IE |  ADC_CTL_END);

    /* Enable sample sequence 3 with a Processor signal trigger.  Sequencer 3
     * will do a single sample.*/
    MAP_ADCSequenceConfigure(ADC1_BASE, 3, ADC_TRIGGER_PROCESSOR, 3);

    /* Clear the interrupt status flag before enabling. This is done to make
     * sure the interrupt flag is cleared before we sample. */
    MAP_ADCIntClearEx(ADC1_BASE, ADC_INT_DMA_SS3);
    MAP_ADCIntEnableEx(ADC1_BASE, ADC_INT_DMA_SS3);

    /* Enable the DMA request from ADC0 Sequencer 3 */
    MAP_ADCSequenceDMAEnable(ADC1_BASE, 3);

    /* Set Phase Delay on the channel */
    MAP_ADCPhaseDelaySet(ADC1_BASE, ADC_PHASE_180);

    /* Since sample sequence 32 is now configured, it must be enabled. */
    MAP_ADCSequenceEnable(ADC1_BASE, 3);

    /* Enable the Interrupt generation from the ADC-0 Sequencer */
    MAP_IntEnable(INT_ADC1SS3);
// ADC0 ------------------------------------------------------------------------
    /* Enable the clock to ADC-1 and wait for it to be ready */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0)))
    {
    }

    /* Configure Sequencer 3 to sample the analog channel : AIN0. The
     * end of conversion and interrupt generation is set for AIN0 */
    MAP_ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH1 | ADC_CTL_IE |
                                 ADC_CTL_END);

    /* Enable sample sequence 3 with a Processor signal trigger.  Sequencer 3
     * will do a single sample*/
    MAP_ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 3);

    /* Clear the interrupt status flag before enabling. This is done to make
     * sure the interrupt flag is cleared before we sample. */
    MAP_ADCIntClearEx(ADC0_BASE, ADC_INT_DMA_SS3);
    MAP_ADCIntEnableEx(ADC0_BASE, ADC_INT_DMA_SS3);

    /* Enable the DMA request from ADC0 Sequencer 3 */
    MAP_ADCSequenceDMAEnable(ADC0_BASE, 3);

    /* Since sample sequence 32 is now configured, it must be enabled. */
    MAP_ADCSequenceEnable(ADC0_BASE, 3);

    /* Enable the Interrupt generation from the ADC-0 Sequencer */
    MAP_IntEnable(INT_ADC0SS3);

    /* Enable the DMA and Configure Channel for ADC0 and ADC1 sequencer for
     * Basic mode of transfer */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_UDMA)))
    {
    }

    MAP_uDMAEnable();

    /* Point at the control table to use for channel control structures. */
    MAP_uDMAControlBaseSet(pui8ControlTable);

    /* Map the ADC0 Sequencer 3 DMA channel */
    MAP_uDMAChannelAssign(UDMA_CH17_ADC0_3);

    /* Put the attributes in a known state for the uDMA ADC0 Sequencer 3
     * channel. These should already be disabled by default. */
    MAP_uDMAChannelAttributeDisable(UDMA_CH17_ADC0_3,
                                    UDMA_ATTR_ALTSELECT | UDMA_ATTR_USEBURST |
                                    UDMA_ATTR_HIGH_PRIORITY |
                                    UDMA_ATTR_REQMASK);

    /* Configure the control parameters for the primary control structure for
     * the ADC0 Sequencer 3 channel. The primary control structure is used for
     * copying the data from ADC0 Sequencer 3 FIFO to dataBuffer. The transfer
     * data size is 16 bits and the source address is not incremented while
     * the destination address is incremented at 16-bit boundary.
     */
    MAP_uDMAChannelControlSet(UDMA_CH17_ADC0_3 | UDMA_PRI_SELECT,
                              UDMA_SIZE_16 | UDMA_SRC_INC_NONE | UDMA_DST_INC_16 |
                              UDMA_ARB_1);

    /* Set up the transfer parameters for the ADC0 Sequencer 2 primary control
     * structure. The mode is Basic mode so it will run to completion. */
    MAP_uDMAChannelTransferSet(UDMA_CH17_ADC0_3 | UDMA_PRI_SELECT,
                               UDMA_MODE_BASIC,
                               (void *)&ADC0->SSFIFO3, (void *)&dataBufferA,
                               sizeof(dataBufferA)/2);

    /* The uDMA ADC0 Sequencer 3 channel is primed to start a transfer. As
     * soon as the channel is enabled and the processor issues an ADC trigger,
     * the ADC will perform the conversion and send a DMA Request. The data
     * transfers will begin. */
    MAP_uDMAChannelEnable(UDMA_CH17_ADC0_3);

    /* Map the ADC1 Sequencer 3 DMA channel */
    MAP_uDMAChannelAssign(UDMA_CH27_ADC1_3);

    /* Put the attributes in a known state for the uDMA ADC1 Sequencer 3
     * channel. These should already be disabled by default. */
    MAP_uDMAChannelAttributeDisable(UDMA_CH27_ADC1_3,
                                    UDMA_ATTR_ALTSELECT | UDMA_ATTR_USEBURST |
                                    UDMA_ATTR_HIGH_PRIORITY |
                                    UDMA_ATTR_REQMASK);

    /* Configure the control parameters for the primary control structure for
     * the ADC1 Sequencer 3 channel. The primary control structure is used for
     * copying the data from ADC1 Sequencer 3 FIFO to dataBuffer. The transfer
     * data size is 16 bits and the source address is not incremented while
     * the destination address is incremented at 16-bit boundary.
     */
    MAP_uDMAChannelControlSet(UDMA_CH27_ADC1_3 | UDMA_PRI_SELECT,
                              UDMA_SIZE_16 | UDMA_SRC_INC_NONE | UDMA_DST_INC_16 |
                              UDMA_ARB_1);

    /* Set up the transfer parameters for the ADC0 Sequencer 2 primary control
     * structure. The mode is Basic mode so it will run to completion. */
    MAP_uDMAChannelTransferSet(UDMA_CH27_ADC1_3 | UDMA_PRI_SELECT,
                               UDMA_MODE_BASIC,
                               (void *)&ADC1->SSFIFO3, (void *)&dataBufferB,
                               sizeof(dataBufferB)/2);

    /* The uDMA ADC0 Sequencer 3 channel is primed to start a transfer. As
     * soon as the channel is enabled and the processor issues an ADC trigger,
     * the ADC will perform the conversion and send a DMA Request. The data
     * transfers will begin. */
    MAP_uDMAChannelEnable(UDMA_CH27_ADC1_3);
}


void adc0_init()
{
//GPIO
    /* 使能GPIOE的时钟并等待其使能完成 */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)))
    {
    }
    /* 设置PE3作为AD的输入IO */
    MAP_GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_0);
//ADC
    /* 使能ADC0的时钟并等待其使能完毕 */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0)))
    {
    }
	//cmsis_msp432e4_dsp_example.c

	ADCClockConfigSet(ADC0_BASE, ADC_CLOCK_SRC_PLL | ADC_CLOCK_RATE_FULL, 5);
  
    /* 使能ADC0采样序列2通道3 */
    MAP_ADCSequenceStepConfigure(ADC0_BASE, 2, 0, ADC_CTL_CH0 | ADC_CTL_IE |
                                 ADC_CTL_END);
 
    /* 使能ADC0为定时器触发，当定时器触发后进行单次采样 */
    MAP_ADCSequenceConfigure(ADC0_BASE, 2, ADC_TRIGGER_TIMER, 2);
 
    /* 在使能之前清除中断状态标志位，这一步是为了确保中断标志位在我们采样时是保持清除状态 */
    MAP_ADCIntClearEx(ADC0_BASE, ADC_INT_DMA_SS2);
    MAP_ADCIntEnableEx(ADC0_BASE, ADC_INT_DMA_SS2);
 
    /* 使能ADC0采样序列2的DMA请求 */
    MAP_ADCSequenceDMAEnable(ADC0_BASE, 2);
 
    /* ADC0采样序列2的配置已经完成，现在进行使能 */
    MAP_ADCSequenceEnable(ADC0_BASE, 2);
 
    /* 使能ADC0采样序列2的中断 */
    MAP_IntEnable(INT_ADC0SS2);
//DMA
    /* 使能DMA并为其配置通道 */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_UDMA)))
    {
    }
 
    MAP_uDMAEnable();
 
    /* 指向控制表，用于通道控制结构 */
    MAP_uDMAControlBaseSet(pui8ControlTable);
 
    /* 映射ADC0通道2到DMA上 */
    MAP_uDMAChannelAssign(UDMA_CH16_ADC0_2);
 
    /* 配置DMA属性为已知状态，默认情况下为失能 */
    MAP_uDMAChannelAttributeDisable(UDMA_CH16_ADC0_2,
                                    UDMA_ATTR_ALTSELECT | UDMA_ATTR_USEBURST |
                                    UDMA_ATTR_HIGH_PRIORITY |
                                    UDMA_ATTR_REQMASK);
 
    /* 为ADC0采样序列2的优先级控制结构体设置控制参数，优先级控制结构体是用来从ADC0采样序列2的
    FIFO中复制数据到数组srcBuffer，这个传输数据大小为16位，源地址不增加，目的地址16位步进 */
 
    MAP_uDMAChannelControlSet(UDMA_CH16_ADC0_2 | UDMA_PRI_SELECT,
                              UDMA_SIZE_16 | UDMA_SRC_INC_NONE | UDMA_DST_INC_16 |
                              UDMA_ARB_4);
 
    /* 为ADC0采样序列2设置优先级控制结构体，模式为BASIC */
    MAP_uDMAChannelTransferSet(UDMA_CH16_ADC0_2 | UDMA_PRI_SELECT,
                               UDMA_MODE_BASIC,
                               (void *)&ADC0->SSFIFO2, (void *)&adc_buff,
                               sizeof(adc_buff)/2);
 
    /* ADC0采样序列2的uDMA已经准备就绪，当通道使能后，定时器触发ADC采样，ADC完成采样之后发送
    一个DMA请求，之后数据传输就会开始 */
//    MAP_uDMAChannelEnable(UDMA_CH16_ADC0_2);
}	
