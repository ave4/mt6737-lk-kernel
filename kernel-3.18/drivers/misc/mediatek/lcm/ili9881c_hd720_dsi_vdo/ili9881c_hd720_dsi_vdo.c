/* BEGIN PN: , Added by h84013687, 2013.08.13*/
#ifndef BUILD_LK
#include <linux/string.h>
#endif
#include "lcm_drv.h"

#ifdef BUILD_LK
 //   #include <platform/mt_gpio.h>
	
#elif defined(BUILD_UBOOT)
//    #include <asm/arch/mt_gpio.h>
#else
    //#include <linux/delay.h>
//    #include <mach/mt_gpio.h>
#endif
#ifdef BUILD_LK
#define LCD_DEBUG(fmt)  dprintf(CRITICAL,fmt)
#else
#define LCD_DEBUG(fmt)  printk(fmt)
#endif


const static unsigned char LCD_MODULE_ID = 0x09;//ID0->1;ID1->X
// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------
#define LCM_DSI_CMD_MODE									0
#define FRAME_WIDTH  										(720)
#define FRAME_HEIGHT 										(1280)

#define REGFLAG_DELAY             								0xFC
#define REGFLAG_END_OF_TABLE      							0xFD   // END OF REGISTERS MARKER

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

const static unsigned int BL_MIN_LEVEL =20;
static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)    								(lcm_util.set_reset_pin((v)))
// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

#define UDELAY(n) 											(lcm_util.udelay(n))
#define MDELAY(n) 											(lcm_util.mdelay(n))

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)	lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)										lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)					lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg(cmd)										lcm_util.dsi_dcs_read_lcm_reg(cmd)
#define read_reg_v2(cmd, buffer, buffer_size)   			lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)    

struct LCM_setting_table {
    unsigned char cmd;
    unsigned char count;
    unsigned char para_list[128];
};

