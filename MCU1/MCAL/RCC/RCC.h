/**
  ******************************************************************************
  * @file    RCC.h
  * @author  Asmaa Newigy
  * @version V1.0.0
  * @date    12-Feb-2024
  * @brief   RCC module driver.
  *          Header file for the RCC module driver.
  ******************************************************************************
**/

/*--------------- Define to prevent recursive inclusion(Header Guard) ----------------------*/
#ifndef RCC_H_
#define RCC_H_

/*--------------------------------------- Includes ------------------------------------------*/
#include "../LIB/Std_Types.h"

/*--------------------------------------- Defines ------------------------------------------*/
/*********************************** CONTROL CLOCK MACROS ***********************************/
#define RCC_ClOCK_HSI	0x00000001
#define RCC_CLOCK_HSE	0x00010000
#define RCC_CLOCK_PLL	0x01000000

/**************************************** CONFIGURE PLL *************************************/
/*``````````````````````````````````````` PLLM VALUES ``````````````````````````````````````*/
#define RCC_CONFIG_PLLM_2                0x2
#define RCC_CONFIG_PLLM_3                0x3
#define RCC_CONFIG_PLLM_4                0x4
#define RCC_CONFIG_PLLM_5                0x5
#define RCC_CONFIG_PLLM_6                0x6
#define RCC_CONFIG_PLLM_7                0x7
#define RCC_CONFIG_PLLM_8                0x8
#define RCC_CONFIG_PLLM_9                0x9
#define RCC_CONFIG_PLLM_10               0xA
#define RCC_CONFIG_PLLM_11               0xB
#define RCC_CONFIG_PLLM_12               0xC
#define RCC_CONFIG_PLLM_13               0xD
#define RCC_CONFIG_PLLM_14               0xE
#define RCC_CONFIG_PLLM_15               0xF
#define RCC_CONFIG_PLLM_16               0x10
#define RCC_CONFIG_PLLM_17               0x11
#define RCC_CONFIG_PLLM_18               0x12
#define RCC_CONFIG_PLLM_19               0x13
#define RCC_CONFIG_PLLM_20               0x14
#define RCC_CONFIG_PLLM_21               0x15
#define RCC_CONFIG_PLLM_22               0x16
#define RCC_CONFIG_PLLM_23               0x17
#define RCC_CONFIG_PLLM_24               0x18
#define RCC_CONFIG_PLLM_25               0x19
#define RCC_CONFIG_PLLM_26               0x1A
#define RCC_CONFIG_PLLM_27               0x1B
#define RCC_CONFIG_PLLM_28               0x1C
#define RCC_CONFIG_PLLM_29               0x1D
#define RCC_CONFIG_PLLM_30               0x1E
#define RCC_CONFIG_PLLM_31               0x1F
#define RCC_CONFIG_PLLM_32               0x20
#define RCC_CONFIG_PLLM_33               0x21
#define RCC_CONFIG_PLLM_34               0x22
#define RCC_CONFIG_PLLM_35               0x23
#define RCC_CONFIG_PLLM_36               0x24
#define RCC_CONFIG_PLLM_37               0x25
#define RCC_CONFIG_PLLM_38               0x26
#define RCC_CONFIG_PLLM_39               0x27
#define RCC_CONFIG_PLLM_40               0x28
#define RCC_CONFIG_PLLM_41               0x29
#define RCC_CONFIG_PLLM_42               0x2A
#define RCC_CONFIG_PLLM_43               0x2B
#define RCC_CONFIG_PLLM_44               0x2C
#define RCC_CONFIG_PLLM_45               0x2D
#define RCC_CONFIG_PLLM_46               0x2E
#define RCC_CONFIG_PLLM_47               0x2F
#define RCC_CONFIG_PLLM_48               0x30
#define RCC_CONFIG_PLLM_49               0x31
#define RCC_CONFIG_PLLM_50               0x32
#define RCC_CONFIG_PLLM_51               0x33
#define RCC_CONFIG_PLLM_52               0x34
#define RCC_CONFIG_PLLM_53               0x35
#define RCC_CONFIG_PLLM_54               0x36
#define RCC_CONFIG_PLLM_55               0x37
#define RCC_CONFIG_PLLM_56               0x38
#define RCC_CONFIG_PLLM_57               0x39
#define RCC_CONFIG_PLLM_58               0x3A
#define RCC_CONFIG_PLLM_59               0x3B
#define RCC_CONFIG_PLLM_60               0x3C
#define RCC_CONFIG_PLLM_61               0x3D
#define RCC_CONFIG_PLLM_62               0x3E
#define RCC_CONFIG_PLLM_63               0x3F

/*``````````````````````````````````````` PLLN VALUES ``````````````````````````````````````*/
#define RCC_CONFIG_PLLN_192                0x000000C0
#define RCC_CONFIG_PLLN_193                0x000000C1
#define RCC_CONFIG_PLLN_194                0x000000C2
#define RCC_CONFIG_PLLN_195                0x000000C3
#define RCC_CONFIG_PLLN_196                0x000000C4
#define RCC_CONFIG_PLLN_197                0x000000C5
#define RCC_CONFIG_PLLN_198                0x000000C6
#define RCC_CONFIG_PLLN_199                0x000000C7
#define RCC_CONFIG_PLLN_200                0x000000C8
#define RCC_CONFIG_PLLN_201                0x000000C9
#define RCC_CONFIG_PLLN_202                0x000000CA
#define RCC_CONFIG_PLLN_203                0x000000CB
#define RCC_CONFIG_PLLN_204                0x000000CC
#define RCC_CONFIG_PLLN_205                0x000000CD
#define RCC_CONFIG_PLLN_206                0x000000CE
#define RCC_CONFIG_PLLN_207                0x000000CF
#define RCC_CONFIG_PLLN_208                0x000000D0
#define RCC_CONFIG_PLLN_209                0x000000D1
#define RCC_CONFIG_PLLN_210                0x000000D2
#define RCC_CONFIG_PLLN_211                0x000000D3
#define RCC_CONFIG_PLLN_212                0x000000D4
#define RCC_CONFIG_PLLN_213                0x000000D5
#define RCC_CONFIG_PLLN_214                0x000000D6
#define RCC_CONFIG_PLLN_215                0x000000D7
#define RCC_CONFIG_PLLN_216                0x000000D8
#define RCC_CONFIG_PLLN_217                0x000000D9
#define RCC_CONFIG_PLLN_218                0x000000DA
#define RCC_CONFIG_PLLN_219                0x000000DB
#define RCC_CONFIG_PLLN_220                0x000000DC
#define RCC_CONFIG_PLLN_221                0x000000DD
#define RCC_CONFIG_PLLN_222                0x000000DE
#define RCC_CONFIG_PLLN_223                0x000000DF
#define RCC_CONFIG_PLLN_224                0x000000E0
#define RCC_CONFIG_PLLN_225                0x000000E1
#define RCC_CONFIG_PLLN_226                0x000000E2
#define RCC_CONFIG_PLLN_227                0x000000E3
#define RCC_CONFIG_PLLN_228                0x000000E4
#define RCC_CONFIG_PLLN_229                0x000000E5
#define RCC_CONFIG_PLLN_230                0x000000E6
#define RCC_CONFIG_PLLN_231                0x000000E7
#define RCC_CONFIG_PLLN_232                0x000000E8
#define RCC_CONFIG_PLLN_233                0x000000E9
#define RCC_CONFIG_PLLN_234                0x000000EA
#define RCC_CONFIG_PLLN_235                0x000000EB
#define RCC_CONFIG_PLLN_236                0x000000EC
#define RCC_CONFIG_PLLN_237                0x000000ED
#define RCC_CONFIG_PLLN_238                0x000000EE
#define RCC_CONFIG_PLLN_239                0x000000EF
#define RCC_CONFIG_PLLN_240                0x000000F0
#define RCC_CONFIG_PLLN_241                0x000000F1
#define RCC_CONFIG_PLLN_242                0x000000F2
#define RCC_CONFIG_PLLN_243                0x000000F3
#define RCC_CONFIG_PLLN_244                0x000000F4
#define RCC_CONFIG_PLLN_245                0x000000F5
#define RCC_CONFIG_PLLN_246                0x000000F6
#define RCC_CONFIG_PLLN_247                0x000000F7
#define RCC_CONFIG_PLLN_248                0x000000F8
#define RCC_CONFIG_PLLN_249                0x000000F9
#define RCC_CONFIG_PLLN_250                0x000000FA
#define RCC_CONFIG_PLLN_251                0x000000FB
#define RCC_CONFIG_PLLN_252                0x000000FC
#define RCC_CONFIG_PLLN_253                0x000000FD
#define RCC_CONFIG_PLLN_254                0x000000FE
#define RCC_CONFIG_PLLN_255                0x000000FF
#define RCC_CONFIG_PLLN_256                0x00000100
#define RCC_CONFIG_PLLN_257                0x00000101
#define RCC_CONFIG_PLLN_258                0x00000102
#define RCC_CONFIG_PLLN_259                0x00000103
#define RCC_CONFIG_PLLN_260                0x00000104
#define RCC_CONFIG_PLLN_261                0x00000105
#define RCC_CONFIG_PLLN_262                0x00000106
#define RCC_CONFIG_PLLN_263                0x00000107
#define RCC_CONFIG_PLLN_264                0x00000108
#define RCC_CONFIG_PLLN_265                0x00000109
#define RCC_CONFIG_PLLN_266                0x0000010A
#define RCC_CONFIG_PLLN_267                0x0000010B
#define RCC_CONFIG_PLLN_268                0x0000010C
#define RCC_CONFIG_PLLN_269                0x0000010D
#define RCC_CONFIG_PLLN_270                0x0000010E
#define RCC_CONFIG_PLLN_271                0x0000010F
#define RCC_CONFIG_PLLN_272                0x00000110
#define RCC_CONFIG_PLLN_273                0x00000111
#define RCC_CONFIG_PLLN_274                0x00000112
#define RCC_CONFIG_PLLN_275                0x00000113
#define RCC_CONFIG_PLLN_276                0x00000114
#define RCC_CONFIG_PLLN_277                0x00000115
#define RCC_CONFIG_PLLN_278                0x00000116
#define RCC_CONFIG_PLLN_279                0x00000117
#define RCC_CONFIG_PLLN_280                0x00000118
#define RCC_CONFIG_PLLN_281                0x00000119
#define RCC_CONFIG_PLLN_282                0x0000011A
#define RCC_CONFIG_PLLN_283                0x0000011B
#define RCC_CONFIG_PLLN_284                0x0000011C
#define RCC_CONFIG_PLLN_285                0x0000011D
#define RCC_CONFIG_PLLN_286                0x0000011E
#define RCC_CONFIG_PLLN_287                0x0000011F
#define RCC_CONFIG_PLLN_288                0x00000120
#define RCC_CONFIG_PLLN_289                0x00000121
#define RCC_CONFIG_PLLN_290                0x00000122
#define RCC_CONFIG_PLLN_291                0x00000123
#define RCC_CONFIG_PLLN_292                0x00000124
#define RCC_CONFIG_PLLN_293                0x00000125
#define RCC_CONFIG_PLLN_294                0x00000126
#define RCC_CONFIG_PLLN_295                0x00000127
#define RCC_CONFIG_PLLN_296                0x00000128
#define RCC_CONFIG_PLLN_297                0x00000129
#define RCC_CONFIG_PLLN_298                0x0000012A
#define RCC_CONFIG_PLLN_299                0x0000012B
#define RCC_CONFIG_PLLN_300                0x0000012C
#define RCC_CONFIG_PLLN_301                0x0000012D
#define RCC_CONFIG_PLLN_302                0x0000012E
#define RCC_CONFIG_PLLN_303                0x0000012F
#define RCC_CONFIG_PLLN_304                0x00000130
#define RCC_CONFIG_PLLN_305                0x00000131
#define RCC_CONFIG_PLLN_306                0x00000132
#define RCC_CONFIG_PLLN_307                0x00000133
#define RCC_CONFIG_PLLN_308                0x00000134
#define RCC_CONFIG_PLLN_309                0x00000135
#define RCC_CONFIG_PLLN_310                0x00000136
#define RCC_CONFIG_PLLN_311                0x00000137
#define RCC_CONFIG_PLLN_312                0x00000138
#define RCC_CONFIG_PLLN_313                0x00000139
#define RCC_CONFIG_PLLN_314                0x0000013A
#define RCC_CONFIG_PLLN_315                0x0000013B
#define RCC_CONFIG_PLLN_316                0x0000013C
#define RCC_CONFIG_PLLN_317                0x0000013D
#define RCC_CONFIG_PLLN_318                0x0000013E
#define RCC_CONFIG_PLLN_319                0x0000013F
#define RCC_CONFIG_PLLN_320                0x00000140
#define RCC_CONFIG_PLLN_321                0x00000141
#define RCC_CONFIG_PLLN_322                0x00000142
#define RCC_CONFIG_PLLN_323                0x00000143
#define RCC_CONFIG_PLLN_324                0x00000144
#define RCC_CONFIG_PLLN_325                0x00000145
#define RCC_CONFIG_PLLN_326                0x00000146
#define RCC_CONFIG_PLLN_327                0x00000147
#define RCC_CONFIG_PLLN_328                0x00000148
#define RCC_CONFIG_PLLN_329                0x00000149
#define RCC_CONFIG_PLLN_330                0x0000014A
#define RCC_CONFIG_PLLN_331                0x0000014B
#define RCC_CONFIG_PLLN_332                0x0000014C
#define RCC_CONFIG_PLLN_333                0x0000014D
#define RCC_CONFIG_PLLN_334                0x0000014E
#define RCC_CONFIG_PLLN_335                0x0000014F
#define RCC_CONFIG_PLLN_336                0x00000150
#define RCC_CONFIG_PLLN_337                0x00000151
#define RCC_CONFIG_PLLN_338                0x00000152
#define RCC_CONFIG_PLLN_339                0x00000153
#define RCC_CONFIG_PLLN_340                0x00000154
#define RCC_CONFIG_PLLN_341                0x00000155
#define RCC_CONFIG_PLLN_342                0x00000156
#define RCC_CONFIG_PLLN_343                0x00000157
#define RCC_CONFIG_PLLN_344                0x00000158
#define RCC_CONFIG_PLLN_345                0x00000159
#define RCC_CONFIG_PLLN_346                0x0000015A
#define RCC_CONFIG_PLLN_347                0x0000015B
#define RCC_CONFIG_PLLN_348                0x0000015C
#define RCC_CONFIG_PLLN_349                0x0000015D
#define RCC_CONFIG_PLLN_350                0x0000015E
#define RCC_CONFIG_PLLN_351                0x0000015F
#define RCC_CONFIG_PLLN_352                0x00000160
#define RCC_CONFIG_PLLN_353                0x00000161
#define RCC_CONFIG_PLLN_354                0x00000162
#define RCC_CONFIG_PLLN_355                0x00000163
#define RCC_CONFIG_PLLN_356                0x00000164
#define RCC_CONFIG_PLLN_357                0x00000165
#define RCC_CONFIG_PLLN_358                0x00000166
#define RCC_CONFIG_PLLN_359                0x00000167
#define RCC_CONFIG_PLLN_360                0x00000168
#define RCC_CONFIG_PLLN_361                0x00000169
#define RCC_CONFIG_PLLN_362                0x0000016A
#define RCC_CONFIG_PLLN_363                0x0000016B
#define RCC_CONFIG_PLLN_364                0x0000016C
#define RCC_CONFIG_PLLN_365                0x0000016D
#define RCC_CONFIG_PLLN_366                0x0000016E
#define RCC_CONFIG_PLLN_367                0x0000016F
#define RCC_CONFIG_PLLN_368                0x00000170
#define RCC_CONFIG_PLLN_369                0x00000171
#define RCC_CONFIG_PLLN_370                0x00000172
#define RCC_CONFIG_PLLN_371                0x00000173
#define RCC_CONFIG_PLLN_372                0x00000174
#define RCC_CONFIG_PLLN_373                0x00000175
#define RCC_CONFIG_PLLN_374                0x00000176
#define RCC_CONFIG_PLLN_375                0x00000177
#define RCC_CONFIG_PLLN_376                0x00000178
#define RCC_CONFIG_PLLN_377                0x00000179
#define RCC_CONFIG_PLLN_378                0x0000017A
#define RCC_CONFIG_PLLN_379                0x0000017B
#define RCC_CONFIG_PLLN_380                0x0000017C
#define RCC_CONFIG_PLLN_381                0x0000017D
#define RCC_CONFIG_PLLN_382                0x0000017E
#define RCC_CONFIG_PLLN_383                0x0000017F
#define RCC_CONFIG_PLLN_384                0x00000180
#define RCC_CONFIG_PLLN_385                0x00000181
#define RCC_CONFIG_PLLN_386                0x00000182
#define RCC_CONFIG_PLLN_387                0x00000183
#define RCC_CONFIG_PLLN_388                0x00000184
#define RCC_CONFIG_PLLN_389                0x00000185
#define RCC_CONFIG_PLLN_390                0x00000186
#define RCC_CONFIG_PLLN_391                0x00000187
#define RCC_CONFIG_PLLN_392                0x00000188
#define RCC_CONFIG_PLLN_393                0x00000189
#define RCC_CONFIG_PLLN_394                0x0000018A
#define RCC_CONFIG_PLLN_395                0x0000018B
#define RCC_CONFIG_PLLN_396                0x0000018C
#define RCC_CONFIG_PLLN_397                0x0000018D
#define RCC_CONFIG_PLLN_398                0x0000018E
#define RCC_CONFIG_PLLN_399                0x0000018F
#define RCC_CONFIG_PLLN_400                0x00000190
#define RCC_CONFIG_PLLN_401                0x00000191
#define RCC_CONFIG_PLLN_402                0x00000192
#define RCC_CONFIG_PLLN_403                0x00000193
#define RCC_CONFIG_PLLN_404                0x00000194
#define RCC_CONFIG_PLLN_405                0x00000195
#define RCC_CONFIG_PLLN_406                0x00000196
#define RCC_CONFIG_PLLN_407                0x00000197
#define RCC_CONFIG_PLLN_408                0x00000198
#define RCC_CONFIG_PLLN_409                0x00000199
#define RCC_CONFIG_PLLN_410                0x0000019A
#define RCC_CONFIG_PLLN_411                0x0000019B
#define RCC_CONFIG_PLLN_412                0x0000019C
#define RCC_CONFIG_PLLN_413                0x0000019D
#define RCC_CONFIG_PLLN_414                0x0000019E
#define RCC_CONFIG_PLLN_415                0x0000019F
#define RCC_CONFIG_PLLN_416                0x000001A0
#define RCC_CONFIG_PLLN_417                0x000001A1
#define RCC_CONFIG_PLLN_418                0x000001A2
#define RCC_CONFIG_PLLN_419                0x000001A3
#define RCC_CONFIG_PLLN_420                0x000001A4
#define RCC_CONFIG_PLLN_421                0x000001A5
#define RCC_CONFIG_PLLN_422                0x000001A6
#define RCC_CONFIG_PLLN_423                0x000001A7
#define RCC_CONFIG_PLLN_424                0x000001A8
#define RCC_CONFIG_PLLN_425                0x000001A9
#define RCC_CONFIG_PLLN_426                0x000001AA
#define RCC_CONFIG_PLLN_427                0x000001AB
#define RCC_CONFIG_PLLN_428                0x000001AC
#define RCC_CONFIG_PLLN_429                0x000001AD
#define RCC_CONFIG_PLLN_430                0x000001AE
#define RCC_CONFIG_PLLN_431                0x000001AF
#define RCC_CONFIG_PLLN_432                0x000001B0

