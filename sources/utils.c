#include <xc.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include "utils.h"


#include <stdint.h>

void IntToStr(int value, char *str) {
    char tmp[7]; // -32768\0
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t neg = 0;

    if (value == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    if (value < 0) {
        neg = 1;
        value = -value;
    }

    while (value > 0) {
        tmp[i++] = (char) (value % 10) + '0';
        value /= 10;
    }

    if (neg)
        tmp[i++] = '-';

    while (i > 0)
        str[j++] = tmp[--i];

    str[j] = '\0';
}

void UInt16ToStr(uint16_t value, char *str) {
    char tmp[5]; // Max 65535 (5 dígitos)
    uint8_t i = 0;
    uint8_t j = 0;

    // Caso especial para el cero
    if (value == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    // Extraer dígitos (salen en orden inverso)
    while (value > 0) {
        tmp[i++] = (char) (value % 10) + '0';
        value /= 10;
    }

    // Invertir el arreglo tmp y pasarlo a str
    while (i > 0) {
        str[j++] = tmp[--i];
    }

    str[j] = '\0'; // Nulificador de cadena
}


//--- Strings -----------------------------------------------------------------

static inline uint8_t is_space(char c) {
    return (c == ' ' || c == '\t' || c == '\r' || c == '\n');
}

// Elimina espacios al inicio (Left Trim)
// Elimina espacios al inicio (Left Trim)

void Ltrim(char *s) {
    char *p = s;
    if (s == NULL)
        return;
    while (is_space((unsigned char) *p)) p++; // Busca el primer caracter que no sea espacio
    if (p != s) {
        memmove(s, p, strlen(p) + 1); // Desplaza la cadena hacia la izquierda
    }
}

// Elimina espacios al final (Right Trim)

void Rtrim(char *s) {
    size_t len;
    if (s == NULL)
        return;
    len = strlen(s);
    while (len > 0 && is_space((unsigned char) s[len - 1])) {
        len--;
    }
    s[len] = '\0'; // Corta la cadena en el último caracter válido
}

// Función combinada para limpiar ambos lados

void Trim(char *s) {
    if (s == NULL)
        return;
    Rtrim(s);
    Ltrim(s);
}

// Copia strings de memoria ROM (flash) a la memoria RAM.
//void CopyRomToRam(char *dst, const char *src) {
//    while(*src)
//        *dst++ = *src++;
//    *dst = 0;
//}

void PadLeft(char *str, uint8_t len, char padChar) {
    uint8_t currentLen = (uint8_t)strlen(str);

    if (currentLen >= len) return; // Ya es suficientemente largo
    if (len > 20) len = 20;        // Seguridad para LCD 20x4

    uint8_t offset = len - currentLen;

    // Desplazamiento hacia la derecha (incluyendo el '\0')
    // Usamos int8_t para evitar el warning 'degenerate comparison'
    for (int8_t i = (int8_t)currentLen; i >= 0; i--) {
        str[i + offset] = str[i];
    }

    // Rellenar el hueco inicial
    for (uint8_t i = 0; i < offset; i++) {
        str[i] = padChar;
    }
}

void PadRight(char *str, uint8_t len, char padChar) {
    uint8_t currentLen = (uint8_t)strlen(str);

    if (currentLen >= len) return; // Ya es suficientemente largo
    if (len > 20) len = 20;        // Seguridad para LCD 20x4

    // Simplemente empezamos donde termina el texto actual
    // y llenamos con el carácter hasta alcanzar 'len'
    for (uint8_t i = currentLen; i < len; i++) {
        str[i] = padChar;
    }

    // Ponemos el terminador nulo al final del nuevo largo
    str[len] = '\0';
}

// A utility function to reverse a string
//void reverse(char str[], uint16_t length)
//{
//    uint16_t start = 0;
//    uint16_t end = length - 1;
//    while (start < end) {
//        char temp = str[start];
//        str[start] = str[end];
//        str[end] = temp;
//        end--;
//        start++;
//    }
//}






//---- Times ------------------------------------------------------------------
//void Transform_Time(char  *sec, char *min, char *hr, char *week_day, char *day, char *mn, char *year) {
//        *sec  =  ((*sec & 0x70) >> 4)*10 + (*sec & 0x0F);
//        *min  =  ((*min & 0xF0) >> 4)*10 + (*min & 0x0F);
//        *hr   =  ((*hr & 0x30) >> 4)*10 + (*hr & 0x0F);
//        *week_day =(*week_day & 0x07);
//        *day  =  ((*day & 0xF0) >> 4)*10 + (*day & 0x0F);
//        *mn   =  ((*mn & 0x10) >> 4)*10 + (*mn & 0x0F);
//        *year =  ((*year & 0xF0)>>4)*10+(*year & 0x0F);
//}




//----- Checksum --------------------------------------------------------------








//----- Conversiones ----------------------------------------------------------
//uint8_t BCD2UpperCh(uint8_t bcd_)
//{
//    return ((bcd_ >> 4) + '0');
//}

//uint8_t BCD2LowerCh(uint8_t bcd_)
//{
//    return ((bcd_ & 0x0F) + '0');
//}

void ByteToHex(unsigned char value, char *buf) {
    static const char hex_chars[] = "0123456789ABCDEF";

    buf[0] = hex_chars[(value >> 4) & 0x0F]; // Extrae el nibble alto
    buf[1] = hex_chars[value & 0x0F]; // Extrae el nibble bajo
    buf[2] = '\0'; // Terminador de cadena
}

//----- HEX, Bin, Dec ---------------------------------------------------------
//uint8_t HEX_Table(uint8_t index) {
//    switch (index) {
//        case 0: return '0';
//        case 1: return '1';
//        case 2: return '2';
//        case 3: return '3';
//        case 4: return '4';
//        case 5: return '5';
//        case 6: return '6';
//        case 7: return '7';
//        case 8: return '8';
//        case 9: return '9';
//        case 10: return 'A';
//        case 11: return 'B';
//        case 12: return 'C';
//        case 13: return 'D';
//        case 14: return 'E';
//        case 15: return 'F';
//        default: return 0;
//    }
//}





//void ByteToBinaryStr(unsigned short input, char *output)
//{
//  char i;
//
//  output[8] = 0;
//  for(i = 8;i>0;)
//  {
//    output[--i] = input % 2 + 48;
//    input = input / 2;
//  }
//}

//void WordToBinaryStr(unsigned input, char *output)
//{
//  unsigned int i;
//
//  output[16] = 0;
//  for(i = 16;i>0;)
//  {
//    output[--i] = input % 2 + 48;
//    input = input / 2;
//  }
//}
//
//void LongWordToBinaryStr(unsigned long input, char *output)
//{
//  unsigned int i;
//
//  output[32] = 0;
//  for(i = 32;i>0;)
//  {
//    output[--i] = input % 2 + 48;
//    input = input / 2;
//  }
//}

// The reflected binary code, also known as Gray code, is a binary numeral system
// where two successive values differ in only one bit
//  Dec  Gray   Binary
//   0   000    000
//   1   001    001
//   2   011    010
//   3   010    011
//   4   110    100
//   5   111    101
//   6   101    110
//   7   100    111
//unsigned short BinaryToGray(unsigned short num)
//{
//  return (num>>1) ^ num;
//}

//unsigned short GrayToBinary(unsigned short num)
//{
//  unsigned short temp;
//  temp = num ^ (num>>8);
//  temp ^= (temp>>4);
//  temp ^= (temp>>2);
//  temp ^= (temp>>1);
//  return temp;
//}