//update initial param for IC boe_nt35521 0.01
static struct LCM_setting_table lcm_initialization_setting[] = {
{0xFF,3,{0x98,0x81,0x03}},
{0x01,1,{0x08}},
{0x02,1,{0x00}},
{0x03,1,{0x73}},
{0x04,1,{0x73}},
{0x05,1,{0x14}},
{0x06,1,{0x06}},
{0x07,1,{0x02}},
{0x08,1,{0x05}},
{0x09,1,{0x00}},
{0x0a,1,{0x0c}},
{0x0b,1,{0x00}},
{0x0c,1,{0x1c}},
{0x0d,1,{0x1c}},
{0x0e,1,{0x00}},
{0x0f,1,{0x0c}},
{0x10,1,{0x0c}}, 
{0x11,1,{0x01}},
{0x12,1,{0x01}},
{0x13,1,{0x1b}},  
{0x14,1,{0x0b}},
{0x15,1,{0x00}},
{0x16,1,{0x00}}, 
{0x17,1,{0x00}}, 
{0x18,1,{0x00}},
{0x19,1,{0x00}},
{0x1a,1,{0x00}},
{0x1b,1,{0x00}},
{0x1c,1,{0x00}},
{0x1d,1,{0x00}},   
{0x1e,1,{0xc8}},
{0x1f,1,{0x80}},  
{0x20,1,{0x02}},
{0x21,1,{0x00}},
{0x22,1,{0x02}},   
{0x23,1,{0x00}},
{0x24,1,{0x00}},  
{0x25,1,{0x00}}, 
{0x26,1,{0x00}},
{0x27,1,{0x00}},
{0x28,1,{0xfb}},  
{0x29,1,{0x43}},
{0x2a,1,{0x00}},
{0x2b,1,{0x00}},
{0x2c,1,{0x07}},
{0x2d,1,{0x07}},
{0x2e,1,{0xff}},
{0x2f,1,{0xff}},
{0x30,1,{0x11}},
{0x31,1,{0x00}},
{0x32,1,{0x00}},
{0x33,1,{0x00}},
{0x34,1,{0x84}},
{0x35,1,{0x80}},
{0x36,1,{0x07}},
{0x37,1,{0x00}},
{0x38,1,{0x00}},
{0x39,1,{0x00}},
{0x3a,1,{0x00}}, 
{0x3b,1,{0x00}},
{0x3c,1,{0x00}},
{0x3d,1,{0x00}},
{0x3e,1,{0x00}},
{0x3f,1,{0x00}},
{0x40,1,{0x00}},
{0x41,1,{0x00}},
{0x42,1,{0x00}},
{0x43,1,{0x80}},
{0x44,1,{0x08}},
{0x50,1,{0x01}},
{0x51,1,{0x23}},
{0x52,1,{0x45}},
{0x53,1,{0x67}},
{0x54,1,{0x89}},
{0x55,1,{0xab}},
{0x56,1,{0x01}},
{0x57,1,{0x23}},
{0x58,1,{0x45}},
{0x59,1,{0x67}},
{0x5a,1,{0x89}},
{0x5b,1,{0xab}},
{0x5c,1,{0xcd}},
{0x5d,1,{0xef}},
{0x5e,1,{0x10}},   
{0x5f,1,{0x02}},
{0x60,1,{0x02}},
{0x61,1,{0x02}},
{0x62,1,{0x02}},
{0x63,1,{0x02}},
{0x64,1,{0x02}},
{0x65,1,{0x02}},
{0x66,1,{0x08}},
{0x67,1,{0x09}},
{0x68,1,{0x02}},
{0x69,1,{0x10}},
{0x6a,1,{0x12}},
{0x6b,1,{0x11}},
{0x6c,1,{0x13}},
{0x6d,1,{0x0c}},
{0x6e,1,{0x0E}},
{0x6f,1,{0x0d}},
{0x70,1,{0x0f}},
{0x71,1,{0x06}},
{0x72,1,{0x07}},
{0x73,1,{0x02}},
{0x74,1,{0x02}},
{0x75,1,{0x02}},
{0x76,1,{0x02}},
{0x77,1,{0x02}},
{0x78,1,{0x02}},
{0x79,1,{0x02}},
{0x7a,1,{0x02}},
{0x7b,1,{0x02}},
{0x7c,1,{0x07}},
{0x7d,1,{0x06}},
{0x7e,1,{0x02}},
{0x7f,1,{0x11}},
{0x80,1,{0x13}},
{0x81,1,{0x10}},
{0x82,1,{0x12}},
{0x83,1,{0x0F}},
{0x84,1,{0x0d}},
{0x85,1,{0x0e}},
{0x86,1,{0x0c}},
{0x87,1,{0x09}},
{0x88,1,{0x08}},
{0x89,1,{0x02}},
{0x8A,1,{0x02}},                                                     
{0xFF,3,{0x98,0x81,0x04}},
{0x6C,1,{0x15}},
{0x6E,1,{0x2B}},     //28       //VGH clamp 15V
{0x6F,1,{0x35}},                
{0x3A,1,{0xA4}},                
{0x8D,1,{0x1F}},                //VGL clamp -12V
{0x87,1,{0xBA}},               
{0x26,1,{0x76}},            
{0xB2,1,{0xD1}},                                                    
{0xFF,3,{0x98,0x81,0x01}},
{0x22,1,{0x0A}},		//BGR,0x SS
{0x31,1,{0x0B}},		//
{0x34,1,{0x01}},
{0x40,1,{0x33}},
{0x53,1,{0x64}},		//VCOM1
{0x55,1,{0x8f}},		//VCOM2
{0x50,1,{0xA7}},    //75         	//VREG1OUT=4.1V
{0x51,1,{0xA7}},    //75        	//VREG2OUT=-4.1V                          
{0x60,1,{0x14}},               //SDT
{0xA0,1,{0x00}},		//VP255	Gamma P
{0xA1,1,{0x22}},               //VP251        
{0xA2,1,{0x37}},               //VP247        
{0xA3,1,{0x0f}},               //VP243        
{0xA4,1,{0x19}},               //VP239        
{0xA5,1,{0x27}},               //VP231        
{0xA6,1,{0x1C}},               //VP219        
{0xA7,1,{0x1E}},               //VP203        
{0xA8,1,{0x96}},               //VP175        
{0xA9,1,{0x19}},               //VP144        
{0xAA,1,{0x25}},               //VP111        
{0xAB,1,{0x83}},               //VP80         
{0xAC,1,{0x19}},               //VP52         
{0xAD,1,{0x18}},               //VP36         
{0xAE,1,{0x4F}},               //VP24         
{0xAF,1,{0x22}},               //VP16         
{0xB0,1,{0x2A}},               //VP12         
{0xB1,1,{0x57}},               //VP8          
{0xB2,1,{0x64}},               //VP4          
{0xB3,1,{0x39}},               //VP0                                        
{0xC0,1,{0x00}},		//VN255 GAMMA N
{0xC1,1,{0x26}},               //VN251        
{0xC2,1,{0x2F}},               //VN247        
{0xC3,1,{0x19}},               //VN243        
{0xC4,1,{0x16}},               //VN239        
{0xC5,1,{0x2C}},               //VN231        
{0xC6,1,{0x1F}},               //VN219        
{0xC7,1,{0x1F}},               //VN203        
{0xC8,1,{0x98}},               //VN175        
{0xC9,1,{0x1D}},               //VN144        
{0xCA,1,{0x2A}},               //VN111        
{0xCB,1,{0x8C}},               //VN80         
{0xCC,1,{0x1D}},               //VN52         
{0xCD,1,{0x1C}},               //VN36         
{0xCE,1,{0x4D}},               //VN24         
{0xCF,1,{0x24}},               //VN16         
{0xD0,1,{0x28}},               //VN12         
{0xD1,1,{0x5F}},               //VN8          
{0xD2,1,{0x6D}},              //VN4          
{0xD3,1,{0x39}},               //VN0  
{0xFF,3,{0x98,0x81,0x00}},
{0x11,01,{0x00}},
{REGFLAG_DELAY, 120, {}},  
{0x29,01,{0x00}},	
{REGFLAG_DELAY, 20, {}},  
{REGFLAG_END_OF_TABLE, 0x00, {}} 
};
static void init_lcm_registers(void)
{
	unsigned int data_array[16];
	
	data_array[0]=0x00043902;
	data_array[1]=0x038198FF;
	dsi_set_cmdq(data_array, 2, 1);

	data_array[0]=0x00023902;
	data_array[1]=0x00000801;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000002;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x00007303;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x00007304;
	dsi_set_cmdq(data_array, 2, 1);

	data_array[0]=0x00023902;
	data_array[1]=0x00001405;
	dsi_set_cmdq(data_array, 2, 1);

	data_array[0]=0x00023902;
	data_array[1]=0x00000606;
	dsi_set_cmdq(data_array, 2, 1);

	data_array[0]=0x00023902;
	data_array[1]=0x00000207;
	dsi_set_cmdq(data_array, 2, 1);

	data_array[0]=0x00023902;
	data_array[1]=0x00000508;
	dsi_set_cmdq(data_array, 2, 1);

	data_array[0]=0x00023902;
	data_array[1]=0x00000009;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000C0A;
	dsi_set_cmdq(data_array, 2, 1);	

	data_array[0]=0x00023902;
	data_array[1]=0x0000000B;
	dsi_set_cmdq(data_array, 2, 1);	

	data_array[0]=0x00023902;
	data_array[1]=0x00001C0C;
	dsi_set_cmdq(data_array, 2, 1);	

	data_array[0]=0x00023902;
	data_array[1]=0x00001C0D;
	dsi_set_cmdq(data_array, 2, 1);	

	data_array[0]=0x00023902;
	data_array[1]=0x0000000E;
	dsi_set_cmdq(data_array, 2, 1);	

	data_array[0]=0x00023902;
	data_array[1]=0x00000C0F;
	dsi_set_cmdq(data_array, 2, 1);	

	data_array[0]=0x00023902;
	data_array[1]=0x00000C10;
	dsi_set_cmdq(data_array, 2, 1);		
/*--------------------------------------------*/
	data_array[0]=0x00023902;
	data_array[1]=0x00000111;
	dsi_set_cmdq(data_array, 2, 1);		
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000112;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00001B13;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000B14;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000015;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000016;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000017;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000018;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000019;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000001A;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000001B;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000001C;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000001D;
	dsi_set_cmdq(data_array, 2, 1);	

	data_array[0]=0x00023902;
	data_array[1]=0x0000C81E;
	dsi_set_cmdq(data_array, 2, 1);	

	data_array[0]=0x00023902;
	data_array[1]=0x0000801F;
	dsi_set_cmdq(data_array, 2, 1);	

	data_array[0]=0x00023902;
	data_array[1]=0x00000220;
	dsi_set_cmdq(data_array, 2, 1);	
/*--------------------------------------------*/
	data_array[0]=0x00023902;
	data_array[1]=0x00000021;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000222;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000023;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000024;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000025;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000026;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000027;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000FB28;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00004329;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000002A;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000002B;
	dsi_set_cmdq(data_array, 2, 1);	

	data_array[0]=0x00023902;
	data_array[1]=0x0000072C;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000072D;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000FF2E;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000FF2F;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00001130;
	dsi_set_cmdq(data_array, 2, 1);
/*--------------------------------------------*/	
	data_array[0]=0x00023902;
	data_array[1]=0x00000031;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000032;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000033;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x00008434;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00008035;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000736;
	dsi_set_cmdq(data_array, 2, 1);

	data_array[0]=0x00023902;
	data_array[1]=0x00000037;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000038;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000039;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000003A;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000003B;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000003C;
	dsi_set_cmdq(data_array, 2, 1);	

	data_array[0]=0x00023902;
	data_array[1]=0x0000003D;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000003E;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000003F;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000040;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000041;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000042;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x00008043;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000844;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000150;
	dsi_set_cmdq(data_array, 2, 1);	
/*--------------------------------------------*/	
	data_array[0]=0x00023902;
	data_array[1]=0x00002351;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00004552;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x00006753;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00008954;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000AB55;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000156;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x00002357;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00004558;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00006759;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000895A;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000AB5B;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000CD5C;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000EF5D;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000105E;
	dsi_set_cmdq(data_array, 2, 1);	

	data_array[0]=0x00023902;
	data_array[1]=0x0000025f;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000260;
	dsi_set_cmdq(data_array, 2, 1);	
/*--------------------------------------------*/		
	data_array[0]=0x00023902;
	data_array[1]=0x00000261;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000262;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000263;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000264;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000265;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000866;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000967;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000268;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00001069;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000126a;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000116b;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000136c;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000c6d;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000e6e;
	dsi_set_cmdq(data_array, 2, 1);	

	data_array[0]=0x00023902;
	data_array[1]=0x00000d6f;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000f70;
	dsi_set_cmdq(data_array, 2, 1);	

	data_array[0]=0x00023902;
	data_array[1]=0x00000671;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000772;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000273;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000274;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000275;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000276;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000277;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000278;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000279;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000027a;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000027b;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000077c;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000067d;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000027e;
	dsi_set_cmdq(data_array, 2, 1);	

	data_array[0]=0x00023902;
	data_array[1]=0x0000117f;
	dsi_set_cmdq(data_array, 2, 1);		
/*--------------------------------------------*/		
	data_array[0]=0x00023902;
	data_array[1]=0x00001380;
	dsi_set_cmdq(data_array, 2, 1);	

	data_array[0]=0x00023902;
	data_array[1]=0x00001081;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00001282;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000f83;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000d84;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000e85;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000c86;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000987;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000888;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000289;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000028a;
	dsi_set_cmdq(data_array, 2, 1);	
/*--------------------------------------------*/				
	data_array[0]=0x00043902;
	data_array[1]=0x048198ff;
	dsi_set_cmdq(data_array, 2, 1);	

	data_array[0]=0x00023902;
	data_array[1]=0x0000156c;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00002b6e;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000356f;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000a43a;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00001f8d;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000ba87;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x00007626;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000d1b2;
	dsi_set_cmdq(data_array, 2, 1);	   	
/*--------------------------------------------*/
	data_array[0]=0x00043902;
	data_array[1]=0x018198ff;
	dsi_set_cmdq(data_array, 2, 1);	

	data_array[0]=0x00023902;
	data_array[1]=0x00000a22;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000b31;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x00000134;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00003340;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00006453;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00008f55;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000a750;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x0000a751;
	dsi_set_cmdq(data_array, 2, 1);	   		

	data_array[0]=0x00023902;
	data_array[1]=0x00001460;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x000000a0;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x000022a1;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x000037a2;
	dsi_set_cmdq(data_array, 2, 1);	   

	data_array[0]=0x00023902;
	data_array[1]=0x00000fa3;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x000019a4;
	dsi_set_cmdq(data_array, 2, 1);	   		

	data_array[0]=0x00023902;
	data_array[1]=0x000027a5;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00001ca6;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x00001ea7;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x000096a8;
	dsi_set_cmdq(data_array, 2, 1);	   
	
	data_array[0]=0x00023902;
	data_array[1]=0x000019a9;
	dsi_set_cmdq(data_array, 2, 1);	    

	data_array[0]=0x00023902;
	data_array[1]=0x000025aa;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x000083ab;
	dsi_set_cmdq(data_array, 2, 1);	   

	data_array[0]=0x00023902;
	data_array[1]=0x000019ac;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x000018ad;
	dsi_set_cmdq(data_array, 2, 1);	   		

	data_array[0]=0x00023902;
	data_array[1]=0x00004fae;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x000022af;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x00002ab0;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x000057b1;
	dsi_set_cmdq(data_array, 2, 1);	   
	
	data_array[0]=0x00023902;
	data_array[1]=0x000064b2;
	dsi_set_cmdq(data_array, 2, 1);	  
	
	data_array[0]=0x00023902;
	data_array[1]=0x000039b3;
	dsi_set_cmdq(data_array, 2, 1);	   
	
	data_array[0]=0x00023902;
	data_array[1]=0x000000c0;
	dsi_set_cmdq(data_array, 2, 1);	 	
 
	data_array[0]=0x00023902;
	data_array[1]=0x000026c1;
	dsi_set_cmdq(data_array, 2, 1);	   

	data_array[0]=0x00023902;
	data_array[1]=0x00002fc2;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x000019c3;
	dsi_set_cmdq(data_array, 2, 1);	   		

	data_array[0]=0x00023902;
	data_array[1]=0x000016c4;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00002cc5;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x00001fc6;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00001fc7;
	dsi_set_cmdq(data_array, 2, 1);	   
	
	data_array[0]=0x00023902;
	data_array[1]=0x000098c8;
	dsi_set_cmdq(data_array, 2, 1);	  
	
	data_array[0]=0x00023902;
	data_array[1]=0x00001dc9;
	dsi_set_cmdq(data_array, 2, 1);	   
	
	data_array[0]=0x00023902;
	data_array[1]=0x00002aca;
	dsi_set_cmdq(data_array, 2, 1);	 	

	data_array[0]=0x00023902;
	data_array[1]=0x00008ccB;
	dsi_set_cmdq(data_array, 2, 1);	

	data_array[0]=0x00023902;
	data_array[1]=0x00001dcc;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x00001ccd;
	dsi_set_cmdq(data_array, 2, 1);
	
	data_array[0]=0x00023902;
	data_array[1]=0x00004dce;
	dsi_set_cmdq(data_array, 2, 1);	
	
	data_array[0]=0x00023902;
	data_array[1]=0x000024cf;
	dsi_set_cmdq(data_array, 2, 1);	   
	
	data_array[0]=0x00023902;
	data_array[1]=0x000028d0;
	dsi_set_cmdq(data_array, 2, 1);	  
	
	data_array[0]=0x00023902;
	data_array[1]=0x00005fd1;
	dsi_set_cmdq(data_array, 2, 1);	   
	
	data_array[0]=0x00023902;
	data_array[1]=0x00006dd2;
	dsi_set_cmdq(data_array, 2, 1);	 	

	data_array[0]=0x00023902;
	data_array[1]=0x000039d3;
	dsi_set_cmdq(data_array, 2, 1);	

	data_array[0]=0x00043902;
	data_array[1]=0x008198ff;
	dsi_set_cmdq(data_array, 2, 1);	
	MDELAY(2); 
		
	data_array[0]= 0x00110500;
	dsi_set_cmdq(data_array, 1, 1);
	MDELAY(500);
	
	data_array[0]= 0x00290500;
	dsi_set_cmdq(data_array, 1, 1);
	MDELAY(200);  
}