/*``````````````````````````````````````` PLLP VALUES ``````````````````````````````````````*/
#define RCC_CONFIG_PLLP_2				   0x00000000
#define RCC_CONFIG_PLLP_4				   0x00010000
#define RCC_CONFIG_PLLP_6				   0x00020000
#define RCC_CONFIG_PLLP_8				   0x00030000

/*``````````````````````````````````````` PLLQ VALUES ``````````````````````````````````````*/
#define RCC_CONFIG_PLLQ_2				   0x02000000
#define RCC_CONFIG_PLLQ_3				   0x03000000
#define RCC_CONFIG_PLLQ_4				   0x04000000
#define RCC_CONFIG_PLLQ_5				   0x05000000
#define RCC_CONFIG_PLLQ_6			       0x06000000
#define RCC_CONFIG_PLLQ_7				   0x07000000
#define RCC_CONFIG_PLLQ_8				   0x08000000
#define RCC_CONFIG_PLLQ_9				   0x09000000
#define RCC_CONFIG_PLLQ_10				   0x0A000000
#define RCC_CONFIG_PLLQ_11				   0x0B000000
#define RCC_CONFIG_PLLQ_12				   0x0C000000	
#define RCC_CONFIG_PLLQ_13				   0x0D000000	
#define RCC_CONFIG_PLLQ_14				   0x0E000000
#define RCC_CONFIG_PLLQ_15                 0x0F000000

