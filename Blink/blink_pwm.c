#include "stm32f4xx.h"

// Define array for levels
unsigned int PWM_levels[10] = {10,100,1000,3000,5000,7000,9000,10000,12000,140000};

int main()
{
	uint8_t counter = 0; // count fron 0 to 9
	// structure for GPIOA Configurations [PWM pin]
	//---- LED config = [GPIOA, PIN6, OUTPUT_MODE, CLK_HIGH_SPEED]
	GPIO_InitTypeDef GPIOA_config; 
	GPIOA_config.Pin = GPIO_PIN_6;
	GPIOA_config.Mode = GPIO_MODE_AF_OD;
	GPIOA_config.Speed = GPIO_SPEED_HIGH;
	GPIOA_config.Alternate = GPIO_AF1_TIM1;

	// structure for GPIOB Configurations [Button pin]
	//---- Button config = [GPIOB, PIN0, INPUT_MODE, INTERNAL_PULLUP_RESISTOR, CLK_LOW_SPEED]
	GPIO_InitTypeDef GPIOB_config;
	GPIOB_config.Pin = GPIO_PIN_0;
	GPIOB_config.Mode = GPIO_MODE_INPUT;
	GPIOB_config.Speed = GPIO_SPEED_LOW;
	GPIOB_config.Pull = GPIO_PULLUP;
	
	// Enable CLK on PORTA
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	// Enable CLK on Timer1 [GPIOA, PIN2]
	__HAL_RCC_TIM1_CLK_ENABLE();
	
	// Enable CLK on PORTB
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	// Initialize GPIOs with the previously defined configurations
	HAL_GPIO_Init(GPIOA, &GPIOA_config);
	HAL_GPIO_Init(GPIOB, &GPIOB_config);
	
	// Initialize PWM
	TIM_HandleTypeDef PWM_handle;
	
	PWM_handle.Channel =  TIM_CHANNEL_1;
	PWM_handle.State = HAL_TIM_STATE_RESET;
	PWM_handle.Init.Prescaler = 0x0000;
	PWM_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	PWM_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	PWM_handle.Init.Period = 4400;
	PWM_handle.Init.RepetitionCounter = 0xff;
	PWM_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	
	TIM_OC_InitTypeDef config ;
	config.Pulse = 500;
	
	HAL_TIM_PWM_Init(&PWM_handle);
	//HAL_TIM_PWM_MspInit(&PWM_handle); // if user wants to write init code himself
	HAL_TIM_PWM_ConfigChannel(&PWM_handle,&config,TIM_CHANNEL_1);
	
	// start PWM
	PWM_handle.State = HAL_TIM_STATE_READY;
	HAL_StatusTypeDef status = HAL_TIM_PWM_Start(&PWM_handle, TIM_CHANNEL_1);
	
	while(1)
	{
		// check if Button is pressed [pin value is LOW]
		GPIO_PinState button_state =  HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0);
		if (button_state == GPIO_PIN_RESET)
		{
			// stop timer
			HAL_TIM_PWM_Stop(&PWM_handle, TIM_CHANNEL_1);
			// update counter value
			counter++;
			counter = counter%10;
			// increment level
			config.Pulse = PWM_levels[counter];
			// restart timer
			HAL_TIM_PWM_Start(&PWM_handle, TIM_CHANNEL_1);
		}
		
			// false -- do nothing
	}
	return 0;
}
