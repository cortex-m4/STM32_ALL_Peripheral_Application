#include "MY_RNG.h"
#include "main.h"

/**
  * @brief  RNG configuration
  * @param  None
  * @retval None
  */
void RNG_Config(void)
{  
 /* Enable RNG clock source */
  RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_RNG, ENABLE);

  /* RNG Peripheral enable */
  RNG_Cmd(ENABLE);
}
/**
  * @brief  Get_Random_Num
	* @param  length:get random num length
	* @param  RNG_Data:get random num
  * @retval None
  */
void Get_Random_Num(uint8_t length,uint32_t *RNG_Data){
	uint32_t random32bit[10];
	uint8_t counter = 0;
	for(counter = 0; counter < length; counter++)
    {
      /* Wait until one RNG number is ready */
      while(RNG_GetFlagStatus(RNG_FLAG_DRDY)== RESET)
      {
      }

      /* Get a 32bit Random number */       
      random32bit[counter] = RNG_GetRandomNumber();

    }
	memcpy(RNG_Data,random32bit,sizeof random32bit);
}



