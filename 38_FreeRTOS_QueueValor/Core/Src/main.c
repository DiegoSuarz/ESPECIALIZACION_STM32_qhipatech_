/* USER CODE BEGIN Header */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct{
	uint8_t ID;
	uint8_t Led1:1;
	uint8_t Led2:1;
	uint8_t Led3:1;
	uint8_t Led4:1;
	uint8_t msTime;
}LedsValor;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
xTaskHandle xTask1; //enviar información
xTaskHandle xTask2; //enviar información
xTaskHandle xTask3; //procesa información

xQueueHandle xQueue;

BaseType_t status;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void vTask1(void *params);
void vTask2(void *params);
void vTask3(void *params);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define SYSTEM_VIEW				1

void UART_Printf(char *format,...);


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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */


  status = xTaskCreate(vTask1, "tarea1", configMINIMAL_STACK_SIZE, NULL, 0, &xTask1);
  configASSERT(status == pdPASS);
  status = xTaskCreate(vTask2, "tarea2", configMINIMAL_STACK_SIZE, NULL, 0, &xTask2);
  configASSERT(status == pdPASS);
  status = xTaskCreate(vTask3, "tarea3", configMINIMAL_STACK_SIZE, NULL, 0, &xTask3);
  configASSERT(status == pdPASS);


  xQueue = xQueueCreate(12,sizeof(LedsValor)); //el tamaño de las estrucutra
  configASSERT(xQueue != NULL);
  vTaskStartScheduler();//Arrancamos el kernel

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while(1){}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 84;
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
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void vTask1(void *params){

	LedsValor ledtarea1;

	ledtarea1.ID = 1;
	ledtarea1.Led1 = 0;
	ledtarea1.Led2 = 0;
	ledtarea1.Led3 = 1;
	ledtarea1.Led4 = 1;
	ledtarea1.msTime = 100;

	for(;;){
		if (xQueueSend(xQueue,(void *)&ledtarea1,portMAX_DELAY)){
			UART_Printf("dato enviado desde task1\n\r");
		}
		vTaskDelay(pdMS_TO_TICKS(100));
	}
	vTaskDelete(NULL);
}

void vTask2(void *params){

	LedsValor ledtarea2;

	ledtarea2.ID = 2;
	ledtarea2.Led1 = 1;
	ledtarea2.Led2 = 1;
	ledtarea2.Led3 = 0;
	ledtarea2.Led4 = 0;
	ledtarea2.msTime = 200;

	for(;;){
		if (xQueueSend(xQueue,(void *)&ledtarea2,portMAX_DELAY)){
			UART_Printf("dato enviado desde task2\n\r");
		}
		vTaskDelay(pdMS_TO_TICKS(100));
	}
	vTaskDelete(NULL);
}

void vTask3(void *params){

	LedsValor datos;

	for (;;){
		if(xQueueReceive(xQueue, &datos, portMAX_DELAY)){
			UART_Printf("dato enviado desde %d\n\r",datos.ID);

			switch (datos.ID) {
				case 1:
					HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, datos.Led1);
					HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, datos.Led2);
					HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, datos.Led3);
					HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, datos.Led4);
					vTaskDelay(pdMS_TO_TICKS(datos.msTime));
					break;

				case 2:
					HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, datos.Led1);
					HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, datos.Led2);
					HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, datos.Led3);
					HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, datos.Led4);
					vTaskDelay(pdMS_TO_TICKS(datos.msTime));
					break;
				default:
					break;
			}

		}
	}
	vTaskDelete(NULL);
}


void UART_Printf(char *format,...){
    char str[80];

    /*Extract the the argument list using VA apis */
    va_list args;
    va_start(args, format);
    vsprintf(str, format,args);
    HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), 10);
    va_end(args);
}
/* USER CODE END 4 */

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
  if (htim->Instance == TIM11) {
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
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */