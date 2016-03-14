/****************************************************************************
 *   $Id:: i2c.c 3662 2010-06-03 19:47:02Z usb00423                         $
 *   Project: NXP LPC11xx I2C example
 *
 *   Description:
 *     This file contains I2C code example which include I2C initialization, 
 *     I2C interrupt handler, and APIs for I2C access.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#include "LPC11xx.h"			/* LPC11xx Peripheral Registers */
#include "type.h"
#include "i2c.h"

volatile uint32_t I2CMasterState = I2C_IDLE;
volatile uint32_t I2CSlaveState = I2C_IDLE;
volatile uint32_t timeout = 0;

volatile uint32_t I2CMode;

volatile uint8_t I2CMasterBuffer[IIC_BUFSIZE];
volatile uint8_t I2CSlaveBuffer [IIC_BUFSIZE];
volatile uint32_t I2CCount = 0;
volatile uint32_t I2CReadLength;
volatile uint32_t I2CWriteLength;

volatile uint32_t RdIndex = 0;
volatile uint32_t WrIndex = 0;

/* 
From device to device, the I2C communication protocol may vary, 
in the example below, the protocol uses repeated start to read data from or 
write to the device:
For master read: the sequence is: STA,Addr(W),offset,RE-STA,Addr(r),data...STO 
for master write: the sequence is: STA,Addr(W),offset,RE-STA,Addr(w),data...STO
Thus, in state 8, the address is always WRITE. in state 10, the address could 
be READ or WRITE depending on the I2C command.
*/   

/*****************************************************************************
** Function name:		I2C_IRQHandler
**
** Descriptions:		I2C interrupt handler, deal with master mode only.
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void I2C_IRQHandler(void) 
{
  uint8_t StatValue;

  timeout = 0;
  /* this handler deals with master read and master write only */
  StatValue = LPC_I2C->STAT;
  switch ( StatValue )
  {
	case 0x08:			/* A Start condition is issued. */
	WrIndex = 0;
	LPC_I2C->DAT = I2CMasterBuffer[WrIndex++];
	LPC_I2C->CONCLR = (I2CONCLR_SIC | I2CONCLR_STAC);
	break;
	
	case 0x10:			/* A repeated started is issued */
	RdIndex = 0;
	/* Send SLA with R bit set, */
	LPC_I2C->DAT = I2CMasterBuffer[WrIndex++];
	LPC_I2C->CONCLR = (I2CONCLR_SIC | I2CONCLR_STAC);
	break;
	
	case 0x18:			/* Regardless, it's a ACK */
	if ( I2CWriteLength == 1 )
	{
	  LPC_I2C->CONSET = I2CONSET_STO;      /* Set Stop flag */
	  I2CMasterState = I2C_NO_DATA;
	}
	else
	{
	  LPC_I2C->DAT = I2CMasterBuffer[WrIndex++];
	}
	LPC_I2C->CONCLR = I2CONCLR_SIC;
	break;
	
	case 0x28:	/* Data byte has been transmitted, regardless ACK or NACK */
	if ( WrIndex < I2CWriteLength )
	{   
	  LPC_I2C->DAT = I2CMasterBuffer[WrIndex++]; /* this should be the last one */
	}
	else
	{
	  if ( I2CReadLength != 0 )
	  {
		LPC_I2C->CONSET = I2CONSET_STA;	/* Set Repeated-start flag */
	  }
	  else
	  {
		LPC_I2C->CONSET = I2CONSET_STO;      /* Set Stop flag */
		I2CMasterState = I2C_OK;
	  }
	}
	LPC_I2C->CONCLR = I2CONCLR_SIC;
	break;

	case 0x30:
	LPC_I2C->CONSET = I2CONSET_STO;      /* Set Stop flag */
	I2CMasterState = I2C_NACK_ON_DATA;
	LPC_I2C->CONCLR = I2CONCLR_SIC;
	break;
	
	case 0x40:	/* Master Receive, SLA_R has been sent */
	if ( (RdIndex + 1) < I2CReadLength )
	{
	  /* Will go to State 0x50 */
	  LPC_I2C->CONSET = I2CONSET_AA;	/* assert ACK after data is received */
	}
	else
	{
	  /* Will go to State 0x58 */
	  LPC_I2C->CONCLR = I2CONCLR_AAC;	/* assert NACK after data is received */
	}
	LPC_I2C->CONCLR = I2CONCLR_SIC;
	break;
	
	case 0x50:	/* Data byte has been received, regardless following ACK or NACK */
	I2CSlaveBuffer[RdIndex++] = LPC_I2C->DAT;
	if ( (RdIndex + 1) < I2CReadLength )
	{   
	  LPC_I2C->CONSET = I2CONSET_AA;	/* assert ACK after data is received */
	}
	else
	{
	  LPC_I2C->CONCLR = I2CONCLR_AAC;	/* assert NACK on last byte */
	}
	LPC_I2C->CONCLR = I2CONCLR_SIC;
	break;
	
	case 0x58:
	I2CSlaveBuffer[RdIndex++] = LPC_I2C->DAT;
	I2CMasterState = I2C_OK;
	LPC_I2C->CONSET = I2CONSET_STO;	/* Set Stop flag */ 
	LPC_I2C->CONCLR = I2CONCLR_SIC;	/* Clear SI flag */
	break;

	case 0x20:		/* regardless, it's a NACK */
	case 0x48:
	LPC_I2C->CONSET = I2CONSET_STO;      /* Set Stop flag */
	I2CMasterState = I2C_NACK_ON_ADDRESS;
	LPC_I2C->CONCLR = I2CONCLR_SIC;
	break;
	
	case 0x38:		/* Arbitration lost, in this example, we don't
					deal with multiple master situation */
	default:
	I2CMasterState = I2C_ARBITRATION_LOST;
	LPC_I2C->CONCLR = I2CONCLR_SIC;	
	break;
  }
  return;
}