/************************************* SELECT SYSTEM CLOCK **********************************/
#define RCC_SYSClOCK_HSI		0x00000000
#define RCC_SYSClOCK_HSE		0x00000001
#define RCC_SYSClOCK_PLL		0x00000002

/************************************* CONTROL PERIPHERAL **********************************/
/*```````````````````````````````````` AHB1 PERIPHERALS ```````````````````````````````````*/
#define RCC_AHB1PERIPH_GPIOA	0x00000001
#define RCC_AHB1PERIPH_GPIOB	0x00000002
#define RCC_AHB1PERIPH_GPIOC	0x00000004
#define RCC_AHB1PERIPH_GPIOD	0x00000008
#define RCC_AHB1PERIPH_GPIOE	0x00000010
#define RCC_AHB1PERIPH_GPIOH	0x00000080
#define RCC_AHB1PERIPH_CRC		0x00001000
#define RCC_AHB1PERIPH_DMA1		0x00200000
#define RCC_AHB1PERIPH_DMA2		0x00400000

/*```````````````````````````````````` AHB2 PERIPHERAL ```````````````````````````````````*/
#define RCC_AHB2PERIPH_OTGFS	0x00000080

/*```````````````````````````````````` APB1 PERIPHERALS ```````````````````````````````````*/
#define RCC_APB1PERIPH_TIM2		0x00000001
#define RCC_APB1PERIPH_TIM3		0x00000002
#define RCC_APB1PERIPH_TIM4		0x00000004
#define RCC_APB1PERIPH_TIM5		0x00000008
#define RCC_APB1PERIPH_WWDG		0x00000800
#define RCC_APB1PERIPH_SPI2		0x00004000
#define RCC_APB1PERIPH_SPI3		0x00008000
#define RCC_APB1PERIPH_USART2	0x00020000
#define RCC_APB1PERIPH_I2C1		0x00200000
#define RCC_APB1PERIPH_I2C2		0x00400000
#define RCC_APB1PERIPH_I2C3		0x00800000
#define RCC_APB1PERIPH_PWR 		0x10000000

 /*```````````````````````````````````` APB2 PERIPHERALS ```````````````````````````````````*/
