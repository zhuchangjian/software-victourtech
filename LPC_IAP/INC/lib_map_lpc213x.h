#ifndef _LIB_MAP_LPC213X_H_
  #define _LIB_MAP_LPC213X_H_

/* 寄存器地址定义 */


/* APB1,APB2,AHB总线基址 */
#define APBPHERIP_BASE  (0xE0000000)
#define AHBPHERIP_BASE  (0xF0000000)

/* APB1总线外设寄存器地址 */
#define WATCHDOG_BASE          APBPHERIP_BASE
#define TIMER_BASE             (APBPHERIP_BASE + 0x00004000)
#define UART0_BASE             (APBPHERIP_BASE + 0x0000C000)
#define UART1_BASE             (APBPHERIP_BASE + 0x00010000)
#define I2C_BASE               (APBPHERIP_BASE + 0x0001C000)
#define SPI_BASE               (APBPHERIP_BASE + 0x00020000)
#define ADC_BASE               (APBPHERIP_BASE + 0x00034000)
#define DAC_BASE               (APBPHERIP_BASE + 0x0006c000)
#define MAM_BASE               (APBPHERIP_BASE + 0x001fc000)
#define SCB_BASE               (APBPHERIP_BASE + 0x001fc040)
#define PINCONNECT_BASE        (APBPHERIP_BASE + 0x0002c000)
#define GPIOA_BASE             (APBPHERIP_BASE + 0x00028000)
#define GPIOF_BASE             (0x3fffc000)



/* AHB总线外设寄存器地址 */
#define VIC_BASE               (AHBPHERIP_BASE + 0x0FFFF000)







#endif