/*****************************************************************************
** Function name:		I2CStart
**
** Descriptions:		Create I2C start condition, a timeout
**				value is set if the I2C never gets started,
**				and timed out. It's a fatal error. 
**
** parameters:			None
** Returned value:		true or false, return false if timed out
** 
*****************************************************************************/
uint32_t I2CStart( void )
{
  uint32_t timeout = 0;
  uint32_t retVal = FALSE;
 
  /*--- Issue a start condition ---*/
  LPC_I2C->CONSET = I2CONSET_STA;	/* Set Start flag */
    
  /*--- Wait until START transmitted ---*/
  while( 1 )
  {
	if ( I2CMasterState == I2C_STARTED )
	{
	  retVal = TRUE;
	  break;	
	}
	if ( timeout >= MAX_TIMEOUT )
	{
	  retVal = FALSE;
	  break;
	}
	timeout++;
  }
  return( retVal );
}

/*****************************************************************************
** Function name:		I2CStop
**
** Descriptions:		Set the I2C stop condition, if the routine
**				never exit, it's a fatal bus error.
**
** parameters:			None
** Returned value:		true or never return
** 
*****************************************************************************/
uint32_t I2CStop( void )
{
  LPC_I2C->CONSET = I2CONSET_STO;      /* Set Stop flag */ 
  LPC_I2C->CONCLR = I2CONCLR_SIC;  /* Clear SI flag */ 
            
  /*--- Wait for STOP detected ---*/
  while( LPC_I2C->CONSET & I2CONSET_STO );
  return TRUE;
}