#define RCC_APB2PERIPH_TIM1		0x00000001
#define RCC_APB2PERIPH_USART1	0X00000010
#define RCC_APB2PERIPH_USART6	0X00000020
#define RCC_APB2PERIPH_ADC1		0X00000100
#define RCC_APB2PERIPH_SDIO		0X00000800
#define RCC_APB2PERIPH_SPI1		0X00001000
#define RCC_APB2PERIPH_SPI4		0X00002000
#define RCC_APB2PERIPH_SYSCFG	0X00004000
#define RCC_APB2PERIPH_TIM9		0X00010000
#define RCC_APB2PERIPH_TIM10	0X00020000
#define RCC_APB2PERIPH_TIM11	0X00040000

/************************ CONFIGURE PRESCALERS FOR AHB, APB1 AND APB2  **********************/
/*````````````````````````````````````` AHB PRESCALERS ````````````````````````````````````*/
#define RCC_AHBPRESCAL_NOPRE	0x00000000
#define RCC_AHBPRESCAL_2 		0x00000080
#define RCC_AHBPRESCAL_4 		0x00000090
#define RCC_AHBPRESCAL_8		0x000000A0
#define RCC_AHBPRESCAL_16 		0x000000B0
#define RCC_AHBPRESCAL_64 		0x000000C0
#define RCC_AHBPRESCAL_128 		0x000000D0
#define RCC_AHBPRESCAL_256		0x000000E0
#define RCC_AHBPRESCAL_512		0x000000F0

