#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>  
#include <linux/sched.h>  //struct task_struct *current  
#include <linux/fs.h>     //file_operation, file, inode  
#include <linux/types.h>  //设备号相关,eg MAJOR, MINOR, MKDEV  
#include <linux/cdev.h>       //字符设备相关操作，init，add，del  
#include <linux/slab.h>       //kmalloc, kfree  
#include <asm/uaccess.h>  //copy_to_user, copy_from_user 
#include <linux/device.h>     //class_create  
//#include <mt_auxadc_sw.h>
//#include <mt_auxadc_hw.h>
//#include <cust_eint.h>
#include <linux/interrupt.h>
#include <linux/sched.h>
#include <linux/kthread.h>
//#include <mach/eint.h>

//#include <mach/upmu_common.h>
//#include <mach/upmu_hw.h>
//#include <mach/mt_gpio.h>
#include <linux/proc_fs.h> 
//#include <mach/mt_pwm.h>
#include <linux/workqueue.h>   
#include <linux/sched.h>   
#include <linux/delay.h> 
#include<linux/timer.h>
#include <linux/spi/spi.h>
//#include <mach/mt_spi.h>
//#include <mach/mt_pm_ldo.h>
#include <linux/ethtool.h>

#include "../../../spi/mediatek/mt6735/mt_spi.h"
#include <mt-plat/mt_gpio.h>
#include <mach/gpio_const.h>



//#include "cust_gpio_usage.h"

//#include "mt_auxadc_sw.h"
//#include "mt_auxadc_hw.h"
//#define GPIO_SPI_CS_PIN (GPIO80 | 0x80000000)
//#define GPIO_SPI_SCK_PIN (GPIO81 | 0x80000000)
//#define GPIO_SPI_MISO_PIN (GPIO82 | 0x80000000)
//#define GPIO_SPI_MOSI_PIN (GPIO83 | 0x80000000)
#define BUFFER_SIZE 4<<10  
#define DRVNAME_PG6137 "pg6317_spi"

/****************************************************
**Setup SPI speed and transfer mode
**SPEEND = SPI_MODULE_CLOCK/(high_time+low_time)  KHZ
**eg:SPI_MODULE_CLOCK = 104000khz
**   high_time = 10   low_time = 10
**SPEEND=104000/(10+10)=5200KHZ=5.2M
*****************************************************/


/**********************************************************
 *Message format:
 *	write cmd   |  ADDR_H |ADDR_L  |  data stream  |
 *    1B         |   1B    |  1B    |  length       |
 *
 * read buffer length should be 1 + 1 + 1 + data_length
 ***********************************************************/

#define Gen_Ko 0     //Build to Ko
#ifndef Gen_Ko
#error "please change the gen_ko 0 or 1"
#endif

static struct mt_chip_conf spi_conf_mt65xx = {

	.setuptime = 15,
	.holdtime = 15,
	.high_time = 500, 
	.low_time = 500,	
	.cs_idletime = 19,
	.ulthgh_thrsh = 0,
	.cpol = 0,
	.cpha = 0,
	.rx_mlsb = 1,
	.tx_mlsb = 1,
	.tx_endian = 0,
	.rx_endian = 0,
	.com_mod = DMA_TRANSFER,
//	.com_mod = FIFO_TRANSFER,
	.pause = 0,
	.finish_intr = 1,
	.deassert = 0,
	.ulthigh = 0,
	.tckdly = 0,
};

int major;
const u8 blox_data[] = {0x81,0x00,0x00,0x13,0xd2,0xe5,0x3b,0x7e,0x11,0x00,0x00,0x33,0x4d,0x56,0x30,0x34,0x0c,0x31,0x75,0x43,0x4f};
const u32 blox_send_data[]={0xffffffff,0xFFFF6200,0x0005F331,0x00840000,0x100000ff};

 struct class *pg6317_drv_class;  
struct device *pg6317_drv_device;  
//struct spi_message pg6317_spi_msg;  
//struct spi_transfer pg6317_spi_xfer;  
//static u8 *tx_buf;
static int pg6317_probe(struct spi_device *spi);
extern int spi_register_board_info(struct spi_board_info const *info, unsigned n);
struct spi_device_id pg6317_spi_id_table = {DRVNAME_PG6137, 0}; //DRVNAME_9051

static struct spi_driver pg6317_spi_driver = {
	.driver	= 
	{
		.name  = DRVNAME_PG6137, 
		.owner = THIS_MODULE,
	},
	.probe   = pg6317_probe,
	.id_table = &pg6317_spi_id_table,
};
static struct spi_device *spi_device;
#if Gen_Ko
static unsigned verbose = 3;
module_param(verbose, uint, 0);
MODULE_PARM_DESC(verbose,"0 silent, >0 show gpios, >1 show devices, >2 show devices before (default=3)");
static void pg6317_device_spi_delete(struct spi_master *master, unsigned cs)
{
	struct device *dev;
	char str[32];

	snprintf(str, sizeof(str), "%s.%u", dev_name(&master->dev), cs);

	dev = bus_find_device_by_name(&spi_bus_type, NULL, str);
	if (dev) {
		if (verbose)
			printk("mayue Spi del\n");
		device_del(dev);
	}
}
static int pg6317_spi_register_board_info(struct spi_board_info *spi, unsigned n)
{
	struct spi_master *master;
	master = spi_busnum_to_master(spi->bus_num);
	if (!master) {
	printk("mayue Spi bus error\n");
		return -EINVAL;
	}
	/* make sure it's available */
	pg6317_device_spi_delete(master, spi->chip_select);
	spi_device = spi_new_device(master, spi);
	put_device(&master->dev);
	if (!spi_device) {
		printk("mayue Spi spi_new_device() error\n");
		return -EPERM;
	}
	return 0;
}
#endif
static int SPI_Init(struct spi_device *db)
{
	struct mt_chip_conf* spi_par; // added 2015-12-3
    spi_par = (struct mt_chip_conf *) db->controller_data;
	spi_par->setuptime = 20;//15; 
	spi_par->holdtime = 20;//15; 
	spi_par->high_time = 500; // 2      //10--6m   15--4m   20--3m  30--2m  [ 60--1m 120--0.5m  300--0.2m]
	spi_par->low_time = 500;  //2
	spi_par->cs_idletime = 25; //20
	spi_par->rx_mlsb = 1; 
	spi_par->tx_mlsb = 1;		 
	spi_par->tx_endian = 0;
	spi_par->rx_endian = 0;
	spi_par->cpol = 0;
	spi_par->cpha = 0;
	spi_par->com_mod = DMA_TRANSFER;
	spi_par->pause = 0;
	spi_par->finish_intr = 1;
	spi_par->deassert = 0;
	spi_setup(db);
	return 0;
}
int spi_readbuf(struct spi_device *spi , u8 *tarnsfer_data , u8 receive_len)
{
	int read_state = 0;
	
	struct spi_transfer pg6317_spi_xfer;  
	struct spi_message pg6317_spi_msg;	

	spi_message_init(&pg6317_spi_msg);  
	
	pg6317_spi_xfer.tx_buf = tarnsfer_data;  
	pg6317_spi_xfer.rx_buf = tarnsfer_data; 
	pg6317_spi_xfer.len = receive_len;
	pg6317_spi_xfer.bits_per_word = 8;  
	
	spi_message_add_tail(&pg6317_spi_xfer, &pg6317_spi_msg);  
	
	read_state = spi_sync(spi, &pg6317_spi_msg);
	
	return read_state;
}
int spi_writebuf(struct spi_device *spi , u8 *tarnsfer_data , u8 len)
{
	struct spi_transfer pg6317_spi_xfer;  
	struct spi_message pg6317_spi_msg;	

	spi_message_init(&pg6317_spi_msg);  
	pg6317_spi_xfer.tx_buf = tarnsfer_data;  
	pg6317_spi_xfer.rx_buf = tarnsfer_data;
	pg6317_spi_xfer.len = len;  
	pg6317_spi_xfer.bits_per_word = 8;  
	spi_message_add_tail(&pg6317_spi_xfer, &pg6317_spi_msg);  
	
	return spi_sync(spi, &pg6317_spi_msg); 
}
static struct spi_board_info pg6317_spi_board_devs[] __initdata = 
{
	[0] = 
	{
	.modalias = DRVNAME_PG6137,
	.max_speed_hz = 8* 1000*1000,  // 25MHz
	.bus_num = 0,
	.chip_select = 0,
	.mode = SPI_MODE_0,
	.controller_data = &spi_conf_mt65xx,
	},
};