/*****************************************************************************
** Function name:		I2CInit
**
** Descriptions:		Initialize I2C controller
**
** parameters:			I2c mode is either MASTER or SLAVE
** Returned value:		true or false, return false if the I2C
**				interrupt handler was not installed correctly
** 
*****************************************************************************/
uint32_t I2CInit( uint32_t I2cMode ) 
{
  LPC_SYSCON->PRESETCTRL |= (0x1<<1);

  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<5);
  LPC_IOCON->PIO0_4 &= ~0x3F;	/*  I2C I/O config */
  LPC_IOCON->PIO0_4 |= 0x01;		/* I2C SCL */
  LPC_IOCON->PIO0_5 &= ~0x3F;	
  LPC_IOCON->PIO0_5 |= 0x01;		/* I2C SDA */
  /* IOCON may change in the next release, save change for future references. */
//  LPC_IOCON->PIO0_4 |= (0x1<<10);	/* open drain pins */
//  LPC_IOCON->PIO0_5 |= (0x1<<10);	/* open drain pins */

  /*--- Clear flags ---*/
  LPC_I2C->CONCLR = I2CONCLR_AAC | I2CONCLR_SIC | I2CONCLR_STAC | I2CONCLR_I2ENC;    

  /*--- Reset registers ---*/
#if FAST_MODE_PLUS
  LPC_IOCON->PIO0_4 |= (0x2<<8);
  LPC_IOCON->PIO0_5 |= (0x2<<8);
  LPC_I2C->SCLL   = I2SCLL_HS_SCLL;
  LPC_I2C->SCLH   = I2SCLH_HS_SCLH;
#else
  LPC_I2C->SCLL   = I2SCLL_SCLL;
  LPC_I2C->SCLH   = I2SCLH_SCLH;
#endif

  if ( I2cMode == I2CSLAVE )
  {
	LPC_I2C->ADR0 = CAT24C02_ADDR;
  }    

  /* Enable the I2C Interrupt */
  NVIC_EnableIRQ(I2C_IRQn);

  LPC_I2C->CONSET = I2CONSET_I2EN;
  return( TRUE );
}

/*****************************************************************************
** Function name:		I2CEngine
**
** Descriptions:		The routine to complete a I2C transaction
**				from start to stop. All the intermitten
**				steps are handled in the interrupt handler.
**				Before this routine is called, the read
**				length, write length, I2C master buffer,
**				and I2C command fields need to be filled.
**				see i2cmst.c for more details. 
**
** parameters:			None
** Returned value:		true or false, return false only if the
**				start condition can never be generated and
**				timed out. 
** 
*****************************************************************************/
uint32_t I2CEngine( void ) 
{
  RdIndex = 0;
  WrIndex = 0;

  /*--- Issue a start condition ---*/
  LPC_I2C->CONSET = I2CONSET_STA;	/* Set Start flag */

  I2CMasterState = I2C_BUSY;	

  while ( I2CMasterState == I2C_BUSY )
  {
	if ( timeout >= MAX_TIMEOUT )
	{
	  I2CMasterState = I2C_TIME_OUT;
	  break;
	}
	timeout++;
  }
  LPC_I2C->CONCLR = I2CONCLR_STAC;

  return ( I2CMasterState );
}
/* ���벢����I2CEngine֮ǰ�����ú����еĲ�������д���ݳ��ȣ������ݳ���
  I2C�����ʼ��I2CMasterBuffer
  (1)���ֻд��I2CWriteLengthΪд�������ֽ�����I2CReadLength������Ϊ0��
	 ��д��������I2CMasterBuffer��
  (2)���ֻ����I2CReadLengthΪ�������ֽ�����I2CWriteLengthΪ0������
	 �����������I2CSlaveBuffer��
  (3)������ж�����д��I2CWriteLengthָ��д�����ݳ��ȣ�I2CReadLength
	 ָ����ȡ���ݳ��ȡ�
	  */