/*````````````````````````````````````` APB1 PRESCALERS ````````````````````````````````````*/
#define RCC_APB1PRESCAL_NOPRE 	0x00000000
#define RCC_APB1PRESCAL_2 		0x00001000
#define RCC_APB1PRESCAL_4 		0x00001400
#define RCC_APB1PRESCAL_8		0x00001800
#define RCC_APB1PRESCAL_16		0x00001C00

/*````````````````````````````````````` APB2 PRESCALERS ````````````````````````````````````*/
#define RCC_APB2PRESCAL_NOPRE 	0x00000000
#define RCC_APB2PRESCAL_2 		0x00008000
#define RCC_APB2PRESCAL_4 		0x0000A000
#define RCC_APB2PRESCAL_8		0x0000C000
#define RCC_APB2PRESCAL_16		0x0000E000

/************************ Get SYSTEM CLOCK  **********************/
#define RCC_SELECTEDSYSClOCK_HSI		0x00000000
#define RCC_SELECTEDSYSClOCK_HSE		0x00000004
#define RCC_SELECTEDSYSClOCK_PLL		0x00000008

/*************************  RCC_CheckRdyStatus *************************/
#define RCC_CLOCK_RDY_STATUS_HSI	0x00000002
#define RCC_CLOCK_RDY_STATUS_HSE    0x00020000
#define RCC_CLOCK_RDY_STATUS_PLL    0x02000000

/*---------------------------------------- Types -------------------------------------------*/

/*
 * @brief  Enum used for error status
*/
typedef enum 
{
	RCC_OK,
	RCC_ClockReady,
	RCC_InvalidParameter,
	RCC_InvalidPll_M_Config,
	RCC_InvalidPll_N_Config,
	RCC_InvalidPll_P_Config,
	RCC_InvalidPll_Q_Config,
	RCC_NullPointer,
	RCC_ClockNotReady
	
}RCC_ErrorStatus_t;


/*--------------------------------- Functions Prototype ------------------------------------*/
/*========================== CONTROL ANY CLOCK IN THE SYSTEM ==============================*/

/*.................................. RCC_EnableClock ....................................*/
/**
  * @brief  Enable any Clock in the System.
  *       
  * @param  RCC_ClOCK: uint32_t that represents one of the clocks in the system
  *         which are(RCC_ClOCK_HSI | RCC_ClOCK_HSE | RCC_ClOCK_PLL).
  *         
  * @note   After Reset the ClOCK_HSI selected as system clock
  *
  * @return RCC_ErrorStatus_t 
  */
RCC_ErrorStatus_t RCC_EnableClock(uint32_t RCC_ClOCK);

/*.................................. RCC_DisableSysClock ....................................*/
/**
  * @brief  Disable any Clock in the System.
  *       
  * @param  RCC_ClOCK: uint32_t that represents one of the system clocks 
  *         which are(RCC_ClOCK_HSI | RCC_ClOCK_HSE | RCC_ClOCK_PLL).
  *         
  * @note  If you want to turn off one of the Clocks, Make sure it isn`t selected 
  *         as a system clock.
  *
  * @note  If PLL is selected as system Clock, Don`t turn off its source.
  *
  * @return RCC_ErrorStatus_t 
  */
RCC_ErrorStatus_t RCC_DisableSysClock(uint32_t RCC_ClOCK);
 
/*================================== CONFIGURE PLL  =====================================*/
/*................................. RCC_ConfigurePLL ....................................*/

/**
  * @brief  Configure  Configure PLL cLOCK.
  *       
  * @param  RCC_CONFIG_PLLM: Division factor for the main PLL (PLL) 
  *						 within range ( 2 ≤ PLLM ≤ 63 )- use MACROS -
  *         
  * @param  CONFIG_PLLN: Main PLL (PLL) multiplication factor for VCO
  *						 within range ( 192 ≤ PLLN ≤ 432 )- use MACROS -
  * 
  * @param  CONFIG_PLLP: Main PLL (PLL) division factor for main system clock
  *						 within range ( PLLP = 2, 4, 6, or 8 )- use MACROS - 
  * 
  * @param  CONFIG_PLLQ: Main PLL (PLL) division factor for USB OTG FS, SDIO and random number generator clocks
  *						 within range ( 2 ≤PLLQ ≤15 )- use MACROS -
  * 
  * @note   You must turn off SYSCLOCK_PLL before configuration
  *
  * @return RCC_ErrorStatus_t 
  */
