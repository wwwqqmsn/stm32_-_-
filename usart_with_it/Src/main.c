/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "stmflash.h" 
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#include <string.h>
 
#define RXBUFFERSIZE 256     //???????
//要写入到STM32 FLASH的字符串数组
unsigned int TEXT_Buffer[12];
#define SIZE sizeof(TEXT_Buffer)	 	//数组长度
unsigned int  datatemp[SIZE];	
#define FLASH_SAVE_ADDR  0X08020000 	//设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小+0X08000000)

unsigned int count[12];
unsigned char RxBuffer[RXBUFFERSIZE];   //????
uint8_t aRxBuffer;			//??????
uint8_t Uart1_Rx_Cnt = 0;		//??????
uint8_t IDH=0,IDL=0;
unsigned int ID=0;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/**
  * ????: ???c???printf?DEBUG_USARTx
  * ????: ?
  * ? ? ?: ?
  * ?    ?:?
  */
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
  return ch;
}
 
/**
  * ????: ???c???getchar,scanf?DEBUG_USARTx
  * ????: ?
  * ? ? ?: ?
  * ?    ?:?
  */
int fgetc(FILE *f)
{
  uint8_t ch = 0;
  HAL_UART_Receive(&huart1, &ch, 1, 0xffff);
  return ch;
}

unsigned int  GPIO_ReCMD(GPIO_TypeDef* GPIOx)
{
	uint16_t cmd;
   cmd= GPIOx->IDR;
	return cmd;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);

STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer,SIZE);
if(TEXT_Buffer[0]==0xffffffff&&TEXT_Buffer[1]==0xffffffff&&TEXT_Buffer[2]==0xffffffff&&TEXT_Buffer[3]==0xffffffff)
{//printf("的确是0xffffffff");
TEXT_Buffer[0]=0x00;TEXT_Buffer[1]=0x00;TEXT_Buffer[2]=0x00;TEXT_Buffer[3]=0x00;TEXT_Buffer[4]=0x00;TEXT_Buffer[5]=0x00;TEXT_Buffer[6]=0x00;
	TEXT_Buffer[7]=0x00;TEXT_Buffer[8]=0x00;TEXT_Buffer[9]=0x00;TEXT_Buffer[10]=0x00;TEXT_Buffer[11]=0x00;
	
	STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer,SIZE);
}
//STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    HAL_Delay(4000);
		ID=GPIO_ReCMD(GPIOB);
		IDH=ID>>8;
		IDL=ID;
//		char a=0xff;
//		HAL_UART_Transmit(&huart1, (uint8_t *)&TEXT_Buffer[0], 1,0xFFFF);
//		HAL_UART_Transmit(&huart1, (uint8_t *)&TEXT_Buffer[1], 1,0xFFFF);
//		HAL_UART_Transmit(&huart1, (uint8_t *)&TEXT_Buffer[2], 1,0xFFFF);
//		HAL_UART_Transmit(&huart1, (uint8_t *)&TEXT_Buffer[3], 1,0xFFFF);
//		HAL_UART_Transmit(&huart1, (uint8_t *)&TEXT_Buffer[4], 1,0xFFFF);
//		HAL_UART_Transmit(&huart1, 0x00, 1,0xFFFF);
//		HAL_UART_Transmit(&huart1, (uint8_t *)0x00, 1,0xFFFF);
//		printf("%x\r\n",GPIO_ReCMD(GPIOB));
		//printf("%x",TEXT_Buffer[0]);
