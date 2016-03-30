
#define LCD_CLK_PORT GPIO_PORT_2
#define LCD_CLK  GPIO_PIN_7

#define LCD_SDIN_PORT GPIO_PORT_2
#define LCD_SDIN GPIO_PIN_1

#define LCD_RST_PORT GPIO_PORT_2
#define LCD_RST  GPIO_PIN_8

#define LCD_DC_PORT GPIO_PORT_2
#define LCD_DC   GPIO_PIN_6

#define LCD_CS_PORT GPIO_PORT_2
#define LCD_CS   GPIO_PIN_0

void LCD_WrDat(unsigned char dat);

void LCD_WrCmd(unsigned char cmd);

void LCD_Set_Pos(unsigned char x, unsigned char y);

void LCD_Fill(unsigned char bmp_dat);

#define LCD_CLS() LCD_Fill(0)

void LCD_Init(void);

void LCD_PrintStr_6_8(unsigned char x, unsigned char y, unsigned char ch[]);

void LCD_PrintStr_8_16(unsigned char x, unsigned y, unsigned char ch[]);

void Draw_BMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[]);
