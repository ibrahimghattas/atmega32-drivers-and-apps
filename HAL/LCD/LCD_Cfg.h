 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_

/*********for prot****/
// #define RS PINA1
// #define EN PINA2
// 
// #define D7 PINA6
// #define D6 PINA5
// #define D5 PINA4
// #define D4 PINA3
// 
// #define LCD_PORT PORTA
/*****************************/
/**************for kit*******/
#define RS PINA1
#define EN PINA2

#define D7 PINA6
#define D6 PINA5
#define D5 PINA4
#define D4 PINA3

#define LCD_PORT PORTA
/**********************************/
#define _8_BIT 0
#define _4_BIT 1
/******************lcd mode****************************/
#define LCD_MODE _4_BIT
/*******************screen cfg************************************/

#define MODE_LINE_FONT  0b00101000  //8bit to change to 4bit change bit#(5) ,,,, 2lines bit#(4) ,,, 5x7   bit#(3) 
#define CURSOR			0b00001100  //0x0e or 0x0f cursor blink-off bit#(1) ,,,  cursor on [off] bit#(2)  screen [on] bit#(3) 
#define CLS				0b00000001  //cls 0x01
#define INC_SHIFT		0b00000110  //auto inc bit#(2) ,, no shift bit#(3) 

#define IN1 0b0010

#define IN2 0b1000



#endif /* LCD_CFG_H_ */