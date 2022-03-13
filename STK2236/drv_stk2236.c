
#include "drv_stk2236.h"


/*************************************************************************************
* enable i2c W and write register, implemented by user
* @param    reg_addr -> register address
* @param    data[]   -> data_buffer
* @param    data_len -> the length of the data buffer
* @return   ->  error code 
* ***********************************************************************************/
uint8_t Stk2236WriteReg(uint8_t reg_addr, uint8_t *data, uint16_t data_len)
{
    
    uint8_t data_buf[data_len + 1];
    data_buf[0] = reg_addr;
    
    // init data buffer
    for(int i = 0; i < data_len; i++)
    {
        data_buf[i + 1] = data[i];
    }
    I2C_Status i2c_ret = I2C_Success;
    I2C_SetSlaveAddress(I2C1, STK2236_I2C_ADDR);
    i2c_ret = I2C_MasterWrite(I2C1, data_buf, data_len + 1);
    if(i2c_ret != I2C_Success)
    {
        Log_info1("i2c write error = %ld",i2c_ret);
    }
    
    return i2c_ret;
}


/*************************************************************************************
* enable i2c R and read register, implemented by user
* @param    reg_addr -> register address
* @param    data[]   -> data_buffer
* @param    data_len -> the length of the data buffer
* @return            ->  error code 
* ***********************************************************************************/
uint8_t Stk2236ReadReg(uint8_t reg_addr, uint8_t *data, uint16_t data_len)
{
    I2C_Status i2c_ret = I2C_Success;

    Log_info1("read reg_addr = 0x%x",reg_addr);

    I2C_SetSlaveAddress(I2C1, STK2236_I2C_ADDR);
    i2c_ret = I2C_RepeatRead(I2C1, &reg_addr, 1 , data, data_len);
    if(i2c_ret != I2C_Success)
    {
        Log_info1("i2c read error = %ld",i2c_ret);
    }
    
    return i2c_ret;
}

/**
 * enable the als/c function
 * @param option_val
 * 0 disable
 * 1 enbale
*/
STK2236_ERR_CODE_E Stk2236EnableAls(uint8_t option_val)
{
    STK2236_ERR_CODE_E ret = STK2236_OK;
    uint8_t state_value = 0;
    
    ret = Stk2236ReadReg(STK2236_EN_ALS_REG, &state_value, 1);
    if(ret != 0)
    {
        return STK2236_EN_ALS_FAIL;
    }
    state_value = STK2236_SET_BITSLICE(state_value, STK2236_EN_ALS, option_val);
    ret = Stk2236WriteReg(STK2236_EN_ALS_REG, &state_value, 1);
    if(ret != 0)
    {
        return STK2236_EN_ALS_FAIL;
    }
    return ret;
}

/**
 * enable tha wait state
 * @param option_val
 * 0 disable
 * 1 enbale
*/
STK2236_ERR_CODE_E Stk2236EnableWait(uint8_t option_val)
{
    STK2236_ERR_CODE_E ret = STK2236_OK;
    uint8_t state_value = 0;

    Log_info0("Set WAIT Register");
    ret = Stk2236ReadReg(STK2236_EN_WAIT_REG, &state_value, 1);
    if(ret != 0)
    {
        Log_info1("Read WAIT Register Failed: %d", ret);
        return STK2236_I2C_R_FAIL;
    }
    state_value = STK2236_SET_BITSLICE(state_value, STK2236_EN_WAIT, option_val);
    ret = Stk2236WriteReg(STK2236_EN_WAIT_REG, &state_value, 1);
    if(ret != 0)
    {
        Log_info1("Set Wait Register Failed %d", ret);
        return STK2236_EN_WAIT_FAIL;
    }
    return ret;
}

/**
 * Set Als integration time
 * @param option_val: 
 * 0 -> 25ms,
 * 1 -> 50ms,
 * 2 -> 100ms,
 * 3 -> 200ms,
 * 4 -> 400ms,
 * 5 -> 800ms,
 * 6 -> 1600ms,
*/
STK2236_ERR_CODE_E Stk2236SetIntegrationTime(uint8_t option_val)
{
    STK2236_ERR_CODE_E ret = STK2236_OK;
    uint8_t reg_val = 0;
    
    Log_info0("Set integration time");
    if(Stk2236ReadReg(STK2236_IT_ALS_REG, &reg_val, 1) != 0)
    {
        Log_info0("Get IT regiser data error!");
        return STK2236_I2C_R_FAIL;
    }
    reg_val = STK2236_SET_BITSLICE(reg_val , STK2236_IT_ALS, option_val);
    ret = Stk2236WriteReg(STK2236_IT_ALS_REG, &reg_val, 1);
    if (ret != 0)
    {
        Log_info0("Set IT regiser data error!");
        return STK2236_SET_IT_FAIL;
    }
    return ret;

}

