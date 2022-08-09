# AVR_Examples
### Examples of AVR Atmega128

&nbsp;

## Target Board
### HANBACK HBE-MCU-Multi II -ST   
|diagram|board|
|:---:|:---:|
|![block](./pic/block.jpg)|![device](./pic/sized_board.jpg)|

&nbsp;

## 개발환경
### Microchip Studio for AVR 7.0.2594

&nbsp;

## Directories
- basic   
  - LED : LED ON / OFF
  - toggle_LED : Delay 함수를 이용해 LED ON / OFF
  - sevenSegment : 7-segment 출력
  - switch : 버튼을 누르면 LED 출력
- Timer (prescaler : 1024)
  - Timer_CTC : CTC 모드를 이용해 1초 주기로 7-segment 출력
  - Tiemr_PWM : PWM 모드로 7-sgement 숫자 출력
- Communication
  - Uart : UART 통신 메시지 echo 기능