#define GPIO_SPI_CS_PIN (GPIO65 | 0x80000000)
#define GPIO_SPI_SCK_PIN (GPIO66 | 0x80000000)
#define GPIO_SPI_MISO_PIN (GPIO67 | 0x80000000)
#define GPIO_SPI_MOSI_PIN (GPIO68 | 0x80000000)

void pg6137_hw_init(void)
{
	mt_set_gpio_mode(GPIO_SPI_CS_PIN, 1);
	mt_set_gpio_dir(GPIO_SPI_CS_PIN,GPIO_DIR_OUT);
	mt_set_gpio_pull_enable(GPIO_SPI_CS_PIN, GPIO_PULL_ENABLE);
	mt_set_gpio_pull_select(GPIO_SPI_CS_PIN, GPIO_PULL_UP);

	mt_set_gpio_mode(GPIO_SPI_SCK_PIN, 1);
	mt_set_gpio_dir(GPIO_SPI_SCK_PIN,GPIO_DIR_OUT);
	mt_set_gpio_pull_enable(GPIO_SPI_SCK_PIN, GPIO_PULL_ENABLE);
	mt_set_gpio_pull_select(GPIO_SPI_SCK_PIN, GPIO_PULL_DOWN);

	mt_set_gpio_mode(GPIO_SPI_MISO_PIN, 1);
	mt_set_gpio_dir(GPIO_SPI_MISO_PIN,GPIO_DIR_IN);
	mt_set_gpio_pull_enable(GPIO_SPI_MISO_PIN, GPIO_PULL_ENABLE);
	mt_set_gpio_pull_select(GPIO_SPI_MISO_PIN, GPIO_PULL_DOWN);

	mt_set_gpio_mode(GPIO_SPI_MOSI_PIN, 1);
	mt_set_gpio_dir(GPIO_SPI_MOSI_PIN,GPIO_DIR_OUT);
	mt_set_gpio_pull_enable(GPIO_SPI_MOSI_PIN, GPIO_PULL_ENABLE);
	mt_set_gpio_pull_select(GPIO_SPI_MOSI_PIN, GPIO_PULL_DOWN);

#if 0	
	mt_set_gpio_mode(GPIO_BEIDOU_POWERON_PIN, GPIO_MODE_00);
	mt_set_gpio_dir(GPIO_BEIDOU_POWERON_PIN,GPIO_DIR_OUT);
	mt_set_gpio_out(GPIO_BEIDOU_POWERON_PIN, GPIO_OUT_ONE);

	mt_set_gpio_mode(GPIO_LEVEL_POWERON_PIN, GPIO_MODE_00);
	mt_set_gpio_dir(GPIO_LEVEL_POWERON_PIN,GPIO_DIR_OUT);	
	mt_set_gpio_out(GPIO_LEVEL_POWERON_PIN, GPIO_OUT_ONE);

	mt_set_gpio_mode(GPIO_PSAM_POWERON_PIN, GPIO_MODE_00);
	mt_set_gpio_dir(GPIO_PSAM_POWERON_PIN,GPIO_DIR_OUT);	
	mt_set_gpio_out(GPIO_PSAM_POWERON_PIN, GPIO_OUT_ONE);
#endif	
	printk("pg6137_hw_init  Set Gpio Ok\n");
}

