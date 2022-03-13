
#include "m_stk2236.h"
#include "m_cli.h"
bool g_stk2236_init_flg = false;

typedef struct stk3x3x_register_table
{
	uint8_t address;
	uint8_t value;
} stk3x3x_register_table_t;

stk3x3x_register_table_t stk3x3x_default_register_table[] =
{
	{0x02,          (0x31)},//(0x21)},
	{0x05,          (0x20)},
	{0x4E,          (0x20)},
	{0xDB,          (0x15)},
	{0x4D,          (0x00)},
};
static void Stk2236Cfg();

uint8_t Stk2236SensorInit()
{
    STK2236_ERR_CODE_E ret = STK2236_OK;
    uint8_t dev_id = 0;

    ret = Stk2236GetDevID(&dev_id);
    if(ret != STK2236_OK)
    {
        APP_PRINT_INFO1("Get stk2236 device ID failed: %d", ret);
        return ret;
    }

    if(dev_id == STK2236_DEV_ID)
    {
        g_stk2236_init_flg = true;
        APP_PRINT_INFO1("Get Stk2236 device id: 0x%2x\r\n", dev_id);
    }
    os_delay(30);
    Stk2236Cfg();
    return ret;
}

/**
 * the gain control bit GAIN_ALS[1:0] and IT period IT_ALS[3:0] shall be set
 * before the the EN_ALS
*/
void Stk2236Cfg()
{
    uint8_t reg_addr = 0;
    uint8_t value  = 0;

    for(int i = 0; i < sizeof(stk3x3x_default_register_table)/sizeof(stk3x3x_register_table_t); i++)
    {
        reg_addr = stk3x3x_default_register_table[i].address;
        value = stk3x3x_default_register_table[i].value;
        Stk2236WriteReg(reg_addr, &value, 1);
    }

}

void Stk2236GetDataT(uint16_t *als_value, uint16_t *ir_value)
{ 
    uint8_t data_buffer[10] = {0,};

    if (Stk2236ReadReg(STK2236_DATA1_ALS_REG, data_buffer, 10) != 0)
    {
        cli_printf("read_error\r\n");
    }
    else
    {
        *als_value = (data_buffer[0]<<8) | data_buffer[1];
        *ir_value = (data_buffer[8]<<8) | data_buffer[9];
    }
    
}

uint8_t Stk2236ReadData(uint16_t *als_value, uint16_t *ir_value)
{
    
    STK2236_ERR_CODE_E ret = STK2236_OK;
    uint8_t flg_als_dr = 0;

    if(g_stk2236_init_flg == true)
    {   
        
        if (Stk2236EnableAls(1) == 0 && Stk2236EnableWait(1) == 0)
        {
            
            while(flg_als_dr != 1)
            {
                ret = Stk2236GetFlgAlsDr(&flg_als_dr);
                if(ret != STK2236_OK)
                {
                    cli_printf("Get ALS Dr Flag Err: %d", ret);
                }
            }

            Stk2236GetDataT(als_value, ir_value);
            if(ret != STK2236_OK)
            {
                Log_info1("Get ALS Data Err: %d", ret);
            }
            
        }
        else
        {
            Log_info1("Enable ALS Failed: %d", ret);
        }
        return ret;
    }
    return STK2236_INIT_FAIL;
}

