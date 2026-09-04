/*****************************************************************************
* File: oled.c
*
* Descirption: this file contains the functions support oled.
*
* Copyright (C) : 2023 ultraception.com
*
* Author: ultraception FW team
* Mail:   ultraception@ultraception.com
* Date:   2023 - 5
*****************************************************************************/
#include <stdlib.h>
#include "oled.h"
#include "oledfont.h"  	 
#include "zn_i2c.h"
#include "common.h"

uint8_t OLED_GRAM[144][8];

extern void dw_i2c_init(uint32_t id, uint32_t speed, uint8_t int_en);



//反显函数
void OLED_ColorTurn(uint8_t i)
{
	if(i==0)
	{
		OLED_WR_Byte(0xA6,OLED_CMD);//正常显示
	}
	if(i==1)
	{
		OLED_WR_Byte(0xA7,OLED_CMD);//反色显示
	}
}

//屏幕旋转180度
void OLED_DisplayTurn(uint8_t i)
{
	if(i==0)
	{
		OLED_WR_Byte(0xC8,OLED_CMD);//正常显示
		OLED_WR_Byte(0xA1,OLED_CMD);
	}
	if(i==1)
	{
		OLED_WR_Byte(0xC0,OLED_CMD);//反转显示
		OLED_WR_Byte(0xA0,OLED_CMD);
	}
}



//发送一个字节
//向SSD1306写入一个字节。
//mode:数据/命令标志 0,表示命令;1,表示数据;
void OLED_WR_Byte(uint8_t dat,uint8_t mode)
{
	uint32_t addr=0;
	I2C_DeviceType deviceCfg = {0};
	if (mode)
	{
		addr=0x40;
	}
	deviceCfg.devAddr = SSD1306_I2C_ADDR;
	deviceCfg.offset = addr;
	deviceCfg.offsetSize = 1;
	deviceCfg.buffer = &dat;
	deviceCfg.len = 1;

	i2c_master_write_poll(I2C0, &deviceCfg);
}

//开启OLED显示 
void OLED_DisPlay_On(void)
{
	OLED_WR_Byte(0x8D,OLED_CMD);//电荷泵使能
	OLED_WR_Byte(0x14,OLED_CMD);//开启电荷泵
	OLED_WR_Byte(0xAF,OLED_CMD);//点亮屏幕
}

//关闭OLED显示 
void OLED_DisPlay_Off(void)
{
	OLED_WR_Byte(0x8D,OLED_CMD);//电荷泵使能
	OLED_WR_Byte(0x10,OLED_CMD);//关闭电荷泵
	OLED_WR_Byte(0xAF,OLED_CMD);//关闭屏幕
}

//更新显存到OLED	
void OLED_Refresh(void)
{
	uint8_t i,n;
	for(i=0;i<8;i++)
	{
	   OLED_WR_Byte(0xb0+i,OLED_CMD); //设置行起始地址
	   OLED_WR_Byte(0x00,OLED_CMD);   //设置低列起始地址
	   OLED_WR_Byte(0x10,OLED_CMD);   //设置高列起始地址
	   for(n=0;n<128;n++)
	   {
		   OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA);
	   }
  }
}
//清屏函数
void OLED_Clear(void)
{
	uint8_t i,n;
	for(i=0;i<8;i++)
	{
		for(n=0;n<128;n++)
		{
			OLED_GRAM[n][i]=0;//清除所有数据
		}
	}
	OLED_Refresh();//更新显示
}

//画点 
//x:0~127
//y:0~63
void OLED_DrawPoint(uint8_t x,uint8_t y)
{
	uint8_t i,m,n;
	i=y>>3; /*y/8*/
	m=y&7;  /*m%8*/
	n=1<<m;
	OLED_GRAM[x][i]|=n;
}

//清除一个点
//x:0~127
//y:0~63
void OLED_ClearPoint(uint8_t x,uint8_t y)
{
	uint8_t i,m,n;
	i=y>>3;
	m=y&7;
	n=1<<m;
	OLED_GRAM[x][i]=~OLED_GRAM[x][i];
	OLED_GRAM[x][i]|=n;
	OLED_GRAM[x][i]=~OLED_GRAM[x][i];
}


