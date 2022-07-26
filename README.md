# AVR_Examples
### Examples of AVR Atmega128
ATmega128 MCU를 기반으로 LED와 7-segment, 버튼등의 입출력 장치와 타이머 기능을 활용한 실습 예제를 작성
&nbsp;

## Target Board
### HANBACK HBE-MCU-Multi II -ST   
* MCU : ATmega128A   
* Memory : EEPROM 2MB / SRAM 128KB   
* Communication : UART 1EA, Bluetooth module   
* Devices : FND, LED, buttons, etc
* link : [https://hanback.com/ko/archives/7945](https://hanback.com/ko/archives/7945)   

|diagram|board|
|:---:|:---:|
|![block](./pic/block.jpg)|![device](./pic/sized_board.jpg)|

&nbsp;

## 개발환경
### Microchip Studio for AVR 7.0.2594

&nbsp;
## Directories
- basic   
  - LED :        LED ON / OFF
  - toggle_LED : Delay 함수를 이용해 LED ON / OFF
  - sevenSegment : 7-segment 출력
  - switch : 버튼을 누르면 LED 출력
- Timer (prescaler : 1024)
  - Timer_CTC : CTC 모드를 이용해 1초 주기로 7-segment 출력
  - Timer_PWM : PWM 모드로 7-sgement 숫자 출력
- Communication
  - Uart : UART 통신 메시지 echo 기능