RCC_ErrorStatus_t RCC_ConfigurePLL(uint32_t RCC_Config_PllM, uint32_t RCC_Config_PllN,uint32_t RCC_Config_PllP,uint32_t RCC_Config_PllQ);
/*================================ SELECT SYSTEM CLOCK ==================================*/
/*................................ RCC_SelectSysClock ...................................*/
/**
  * @brief  Switch to the desired Clock to be the System clock.
  *       
  * @param  RCC_Sysclock: uint32_t that represents one of the system clocks 
  *         which are(RCC_SYSClOCK_HSI | RCC_SYSClOCK_HSE | RCC_SYSClOCK_PLL).
  *         
  * @note   The selected clock must be on and ready before you  
  *         select it as a system clock.
  *
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_SelectSysClock(uint8_t RCC_Sysclock);

/*================================ CONTROL PERIPHERAL ==================================*/
/*............................... RCC_EnableAHB1Periphs .................................*/
/**
  * @brief  Enable Peripherals which are connected to AHB1 Bus.
  *       
  * @param  RCC_AHB1Periph: RCC_AHB1PERIPH_DMA1 |  RCC_AHB1PERIPH_DMA2 | RCC_AHB1PERIPH_CRC | 
  *         RCC_AHB1PERIPH_GPIOH | RCC_AHB1PERIPH_GPIOE | RCC_AHB1PERIPH_GPIOD | RCC_AHB1PERIPH_GPIOC
  *         | RCC_AHB1PERIPH_GPIOB | RCC_AHB1PERIPH_GPIOA
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_EnableAHB1Periphs(uint32_t RCC_AHB1Periph);

/*............................... RCC_EnableAHB2Periphs .................................*/
/**
  * @brief  Enable Peripherals which are connected to AHB2 Bus.
  *       
  * @param  RCC_AHB2Periph: RCC_AHB2PERIPH_OTGFS
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_EnableAHB2Periphs(uint32_t RCC_AHB2Periph);

/*............................... RCC_EnableAPB1Periphs .................................*/
/**
  * @brief  Enable Peripherals which are connected to APB1 Bus.
  *       
  * @param  RCC_APB1Periph: RCC_APB1PERIPH_PWR |  RCC_APB1PERIPH_I2C3 | RCC_APB1PERIPH_I2C2 | RCC_APB1PERIPH_I2C1
  *         RCC_APB1PERIPH_USART2 | RCC_APB1PERIPH_SPI3 | RCC_APB1PERIPH_SPI2 | RCC_APB1PERIPH_WWDG
  *			RCC_APB1PERIPH_TIM5 | RCC_APB1PERIPH_TIM4 | RCC_APB1PERIPH_TIM3 | RCC_APB1PERIPH_TIM2
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_EnableAPB1Periphs(uint32_t RCC_APB1Periph);
 
 /*............................... RCC_EnableAPB2Periphs .................................*/
/**
  * @brief  Enable Peripherals which are connected to APB2 Bus.
  *       
  * @param  RCC_APB2Periph: RCC_APB2PERIPH_TIM11 |  RCC_APB2PERIPH_TIM10 | RCC_APB2PERIPH_TIM9 | RCC_APB2PERIPH_SYSCFG
  *         RCC_APB2PERIPH_SPI4 | RCC_APB2PERIPH_SPI1 | RCC_APB2PERIPH_SDIO |RCC_APB2PERIPH_ADC1
  *			RCC_APB2PERIPH_USART6 | RCC_APB2PERIPH_USART1 |  RCC_APB2PERIPH_TIM1
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_EnableAPB2Periphs(uint32_t RCC_APB2Periph);
 
/*............................... RCC_DisableAHB1Periphs .................................*/
/**
  * @brief  Disable Peripherals which are connected to AHB1 Bus as you select.
  *       
  * @param 	RCC_AHB1Periph: RCC_AHB1PERIPH_DMA1 |  RCC_AHB1PERIPH_DMA2 | RCC_AHB1PERIPH_CRC | 
  *         RCC_AHB1PERIPH_GPIOH | RCC_AHB1PERIPH_GPIOE | RCC_AHB1PERIPH_GPIOD | RCC_AHB1PERIPH_GPIOC
  *         | RCC_AHB1PERIPH_GPIOB | RCC_AHB1PERIPH_GPIOA
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_DisableAHB1Periphs(uint32_t RCC_AHB1Periph);

/*............................... RCC_DisableAHB2Periphs .................................*/
/**
  * @brief  Disable Peripherals which are connected to AHB2 Bus.
  *       
  * @param   RCC_AHB2Periph: RCC_AHB2PERIPH_OTGFS
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_DisableAHB2Periphs(uint32_t RCC_AHB2Periph);

/*............................... RCC_DisableAPB1Periphs .................................*/
/**
  * @brief  Disable Peripherals which are connected to APB1 Bus.
  *       
  * @param  RCC_APB1Periph: RCC_APB1PERIPH_PWR |  RCC_APB1PERIPH_I2C3 | RCC_APB1PERIPH_I2C2 | RCC_APB1PERIPH_I2C1
  *         RCC_APB1PERIPH_USART2 | RCC_APB1PERIPH_SPI3 | RCC_APB1PERIPH_SPI2 | RCC_APB1PERIPH_WWDG
  *			RCC_APB1PERIPH_TIM5 | RCC_APB1PERIPH_TIM4 | RCC_APB1PERIPH_TIM3 | RCC_APB1PERIPH_TIM2
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_DisableAPB1Periphs(uint32_t RCC_APB1Periph);
 
 /*............................... RCC_DisableAPB2Periphs .................................*/