//画线
//x:0~128
//y:0~64
void OLED_DrawLine(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2)
{
	uint8_t i,k,k1,k2,y0;
	if((x1<0)||(x2>128)||(y1<0)||(y2>64)||(x1>x2)||(y1>y2))return;
	if(x1==x2)    //画竖线
	{
		for(i=0;i<(y2-y1);i++)
		{
			OLED_DrawPoint(x1,y1+i);
		}
	}
	else if(y1==y2)   //画横线
	{
		for(i=0;i<(x2-x1);i++)
		{
			OLED_DrawPoint(x1+i,y1);
		}
	}
	else      //画斜线
	{
		k1=y2-y1;
		k2=x2-x1;
		k=k1*10/k2;
		for(i=0;i<(x2-x1);i++)
		{
		  OLED_DrawPoint(x1+i,y1+i*k/10);
		}
	}
}
//x,y:圆心坐标
//r:圆的半径
void OLED_DrawCircle(uint8_t x,uint8_t y,uint8_t r)
{
	int a, b,num;
    a = 0;
    b = r;
    while(2 * b * b >= r * r)      
    {
        OLED_DrawPoint(x + a, y - b);
        OLED_DrawPoint(x - a, y - b);
        OLED_DrawPoint(x - a, y + b);
        OLED_DrawPoint(x + a, y + b);
 
        OLED_DrawPoint(x + b, y + a);
        OLED_DrawPoint(x + b, y - a);
        OLED_DrawPoint(x - b, y - a);
        OLED_DrawPoint(x - b, y + a);
        
        a++;
        num = (a * a + b * b) - r*r;//计算画的点离圆心的距离
        if(num > 0)
        {
            b--;
            a--;
        }
    }
}



//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//size:选择字体 12/16/24
//取模方式 逐列式
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size1)
{
	uint8_t i,m,temp,size2,chr1;
	uint8_t y0=y;
	size2=((size1>>3)+((size1&7)?1:0))*(size1>>1); //size2=(size1/8+((size1%8)?1:0))*(size1/2)得到字体一个字符对应点阵集所占的字节数
	chr1=chr-' ';  //计算偏移后的值
	for(i=0;i<size2;i++)
	{
		if(size1==12)
        {
			temp=asc2_1206[chr1][i];//调用1206字体
		} 
		else if(size1==16)
        {
			temp=asc2_1608[chr1][i];//调用1608字体
		} 
		else if(size1==24)
        {
			temp=asc2_2412[chr1][i];//调用2412字体
		} 
		else
		{			
			return;
		}
		for(m=0;m<8;m++)           //写入数据
		{
			if(temp&0x80)OLED_DrawPoint(x,y);
			else OLED_ClearPoint(x,y);
			temp<<=1;
			y++;
			if((y-y0)==size1)
			{
				y=y0;
				x++;
				break;
			}
		}
	}
}


//显示字符串
//x,y:起点坐标  
//size1:字体大小 
//*chr:字符串起始地址 
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t size1)
{
	while((*chr>=' ')&&(*chr<='~'))//判断是不是非法字符!
	{
		OLED_ShowChar(x,y,*chr,size1);
		x+=(size1>>1); //x+=size1/2;
		if(x>128-size1)  //换行
		{
			x=0;
			y+=2;
		}
		chr++;
	}
}

//m^n
uint32_t OLED_Pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;
	while(n--)
	{
	  result*=m;
	}
	return result;
}

////显示2个数字
////x,y :起点坐标	 
////len :数字的位数
////size:字体大小
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size1)
{
	uint8_t t,temp;
	for(t=0;t<len;t++)
	{
		temp=(num/OLED_Pow(10,len-t-1))%10;
		if(temp==0)
		{
			OLED_ShowChar(x+(size1/2)*t,y,'0',size1);
		}
		else 
		{
			OLED_ShowChar(x+(size1/2)*t,y,temp+'0',size1);
		}
  }
}

//显示汉字
//x,y:起点坐标
//num:汉字对应的序号
//取模方式 列行式
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t num,uint8_t size1)
{
	uint8_t i,m,n=0,temp,chr1;
	uint8_t x0=x,y0=y;
	uint8_t size3=size1>>3; //size3=size1/8
	while(size3--)
	{
		chr1=num*size1/8+n;
		n++;
		for(i=0;i<size1;i++)
		{
			if(size1==16)
			{
				temp=Hzk1[chr1][i];//调用16*16字体
			}
			else if(size1==24)
			{
				temp=Hzk2[chr1][i]; //调用24*24字体
			}
			else if(size1==32)       
			{
				temp=Hzk3[chr1][i];//调用32*32字体
			}
			else if(size1==64)
			{
				temp=Hzk4[chr1][i];//调用64*64字体
			}
			else 
			{
				return;
			}
						
			for(m=0;m<8;m++)
			{
				if(temp&0x01)
				{
					OLED_DrawPoint(x,y);
				}
				else 
				{
					OLED_ClearPoint(x,y);
				}
				temp>>=1;
				y++;
			}
			x++;
			if((x-x0)==size1)
			{
				x=x0;
				y0=y0+8;
			}
			y=y0;
		 }
	}
}