/**
 * Als gain setting. GAIN_ALS is used to conrol of the ALS channel signal gain
 * @param option_val
 * 0b00(0) -> x1 times,
 * 0b01(1) -> x4 times,
 * 0b10(2) -> x16 times,
 * 0b11(3) -> x64 times,
*/
STK2236_ERR_CODE_E Stk2236SetGainAls(uint8_t option_val)
{
    STK2236_ERR_CODE_E ret = STK2236_OK;
    uint8_t reg_val = 0;

    Log_info0("Set Gain ALS");
    if(Stk2236ReadReg(STK2236_GAIN_ALS_REG, &reg_val, 1) != 0)
    {
        Log_info0("Get GAIN_ALS register Error!");
        return STK2236_I2C_R_FAIL;
    }

    reg_val = STK2236_SET_BITSLICE(reg_val, STK2236_GAIN_ALS, option_val);
    Log_info1("reg_val = 0x%02x", reg_val);
    ret = Stk2236WriteReg(STK2236_GAIN_ALS_REG, &reg_val, 1);
    if(ret != 0)
    {
        Log_info0("Set GAIN_ALS register Error!");
        return STK2236_SET_GAIN_ALS_FAIL;
    }
    return ret;
}

/**
 * Als persistence setting. The ALS has an interrupt persistence filter.
 * The persistence filter allows user to specific the number of consecutive
 * out-of-windows ALS occurrences before an interrupt is triggered.
 * @param option_val
 * 0b00(0) -> x1 times,
 * 0b01(1) -> x2 times,
 * 0b10(2) -> x4 times,
 * 0b11(3) -> x8 times,
*/
STK2236_ERR_CODE_E Stk2236SetPRSTAls(uint8_t option_val)
{
    STK2236_ERR_CODE_E ret = STK2236_OK;
    uint8_t reg_val = 0;

    Log_info0("Set Persistence time");
    if(Stk2236ReadReg(STK2236_PRST_ALS_REG, &reg_val, 1) != 0)
    {
        Log_info0("Get PRST_ALS Register Error!");
        return STK2236_SET_PRST_ALS_FAIL;
    }
    reg_val = STK2236_SET_BITSLICE(reg_val, STK2236_PRST_ALS, option_val);
    ret = Stk2236WriteReg(STK2236_PRST_ALS_REG, &reg_val, 1);
    if(ret != 0)
    {
        Log_info0("Set PRST_ALS Register Error!");
        return STK2236_SET_PRST_ALS_FAIL;
    }
    return ret;
}

/**
 * Enable the ALS out-of-window intterupt
 * @param option_val
 * 0 -> disable,
 * 1 -> enable,
*/
STK2236_ERR_CODE_E Stk2236EnableAlsInt(uint8_t option_val)
{
    STK2236_ERR_CODE_E ret = STK2236_OK;
    uint8_t reg_val = 0;

    Log_info0("Enable ALS Interrupt");
    if(Stk2236ReadReg(STK2236_EN_ALS_INT_REG, &reg_val, 1) != 0)
    {
        Log_info0("Get EN_ALS_INT Register Error!");
        return STK2236_I2C_R_FAIL;
    }
    reg_val = STK2236_SET_BITSLICE(reg_val, STK2236_EN_ALS_INT, option_val);
    ret = Stk2236WriteReg(STK2236_EN_ALS_INT_REG, &reg_val, 1);
    if(ret != 0)
    {
        Log_info0("Set EN_ALS_INT Register Error!");
        return STK2236_EN_ALS_INT_FAIL;
    }
    return ret;
}

/**
 * Set INT_CRTL
*/
STK2236_ERR_CODE_E Stk2236SetIntCtrl(uint8_t option_val)
{
    return 0;
}

