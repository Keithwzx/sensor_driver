#include "m_sfh5721.h"


osram_ctx_t g_osram_ctx;
bool g_single_mode_flg = false;
bool g_en_als_ch = false;
bool g_en_ir_ch = false;
bool g_en_dark_ch = false;

/**
 * @brief implement by user with the specific platform  
 * I2C master write one byte
 * 
 * @param reg_addr   address of the register
 * @param data       the data buffer to write
 * @param data_len   the length of the data buffer
 * @return uint32_t 
 */
static uint32_t I2cWrite(void *I2Cx, uint8_t reg_addr, uint8_t *data, uint16_t data_len)
{
    uint8_t data_buf[data_len + 1];
    data_buf[0] = reg_addr;
    
    APP_PRINT_INFO2("write reg_addr = 0x%02X, value = 0x%02X", reg_addr, *data);
    // init data buffer
    for(int i = 0; i < data_len; i++)
    {
        data_buf[i + 1] = data[i];
    }
    I2C_Status i2c_ret = I2C_Success;
    I2C_SetSlaveAddress(I2Cx, SFH5721_I2C_ADDR_L);
    i2c_ret = I2C_MasterWrite(I2Cx, data_buf, data_len + 1);
    if(i2c_ret != I2C_Success)
    {
        APP_PRINT_INFO1("i2c write error = %ld",i2c_ret);
    }
    
    return i2c_ret;
}

/**
 * @brief implement by user with the specific platform  
 * I2C master read one byte
 * 
 * @param reg_addr   address of the register
 * @param data       the data buffer to read
 * @param data_len   the length of the data buffer
 * @return uint32_t 
 */
static uint32_t I2cRead(void *I2Cx, uint8_t reg_addr, uint8_t *data, uint16_t data_len)
{
    I2C_Status i2c_ret = I2C_Success;

    APP_PRINT_INFO1("read reg_addr = 0x%x",reg_addr);

    I2C_SetSlaveAddress(I2Cx, SFH5721_I2C_ADDR_L);
    i2c_ret = I2C_RepeatRead(I2Cx, &reg_addr, 1 , data, data_len);
    if(i2c_ret != I2C_Success)
    {
        APP_PRINT_INFO1("i2c read error = %ld",i2c_ret);
    }
    
    return i2c_ret;
}

int32_t Sfh5721Cfg(void)
{
    int32_t ret = 0;

    #if EN_SINGLE_MODE
        ret |= Sfh5721EnSingleMode(&g_osram_ctx);
    #endif

    #if EN_SYNC_MODE
        ret |= Sfh5721EnSyncMode(&g_osram_ctx);
    #endif

    #if EN_ALS_CH
        ret |= Sfh5721EnAlsCh(&g_osram_ctx);
    #endif

    #if EN_IR_CH
        ret |= Sfh5721EnIRCh(&g_osram_ctx);
    #endif

    #if EN_DRK_CH
        ret |= Sfh5721EnDarkCh(&g_osram_ctx);
    #endif

    #if EN_ALS_INT
        ret |= Sfh5721EnIenAlsL(&g_osram_ctx);
        ret |= Sfh5721EnIenAlsH(&g_osram_ctx);
    #endif

    #if EN_IR_INT
        ret |= Sfh5721EnIenIRL(&g_osram_ctx);
        ret |= Sfh5721EnIenIRH(&g_osram_ctx);
    #endif

    #if EN_DRK_INT
        ret |= Sfh5721EnIenDarkL(&g_osram_ctx);
        ret |= Sfh5721EnIenDarkH(&g_osram_ctx);
    #endif

    #if EN_ALS_INT | EN_IR_INT | EN_DRK_INT
        ret |= Sfh5721SetIntLowThr(&g_osram_ctx, LOW_INT_THR);
        ret |= Sfh5721SetIntHighThr(&g_osram_ctx, HIGH_INT_THR);
    #endif

    #if EN_LPF_ALS
        ret |= Sfh5721EnLpfAls(&g_osram_ctx);
    #endif

    #if  EN_LPF_IR
        ret |= Sfh5721EnLpfIR(&g_osram_ctx);
    #endif

    #if  EN_LPF_DRK
        ret |= Sfh5721EnLpfDark(&g_osram_ctx);
    #endif

    #if EN_LPF_ALS | EN_LPF_IR | EN_LPF_DRK
        ret |= Sfh5721SetLpfDepth(&g_osram_ctx, LPF_DEP);
    #endif

    /**Set the Analog Gain**/ 
    ret |= Sfh5721SetA_Gain(&g_osram_ctx, ANALOG_GAIN);

    /**Set the integration Time**/
    ret |= Sfh5721SetIT(&g_osram_ctx, IT_TIME);

    /**Set the Digital Gain**/
    ret |= Sfh5721SetD_Gain(&g_osram_ctx, DIGITAL_GAIN);

    /**Set Wait Time**/
    ret |= Sfh5721SetWait(&g_osram_ctx, WAIT_TIME);

    return ret;
}


