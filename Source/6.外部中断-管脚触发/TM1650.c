#include "TM1650.h"
#include "delay.h"
static u8 s_7number[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F}; 
static u8 s_8number[10] = {0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF};   // 8����ʾ��ʽ0~9
//--------------------------------------------------------------
// Prototype      : void IIC_Init_TM1650(void)
// Calls          : 
// Description    : 
//--------------------------------------------------------------
void IIC_Init_TM1650(void)
{
   SET_SCL_OUT_TM1650();
   SET_SDA_OUT_TM1650(); 
   SCL_TM1650(1);
   SDA_TM1650(1);
}
//--------------------------------------------------------------
// Prototype      : void Delay_us(void)
// Description    : 大约延时 z us
//--------------------------------------------------------------
void TDelay_us(u8 z)
{
   //u8 i;                   //fcpu 8MHz �  //for (i=50; i>0; i--);
	while(z--)
  {
    nop();nop();nop();nop();
	nop();nop();nop();nop();
  }
}
//--------------------------------------------------------------
// Prototype      : void I2C_Start(void)
// Calls          : Delay_5us()
// Description    : Start Singnal
//--------------------------------------------------------------
void I2C_Start_TM1650(void)
{
    // SDA 1->0 while SCL High
  	//SCL高电平期间，SDA出现一个下降沿表示起始信号
  	SET_SDA_OUT_TM1650();
    SDA_TM1650(1);    	//数据线先保持为高，起始信号要该口的下降沿 
	TDelay_us(4);
    SCL_TM1650(1);        //时钟线保持为�         
    TDelay_us(40);    //有一个大榵s的延时具体以器件而定            
    SDA_TM1650(0);        //数据线拉低出现下降沿           
    TDelay_us(4);    //延时 一小会，保证可靠的下降�         
    SCL_TM1650(0);        //拉低时钟线，保证接下来数据线允许改变            
}
 
 
//--------------------------------------------------------------
// Prototype      : void I2C_Stop(void)
// Calls          : Delay_5us()
// Description    : Stop Singnal
//-------------------------------------------------------------- 
void I2C_Stop_TM1650(void)
{
    // SDA 0->1 while SCL High
    //SCL高电平期间，SDA产生一个上升沿 表示停止
  	SET_SDA_OUT_TM1650();
	SCL_TM1650(0);
	TDelay_us(2);
	SDA_TM1650(0);		//保证数据线为低电�TDelay_us(40);
    SCL_TM1650(1);		//先保证时钟线为高电平
    TDelay_us(10);    //延时 以得到一个可靠的电平信号            
    SDA_TM1650(1);        //数据线出现上升沿           
    TDelay_us(40);    //延时 保证一个可靠的高电�        
}
 
 
//应答函数
void IIC_Ack_TM1650(void)
{
    //数据线一直保持为低电平，时钟线出现上升沿即为应答
 
	SET_SDA_OUT_TM1650();
	TDelay_us(10);
    SDA_TM1650(0);
    TDelay_us(10);
    SCL_TM1650(0);
    TDelay_us(40);
	SCL_TM1650(1);
	TDelay_us(40);
    //应答完成吥І时钟线拉低 允许数据修改
    SCL_TM1650(0);
}
void IIC_NAck_TM1650(void)
{
    //非应答即相反 与应答区别即为数据线保持高电平即�SET_SDA_OUT_TM1650();
	TDelay_us(10);
    SDA_TM1650(1);
    TDelay_us(10);
	SCL_TM1650(0);
	TDelay_us(40);
    SCL_TM1650(1);
    TDelay_us(40);
    //最后要将时钟线拉低 允许数据变化
    SCL_TM1650(0);
}
//等待应答
u8 IIC_Wait_Ack_TM1650(void)//0为有应答Ｄغ无应答
{
    //应答等待计数
    u8 ackTime = 0;
    //先将数据线要设置成输入模式本程序未体现，有应答则会出现下降沿
	SCL_TM1650(0);
	SET_SDA_OUT_TM1650();
    TDelay_us(10);	
	SDA_TM1650(1);//
	TDelay_us(30);
	SET_SDA_IN_TM1650();//切换为输入模�
    //时钟线拉�   SCL_TM1650 = 1;
    TDelay_us(30);
    //等待数据线拉低应�   
    while(SDAM_TM1650){
        //如果在该时间内仍未拉�       
      ackTime ++;
        if(ackTime > 250)
        {
            //认为非应筥\止信�
            I2C_Stop_TM1650();
            return 1;
        }
    }
    SCL_TM1650(0);
    return 0 ;
}
 
void IIC_WrByte_TM1650(u8 txd)
{ 
    u8 i;
	SET_SDA_OUT_TM1650();
//    SCL = 0;
    //按位发送数�   
	for(i = 0;i < 8; i ++)
    {
	  	TDelay_us(2);
        if((txd&0x80)>>7)
		{
			SDA_TM1650(1);
		}else{
			SDA_TM1650(0);
		}
			
        txd<<=1; 	  
		TDelay_us(20);   
		SCL_TM1650(1);
		TDelay_us(20);  
		SCL_TM1650(0);	
		TDelay_us(20); 
    }
}
 
/***************************
u8 Scan_Key(void)	  //按键扫描
{
	u8 i;
	u8 rekey;
	I2C_Start_TM1650();
	IIC_WrByte_TM1650(0x49);//读按键命�IIC_Ack_TM1650();
	//DIO_H;
	SET_SDA_IN_TM1650();//切换为输入模�for(i=0;i<8;i++)
	{
	   SCL_TM1650=1;
	   rekey = rekey<<1;
	   
	   if(SDAM_TM1650)
	   {
	   	rekey++;
	   } 
	   TDelay_us(5);
	   SCL_TM1650=0;	
	}
	IIC_Ack_TM1650();
	I2C_Stop_TM1650();
	return(rekey);
}
****************************/
 
void TM1650_Set(u8 add,u8 dat) 
{
	I2C_Start_TM1650();
	IIC_WrByte_TM1650(add); //第一个显存地址
	IIC_Ack_TM1650();
	IIC_WrByte_TM1650(dat);
	IIC_Ack_TM1650();
	I2C_Stop_TM1650();
}
void Init_Tm1650(void)
{
	IIC_Init_TM1650();
	delay_ms(50);			//需要延时一小段时间，否则开显示会无响应
	TM1650_Set(0x48,0x31);//初始化为5级灰度，开显示
	
}

void TM1650_SetNumber(u8 index, u8 num)
{
    u8 indexAddr = 0;
    u8 numValue = 0;
    
    if(index == 1)
    {
        indexAddr = 0x68;
    }
    else if(index == 2)
    {
        indexAddr = 0x6A;
    }
    else if(index == 3)
    {
        indexAddr = 0x6C;
    }
    else if(index == 4)
    {
        indexAddr = 0x6E;
    }
    
    numValue = s_7number[num];

    TM1650_Set(indexAddr, numValue);
}

void TM1650_SetDisplay(u8 brightness, u8 mode, u8 state)
{       
    if(state)
    {
        if(mode == 7)                                                   // 7段显示方�
        {
            TM1650_Set(0x48, brightness*16 + 1*4 + 1);
        }
        else if(mode == 8)                                              // 8段显示方�
        {
            TM1650_Set(0x48, brightness*16 + 1);                      
        }
    }
    else
    {
        TM1650_Set(0x48, 0x00);                                       // 关闭显示
    }
}
void TM1650_show_u8(u8 num)
{
	u8 one = num%10;
	u8 two = num/10;
	TM1650_SetNumber(1,one);
	TM1650_SetNumber(2,two);
}
