## Hardware Details

![w5500 module](https://extremeelectronics.co.in/github/w5500/w5500-module.jpg)
![STM32 Discovery Kit](https://extremeelectronics.co.in/github/w5500/stm32f051-discovery-board.jpg)

The code is written to run on a STM32F051 ARM Cortex M0 MCU. The W5500 is attached to the SPI Port and shown in table below.

| W5500    | STM32   |
| -------- | ------- |
| MISO     | PA6     |
| MOSI     | PA7     |
| SCLK     | PA5     |
| SCS      | PA1     |
| RST      | PA0     |
| INT      | NC      |

NC=No Connection
SCS=Chip Select (Active Low)

To view the debug output of the program we need a USB to Serial convertor like FT232RL (3.3V Version only)
The debug messages comes out on the TX pin of the USART2 peripheral of the STM32F051. This is **PA2**.
The baud rate is 38400. User RealTerm to view the outputs.

![real term showing output of http webserver](https://extremeelectronics.co.in/github/w5500/w5500-webserver-realterm.png)

You will need ![STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) (Free from ST Microelectronics) to compile, build, flash (burn) and debug this project.

![STM32CubeIDE Popup](https://extremeelectronics.co.in/github/w5500/stm32cube_ide.png)

## More information
To learn more about w5500 Ethernet controller and its interface with STM32, please subsribe to our course on Udemy.
[Udemy's course on W5500 Interfacing](https://www.udemy.com/course/ethernet-on-stm32-using-w5500/)
