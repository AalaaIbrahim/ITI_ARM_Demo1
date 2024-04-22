#ifndef MCAL_NVIC_NVIC_STM32401_H_
#define MCAL_NVIC_NVIC_STM32401_H_

typedef enum
  {
	WWDG=0,            //!< WWDG
	EXTI16_PVD,        //!< EXTI16_PVD
	EXTI21_TAMP_STAMP, //!< EXTI21_TAMP_STAMP
	EXTI22_RTC_WKUP,   //!< EXTI22_RTC_WKUP
	FLASH,             //!< FLASH
	RCC,               //!< RCC
	EXTI0,             //!< EXTI0
	EXTI1,             //!< EXTI1
	EXTI2,             //!< EXTI2
	EXTI3,             //!< EXTI3
	EXTI4,             //!< EXTI4
	DMA1_Stream0,      //!< DMA1_Stream0
	DMA1_Stream1,      //!< DMA1_Stream1
	DMA1_Stream2,      //!< DMA1_Stream2
	DMA1_Stream3,      //!< DMA1_Stream3
	DMA1_Stream4,      //!< DMA1_Stream4
	DMA1_Stream5,      //!< DMA1_Stream5
	DMA1_Stream6,      //!< DMA1_Stream6
	ADC,               //!< ADC
	EXTI9_5=23,           //!< EXTI9_5
	TIM1_BRK_TIM9,     //!< TIM1_BRK_TIM9
	TIM1_UP_TIM10,     //!< TIM1_UP_TIM10
	TIM1_TRG_COM_TIM11,//!< TIM1_TRG_COM_TIM11
	TIM1_CC,           //!< TIM1_CC
	TIM2,              //!< TIM2
	TIM3,              //!< TIM3
	TIM4,              //!< TIM4
	I2C1_EV,           //!< I2C1_EV
	I2C1_ER,           //!< I2C1_ER
	I2C2_EV,           //!< I2C2_EV
	I2C2_ER,           //!< I2C2_ER
	SPI1,              //!< SPI1
	SPI2,              //!< SPI2
	USART1,            //!< USART1
	USART2,            //!< USART2
	EXTI15_10=40,         //!< EXTI15_10
	EXTI17RTC_Alarm,   //!< EXTI17RTC_Alarm
	EXTI18_OTG_FS_WKUP,//!< EXTI18_OTG_FS_WKUP
	DMA1_Stream7=47,      //!< DMA1_Stream7
	SDIO=49,              //!< SDIO
	TIM5,              //!< TIM5
	SPI3,              //!< SPI3
	DMA2_Stream0=56,      //!< DMA2_Stream0
	DMA2_Stream1,      //!< DMA2_Stream1
	DMA2_Stream2,      //!< DMA2_Stream2
	DMA2_Stream3,      //!< DMA2_Stream3
	DMA2_Stream4,      //!< DMA2_Stream4
	OTG_FS=67,            //!< OTG_FS
	DMA2_Stream5,      //!< DMA2_Stream5
	DMA2_Stream6,      //!< DMA2_Stream6
	DMA2_Stream7,      //!< DMA2_Stream7
	USART6,            //!< USART6
	I2C3_EV,           //!< I2C3_EV
	I2C3_ER,           //!< I2C3_ER
	FPU=81,               //!< FPU
	SPI4=84              //!< SPI4
}NVIC_IRQ_ID_t;


#endif // MCAL_NVIC_NVIC_STM32401_H_