static int pg6317_probe(struct spi_device *spi)
{
	
	printk("pg6317_probe  \n");
	
	spi_device = spi ;
	pg6137_hw_init();
	SPI_Init(spi_device);
	
	return 0;
}
void pg6317_hw_power(bool on)
{
	static bool state = 0;

	printk("pg6317_hw_power on=%d state=%d\n",on,state);
	if(state == on)
		return;

	state = on;

#if 0	
	mt_set_gpio_mode(GPIO_BEIDOU_POWERON_PIN, GPIO_MODE_00);
	mt_set_gpio_dir(GPIO_BEIDOU_POWERON_PIN,GPIO_DIR_OUT);

	mt_set_gpio_mode(GPIO_LEVEL_POWERON_PIN, GPIO_MODE_00);
	mt_set_gpio_dir(GPIO_LEVEL_POWERON_PIN,GPIO_DIR_OUT);	

	
	mt_set_gpio_mode(GPIO_PSAM_POWERON_PIN, GPIO_MODE_00);
	mt_set_gpio_dir(GPIO_PSAM_POWERON_PIN,GPIO_DIR_OUT);
	if(on)
	{
		mt_set_gpio_out(GPIO_BEIDOU_POWERON_PIN, GPIO_OUT_ONE);
		mt_set_gpio_out(GPIO_LEVEL_POWERON_PIN, GPIO_OUT_ONE);
		mt_set_gpio_out(GPIO_PSAM_POWERON_PIN, GPIO_OUT_ONE);
	}
	else
	{
		mt_set_gpio_out(GPIO_BEIDOU_POWERON_PIN, GPIO_OUT_ZERO);
		mt_set_gpio_out(GPIO_LEVEL_POWERON_PIN, GPIO_OUT_ZERO);
		mt_set_gpio_out(GPIO_PSAM_POWERON_PIN, GPIO_OUT_ZERO);
	}
#endif
}

#if 0
static void big_to_small(u32 udata , u8 *data)
{
	//u32 mm;
	*data = *(data+1) = *(data+2) = *(data+3) = 0xff;
	*(data+0) &= udata>>0;
	*(data+1) &= udata>>8;
	*(data+2) &= udata>>16;
	*(data+3) &= udata>>24;
}
#endif
#define PG6317_POWER 0X01

#define PG6317_RESET 0X20

static ssize_t beidou_pg6317_ioctl(struct file *filp,unsigned int cmd, unsigned long arg)
{
	u8 spi_dat[50],m;
	u32 state = 0;
	switch(cmd)
	{
		case PG6317_POWER:
			printk("beidou_pg6317_ioctl PG6317_POWER arg = %lu\n",arg);
			if(arg == 1)
				pg6317_hw_power(1);		
			else
				pg6317_hw_power(0); 	
			break;

		case PG6317_RESET:		
			printk("beidou_pg6317_ioctl PG6317_RESET\n");
			#if 1
			for (m=0 ; m<50 ; m++)
			{
				memset(spi_dat,0,sizeof(spi_dat));
				state = spi_readbuf(spi_device , spi_dat , 28);	
				printk("pg6317 state = %d \n",state);
			}

			for(m = 0 ;m < 28; m++)
				printk("spi_dat[%d]=%d \n",spi_dat[m],m);
			#endif
			break;

		default:
			break;
	}

	return 1;
}
#if 0
int beidou_pg6317_ioctl(struct file *filp,unsigned int cmd, unsigned long arg)
{
	u32 spi_dat[50];
	u32 const spi_resonse_data = 0xaaaaaaaa;
	u8 i,m,l=0,spi_change_dat[100],p,flag=0;
	if (cmd==1)
	{
		//mt_set_gpio_out(GPIO1, 0);
		pg6317_hw_power(0);
		mdelay(100); 
		//mt_set_gpio_out(GPIO1, 1);
		pg6317_hw_power(1);
		mdelay(1); 
		for (m=0 ; m<50 ; m++)
		{
			l=0;
			memset(spi_dat,0x00,sizeof(spi_dat));
			printk("SPI_DATA start\n");
			spi_readbuf(spi_device , &spi_dat , 28);
			for(i=0;i<25;i++)
			{
				p=i*4;
				big_to_small(spi_dat[i] , &spi_change_dat[p]);
			}
			for(i=0;i<100;i++)
			{
				printk("0x%x\n",spi_change_dat[i]);
				if(spi_change_dat[i]==blox_data[l])
				l++;
				if(l==18)
				{
					flag=1;
					break;
				}
			}
			if(flag==1)
			{
				break;
			}
			mdelay(10); 
		}
		if(flag==1)
		{
			spi_writebuf(spi_device , &spi_resonse_data ,4);
			//mt_set_gpio_out(GPIO1, 1);
			pg6317_hw_power(1);
			printk("compare blox ok\n");
			printk("power up\n");
			return 1;
		}
		else 
		{
			//mt_set_gpio_out(GPIO1, 0);
			pg6317_hw_power(0);
			printk("compare blox error\n");
			printk("power down\n");
			return 0;
		}
	}
}
#endif 