/**
 * @brief   initializes the read and write interface
 *          configures the registers
 * 
 * @return int32_t 
 */
int32_t Sfh5721SensorInit(void)
{
    int32_t ret = 0;
    APP_PRINT_INFO0("[sfh5721_initialize]: initializing als sensor\n");
    g_osram_ctx.read_reg = I2cRead;
    g_osram_ctx.write_reg = I2cWrite;
    g_osram_ctx.i2c_handle = I2C1;

    
#if RTK_ALS_SUPPORT
    Sfh5721RTKInit();
#else
    ret |= Sfh5721Cfg();
#endif

    return ret;
}

/**
 * @brief Get the raw channel data 
 * 
 * @param ctx 
 * @param value 
 * @return uint32_t 
 */
int32_t Sfh5721ReadVal(osram_ctx_t *ctx, uint16_t *value, uint8_t ch)
{
    int32_t ret = 0;
    uint8_t value_h = 0;
    uint8_t value_l = 0;
    uint8_t dry_flg  = 0;

    if(g_single_mode_flg == true)
    {
        ret |= Sfh5721EnSingleMode(ctx);
        if(g_en_ir_ch == true)
        {
            ret |= Sfh5721EnIRCh(ctx);
        }
        if(g_en_als_ch == true)
        {
            ret |= Sfh5721EnAlsCh(ctx);
        }
        if(g_en_dark_ch == true)
        {
            ret |= Sfh5721EnDarkCh(ctx);
        }
    }
    while (dry_flg != 1)
    {
        switch (ch)
        {
            case 1:
                ret |= Sfh5721GetDryDark(ctx, &dry_flg);
                if(dry_flg == 1)
                {
                    ret |= Sfh5721GetDarkValH(ctx, &value_h);
                    ret |= Sfh5721GetDarkValL(ctx, &value_l);
                }
                break;
            case 2:
                ret |= Sfh5721GetDryIR(ctx, &dry_flg);
                if(dry_flg == 1)
                {
                    ret |= Sfh5721GetIRValH(ctx, &value_h);
                    ret |= Sfh5721GetIRValL(ctx, &value_l);
                }
                break;
            case 3:
                ret |= Sfh5721GetDryAls(ctx, &dry_flg);
                if(dry_flg == 1)
                {
                    ret |= Sfh5721GetAlsValH(ctx, &value_h);
                    ret |= Sfh5721GetAlsValL(ctx, &value_l);
                }
                break;
            default:
                break;
        }
        
        if(ret != 0)
        {
            APP_PRINT_INFO0("Error Get DRY ALS\r\n");
            return ret;
        }
        os_delay(10);
    }


    *value = (value_h << 8) | value_l;

    return ret;
}

int32_t Sfh5721GetAllData(osram_ctx_t *ctx, osram_all_data_t *all_data, uint8_t *all_data_arr)
{
    uint8_t ret = 0;
    uint8_t dry_flag = 0;
    uint8_t it_time =  0;

    ret |= Sfh5721GetIT(ctx, &it_time);

    if(g_single_mode_flg == true)
    {
        uint8_t value = 0x17;
        ret |= I2cWrite(I2C1,0x00,&value, 1);
    }
    while(dry_flag != 0x07)
    {
        ret |= Sfh5721I2cRead(ctx, 0x01, &dry_flag, 1);
        dry_flag = dry_flag & 0x07;
        if(ret != 0)
        {
            APP_PRINT_INFO0("Error Get DRY ALS\r\n");
            return ret;
        }
        os_delay(it_time);
    }
    
    ret |= Sfh5721I2cRead(ctx, 0x0C, all_data_arr, 6);

    all_data->dark_data = all_data_arr[1] << 8 | all_data_arr[0];
    
    all_data->ir_data   = all_data_arr[3] << 8 | all_data_arr[2];

    all_data->als_data  = all_data_arr[5] << 8 | all_data_arr[4];
    
    return ret;
    
}