static struct LCM_setting_table lcm_deep_sleep_mode_in_setting[] = {

    {0xFF, 3, {0x98,0x81,0x00}},	
    // Display off sequence
    {0x28, 1, {0x00}},
    {REGFLAG_DELAY, 20, {}},

    // Sleep Mode On
    {0x10, 1, {0x00}},
    {REGFLAG_DELAY, 120, {}},
    {REGFLAG_END_OF_TABLE, 0x00, {}}
};

static void push_table(struct LCM_setting_table *table, unsigned int count, unsigned char force_update)
{
    unsigned int i;

    for(i = 0; i < count; i++)
    {
        unsigned cmd;
        cmd = table[i].cmd;

        switch (cmd) {
		case REGFLAG_DELAY:
			MDELAY(table[i].count);
			break;

            case REGFLAG_END_OF_TABLE :
                break;

            default:
                dsi_set_cmdq_V2(cmd, table[i].count, table[i].para_list, force_update);
        }
    }
}

// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
    	memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}

static void lcm_get_params(LCM_PARAMS *params)
{
	memset(params, 0, sizeof(LCM_PARAMS));
	params->type   = LCM_TYPE_DSI;

	params->width  = FRAME_WIDTH;
	params->height = FRAME_HEIGHT;
	// enable tearing-free
	params->dbi.te_mode 				= LCM_DBI_TE_MODE_VSYNC_ONLY;
	params->dbi.te_edge_polarity		= LCM_POLARITY_RISING;

#if (LCM_DSI_CMD_MODE)
		params->dsi.mode   = CMD_MODE;
#else
		params->dsi.mode   =SYNC_PULSE_VDO_MODE; //SYNC_PULSE_VDO_MODE; //BURST_VDO_MODE;
	//params->dsi.mode   = BURST_VDO_MODE;
#endif

	// DSI
	/* Command mode setting */
	params->dsi.LANE_NUM				= LCM_FOUR_LANE;
	params->dsi.data_format.format      		= LCM_DSI_FORMAT_RGB888;

	//video mode timing
    	params->dsi.PS=LCM_PACKED_PS_24BIT_RGB888;

params->dsi.vertical_sync_active				= 10; //8;	//2;
params->dsi.vertical_backporch					= 20; //18;	//14;
params->dsi.vertical_frontporch					= 10; //20;	//16;
    params->dsi.vertical_active_line				= FRAME_HEIGHT;

params->dsi.horizontal_sync_active				= 40;	//2;
params->dsi.horizontal_backporch				= 100;//120;	//60;	//42;
params->dsi.horizontal_frontporch				= 80;//100;	//60;	//44;
params->dsi.horizontal_active_pixel				= FRAME_WIDTH;

params->dsi.PLL_CLOCK = 175;//208; 210	

}
void lcm_display_on(void)
{
	unsigned int array[16];
	
	array[0]=0x00043902;      
	array[1]=0x008198FF;          
	dsi_set_cmdq(array, 2, 1);       
	MDELAY(10); 
	  
	array[0]= 0x00110500;
	dsi_set_cmdq(array, 1, 1);
	MDELAY(200);
	
	array[0]= 0x00290500;
	dsi_set_cmdq(array, 1, 1);
	MDELAY(10);   		
}