/*****************************************************************
	                      IICд1���ֽ�
��  �ܣ� ��IIC�豸ָ����ַдһ���ֽ�

��  ���� Dev_WR_Addr:�豸��ַ 
         DataAddr   :������ʼ��ַ	
         Pdata      :�������ݵ�ָ��
         Len        : ���ݳ��ȣ��ֽ�Ϊ��λ��

����ֵ�� ��
*****************************************************************/
void I2C_WriteByte( uint8_t Dev_WR_Addr,uint8_t DataAddr,uint8_t Data ) 
{
	uint32_t j;
    I2CWriteLength = 3;	//1�ֽ��豸��ַ��1�ֽ����ݵ�ַ��1�ֽھ�����ֵ		  
    I2CReadLength  = 0;
    I2CMasterBuffer[0] = Dev_WR_Addr;  
    I2CMasterBuffer[1] = DataAddr;
	I2CMasterBuffer[2] = Data;	
    I2CEngine(); 
	for (j = 0; j < 0x20000; j++ ); 	   //д�ӳ�
} 

/*****************************************************************
	                    24C08дһҳ16���ֽ�
��  �ܣ� ��IIC�豸ָ����ַдn���ֽ�

��  ���� Pdata      :�������ݵ�ָ��
         Len        :���ݳ��ȣ��ֽ�Ϊ��λ��
		 DataAddr   :������ʼ��ַ
         Dev_WR_Addr:�豸��ַ  
		         	              
����ֵ�� ��
*****************************************************************/
void I2C_Write( volatile uint8_t *Pdata,uint8_t Len,uint8_t DataAddr,uint8_t Dev_WR_Addr) 
{
    uint8_t i;
	uint32_t j;
    I2CWriteLength = Len+2;			  
    I2CReadLength  = 0;
    I2CMasterBuffer[0] = Dev_WR_Addr;  
    I2CMasterBuffer[1] = DataAddr;
	for(i=0;i<Len;i++)
	{		 		
        I2CMasterBuffer[i+2] = Pdata[i];  
	}	
    I2CEngine(); 
	for (j = 0; j < 0x20000; j++ ); 	   //д�ӳ�
} 

/*****************************************************************
	                      IIC��1���ֽ�
��  �ܣ� ��IIC�豸�ڲ�ָ����ַ����һ���ֽ�

��  ���� Dev_WR_Addr���豸��ַ 
         DataAddr   ���ڲ����ݵ�ַ

����ֵ�� ��
*****************************************************************/
uint8_t I2C_ReadByte( uint8_t Dev_WR_Addr,uint8_t DataAddr ) 
{
    I2CWriteLength = 2;				  //1�ֽ��豸��ַ��1�ֽ����ݵ�ַ
    I2CReadLength  = 1;				  //��1�ֽھ�����ֵ
    I2CMasterBuffer[0] = Dev_WR_Addr;
    I2CMasterBuffer[1] = DataAddr;				
    I2CMasterBuffer[2] = Dev_WR_Addr | RD_BIT;
    I2CEngine();
	return I2CSlaveBuffer[0];
}

/*****************************************************************
	                      IIC��N���ֽ�(N<=64)
��  �ܣ� ��IIC�豸�ڲ�ָ����ַ����N���ֽ�

��  ���� Pdata      :�������ݵ�ָ��
         Len        :���ݳ��ȣ��ֽ�Ϊ��λ��
		 DataAddr   :������ʼ��ַ
         Dev_WR_Addr:�豸��ַ

����ֵ�� ��
*****************************************************************/
void I2C_Read( volatile uint8_t *Pdata,uint8_t Len,uint8_t DataAddr,uint8_t Dev_WR_Addr ) 
{
    uint32_t j;
    I2CWriteLength = 2;				 //1�ֽ��豸��ַ��1�ֽ����ݵ�ַ
    I2CReadLength  = Len;			 //��Len�ֽھ�����ֵ
    I2CMasterBuffer[0] = Dev_WR_Addr;
    I2CMasterBuffer[1] = DataAddr;				
    I2CMasterBuffer[2] = Dev_WR_Addr | RD_BIT;
    I2CEngine();
	for (j = 0; j < 0x20000; j++ );  //	�ȴ������
}

/**
  * @}
  */ 

/**
  * @}
  */ 

/************* (C) COPYRIGHT 2010 Wuhan R&D Center, Embest *****�ļ�����*******/