//		//GPIO_ReCMD(GPIOB);
//		for(int i=0;i<1;i++)
//		//printf("NO.%d count is %d\r\n",i+1,count[i]);
//		printf("1\r\n");
//		STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);
//		printf("%s",datatemp);
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin : PC0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PC1 PC2 PC3 PC4 
                           PC5 PC6 PC7 PC8 
                           PC9 PC10 PC11 PC12 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4 
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8 
                          |GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB10 
                           PB11 PB12 PB13 PB14 
                           PB15 PB3 PB4 PB5 
                           PB6 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10 
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
                          |GPIO_PIN_15|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5 
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 4, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 6, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 7, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE BEGIN 4 */
 
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_UART_TxCpltCallback could be implemented in the user file
   */
 
	if(Uart1_Rx_Cnt >= 255)  //????
	{
		Uart1_Rx_Cnt = 0;
		memset(RxBuffer,0x00,sizeof(RxBuffer));
		HAL_UART_Transmit(&huart1, (uint8_t *)"????", 10,0xFFFF); 	
        
	}
	else
	{
		RxBuffer[Uart1_Rx_Cnt++] = aRxBuffer;   //??????
	
		if((RxBuffer[Uart1_Rx_Cnt-1] == 0xAA)&&(RxBuffer[Uart1_Rx_Cnt-2] == 0xAA)&&(RxBuffer[Uart1_Rx_Cnt-3] ==0xAA)&&(RxBuffer[Uart1_Rx_Cnt-4] == 0xAA)) //?????
		{
			STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);
			char a=0xAA,b=0x01;//b用痈窀柃
		//	IDH=0x01;
			//IDL=0x04;//改这个ID
			
			
			//16进制发送部分
			 //printf("!!!!");printf("$$$$");printf("#####");
			
			HAL_UART_Transmit(&huart1, (uint8_t *)&b, 1,0xFFFF);
			HAL_UART_Transmit(&huart1, (uint8_t *)&b, 1,0xFFFF);
			HAL_UART_Transmit(&huart1, (uint8_t *)&b, 1,0xFFFF);
			HAL_UART_Transmit(&huart1, (uint8_t *)&b, 1,0xFFFF);
			HAL_UART_Transmit(&huart1, (uint8_t *)&b, 1,0xFFFF);
			HAL_UART_Transmit(&huart1, (uint8_t *)&b, 1,0xFFFF);
			HAL_UART_Transmit(&huart1, (uint8_t *)&b, 1,0xFFFF);
			HAL_UART_Transmit(&huart1, (uint8_t *)&b, 1,0xFFFF);
			
			
			HAL_UART_Transmit(&huart1, (uint8_t *)&IDH, 1,0xFFFF);
			HAL_UART_Transmit(&huart1, (uint8_t *)&IDL, 1,0xFFFF);
						HAL_UART_Transmit(&huart1, (uint8_t *)&b, 1,0xFFFF);
			for(int i=0;i<12;i++)//这里是16进制发送
			{

			HAL_UART_Transmit(&huart1, (uint8_t *)&datatemp[i], 1,0xFFFF);
			}
			//16进制发送部分
			
//			//字符串发送部分
//			//printf("%d",IDH);
//			 printf("!!!!");
//			printf("%6d",IDL);
//			printf(",");
//			//printf("%d",0x00);
//			printf("%d",0x01);
//			//printf(",");
//			for(int i=0;i<12;i++)//这里是16进制发送
//			{
//      printf(",");
//			printf("%d",datatemp[i]);
//			}
//			printf("$$$$");
//			//字符串进制发送部分
//			
			
			
			
//			for(int i=0;i<12;i++)
//			{
//			HAL_UART_Transmit(&huart1, (uint8_t *)&TEXT_Buffer[i], 1,0xFFFF);
//			}
			//printf("%d",datatemp[0]);
//			HAL_UART_Transmit(&huart1, (uint8_t *)&RxBuffer, Uart1_Rx_Cnt,0xFFFF); //??????????
//            while(HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX);//??UART????
			Uart1_Rx_Cnt = 0;
			memset(RxBuffer,0x00,sizeof(RxBuffer)); //????
		}
	}
	
	HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);   //???????
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//	printf("interrupt\r\n");
	//////////////////////////////////////////////////////
	if(GPIO_Pin == GPIO_PIN_0)
	{
		HAL_Delay(1);//如果发生中断  是需要复位flash中的数据。
	//	printf("ZHONGDUANLE");
	//	if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_0)==GPIO_PIN_RESET)
		{	
			//printf("的确是0xffffffff");
  TEXT_Buffer[0]=0x00;TEXT_Buffer[1]=0x00;TEXT_Buffer[2]=0x00;TEXT_Buffer[3]=0x00;TEXT_Buffer[4]=0x00;TEXT_Buffer[5]=0x00;TEXT_Buffer[6]=0x00;
	TEXT_Buffer[7]=0x00;TEXT_Buffer[8]=0x00;TEXT_Buffer[9]=0x00;TEXT_Buffer[10]=0x00;TEXT_Buffer[11]=0x00;
	count[0]=0x00;count[1]=0x00;count[2]=0x00;count[3]=0x00;count[4]=0x00;count[5]=0x00;count[6]=0x00;
	count[7]=0x00;count[8]=0x00;count[9]=0x00;count[10]=0x00;count[11]=0x00;
			datatemp[0]=0x00;datatemp[1]=0x00;datatemp[2]=0x00;datatemp[3]=0x00;datatemp[4]=0x00;datatemp[5]=0x00;datatemp[6]=0x00;
	datatemp[7]=0x00;datatemp[8]=0x00;datatemp[9]=0x00;datatemp[10]=0x00;datatemp[11]=0x00;
	STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer,SIZE);

		}
	}
	////////////////////////////////////////////
	if(GPIO_Pin == GPIO_PIN_1)
	{
	//	HAL_Delay(1);
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1)==GPIO_PIN_RESET)
		{	
			count[0]++;
			TEXT_Buffer[0]++;
		}
	}
	if(GPIO_Pin == GPIO_PIN_2)
	{
	//	HAL_Delay(1);
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)==GPIO_PIN_RESET)
		{	
			count[1]++;TEXT_Buffer[1]++;
		}
	}
	if(GPIO_Pin == GPIO_PIN_3)
	{
	//	HAL_Delay(1);
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_3)==GPIO_PIN_RESET)
		{	
			count[2]++;TEXT_Buffer[2]++;
		}
	}
	if(GPIO_Pin == GPIO_PIN_4)
	{
	//	HAL_Delay(1);
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_4)==GPIO_PIN_RESET)
		{	
			count[3]++;TEXT_Buffer[3]++;
		}
	}
	if(GPIO_Pin == GPIO_PIN_5)
	{
	//	HAL_Delay(1);
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5)==GPIO_PIN_RESET)
		{	
			count[4]++;TEXT_Buffer[4]++;
		}
	}
	if(GPIO_Pin == GPIO_PIN_6)
	{
	//	HAL_Delay(1);
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_6)==GPIO_PIN_RESET)
		{	
			count[5]++;TEXT_Buffer[5]++;
		}
	}
	if(GPIO_Pin == GPIO_PIN_7)
	{
	//	HAL_Delay(1);
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_7)==GPIO_PIN_RESET)
		{	
			count[6]++;TEXT_Buffer[6]++;
		}
	}
	if(GPIO_Pin == GPIO_PIN_8)
	{
	//	HAL_Delay(1);
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_8)==GPIO_PIN_RESET)
		{	
			count[7]++;TEXT_Buffer[7]++;
		}
	}
	if(GPIO_Pin == GPIO_PIN_9)
	{
	//	HAL_Delay(1);
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_9)==GPIO_PIN_RESET)
		{	
			count[8]++;TEXT_Buffer[8]++;
		}
	}
	if(GPIO_Pin == GPIO_PIN_10)
	{
//		HAL_Delay(1);
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_10)==GPIO_PIN_RESET)
		{	
			count[9]++;TEXT_Buffer[9]++;
		}
	}
	if(GPIO_Pin == GPIO_PIN_11)
	{
//		HAL_Delay(1);
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_11)==GPIO_PIN_RESET)
		{	
			count[10]++;TEXT_Buffer[10]++;
		}
	}
	if(GPIO_Pin == GPIO_PIN_12)
	{
//		HAL_Delay(1);
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_12)==GPIO_PIN_RESET)
		{	
			count[11]++;TEXT_Buffer[11]++;
		}
	}
	
	
	STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer,SIZE);// jishu hou  bao cun  flash
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
