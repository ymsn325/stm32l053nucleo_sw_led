#include <stm32l053xx.h>

int button_state = 0;

void pin_settings(void)
{
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN | RCC_IOPENR_GPIOCEN;
    GPIOA->MODER &= ~GPIO_MODER_MODE5;
    GPIOA->MODER |= GPIO_MODER_MODE5_0;
    GPIOC->MODER &= ~GPIO_MODER_MODE13;
    GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD13;
    GPIOC->PUPDR |= GPIO_PUPDR_PUPD13_0;
}

int read_button(void)
{
    return GPIOC->IDR;
}

int main(void)
{
    pin_settings();
    while (1)
    {
        button_state = read_button();
        if (!button_state)
        {
            GPIOA->BSRR = GPIO_BSRR_BS_5;
        }
        else
        {
            GPIOA->BSRR = GPIO_BSRR_BR_5;
        }
    }
    return 0;
}