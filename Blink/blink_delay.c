//#include "stm32f4xx.h"

//int main(){
//	
//	GPIO_InitTypeDef GPIOA_Params; // Initilisation structure for GPIOD Settings
//	
//	uint32_t i; // Loop variable
//	
//	__HAL_RCC_GPIOA_CLK_ENABLE(); // Turn on Clock of GPIOA
//	
//	// Configure the GPIO Pins 12, 13, 14 and 15 used for LEDs
//	GPIOA_Params.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15; // Select pins 12 to 15
//	GPIOA_Params.Mode = GPIO_MODE_OUTPUT_PP; // Set pins to push pull output mode
//	GPIOA_Params.Speed = GPIO_SPEED_LOW; // Set low output speed
//	HAL_GPIO_Init(GPIOA, &GPIOA_Params); // Initialise GPIOA according to parameters on GPIOA_Params
//	
//	while(1){
//		
//		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_SET); // Turn on LEDs
//		
//		for(i = 0; i < 2000000; i++){}; // Implement a 1 second (ish!) delay
//		
//		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_RESET); // Turn off LEDs
//			
//		for(i = 0; i < 2000000; i++){}; // Implement a 1 second (ish!) delay
//		
//	}
//}