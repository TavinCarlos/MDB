#ifndef UTILS_H
#define	UTILS_H

// #define bool bit
#define true  1
#define false 0

#define Bit_convert(a,b) a&(1<<b) ? '1' : '0'
#define Bit_convert_bit(a,b) (a&(1<<b) ? (short)1 : (short)0)

extern volatile uint32_t timer0_millis;

void IntToStr(int value, char *str);
void UInt16ToStr(uint16_t value, char *str);

void ByteToHex(unsigned char value, char *buf);


//----- UART ------------------------------------------------------------------
//void  SOFT_UART_Write_Text(char *txt);
//void  SOFT_UART_Write_CText(const char *txt);


//--- Strings -----------------------------------------------------------------
void Ltrim(char *s);
void Rtrim(char *s);
void Trim(char *s);

void PadLeft(char *str, uint8_t len, char padChar);
void PadRight(char *str, uint8_t len, char padChar);

//void reverse(char str[], uint16_t length);
// void CopyRomToRam(char *ram, const char *rom);


//----- Timers ---------------------------------------------------------------
uint32_t Millis();

//---- Times ------------------------------------------------------------------

//----- Checksum --------------------------------------------------------------
// uint8_t CalculateChecksum(uint8_t *buffer, uint8_t length);
// uint8_t ValidateChecksum(uint8_t tdata[], uint8_t n);


//----- Conversiones ----------------------------------------------------------
void byte2ascii(char value, char position);
// char* citoa(int num, char* str, int base);
void Transform_Time(char  *sec, char *min, char *hr, char *week_day, char *day, char *mn, char *year);
// uint8_t BCD2UpperCh(uint8_t bcd_);
// uint8_t BCD2LowerCh(uint8_t bcd_);
char nib2asc(char tmp);


//----- HEX, Bin, Dec ---------------------------------------------------------
// uint8_t HEX_Table(uint8_t index);

#endif	/* UTILS_H */