/**
 * Set WAIT[7:0] Register
 * wait period = (WAIT[7:0] + 1) *1.54
 * 
*/
STK2236_ERR_CODE_E Stk2236SetWait(uint8_t value)
{
    STK2236_ERR_CODE_E ret = STK2236_OK;
    uint8_t reg_val = 0;

    Log_info0("Set Waite Register");
    if(Stk2236ReadReg(STK2236_WAIT_REG, &reg_val, 1) != 0)
    {
        Log_info0("Get WAIT Register Error!");
        return STK2236_I2C_R_FAIL;
    }
    reg_val = STK2236_SET_BITSLICE(reg_val, STK2236_WAIT, value);
    ret = Stk2236WriteReg(STK2236_WAIT_REG, &reg_val, 1);
    if(ret != 0)
    {
        Log_info0("Set WAIT Register Error!");
        return STK2236_SET_WAIT_FAIL;
    }
    return ret;
}


/**
 * Indicate the ALS channel circuit saturation
 * @param flg_als_sat
 * 0 -> no als channel circuit saturation, the data is valid;
 * 1 -> als channel circuit saturation, the data is not valid;
*/
STK2236_ERR_CODE_E Stk2236GetFlgAlsSat(uint8_t *flg_als_sat)
{
    STK2236_ERR_CODE_E ret = STK2236_OK;
    uint8_t reg_val = 0;

    Log_info0("Get FLG_ALS_SAT");
    ret = Stk2236ReadReg(STK2236_FLG_ALS_SAT_REG, &reg_val, 1);
    if(ret != 0)
    {
        Log_info0("Get the FLG_ALS_SAT Register Error!");
        return STK2236_GET_FLG_ALS_SAT_FAIL;
    }
    *flg_als_sat = STK2236_GET_BITSLICE(reg_val, STK2236_FLG_ALS_SAT);
    return ret;
}

/**
 * indicate if interrupt event is related to als_int, write bit 0 to clear
 * @param flg_als_int:
 * 0 -> no ALS_INT event,
 * 1 -> ALS_INT event,
*/
STK2236_ERR_CODE_E Stk2236GetFlgAlsInt(uint8_t *flg_als_int)
{
    STK2236_ERR_CODE_E ret = STK2236_OK;
    uint8_t reg_val = 0;

    Log_info0("Get FLG_ALS_INT");
    ret = Stk2236ReadReg(STK2236_FLG_ALS_INT_REG, &reg_val, 1);
    if(ret != 0)
    {
        Log_info0("Get the FLG_ALS_INT Register Error!");
        return STK2236_GET_FLG_ALS_INT_FAIL;
    }
    *flg_als_int = STK2236_GET_BITSLICE(reg_val, STK2236_FLG_ALS_INT);
    return ret;
}
/**
 * indicate als data conversion complete. automatically cleared after DATA_ALS[15:0] is read
 * @param flg_als_dr
 * 0 -> als data is not ready
 * 1 -> als data is ready
 * while(flg_als_dr != 1)
 * { get the flag status}
*/
STK2236_ERR_CODE_E Stk2236GetFlgAlsDr(uint8_t *flg_als_dr)
{
    STK2236_ERR_CODE_E ret = STK2236_OK;
    uint8_t reg_val = 0;

    Log_info0("Get FLG_ALS_DR");
    ret = Stk2236ReadReg(STK2236_FLG_ALS_DR_REG, &reg_val, 1);
    if(ret != 0)
    {
        Log_info1("Get the FLG_ALS_DR Register Error: %d", ret);
        return STK2236_GET_FLG_ALS_DR_FAIL;
    }
    *flg_als_dr = STK2236_GET_BITSLICE(reg_val, STK2236_FLG_ALS_DR);
    return ret;
}



STK2236_ERR_CODE_E Stk2236GetAlsDataH(uint8_t *als_data_h)
{
    STK2236_ERR_CODE_E ret = STK2236_OK;

    Log_info0("Get als data high byte");
    ret = Stk2236ReadReg(STK2236_DATA1_ALS_REG, als_data_h, 1);
    if(ret != 0)
    {
        Log_info1("als high byte error: %d", ret);
        return STK2236_GET_ALS_H_FAIL;
    }
    
    return ret;
}