//num 显示汉字的个数
//space 每一遍显示的间隔
void OLED_ScrollDisplay(uint8_t num,uint8_t space)
{
	uint8_t i,n,t=0,m=0,r;
	while(1)
	{
		if(m==0)
		{
			OLED_ShowChinese(128,24,t,16); //写入一个汉字保存在OLED_GRAM[][]数组中
			t++;
		}
		if(t==num)
		{
			for(r=0;r<16*space;r++)      //显示间隔
			{
				for(i=0;i<144;i++)
				{
					for(n=0;n<8;n++)
					{
						OLED_GRAM[i-1][n]=OLED_GRAM[i][n];
					}
				}
				OLED_Refresh();
			}
			t=0;
		}
		m++;
		if(m==16)
		{
			m=0;
		}
		for(i=0;i<144;i++)   //实现左移
		{
			for(n=0;n<8;n++)
			{
				OLED_GRAM[i-1][n]=OLED_GRAM[i][n];
			}
		}
		OLED_Refresh();
	}
}

//配置写入数据的起始位置
void OLED_WR_BP(uint8_t x,uint8_t y)
{
	OLED_WR_Byte(0xb0+y,OLED_CMD);//设置行起始地址
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD);
}

//x0,y0：起点坐标
//x1,y1：终点坐标
//BMP[]：要写入的图片数组
void OLED_ShowPicture(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t BMP[])
{
	uint32_t j=0;
	uint8_t x=0,y=0;
	if((y&7)==0) //y%8==0
	{
		y=0;
	}
	else
	{		
		y+=1;
	}
	for(y=y0;y<y1;y++)
	{
		OLED_WR_BP(x0,y);
		for(x=x0;x<x1;x++)
		{
			OLED_WR_Byte(BMP[j],OLED_DATA);
			j++;
		}
	}
}
//OLED的初始化
void OLED_Init(void)
{
	/*i2c init*/
	I2C_ConfigType config ={0};
	
	config.master = 1;
	config.clk = 38400000; 
	config.speed = I2C_STANDARD_SPEED;
	i2c_init(I2C0, &config);
	
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD);// Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF,OLED_CMD);
	OLED_Clear();
}

void OLED_Dis(void)
{
    uint8_t t = ' ';

    OLED_Init();
    mdelay(500);
    OLED_Clear();
    OLED_ShowChinese(0,0,0,16);
    OLED_ShowChinese(18,0,1,16);
    OLED_ShowChinese(36,0,2,16);
    OLED_ShowChinese(54,0,3,16);
    OLED_ShowChinese(72,0,4,16);
    OLED_ShowChinese(90,0,5,16);
    OLED_ShowChinese(108,0,6,16);
    OLED_ShowString(8,16,(uint8_t *)"UltraCeption",16);
    OLED_ShowString(20,32,(uint8_t *)"2023/02/08",16);
    OLED_ShowString(0,48,(uint8_t *)"  DEMO:ZN2014",16);
    OLED_Refresh();
}

void OLED_DisRangeFix(uint8_t type)
{
    OLED_Clear();

    if(0 == type)
    {
        OLED_ShowString(8, 8, (uint8_t *)"This is Anchor", 16);
    }
    else
    {
        OLED_ShowString(20, 8, (uint8_t *)"This is Tag", 16);
    }

    OLED_ShowString(2, 24, (uint8_t *)"Distance:", 16);

    OLED_ShowString(2, 40, (uint8_t *)"Aoa1:", 16);
    OLED_ShowString(66, 40, (uint8_t *)"Aoa2:", 16);

    OLED_Refresh();
}

