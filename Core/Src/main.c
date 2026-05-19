/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include "usbd_cdc_if.h"
#include "BoardLed.h"
#include "DAQ_Config.h"
#include "Trejser.h"
#include "Radio.h"
#include "Merenja.h"
#include "Kalendar.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

CRC_HandleTypeDef hcrc;

I2C_HandleTypeDef hi2c1;

RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi2;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TaskBlinky */
osThreadId_t TaskBlinkyHandle;
const osThreadAttr_t TaskBlinky_attributes = {
  .name = "TaskBlinky",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for TaskTrace */
osThreadId_t TaskTraceHandle;
const osThreadAttr_t TaskTrace_attributes = {
  .name = "TaskTrace",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for TaskDispecer */
osThreadId_t TaskDispecerHandle;
const osThreadAttr_t TaskDispecer_attributes = {
  .name = "TaskDispecer",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for TaskRadioComms */
osThreadId_t TaskRadioCommsHandle;
const osThreadAttr_t TaskRadioComms_attributes = {
  .name = "TaskRadioComms",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for TaskID */
osThreadId_t TaskIDHandle;
const osThreadAttr_t TaskID_attributes = {
  .name = "TaskID",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for d3 */
osThreadId_t d3Handle;
const osThreadAttr_t d3_attributes = {
  .name = "d3",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for d4 */
osThreadId_t d4Handle;
const osThreadAttr_t d4_attributes = {
  .name = "d4",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for d5 */
osThreadId_t d5Handle;
const osThreadAttr_t d5_attributes = {
  .name = "d5",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for d6 */
osThreadId_t d6Handle;
const osThreadAttr_t d6_attributes = {
  .name = "d6",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for TaskHwI2c */
osThreadId_t TaskHwI2cHandle;
const osThreadAttr_t TaskHwI2c_attributes = {
  .name = "TaskHwI2c",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for TaskHwSpi */
osThreadId_t TaskHwSpiHandle;
const osThreadAttr_t TaskHwSpi_attributes = {
  .name = "TaskHwSpi",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for TaskDigitalIn */
osThreadId_t TaskDigitalInHandle;
const osThreadAttr_t TaskDigitalIn_attributes = {
  .name = "TaskDigitalIn",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for TaskAnalogIn */
osThreadId_t TaskAnalogInHandle;
const osThreadAttr_t TaskAnalogIn_attributes = {
  .name = "TaskAnalogIn",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for qTrace */
osMessageQueueId_t qTraceHandle;
const osMessageQueueAttr_t qTrace_attributes = {
  .name = "qTrace"
};
/* Definitions for qRadioTx */
osMessageQueueId_t qRadioTxHandle;
const osMessageQueueAttr_t qRadioTx_attributes = {
  .name = "qRadioTx"
};
/* Definitions for qRadioRx */
osMessageQueueId_t qRadioRxHandle;
const osMessageQueueAttr_t qRadioRx_attributes = {
  .name = "qRadioRx"
};
/* Definitions for qRadioFwd */
osMessageQueueId_t qRadioFwdHandle;
const osMessageQueueAttr_t qRadioFwd_attributes = {
  .name = "qRadioFwd"
};
/* Definitions for mtxMeasCnt */
osMutexId_t mtxMeasCntHandle;
const osMutexAttr_t mtxMeasCnt_attributes = {
  .name = "mtxMeasCnt"
};
/* Definitions for EvtTrace */
osEventFlagsId_t EvtTraceHandle;
const osEventFlagsAttr_t EvtTrace_attributes = {
  .name = "EvtTrace"
};
/* Definitions for EvtGlobalRunStop */
osEventFlagsId_t EvtGlobalRunStopHandle;
const osEventFlagsAttr_t EvtGlobalRunStop_attributes = {
  .name = "EvtGlobalRunStop"
};
/* Definitions for EvtTaskHealth */
osEventFlagsId_t EvtTaskHealthHandle;
const osEventFlagsAttr_t EvtTaskHealth_attributes = {
  .name = "EvtTaskHealth"
};
/* Definitions for EvtTriggers */
osEventFlagsId_t EvtTriggersHandle;
const osEventFlagsAttr_t EvtTriggers_attributes = {
  .name = "EvtTriggers"
};
/* Definitions for EvtSpare2 */
osEventFlagsId_t EvtSpare2Handle;
const osEventFlagsAttr_t EvtSpare2_attributes = {
  .name = "EvtSpare2"
};
/* USER CODE BEGIN PV */


const uint32_t qWt = 10;					// wait za upis u queue
const uint32_t trcWt = 100;					// timeout za uart i usb trace facility
const uint32_t allMeasTmout = 1000U * 20;	// timeout da se zavrse sva merenja
uint32_t measCnt = 0;


// maksimalni flegovi
uint32_t flg_MAX = 0x7FFFFFFFU;

typedef enum {									// enum je potreban sa switch case
	flg_BLINK_ENABLED =				(1 << 0 ),

	flg_DIGITAL_ENABLED =			(1 << 1 ),
	flg_DIGITAL_IRQ =				(1 << 2 ),	// EXTI callback: digitalni ulaz se promenio
	flg_DIGITAL_REQUEST =			(1 << 3 ),	// neki task zahteva ocitavanje digitalnih ulaza
	flg_DIGITAL_PROCESSING_DONE =	(1 << 4 ),	// svi digitalni pinovi procitani i spremni za slanje
	flg_DIGITAL_TRIGGERED =			(1 << 5 ),	// svi digitalni pinovi procitani i spremni za slanje

	flg_ANALOG_ENABLED = 			(1 << 6 ),
	flg_ADC_CONV_CPLT_IRQ =			(1 << 7 ),	// ADC IRQ callback: zavrsena adc konverzija u pozadini i DMA je obavio svoje
	flg_ADC_REQUEST =				(1 << 8 ),	// neki task zahteva adc konverziju
	flg_ANALOG_PROCESSING_DONE =	(1 << 9 ),	// zavrsena analogna merenja ali ni jedan threshold nije prekoracen
	flg_ANALOG_TRIGGERED =			(1 << 10),	// zavrsena analogna merenja i neka vrednost je prekoracena

	flg_RADIO_ENABLED =				(1 << 11),

	evtflg_SPARE1_TRIGGER =			(1 << 12),
	evtflg_SPARE2_TRIGGER =			(1 << 13),
	evtflg_SPARE3_TRIGGER =			(1 << 14),
	evtflg_SPARE4_TRIGGER =			(1 << 15),
} Flegovi_t;

typedef enum {
	bit0 = 0,
	bit1 = 1,
	bit2 = 2,
	bit3 = 3,
	bit4 = 4,
	bit5 = 5,
	bit6 = 6,
	bit7 = 7,
} ExtiPosition_t;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_CRC_Init(void);
static void MX_I2C1_Init(void);
static void MX_RTC_Init(void);
static void MX_SPI2_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
void StartDefaultTask(void *argument);
void startTaskBlinky(void *argument);
void startTaskTrace(void *argument);
void startTaskDispecer(void *argument);
void startTaskRadioComms(void *argument);
void startTaskID(void *argument);
void d3start(void *argument);
void d4start(void *argument);
void d5start(void *argument);
void d6start(void *argument);
void startTaskHwI2c(void *argument);
void startTaskHwSpi(void *argument);
void startTaskDigitalIn(void *argument);
void startTaskAnalogIn(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_CRC_Init();
  MX_I2C1_Init();
  MX_RTC_Init();
  MX_SPI2_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();
  /* Create the mutex(es) */
  /* creation of mtxMeasCnt */
  mtxMeasCntHandle = osMutexNew(&mtxMeasCnt_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of qTrace */
  qTraceHandle = osMessageQueueNew (64, sizeof(TRACE_MESSAGE_STRUCT), &qTrace_attributes);

  /* creation of qRadioTx */
  qRadioTxHandle = osMessageQueueNew (64, 128, &qRadioTx_attributes);

  /* creation of qRadioRx */
  qRadioRxHandle = osMessageQueueNew (16, 128, &qRadioRx_attributes);

  /* creation of qRadioFwd */
  qRadioFwdHandle = osMessageQueueNew (64, sizeof(uint32_t), &qRadioFwd_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of TaskBlinky */
  TaskBlinkyHandle = osThreadNew(startTaskBlinky, NULL, &TaskBlinky_attributes);

  /* creation of TaskTrace */
  TaskTraceHandle = osThreadNew(startTaskTrace, NULL, &TaskTrace_attributes);

  /* creation of TaskDispecer */
  TaskDispecerHandle = osThreadNew(startTaskDispecer, NULL, &TaskDispecer_attributes);

  /* creation of TaskRadioComms */
  TaskRadioCommsHandle = osThreadNew(startTaskRadioComms, NULL, &TaskRadioComms_attributes);

  /* creation of TaskID */
  TaskIDHandle = osThreadNew(startTaskID, NULL, &TaskID_attributes);

  /* creation of d3 */
  d3Handle = osThreadNew(d3start, NULL, &d3_attributes);

  /* creation of d4 */
  d4Handle = osThreadNew(d4start, NULL, &d4_attributes);

  /* creation of d5 */
  d5Handle = osThreadNew(d5start, NULL, &d5_attributes);

  /* creation of d6 */
  d6Handle = osThreadNew(d6start, NULL, &d6_attributes);

  /* creation of TaskHwI2c */
  TaskHwI2cHandle = osThreadNew(startTaskHwI2c, NULL, &TaskHwI2c_attributes);

  /* creation of TaskHwSpi */
  TaskHwSpiHandle = osThreadNew(startTaskHwSpi, NULL, &TaskHwSpi_attributes);

  /* creation of TaskDigitalIn */
  TaskDigitalInHandle = osThreadNew(startTaskDigitalIn, NULL, &TaskDigitalIn_attributes);

  /* creation of TaskAnalogIn */
  TaskAnalogInHandle = osThreadNew(startTaskAnalogIn, NULL, &TaskAnalogIn_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* creation of EvtTrace */
  EvtTraceHandle = osEventFlagsNew(&EvtTrace_attributes);

  /* creation of EvtGlobalRunStop */
  EvtGlobalRunStopHandle = osEventFlagsNew(&EvtGlobalRunStop_attributes);

  /* creation of EvtTaskHealth */
  EvtTaskHealthHandle = osEventFlagsNew(&EvtTaskHealth_attributes);

  /* creation of EvtTriggers */
  EvtTriggersHandle = osEventFlagsNew(&EvtTriggers_attributes);

  /* creation of EvtSpare2 */
  EvtSpare2Handle = osEventFlagsNew(&EvtSpare2_attributes);

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV8;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enables the Clock Security System
  */
  HAL_RCC_EnableCSS();
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 4;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_6;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_7;
  sConfig.Rank = 2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_8;
  sConfig.Rank = 3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_9;
  sConfig.Rank = 4;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 0x1;
  sDate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

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
  huart1.Init.BaudRate = 115200;
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
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BOARD_LED0_GPIO_Port, BOARD_LED0_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, KBD_o0_Pin|KBD_o1_Pin|KBD_o2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : BOARD_LED0_Pin */
  GPIO_InitStruct.Pin = BOARD_LED0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BOARD_LED0_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Exti_d0_BOARD_KEY0_Pin Exti_d1_Pin Exti_d2_Pin */
  GPIO_InitStruct.Pin = Exti_d0_BOARD_KEY0_Pin|Exti_d1_Pin|Exti_d2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : KBD_o0_Pin KBD_o1_Pin KBD_o2_Pin */
  GPIO_InitStruct.Pin = KBD_o0_Pin|KBD_o1_Pin|KBD_o2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : KBD_i2_Pin KBD_i3_Pin KBD_i0_Pin KBD_i1_Pin */
  GPIO_InitStruct.Pin = KBD_i2_Pin|KBD_i3_Pin|KBD_i0_Pin|KBD_i1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	//	uint32_t flg = osThreadFlagsSet(TaskDigitalInHandle, GPIO_Pin);
	osThreadFlagsSet(TaskDigitalInHandle, (uint32_t) GPIO_Pin);
	__NOP();
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	osThreadFlagsSet(TaskAnalogInHandle, flg_ADC_CONV_CPLT_IRQ); // ADC merenje zavrseno u pozadini
}

#define BIN4_TO_STR(val, buf)                  \
do {                                       \
	(buf)[0] = ((val) & (1 << 3)) ? '1' : '0'; \
	(buf)[1] = ((val) & (1 << 2)) ? '1' : '0'; \
	(buf)[2] = ((val) & (1 << 1)) ? '1' : '0'; \
	(buf)[3] = ((val) & (1 << 0)) ? '1' : '0'; \
	(buf)[4] = '\0';                       \
} while (0)


/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
for (;;) {
	osDelay(1000);
}
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_startTaskBlinky */
/**
* @brief Function implementing the TaskBlinky thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startTaskBlinky */
void startTaskBlinky(void *argument)
{
  /* USER CODE BEGIN startTaskBlinky */
	const char blr[] = "led blur";
	const char other[] = "led blink";

	osEventFlagsWait(EvtGlobalRunStopHandle, flg_BLINK_ENABLED, osFlagsWaitAll, osWaitForever);
	osEventFlagsSet(EvtTaskHealthHandle, flg_BLINK_ENABLED);
	/* Infinite loop */
	for (;;) {
		uint32_t per = cfg_GetHeartbeatPeriod();
		uint32_t flg = osThreadFlagsWait(flg_MAX, osFlagsWaitAny, per);
		if (flg == osFlagsErrorTimeout) {
			tracePrint1s(qTraceHandle, dbg_4, blr);		// retko cemo gledati bas svaki blur
			ledBlur(500, 1, 10);
		} else {
			tracePrint1s(qTraceHandle, dbg_6, other);		// ULTRA_HIGH za bas teske slucajeve debugginga
			ledBlink(5);
		}
		osDelay(1);
	}
  /* USER CODE END startTaskBlinky */
}

/* USER CODE BEGIN Header_startTaskTrace */
/**
* @brief Function implementing the TaskTrace thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startTaskTrace */
void startTaskTrace(void *argument)
{
  /* USER CODE BEGIN startTaskTrace */
	TraceMessage_t rxmsg;
	HAL_StatusTypeDef stat;
	uint32_t cdcTmout;
	/* Infinite loop */
	for (;;) {
		osMessageQueueGet(qTraceHandle, &rxmsg, 0U, osWaitForever);
		stat = HAL_UART_Transmit(&UART_trace, (uint8_t *)rxmsg.txt, strlen(rxmsg.txt), trcWt);	// ako nije gotovo za 200mS batali tracing
		if (stat != HAL_OK) {
			//	  		 TODO kome signalizirati ako UART trejser ne radi?
			__NOP();
		}

		cdcTmout = 0;
		while ( (cdcTmout<trcWt) && ( CDC_Transmit_FS((uint8_t *)rxmsg.txt, strlen(rxmsg.txt))==USBD_BUSY )
			) {
			osDelay(1);
			cdcTmout++;
			if (cdcTmout >= trcWt) {
				// TODO kome signalizirati ako ni USB trejser ne radi!
			}
			}
		osDelay(1);
		osThreadYield();

	}

  /* USER CODE END startTaskTrace */
}

/* USER CODE BEGIN Header_startTaskDispecer */
/**
* @brief Function implementing the TaskDispecer thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startTaskDispecer */
void startTaskDispecer(void *argument)
{
  /* USER CODE BEGIN startTaskDispecer */
	const char sys_boot[] =			"system: reboot";
	const char sys_startup[] =		"system: startup...";
	const char sys_ok[] = 			"system: startup OK";
	const char sys_enx[] =			"system: enabling task(s)";
	uint32_t rez;

	tracePrint1s(qTraceHandle, dbg_2, sys_boot);

	setTraceLevel(dbg_7);
	INIT_DAQ_HW();

	radioTx1s(qRadioTxHandle, sys_boot);

	uint32_t cfg_enabledTasks = 0;
	cfg_enabledTasks |= flg_BLINK_ENABLED;
	cfg_enabledTasks |= flg_DIGITAL_ENABLED;
	cfg_enabledTasks |= flg_ANALOG_ENABLED;
	//	cfg_enabledTasks |= flg_RADIO_ENABLED;


	tracePrint1s(qTraceHandle, dbg_3, sys_startup);
	osDelay(1000);											// TODO dymmy init delay
	tracePrint1s(qTraceHandle, dbg_3, sys_ok);
	radioTx1s(qRadioTxHandle, sys_ok);

	radioTx1s1u(qRadioTxHandle, sys_enx, cfg_enabledTasks);
	for (int i = 0; i < 31; ++i) {
		uint32_t curflg = (1 << i);
		if ( (curflg & cfg_enabledTasks) != 0) {
			tracePrint1u(qTraceHandle, dbg_3, sys_enx, curflg);
			osEventFlagsSet(EvtGlobalRunStopHandle, curflg);
		}
	}


	/* Infinite loop */
	for (;;) {
		rez = osThreadFlagsWait(flg_MAX, osFlagsWaitAny, osWaitForever);
		//		switch (rez) {
		//			case osFlagsErrorTimeout:
		//				// za sada nista
		//				break;
		//
		//			default:
		//				// koliko god taskova ima
		//				osMutexAcquire(mtxMeasCntHandle, osWaitForever);
		//				measCnt++;
		//				osThreadFlagsSet(TaskDigitalInHandle, flg_DIGITAL_REQUEST);
		//				measCnt++;
		//				osThreadFlagsSet(TaskAnalogInHandle, flg_ADC_REQUEST);
		//				osDelay(2);		// dajem sansu da taskovi za merenja krenu
		//				osMutexRelease(mtxMeasCntHandle);
		//				break;
		//		}

		osDelay(10);
		osThreadYield();
	}
  /* USER CODE END startTaskDispecer */
}

/* USER CODE BEGIN Header_startTaskRadioComms */
/**
* @brief Function implementing the TaskRadioComms thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startTaskRadioComms */
void startTaskRadioComms(void *argument)
{
  /* USER CODE BEGIN startTaskRadioComms */
	RadioMessage_t rmsg;
	uint32_t cnt = 0;

	const char rad_ready[] = 		"radio ready";
	const char rad_txOn[] = 		"radio tx on";
	const char rad_txOnIncplt[] = 	"radio tx will be done with incomplete measurements";
	const char rad_txDone[] = 		"radio tx done";

	osEventFlagsWait(EvtGlobalRunStopHandle, flg_RADIO_ENABLED, osFlagsWaitAll, osWaitForever);
	INIT_RADIO();	// TODO timeout or error
	tracePrint1s(qTraceHandle, dbg_3, rad_ready);

	/* Infinite loop */
	for (;;) {
		// cekam da neko zada start
		cnt = osMessageQueueGetCount(qRadioRxHandle);
		if (cnt == 0) {
			osDelay(1);
			osThreadYield();	// nista nije stiglo, prepusti kontrolu
		} else {
			osDelay(1000);		// sacekaj jos neku poruku
			// radio on			// radio prepare and turn on
			while (osOK == osMessageQueueGet(qRadioRxHandle, &rmsg, 0U, qWt) ) {
				// transmit message for real
				// osDelay(1);	// treba li pauza izmedju poruka?
			}
			// radio off
			osDelay(100);	// odmori se

		}
		// zatim cekam da sva merenja zavrse
//		osMutexAcquire(mtxMeasCntHandle, osWaitForever);
//		if (rez == osErrorTimeout) {
//			// posalji sta imas, cak i ako se nisu svi senzori odazvali na vreme (mozda zbog kvara?)
//			sprintf(bfr, "%s \n\r", rad_txOnIncplt);
//			osMessageQueuePut(qTraceExecHandle, &ptr, 0U, qWt);
//			osDelay(200);
//			sprintf(bfr, "%s \n\r", rad_txOn);
//			osMessageQueuePut(qTraceExecHandle, &ptr, 0U, qWt);
//			// TODO RADIO SEND pritom obavezno signaliziraj neku gresku
//
//			osDelay(1000);	// TODO simulira trajanje radio transmisije
//			sprintf(bfr, "%s \n\r", rad_txDone);
//			osMessageQueuePut(qTraceExecHandle, &ptr, 0U, qWt);
//		} else {
//			sprintf(bfr, "%s \n\r", rad_txOn);
//			osMessageQueuePut(qTraceExecHandle, &ptr, 0U, qWt);
//			// TODO RADIO SEND
//
//			osDelay(1000);	// TODO simulira trajanje radio transmisije
//			sprintf(bfr, "%s \n\r", rad_txDone);
//			osMessageQueuePut(qTraceExecHandle, &ptr, 0U, qWt);
//		}
//		osMutexRelease(mtxMeasCntHandle);

		osDelay(1);
		osThreadYield();
	}
  /* USER CODE END startTaskRadioComms */
}

/* USER CODE BEGIN Header_startTaskID */
/**
* @brief Function implementing the TaskID thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startTaskID */
void startTaskID(void *argument) {
	/* USER CODE BEGIN startTaskID */
	uint32_t id0 = 0;
	uint32_t id1 = 0;
	uint32_t id2 = 0;
	// ovo dodje kao neki template
	// osEventFlagsWait(EvtGlobalRunStopHandle, flg_DIGITAL_ENABLED, osFlagsWaitAll, osWaitForever);
	// INIT_DIGITAL_INPUTS();	// TODO neki timeout
	// osEventFlagsSet(EvtTaskHealthHandle, flg_DIGITAL_ENABLED);
	// tracePrint1s(qTraceHandle, dbg_3, dig_running);
	/* Infinite loop */
	for (;;) {
		id0 = 0;
		id1 = 0;
		id2 = 0;
		HAL_GPIO_WritePin(KBD_o0_GPIO_Port, KBD_o0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(KBD_o1_GPIO_Port, KBD_o1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(KBD_o2_GPIO_Port, KBD_o2_Pin, GPIO_PIN_SET);

		// PRVA cifra
		HAL_GPIO_WritePin(KBD_o0_GPIO_Port, KBD_o0_Pin, GPIO_PIN_RESET);
		osDelay(20);
		//i am  1 << (Exti_d2_Pin>>1)  zato sto gpio pinovi u hal-u idu od 1..32 a meni treba shiftofanje 0..31 puta
		if (HAL_GPIO_ReadPin(KBD_i0_GPIO_Port, KBD_i0_Pin) == GPIO_PIN_SET) { id0 |= (1 << bit0); };
		if (HAL_GPIO_ReadPin(KBD_i1_GPIO_Port, KBD_i1_Pin) == GPIO_PIN_SET) { id0 |= (1 << bit1); };
		if (HAL_GPIO_ReadPin(KBD_i2_GPIO_Port, KBD_i2_Pin) == GPIO_PIN_SET) { id0 |= (1 << bit2); };
		if (HAL_GPIO_ReadPin(KBD_i3_GPIO_Port, KBD_i3_Pin) == GPIO_PIN_SET) { id0 |= (1 << bit3); };

		// DRUGA cifra
		HAL_GPIO_WritePin(KBD_o0_GPIO_Port, KBD_o0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(KBD_o1_GPIO_Port, KBD_o1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(KBD_o2_GPIO_Port, KBD_o2_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(KBD_o1_GPIO_Port, KBD_o1_Pin, GPIO_PIN_RESET);
		osDelay(20);
		//i am  1 << (Exti_d2_Pin>>1)  zato sto gpio pinovi u hal-u idu od 1..32 a meni treba shiftofanje 0..31 puta
		if (HAL_GPIO_ReadPin(KBD_i0_GPIO_Port, KBD_i0_Pin) == GPIO_PIN_SET) { id1 |= (1 << bit0); };
		if (HAL_GPIO_ReadPin(KBD_i1_GPIO_Port, KBD_i1_Pin) == GPIO_PIN_SET) { id1 |= (1 << bit1); };
		if (HAL_GPIO_ReadPin(KBD_i2_GPIO_Port, KBD_i2_Pin) == GPIO_PIN_SET) { id1 |= (1 << bit2); };
		if (HAL_GPIO_ReadPin(KBD_i3_GPIO_Port, KBD_i3_Pin) == GPIO_PIN_SET) { id1 |= (1 << bit3); };

		// TRECA cifra
		HAL_GPIO_WritePin(KBD_o0_GPIO_Port, KBD_o0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(KBD_o1_GPIO_Port, KBD_o1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(KBD_o2_GPIO_Port, KBD_o2_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(KBD_o2_GPIO_Port, KBD_o2_Pin, GPIO_PIN_RESET);
		osDelay(20);
		//i am  1 << (Exti_d2_Pin>>1)  zato sto gpio pinovi u hal-u idu od 1..32 a meni treba shiftofanje 0..31 puta
		if (HAL_GPIO_ReadPin(KBD_i0_GPIO_Port, KBD_i0_Pin) == GPIO_PIN_SET) { id2 |= (1 << bit0); };
		if (HAL_GPIO_ReadPin(KBD_i1_GPIO_Port, KBD_i1_Pin) == GPIO_PIN_SET) { id2 |= (1 << bit1); };
		if (HAL_GPIO_ReadPin(KBD_i2_GPIO_Port, KBD_i2_Pin) == GPIO_PIN_SET) { id2 |= (1 << bit2); };
		if (HAL_GPIO_ReadPin(KBD_i3_GPIO_Port, KBD_i3_Pin) == GPIO_PIN_SET) { id2 |= (1 << bit3); };

		setUID(id0, id1, id2);

		osDelay(10000);
	}
	/* USER CODE END startTaskID */
}

/* USER CODE BEGIN Header_d3start */
/**
* @brief Function implementing the d3 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_d3start */
void d3start(void *argument)
{
  /* USER CODE BEGIN d3start */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1000);
  }
  /* USER CODE END d3start */
}

/* USER CODE BEGIN Header_d4start */
/**
* @brief Function implementing the d4 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_d4start */
void d4start(void *argument)
{
  /* USER CODE BEGIN d4start */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1000);
  }
  /* USER CODE END d4start */
}

/* USER CODE BEGIN Header_d5start */
/**
* @brief Function implementing the d5 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_d5start */
void d5start(void *argument)
{
  /* USER CODE BEGIN d5start */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1000);
  }
  /* USER CODE END d5start */
}

/* USER CODE BEGIN Header_d6start */
/**
* @brief Function implementing the d6 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_d6start */
void d6start(void *argument)
{
  /* USER CODE BEGIN d6start */
  /* Infinite loop */
  for(;;)
  {
    osDelay(30000);
  }
  /* USER CODE END d6start */
}

/* USER CODE BEGIN Header_startTaskHwI2c */
/**
* @brief Function implementing the TaskHwI2c thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startTaskHwI2c */
void startTaskHwI2c(void *argument)
{
  /* USER CODE BEGIN startTaskHwI2c */
	/* Infinite loop */
	for (;;) {
		osDelay(100);
	}
  /* USER CODE END startTaskHwI2c */
}

/* USER CODE BEGIN Header_startTaskHwSpi */
/**
* @brief Function implementing the TaskHwSpi thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startTaskHwSpi */
void startTaskHwSpi(void *argument)
{
  /* USER CODE BEGIN startTaskHwSpi */
	/* Infinite loop */
	for (;;) {
		osDelay(100);
	}
  /* USER CODE END startTaskHwSpi */
}

/* USER CODE BEGIN Header_startTaskDigitalIn */
/**
* @brief Function implementing the TaskDigitalIn thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startTaskDigitalIn */
void startTaskDigitalIn(void *argument)
{
  /* USER CODE BEGIN startTaskDigitalIn */
	// ovde se dolazi iz HAL_GPIO_EXTI_Callback
	// irq callback salje broj pina kao thread flag
	const char dig_running[] =		"digital running";
	const char dig_trig[] = 		"digital triggered";
	const char dig_complete[] = 	"digital processing done";
	uint32_t extPinovi = 0;

	osEventFlagsWait(EvtGlobalRunStopHandle, flg_DIGITAL_ENABLED, osFlagsWaitAll, osWaitForever);
	INIT_DIGITAL_INPUTS();	// TODO neki timeout
	osEventFlagsSet(EvtTaskHealthHandle, flg_DIGITAL_ENABLED);
	tracePrint1s(qTraceHandle, dbg_3, dig_running);
	radioTx1s(qRadioRxHandle, dig_running);

	/* Infinite loop */
	for (;;) {
		uint32_t rez = osThreadFlagsWait(flg_MAX, osFlagsWaitAny, osWaitForever);
		switch (rez) {
			case osFlagsErrorTimeout:
				// ni jedan digitalni ulaz se nije promenio. ne radim nista
				break;

				default:
				// bilo koji flag -> primio sam EXTI sa nekog digitalnog pina ili je trazeno merenje zbog promene na ANALOGNOM delu
				// procitam vrednosti i posaljem u measurement set
				extPinovi = 0;
				// 1 << (Exti_d2_Pin>>1)  zato sto gpio pinovi u hal-u idu od 1..32 a meni treba shiftofanje 0..31 puta
				if ( HAL_GPIO_ReadPin(Exti_d0_BOARD_KEY0_GPIO_Port, Exti_d0_BOARD_KEY0_Pin) == GPIO_PIN_SET) { extPinovi |= ( 1 << bit0 ); };
				if ( HAL_GPIO_ReadPin(Exti_d1_GPIO_Port, Exti_d1_Pin) 						== GPIO_PIN_SET) { extPinovi |= ( 1 << bit1 ); };
				if ( HAL_GPIO_ReadPin(Exti_d2_GPIO_Port, Exti_d2_Pin) 						== GPIO_PIN_SET) { extPinovi |= ( 1 << bit2 ); };

				setDigitalResult(extPinovi);
				char bintostr[5];
				BIN4_TO_STR(extPinovi, bintostr);
//				snprintf(msg.txt, sizeof(msg.txt), "%s: %s (%d)", dig_trig, bintostr, (unsigned int)extPinovi);
//				tracePrint(qTraceHandle, dbg_3, msg.txt);
				tracePrint2s2u(qTraceHandle, dbg_3, dig_trig, bintostr, extPinovi, 0);
				osEventFlagsSet(EvtTriggersHandle, flg_DIGITAL_TRIGGERED);

				tracePrint1s(qTraceHandle, dbg_5, dig_complete);
				osEventFlagsSet(EvtTriggersHandle, flg_DIGITAL_PROCESSING_DONE);				// signaliziram zavrsetak
				radioTx2s2u(qRadioRxHandle, dig_trig, bintostr, extPinovi, 0);

				break;
		}
		osDelay(1);
		osThreadYield();
	}
  /* USER CODE END startTaskDigitalIn */
}

/* USER CODE BEGIN Header_startTaskAnalogIn */
/**
* @brief Function implementing the TaskAnalogIn thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startTaskAnalogIn */
void startTaskAnalogIn(void *argument)
{
  /* USER CODE BEGIN startTaskAnalogIn */
	TraceMessage_t msg;
	uint32_t AD_REZULT_izDMA[hadc1.Init.NbrOfConversion];
	uint32_t ad_threshold[hadc1.Init.NbrOfConversion];
	
	const char adc_running[] =			"adc running";
	const char adc_triggered[] = 		"adc done, triggered: yes";
	const char adc_not_triggered[] = 	"adc done, triggered: no";

	osEventFlagsWait(EvtGlobalRunStopHandle, flg_ANALOG_ENABLED, osFlagsWaitAll, osWaitForever);
	INIT_ADC();	// TODO neki timeout
	osEventFlagsSet(EvtTaskHealthHandle, flg_ANALOG_ENABLED);
	tracePrint1s(qTraceHandle, dbg_3, adc_running);

	/* Infinite loop */
	for (;;) {
		uint32_t flg = osThreadFlagsWait(flg_MAX, osFlagsWaitAny, getAdcPeriodTicks());
		// analogno merenje svakih ADC_REPETITION_PERIOD_mS, ili ako pre vremena dobijem fleg zbog nekog drugog trigera
		switch (flg) {
			case osFlagsErrorTimeout:
			case flg_ADC_REQUEST:
				// ako istekne ADC_REPETITION_PERIOD_mS ili neki drugi task zatrazi merenje
				HAL_ADC_Start_DMA(&hadc1, AD_REZULT_izDMA, hadc1.Init.NbrOfConversion);	// posle ovoga cekam DMA da zavrsi
				break;

			case flg_ADC_CONV_CPLT_IRQ:
				// ADC_DMA transfer je zavrsen
				bool desioSeTrig = desioSeTrig = false;		// FREEZE: ovde setujem varijablu a tek na kraju SAMO JEDNOM SETUJEM thread flag
				for (uint32_t i = 0; i < hadc1.Init.NbrOfConversion; i++) {
					setAnalogResult(i, AD_REZULT_izDMA[i]);

					ADinput_t inputCfg = getAnalogInputCfg(i);
					// ALARM_POLARITY > 0 => signaliziram prekoracenje IZNAD
					if ( inputCfg.alarmPolarity > 0 ) {
						if ( AD_REZULT_izDMA[i] > inputCfg.alarmThreshold ) {
							desioSeTrig = true;
						} else if ( AD_REZULT_izDMA[i] <= (inputCfg.alarmThreshold - inputCfg.hysteresisValue) ) {
							// FREEZE!!! NE DIRAJ desioSeTrig da ne ponistis vec postojeci true!
						}
					}

					// ALARM_POLARITY < 0 => signaliziram prekoracenje ISPOD
					if ( inputCfg.alarmPolarity < 0) {
						if (AD_REZULT_izDMA[i] < ( inputCfg.alarmThreshold ) ) {
							desioSeTrig = true;
						} else if (AD_REZULT_izDMA[i] >= ( inputCfg.alarmThreshold + inputCfg.hysteresisValue) ) {
							// FREEZE!!! NE DIRAJ desioSeTrig da ne ponistis vec postojeci true!
						}
					}

					// ALARM_POLARITY = 0 => Disable za taj ulaz. Samo merim i ne signaliziram nikom nista.
					if ( inputCfg.alarmPolarity == 0) {
						// za sada nista
					}

				}

				if (desioSeTrig) {
					// ostavi poruku i signaliziraj trigger
					snprintf(msg.txt, sizeof(msg.txt), "%s, %u, %u, %u, %u", adc_triggered, AD_REZULT_izDMA[0], AD_REZULT_izDMA[1], AD_REZULT_izDMA[2], AD_REZULT_izDMA[3]);
					tracePrint1s(qTraceHandle, dbg_3, msg.txt);
					osEventFlagsSet(EvtTriggersHandle, flg_ANALOG_TRIGGERED);
				} else {
					// nije bio trigger
					snprintf(msg.txt, sizeof(msg.txt), "%s, %u, %u, %u, %u", adc_not_triggered, AD_REZULT_izDMA[0], AD_REZULT_izDMA[1], AD_REZULT_izDMA[2], AD_REZULT_izDMA[3]);
					tracePrint1s(qTraceHandle, dbg_6, msg.txt);
					osEventFlagsClear(EvtTriggersHandle, flg_ANALOG_TRIGGERED);
				}
				// konacno signaliziraj zavrseno merenje
				osEventFlagsSet(EvtTriggersHandle, flg_ANALOG_PROCESSING_DONE);

				break;

			default:
				// TODO sta ovde? nista?
				break;
		}
		osDelay(1);
		osThreadYield();
	}
  /* USER CODE END startTaskAnalogIn */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM11 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM11)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  	__NOP();
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