/**
  * @brief  Disable Peripherals which are connected to APB2 Bus.
  *       
  * @param  RCC_APB2Periph: RCC_APB2PERIPH_TIM11 | RCC_APB2PERIPH_TIM10 | RCC_APB2PERIPH_TIM9 | RCC_APB2PERIPH_SYSCFG
  *         RCC_APB2PERIPH_SPI4 | RCC_APB2PERIPH_SPI1 | RCC_APB2PERIPH_SDIO | RCC_APB2PERIPH_ADC1
  *			RCC_APB2PERIPH_USART6 | RCC_APB2PERIPH_USART1 | RCC_APB2PERIPH_TIM1
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_DisableAPB2Periphs(uint32_t RCC_APB2Periph);

/*==================== CONFIGURE PRESCALERS FOR AHB, APB1 AND APB2 ========================*/
/*............................... RCC_CofigureAHBPrescaler .................................*/
 /**
  * @brief  Configure AHB Bus Prescaler.
  *       
  * @param  RCC_AHBPrescal: RCC_AHBPRESCAL_NOPRE |  RCC_AHBPRESCAL_2 | RCC_AHBPRESCAL_4 |RCC_AHBPRESCAL_8
  *         RCC_AHBPRESCAL_16 | RCC_AHBPRESCAL_64 | RCC_AHBPRESCAL_128 | RCC_AHBPRESCAL_256
  *			RCC_AHBPRESCAL_512
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_CofigureAHBPrescaler(uint32_t RCC_AHBPrescal);

/*............................... RCC_CofigureAPB1Prescaler .................................*/
 /**
  * @brief  Configure  APB Low speed prescaler (APB1).
  *       
  * @param  RCC_APB1Prescal: RCC_APB1PRESCAL_NOPRE |  RCC_APB1PRESCAL_2 | RCC_APB1PRESCAL_4 | RCC_APB1PRESCAL_8
  *         RCC_APB1PRESCAL_16 
  *
  * @note   The software has to set these bits correctly not to exceed 42 MHz on this domain
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_CofigureAPB1Prescaler(uint32_t RCC_APB1Prescal);

/*............................... RCC_CofigureAPB2Prescaler .................................*/
 /**
  * @brief  Configure : APB high-speed prescaler (APB2).
  *       
  * @param  RCC_APB2Prescal:RCC_APB2PRESCAL_NOPRE |  RCC_APB2PRESCAL_2 | RCC_APB2PRESCAL_4 | RCC_APB2PRESCAL_8
  *         RCC_APB2PRESCAL_16 
  *
  * @note   The software has to set these bits correctly not to exceed 84 MHz on this domain. 
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_CofigureAPB2Prescaler(uint32_t RCC_APB2Prescal);

/*==================================== Get SYSTEM CLOCK ====================================*/
/*.................................... RCC_GetSysClock .....................................*/
/**
  * @brief  Return the runing system clock.
  *       
  * @param  SysClock: stores the runing system clock.
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_GetSysClock(uint32_t* SysClock);
 
 /*================================= SELECT PLL CLOCK SOURCE ================================*/
 /*.................................. RCC_SetPllSourceHSI ...................................*/
 /**
  * @brief  Select Pll Source with HSI clock.
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_SetPllSourceHSI();
 
 /*.................................. RCC_SetPllSourceHSE ...................................*/
 /**
  * @brief  Select Pll Source with HSE clock.
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_SetPllSourceHSE();
 
 /*================================== CHECK READY FLAG STATUS =================================*/
 /*.................................... RCC_CheckRdyStatus ....................................*/
 /**
  * @brief  ChecK ready flag status for each clock
  *       
  * @param  RCC_CLockRDYStatus: RCC_CLOCK_RDY_STATUS_HSI | RCC_CLOCK_RDY_STATUS_HSE | RCC_CLOCK_RDY_STATUS_PLL
  *
  * @return RCC_ErrorStatus_t 
  */
 RCC_ErrorStatus_t RCC_CheckRdyStatus(uint32_t RCC_CLock_RDY_Status);


#endif  //RCC_H_