STK2236_ERR_CODE_E Stk2236GetAlsDataL(uint8_t *als_data_l)
{
    STK2236_ERR_CODE_E ret = STK2236_OK;

    Log_info0("Get als data low byte");
    ret = Stk2236ReadReg(STK2236_DATA2_ALS_REG, als_data_l, 1);
    if(ret != 0)
    {
        Log_info1("als low byte error: %d", ret);
        return STK2236_GET_ALS_L_FAIL;
    }
    
    return ret;
}
/**
 * The als data are 16-bit output and are stored in two bytes registers
 * higher byte register must be read first than lower byte register
*/
STK2236_ERR_CODE_E Stk2236GetAlsData(uint16_t *als_data)
{
    uint8_t als_data_h = 0;
    uint8_t als_data_l = 0;

    Log_info0("Get ALS Data");
    if( Stk2236GetAlsDataH(&als_data_h) == 0 && 
        Stk2236GetAlsDataL(&als_data_l) == 0)
    {
        Log_info1("als high byte is: %d", als_data_h);
        Log_info1("als low byte is: %d", als_data_l);
        *als_data = (als_data_h << 8) | als_data_l;
        Log_info1("ALS Data is: %d",*als_data);
        return STK2236_OK;
    }
    return STK2236_GET_DATA_FAIL;
}

STK2236_ERR_CODE_E Stk2236GetCDataH(uint8_t *c_data_h)
{
    int ret = STK2236_OK;
    
    Log_info0("Get c data high byte");
    ret = Stk2236ReadReg(STK2236_DATA1_C_REG, c_data_h, 1);
    if(ret != 0)
    {
        Log_info0("c data high byte error!");
        return STK2236_GET_C_DATA_H_FAIL;
    }
    return ret;
}

STK2236_ERR_CODE_E Stk2236GetCDataL(uint8_t *c_data_l)
{
    int ret = STK2236_OK;
    
    Log_info0("Get c data low byte");
    ret = Stk2236ReadReg(STK2236_DATA2_C_REG, c_data_l, 1);
    if(ret != 0)
    {
        Log_info0("c data low byte error!");
        return STK2236_GET_C_DATA_L_FAIL;
    }
    return ret;
}

STK2236_ERR_CODE_E Stk2236GetCData(uint16_t *c_data)
{
    uint8_t c_data_h = 0;
    uint8_t c_data_l = 0;

    Log_info0("Get c data");
    if( Stk2236GetCDataH(&c_data_h) == 0 && 
        Stk2236GetCDataL(&c_data_l) == 0)
    {
        *c_data = (c_data_h << 8) + c_data_l;
        return STK2236_OK;
    }
    return STK2236_GET_C_DATA_FAIL;
}

/**
 * Get the device id from register
*/
STK2236_ERR_CODE_E Stk2236GetDevID(uint8_t *dev_id)
{
    STK2236_ERR_CODE_E ret = STK2236_OK;

    Log_info0("Get the Device Product ID");
    ret = Stk2236ReadReg(STK2236_PDT_ID_REG,dev_id,1);
    if(ret != 0)
    {
        Log_info1("get device error, %d", ret);
        return STK2236_GET_DEV_ID_FAIL;
    }
    return ret;

}
/**
 * soft reset sensor, write any data to 0x80 register
*/
STK2236_ERR_CODE_E Stk2236SoftRst(void)
{
    STK2236_ERR_CODE_E ret = STK2236_OK;
    uint8_t reg_val = 0xAB;

    Log_info0("Software Reset");
    ret = Stk2236WriteReg(STK2236_SOFT_RESET_REG, &reg_val, 1);
    if(ret != 0)
    {
        Log_info0("Set Software Reste Register Error!");
        return STK2236_SFT_RST_FAIL;
    }
    return ret;
}


/**
 * Clear Channel gain setting. GAIN_C is used to conrol of the ALS channel signal gain
 * @param option_val
 * 0b00(0) -> x1 times,
 * 0b01(1) -> x4 times,
 * 0b10(2) -> x16 times,
 * 0b11(3) -> x64 times,
*/
STK2236_ERR_CODE_E Stk2236SetGainClear(uint8_t option_val)
{
    STK2236_ERR_CODE_E ret = STK2236_OK;
    uint8_t reg_val = 0;

    Log_info0("Set Gain ALS");
    if(Stk2236ReadReg(STK2236_GAIN_C_REG, &reg_val, 1) != 0)
    {
        Log_info0("Get GAIN_ALS register Error!");
        return STK2236_I2C_R_FAIL;
    }

    reg_val = STK2236_SET_BITSLICE(reg_val, STK2236_GAIN_C, option_val);
    Log_info1("reg_val = 0x%02x", reg_val);
    ret = Stk2236WriteReg(STK2236_GAIN_C_REG, &reg_val, 1);
    if(ret != 0)
    {
        Log_info0("Set GAIN_ALS register Error!");
        return STK2236_SET_GAIN_ALS_FAIL;
    }
    return ret;
}