static ssize_t beidou_pg6317_read(struct file *filp, char *buffer, size_t length,loff_t * offset)  
{
	u8 spi_dat[10];
	u8 i;
	int state = -1;	
	memset(spi_dat,0,10);
	state = spi_readbuf(spi_device , spi_dat , 2);
	printk("beidou_pg6317_read state=%d\n",state);

	for(i=0;i<2;i++)
	{
		printk("LRZ read spi spi_dat[%d]=%d\n",i,spi_dat[i]);
	}
	#if 0
	printk("********************* \n");
	for(i=0;i<50;i++)
	{
		spi_dat[i]=cpu_to_be32(spi_dat[i]);
	}
	printk("********************* \n");
	#endif 
	i=copy_to_user(buffer , (char *)spi_dat , length);
	if(state >= 0)
		return length;
	
	return -1;
}


u32 spi_resonse_data = 0xaaaaaaaa;
char send_data[] = {0xaa , 0xaa};
static ssize_t beidou_pg6317_write(struct file *filp, const char *buff, size_t len, loff_t * off)
{
	char spi_dat[50];
	int i;
	int state = -1;
	
	i=copy_from_user(spi_dat , buff , len);
	#if 0
	printk("********************* \n");
	for(i=0;i<50;i++)
	{
		spi_dat[i]=cpu_to_be32(spi_dat[i]);
		printk("0x%x",spi_dat[i]);
	}
	#endif
	for(i = 0; i < len ; i++)
		printk("spi_dat[%d]=%x---",i,spi_dat[i]);
	printk(" \n");

    state = spi_writebuf(spi_device , spi_dat , sizeof(send_data));
	printk("beidou_pg6317_write state=%d\n",state);
	
	if(state >= 0)
		return len;

	return -1;
   
}


static const struct file_operations char_mem_ops = {  
    .owner = THIS_MODULE,  
	.read =	beidou_pg6317_read,
	.write = beidou_pg6317_write,
	.unlocked_ioctl = beidou_pg6317_ioctl,
};  
static int pg6317_init(void)
{
	//int ret;
	printk( "pg6317-spi init.\n" );
	pg6317_hw_power(1);
	major = register_chrdev(0, "pg6317_drv", &char_mem_ops); 
	pg6317_drv_class = class_create(THIS_MODULE, "pg6317_drv");  
	pg6317_drv_device = device_create(pg6317_drv_class, NULL, MKDEV(major, 0), NULL, "pg6317_spi"); 

	#if Gen_Ko
		pg6317_spi_register_board_info(pg6317_spi_board_devs, ARRAY_SIZE(pg6317_spi_board_devs));
	#else
		spi_register_board_info(pg6317_spi_board_devs, ARRAY_SIZE(pg6317_spi_board_devs));
	#endif

	return spi_register_driver(&pg6317_spi_driver);
}

static void pg6317_exit(void)
{	
	printk( KERN_ALERT "pg6317 spi exit.\n" );
	
	unregister_chrdev(major, "pg6317_drv");  
	device_unregister(pg6317_drv_device); 
	class_destroy(pg6317_drv_class);       
	#if Gen_Ko
		if (spi_device)
		{
		device_del(&spi_device->dev);
		kfree(spi_device);
		}
	#endif
	
	spi_unregister_driver(&pg6317_spi_driver);
}


MODULE_LICENSE("Dual BSD/GPL");
module_init( pg6317_init );
module_exit( pg6317_exit );