/*to prevent electric leakage*/
static void lcm_init(void)
{
	
 
	SET_RESET_PIN(1);
	MDELAY(10);
	SET_RESET_PIN(0);
	MDELAY(10);
	SET_RESET_PIN(1);
	MDELAY(120);
    //push_table(lcm_initialization_setting, sizeof(lcm_initialization_setting) / sizeof(struct LCM_setting_table), 1);
	init_lcm_registers();
	lcm_display_on();
    LCD_DEBUG("uboot:boe_nt35521_lcm_init\n");
}


static void lcm_suspend(void)
{

    push_table(lcm_deep_sleep_mode_in_setting, sizeof(lcm_deep_sleep_mode_in_setting) / sizeof(struct LCM_setting_table), 1);

	SET_RESET_PIN(0);
	MDELAY(10);
	SET_RESET_PIN(1);
	MDELAY(10);
	SET_RESET_PIN(0);
	MDELAY(120);
    LCD_DEBUG("kernel:boe_nt35521_lcm_suspend\n");
}

static void lcm_resume(void)
{

	SET_RESET_PIN(1);
	MDELAY(10);
	SET_RESET_PIN(0);
	MDELAY(10);
	SET_RESET_PIN(1);
	MDELAY(120);
    push_table(lcm_initialization_setting, sizeof(lcm_initialization_setting) / sizeof(struct LCM_setting_table), 1);


    LCD_DEBUG("kernel:boe_nt35521_lcm_resume\n");
}



