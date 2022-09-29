/*
 * OLED_control.h
 *
 * Created: 22/09/2022 13:01:06
 *  Author: danie
 */ 


#ifndef OLED_CONTROL_H_
#define OLED_CONTROL_H_




void OLED_Write_Command(uint8_t command);

void OLED_Write_Data(uint8_t data);

void OLED_init();

int oled_put_char(unsigned char c);


void oled_printf(char* data, ...);

void OLED_reset(void);

void OLED_home(void);

int OLED_goto_line(uint8_t line);

void OLED_clear_line(uint8_t line);

void OLED_fill_line(uint8_t line);

void OLED_goto_pos(uint8_t row, uint8_t column );

int OLED_goto_column(uint8_t column);

void OLED_print_at_Pos(char ch);

void OLED_print_string(char* string);

void OLED_set_brightness(int lvl);


void OLED_print_arrow ( uint8_t row , uint8_t col );

#endif /* OLED_CONTROL_H_ */