void OLED_DisRangeFresh(uint32_t distance)
{
    uint32_t bai, shi, ge;

    if(0xffff == distance)
    {
        OLED_ShowString(78, 28, (uint8_t *)"invalid", 12);
        OLED_ShowChar(120, 28, ' ', 12);
    }
    else
    {
        bai = distance / 100;
        shi = (distance - bai *100) / 10;
        ge  = distance - (bai * 100 + shi * 10);

        if(bai >= 0 && bai <= 9)
        {
            OLED_ShowChar(78, 28, ' ', 12);
            OLED_ShowNum(84, 28, bai, 1, 12);
            OLED_ShowString(90, 28, (uint8_t *)".", 12);
            OLED_ShowNum(96, 28, shi, 1, 12);
            OLED_ShowNum(102, 28, ge, 1, 12);
            OLED_ShowChar(108, 28, ' ', 12);
            OLED_ShowChar(114, 28, ' ', 12);
        }
        else if(bai >= 10 && bai <= 99)
        {
            OLED_ShowChar(78, 28, ' ', 12);
            OLED_ShowNum(81, 28, bai, 2, 12);
            OLED_ShowString(93, 28, (uint8_t *)".", 12);
            OLED_ShowNum(99, 28, shi, 1, 12);
            OLED_ShowNum(105, 28, ge, 1, 12);
            OLED_ShowChar(111, 28, ' ', 12);
            OLED_ShowChar(117, 28, ' ', 12);
        }
        else
        {
            OLED_ShowNum(78, 28, bai, 3, 12);
            OLED_ShowString(96, 28, (uint8_t *)".", 12);
            OLED_ShowNum(102, 28, shi, 1, 12);
            OLED_ShowNum(108, 28, ge, 1, 12);
            OLED_ShowChar(114, 28, ' ', 12);
        }
        OLED_ShowString(116, 24, (uint8_t *)"m", 16);
    }

    OLED_Refresh();
}

void OLED_DisAoaAzimuthFresh(int16_t aoa)
{
    uint16_t bai, shi, ge;

    if((aoa > 180) || (aoa < -180))
    {
        OLED_ShowString(40, 44, (uint8_t *)" -- ", 12);
        return;
    }

    if(aoa >= 0)
    {
        OLED_ShowChar(40, 44, ' ', 12);
    }
    else
    {
        aoa = abs(aoa);
        OLED_ShowChar(40, 44, '-', 12);
    }

    bai = aoa / 100;
    shi = (aoa - bai * 100) / 10;
    ge  = aoa - (bai * 100 + shi * 10);

    if(bai > 0 && bai <= 9)
    {
        OLED_ShowNum(44, 44, bai, 1, 12);
        OLED_ShowNum(50, 44, shi, 1, 12);
        OLED_ShowNum(56, 44, ge, 1, 12);
    }
    else if(shi > 0 && shi <= 9)
    {
        OLED_ShowNum(44, 44, shi, 1, 12);
        OLED_ShowNum(50, 44, ge, 1, 12);
        OLED_ShowChar(56, 44, ' ', 12);
    }
    else
    {
        OLED_ShowNum(44, 44, ge, 1, 12);
        OLED_ShowChar(50, 44, ' ', 12);
        OLED_ShowChar(56, 44, ' ', 12);
    }

    OLED_Refresh();
}

void OLED_DisAoaElevationFresh(int16_t aoa)
{
    uint16_t bai, shi, ge;

    if((aoa > 180) || (aoa < -180))
    {
        OLED_ShowString(104, 44, (uint8_t *)" --", 12);
        OLED_ShowChar(122, 44, ' ', 12);
        return;
    }

    if(aoa >= 0)
    {
        OLED_ShowChar(104, 44, ' ', 12);
    }
    else
    {
        aoa = abs(aoa);
        OLED_ShowChar(104, 44, '-', 12);
    }

    bai = aoa / 100;
    shi = (aoa - bai * 100) / 10;
    ge  = aoa - (bai * 100 + shi * 10);

    if(bai > 0 && bai <= 9)
    {
        OLED_ShowNum(110, 44, bai, 1, 12);
        OLED_ShowNum(116, 44, shi, 1, 12);
        OLED_ShowNum(122, 44, ge, 1, 12);
    }
    else if(shi > 0 && shi <= 9)
    {
        OLED_ShowNum(110, 44, shi, 1, 12);
        OLED_ShowNum(116, 44, ge, 1, 12);
        OLED_ShowChar(122, 44, ' ', 12);
    }
    else
    {
        OLED_ShowNum(110, 44, ge, 1, 12);
        OLED_ShowChar(116, 44, ' ', 12);
        OLED_ShowChar(122, 44, ' ', 12);
    }

    OLED_Refresh();
}

void OLED_Test(void)
{

	OLED_Init();
	OLED_DisplayTurn(0);
	OLED_ShowString(0,0,(uint8_t *)("Hello"),24);

	OLED_Refresh();
};