static unsigned int lcm_compare_id(void)
{
	unsigned int id1 = 0,id2 = 0,ID=0;
	unsigned char buffer[3];
	unsigned int array[16];
	
	array[0]=0x00043902;      
	array[1]=0x018198FF;          
	dsi_set_cmdq(array, 2, 1);       
	MDELAY(10);   
	
	array[0] = 0x00033700;// read id return two byte,version and id
	dsi_set_cmdq(array, 1, 1);
	read_reg_v2(0x00, buffer, 1);
	id1 = buffer[0];
	#ifndef BUILD_LK
		printk("tangh read 0x00 buffer[0]=%x \n",buffer[0]);
	#else
		printf("tangh read 0x00 buffer[0]=%x \n",buffer[0]);
	#endif 
	read_reg_v2(0x01, buffer, 1);
	id2 = buffer[0];
	#ifndef BUILD_LK
		printk("tangh read 0x01  buffer[0]=%x \n",buffer[0]);
	#else
		printf("tangh read 0x01  buffer[0]=%x \n",buffer[0]);	
	#endif 	
	ID = (id1 << 8)|id2;
	#ifndef BUILD_LK
		printk("tangh read ID=%x \n",ID);
	#else
		printf("tangh read ID=%x \n",ID);		
	#endif 
	//return 1;
	 
	return (ID == 0x9881)?1:0;
  //  return 1;
} 

LCM_DRIVER ili9881c_lcm_drv = 
{
    //.name			=" _xxxxxxxxx",
    .name			=" ili9881c_lcm_drv",
	.set_util_funcs = lcm_set_util_funcs,
	.get_params     = lcm_get_params,
	.init           = lcm_init,
	.suspend        = lcm_suspend,
	.resume         = lcm_resume,
	.compare_id    = lcm_compare_id,
};

