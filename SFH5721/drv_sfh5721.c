#include "drv_sfh5721.h"

/**
 * @brief SFH5721_OPSEL - Operation Selection Register 0x00
 * 
 */

osram_reg_bit_t sfh5721_reset_bit               = {7,1,0x80,0x00};
osram_reg_bit_t sfh5721_sync_m_bit              = {5,1,0x20,0x00};
osram_reg_bit_t sfh5721_single_m_bit            = {4,1,0x10,0x00};
osram_reg_bit_t sfh5721_en_als_bit              = {2,1,0x04,0x00};
osram_reg_bit_t sfh5721_en_ir_bit               = {1,1,0x02,0x00};
osram_reg_bit_t sfh5721_en_dark_bit             = {0,1,0x01,0x00};
/**
 * @brief SFH5721_STAT - Status Register 0x01
 *      The STAT register is used for checking the status of the measurement data and of OTP memory. 
 *      The DRY bits indicate whether new results are available. 
 *      These status bits are cleared when the new measurement results have been read (DATA registers). 
 *      The OTPED and OTPES bits indicate whether the OTP memory is functioning correctly.
 */

osram_reg_bit_t sfh5721_opted_bit               = {5,1,0x20,0x01};
osram_reg_bit_t sfh5721_optes_bit               = {4,1,0x10,0x01};
osram_reg_bit_t sfh5721_dry_als_bit             = {2,1,0x04,0x01};
osram_reg_bit_t sfh5721_dry_ir_bit              = {1,1,0x02,0x01};
osram_reg_bit_t sfh5721_dry_dark_bit            = {0,1,0x01,0x01};
/**
 * @brief   SFH5721_IEN - Interrupt Enable Register
 *          The IEN register is used to enable the interrupt functions of the IC. 
 *          Both IEL and IEH must be set to HIGH, to activate interrupt functionality of a single channel.
 */

osram_reg_bit_t sfh5721_ien_als_h_bit           = {5,1,0x20,0x02};
osram_reg_bit_t sfh5721_ien_als_l_bit           = {4,1,0x10,0x02};
osram_reg_bit_t sfh5721_ien_ir_h_bit            = {3,1,0x08,0x02};
osram_reg_bit_t sfh5721_ien_ir_l_bit            = {2,1,0x04,0x02};
osram_reg_bit_t sfh5721_ien_dark_h_bit          = {1,1,0x02,0x02};
osram_reg_bit_t sfh5721_ien_dark_l_bit          = {0,1,0x01,0x02};
/**
 * @brief SFH5721_ICONF - Interrupt Configuration Register 0x03
 * 
 */
//ICC Interrupt-Clear Configuration
osram_reg_bit_t sfh5721_icc_bit                 = {5,1,0x20,0x03};
//IOA Interrupt-Or-And
osram_reg_bit_t sfh5721_ioa_bit                 = {4,1,0x10,0x03};

osram_reg_bit_t sfh5721_ipers_bit               = {0,4,0x0f,0x03};

// ILTL - Interrupt Low Threshold MSB Register 0x04
osram_reg_bit_t sfh5721_iltl_bit                = {0,8,0xff,0x04};

// ILTH - Interrupt Low Threshold MSB Register 0x05
osram_reg_bit_t sfh5721_ilth_bit                = {0,8,0xff,0x05};

// IHTL - Interrupt High Threshold LSB Register 0x06
osram_reg_bit_t sfh5721_ihtl_bit                = {0,8,0xff,0x06};

// IHTH - Interrupt High Threshold MSB Register
osram_reg_bit_t sfh5721_ihth_bit                = {0,8,0xff,0x07};

/**
 * @brief IFLAG - Interrupt Flag Register
 * 
 */

osram_reg_bit_t sfh5721_als_h_flg_bit           = {5,1,0x20,0x08};
osram_reg_bit_t sfh5721_als_l_flg_bit           = {4,1,0x10,0x08};
osram_reg_bit_t sfh5721_ir_h_flg_bit            = {3,1,0x08,0x08};
osram_reg_bit_t sfh5721_ir_l_flg_bit            = {2,1,0x04,0x08};
osram_reg_bit_t sfh5721_dark_h_flg_bit          = {1,1,0x02,0x08};
osram_reg_bit_t sfh5721_dark_l_flg_bit          = {0,1,0x01,0x08};

/**
 * @brief   MCONFA - Measurement Configuration Register A
 *          The MCONFA register is used to set the analog gain and the ADC integration time of the measurements. 
 *          If a measurement is running, writing MCONFA will restart the measurement.
 */

uint16_t g_a_gain_arr[5] = {1,4,16,128,256};
float g_it_arr[] = {0.2, 0.4, 0.8, 1.6, 3.1, 6.3, 12.5, 25.0, 50.0, 100.0, 200.0,400.0, 800.0, 1600.0};
osram_reg_bit_t sfh5721_a_gain_bit              = {0,3,0x07,0x09};
osram_reg_bit_t sfh5721_it_bit                  = {3,4,0x78,0x09};

/**
 * @brief MCONFB - Measurement Configuration Register B
 * 
 */

uint8_t g_d_gain_arr[5] = {1,2,4,8,16};
osram_reg_bit_t sfh5721_d_gain_bit              = {5,3,0xe0,0x0A};
osram_reg_bit_t sfh5721_sub_bit                 = {4,1,0x10,0x0A};
osram_reg_bit_t sfh5721_wait_bit                = {0,4,0x0f,0x0A};

/**
 * @brief MCONFC - Measurement Configuration Register C 0x0B
 * The MCONFC register is used to configure the digital low pass filtering of the measurement data. 
 * If a measurement is running, writing MCONFC will restart the measurement.
 */

osram_reg_bit_t sfh5721_lpf_depth_th_bit        = {4,2,0x30,0x0B};
osram_reg_bit_t sfh5721_lpf_als_bit             = {2,1,0x04,0x0B};
osram_reg_bit_t sfh5721_lpf_ir_bit              = {1,1,0x02,0x0B};
osram_reg_bit_t sfh5721_lpf_dark_bit            = {0,1,0x01,0x0B};

/**
 * @brief 
 * DATA1L - Data 1 LSB Register 0x0C
 * DATA1H - Data 1 MSB Register 0x0D
 * The DATA1L and DATA1H registers are 
 * used to store the data of readout Dark channel.
 */

osram_reg_bit_t sfh5721_dark_data_l_bit         = {0,8,0xff,0x0C};
osram_reg_bit_t sfh5721_dark_data_h_bit         = {0,8,0xff,0x0D};

/**
 * @brief 
 * DATA2L - Data 2 LSB Register
 * DATA2H - Data 2 MSB Register
 * The DATA2L and DATA2H registers are 
 * used to store the data of readout IR channel.
 */

osram_reg_bit_t sfh5721_ir_data_l_bit           = {0,8,0xff,0x0E};
osram_reg_bit_t sfh5721_ir_data_h_bit           = {0,8,0xff,0x0F};

/**
 * @brief 
 * DATA3L - Data 3 LSB Register
 * DATA4H - Data 3 MSB Register
 * The DATA3L and DATA3H registers are 
 * used to store the data of readout ALS channel.
 */

osram_reg_bit_t sfh5721_als_data_l_bit          = {0,8,0xff,0x10};
osram_reg_bit_t sfh5721_als_data_h_bit          = {0,8,0xff,0x11};


/**
  * @brief  Read generic device register
  *
  * @param  ctx   read / write interface definitions(ptr)
  * @param  reg   register to read
  * @param  data  pointer to buffer that store the data read(ptr)
  * @param  len   number of consecutive register to read
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t Sfh5721I2cRead(osram_ctx_t *ctx, uint8_t reg,
                          uint8_t *data,
                          uint16_t len)
{
    int32_t ret;

    ret = ctx->read_reg(ctx->i2c_handle, reg, data, len);

    return ret;
}

/**
  * @brief  Write generic device register
  *
  * @param  ctx   read / write interface definitions(ptr)
  * @param  reg   register to write
  * @param  data  pointer to data to write in register reg(ptr)
  * @param  len   number of consecutive register to write
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t Sfh5721I2cWrite(osram_ctx_t *ctx, uint8_t reg,
                           uint8_t *data,
                           uint16_t len)
{
    int32_t ret;

    ret = ctx->write_reg(ctx->i2c_handle, reg, data, len);

    return ret;
}

/**
 * @brief Modify the bit 
 * 
 * @param ctx           read / write interface definitions(ptr)
 * @param reg_bit_t     bit struct  
 * @param val           
 * @return int32_t 
 */
int32_t Sfh5721SetBit(osram_ctx_t *ctx, osram_reg_bit_t reg_bit_t, uint8_t val)
{
	int32_t ret = 0;
    uint8_t reg_value = 0;
    // APP_PRINT_INFO1("[shf5721_set_bit]: the address of reg is 0x%02X", reg_bit_t.reg);
    
    ret |= ctx->read_reg(ctx->i2c_handle, reg_bit_t.reg, &reg_value, 1);

    reg_value = ((reg_value & ~reg_bit_t.msk) | ((val<<reg_bit_t.pos)&reg_bit_t.msk));

    ret |= ctx->write_reg(ctx->i2c_handle, reg_bit_t.reg, &reg_value, 1);

    return ret;
}

/**
 * @brief 
 * 
 * @param ctx           read / write interface definitions(ptr)
 * @param reg_bit_t     
 * @param val           pointer to data to get in register reg(ptr)
 * @return int32_t 
 */
int32_t Sfh5721GetBit(osram_ctx_t *ctx, osram_reg_bit_t reg_bit_t, uint8_t *val)
{
    int32_t ret = 0;
    uint8_t reg_value = 0;
    
    ret |= ctx->read_reg(ctx->i2c_handle, reg_bit_t.reg, &reg_value, 1);

    *val = (reg_value & reg_bit_t.msk) >> reg_bit_t.pos;
    
    return ret;
}


/**
 * @brief Reset the default seetings
 * 
 * @param ctx 
 * @return int32_t 
 */
int32_t Sfh5721Reset(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_reset_bit, 1);
}

/**
 * @brief enable the Synchronous Mode
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721EnSyncMode(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_sync_m_bit, PROPERTY_ENABLE);
}

/**
 * @brief Disable the Synchronous Mode
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721DisSyncMode(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_sync_m_bit, PROPERTY_DISABLE);
}

/**
 * @brief Enable the single mode
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721EnSingleMode(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_single_m_bit, PROPERTY_ENABLE);
}

/**
 * @brief Disable single mode
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721DisSingleMode(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_sync_m_bit, PROPERTY_DISABLE);
}

/**
 * @brief Enable the ALS Channel
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721EnAlsCh(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_en_als_bit, PROPERTY_ENABLE);
}
/**
 * @brief Disable the ALS Channel
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721DisAlsCh(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_en_als_bit, PROPERTY_DISABLE);
};

/**
 * @brief Enable the IR Channel
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721EnIRCh(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_en_ir_bit, PROPERTY_ENABLE);
}

/**
 * @brief Disable the IR Channel
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721DisIRCh(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_en_ir_bit, PROPERTY_DISABLE);
}

/**
 * @brief Enable the Dark Channel
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721EnDarkCh(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_en_dark_bit, PROPERTY_ENABLE);
}
/**
 * @brief Disable the Dark Channel
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721DisDarkCh(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_en_dark_bit, PROPERTY_DISABLE);
}

/**
 * @brief Get double bit error in OTP
 * 
 * @param ctx read / write interface definitions(ptr)
 * @param flg   pointer to data to get in register reg(ptr)
 * @return int32_t 
 */
int32_t Sfh5721GetOtped(osram_ctx_t *ctx, uint8_t *flg)
{
    return Sfh5721GetBit(ctx, sfh5721_opted_bit, flg);
}
/**
 * @brief Get double bit error in OTP
 * 
 * @param ctx read / write interface definitions(ptr)
 * @param flg   pointer to data to get in register reg(ptr)
 * @return int32_t 
 */
int32_t Sfh5721GetOtpes(osram_ctx_t *ctx, uint8_t *flg)
{
    return Sfh5721GetBit(ctx, sfh5721_optes_bit, flg);
}
/**
 * @brief Get the data ready flag of ALS Channel
 * 
 * @param ctx read / write interface definitions(ptr)  
 * @param flg   pointer to data to get in register reg(ptr)
 * @return int32_t 
 */
int32_t Sfh5721GetDryAls(osram_ctx_t *ctx, uint8_t *flg)
{
    return Sfh5721GetBit(ctx, sfh5721_dry_als_bit, flg);
}

/**
 * @brief Get the data ready flag of IR Channel
 * 
 * @param ctx read / write interface definitions(ptr)
 * @param flg 
 * @return int32_t 
 */
int32_t Sfh5721GetDryIR(osram_ctx_t *ctx, uint8_t *flg)
{
    return Sfh5721GetBit(ctx, sfh5721_dry_ir_bit, flg);
}

/**
 * @brief Get the data ready flag of Dark Channel
 * 
 * @param ctx read / write interface definitions(ptr)
 * @param flg 
 * @return int32_t 
 */
int32_t Sfh5721GetDryDark(osram_ctx_t *ctx, uint8_t *flg)
{
    return Sfh5721GetBit(ctx, sfh5721_dry_dark_bit, flg);
}
/**
 * @brief Enable Interrupt ALS Threshold high byte
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721EnIenAlsH(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_ien_als_h_bit, PROPERTY_ENABLE);
}

/**
 * @brief  EN ALS interrupt threshold low byte
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721EnIenAlsL(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_ien_als_l_bit, PROPERTY_ENABLE);
}
/**
 * @brief EN IR interrupt threshold high byte
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721EnIenIRH(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_ien_ir_h_bit, PROPERTY_ENABLE);
}

/**
 * @brief EN IR interrupt threshold low byte
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721EnIenIRL(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_ien_ir_l_bit, PROPERTY_ENABLE);
}

/**
 * @brief EN Dark interrupt threshold high byte
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721EnIenDarkH(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_ien_dark_h_bit, PROPERTY_ENABLE);
}


/**
 * @brief EN Dark interrupt threshold low byte
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721EnIenDarkL(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_ien_dark_l_bit, PROPERTY_ENABLE);
}


/**
 * @brief Disable the ALS interrupt threshold high byte
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721DisIenAlsH(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_ien_als_h_bit, PROPERTY_DISABLE);
}

/**
 * @brief Disable the ALS interrupt threshold low byte
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721DisIenAlsL(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_ien_als_l_bit, PROPERTY_DISABLE);
}


/**
 * @brief Disable the IR interrupt threshold High byte
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721DisIenIRH(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_ien_ir_h_bit, PROPERTY_DISABLE);
}

/**
 * @brief Disable the IR interrupt threshold low byte
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721DisIenIRL(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_ien_ir_l_bit, PROPERTY_DISABLE);
}

/**
 * @brief Disable the Dark interrupt threshold High byte
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721DisIenDarkH(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_ien_dark_h_bit, PROPERTY_DISABLE);
}

/**
 * @brief Disable the Dark interrupt threshold low byte
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721DisIenDarkL(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_ien_dark_l_bit, PROPERTY_DISABLE);
}

/**
 * @brief   0 -> Interrupt is generated if a single readout channel generates the interrupt;
            1 -> Interrupt is generated if all enabled readout channels generate the interrupt;
 * 
 * @param ctx read / write interface definitions(ptr)
 * @param value 
 * @return int32_t 
 */
int32_t Sfh5721SetICC(osram_ctx_t *ctx, uint8_t value)
{
    return Sfh5721SetBit(ctx, sfh5721_icc_bit, value);
}

/**
 * @brief   0 -> Interrupt is cleared when IFLAG register is read;
            1 -> Interrupt is cleared when any one of the eight DATA1L to DATA4H register is read;
 * @param ctx read / write interface definitions(ptr)
 * @param value 
 * @return int32_t 
 */
int32_t Sfh5721SetIOA(osram_ctx_t *ctx, uint8_t value)
{
    return Sfh5721SetBit(ctx, sfh5721_ioa_bit, value);
}

/**
 * @brief           Persistence Configuration
 * 
 * @param ctx read / write interface definitions(ptr)
 * @param value     <value> consecutive value out of range generate an interrupt
 * @return int32_t 
 */
int32_t Sfh5721SetPersistence(osram_ctx_t *ctx, SFH5721_INT_PER_E value)
{
    return Sfh5721SetBit(ctx, sfh5721_ipers_bit, value);
}
/**
 * @brief   Set the low threshold of interrupt
 * 
 * @param ctx read / write interface definitions(ptr)
 * @param value 
 * @return int32_t 
 */
int32_t Sfh5721SetIntLowThr(osram_ctx_t *ctx, uint16_t value)
{
    uint32_t ret = 0;

    ret |= Sfh5721SetBit(ctx, sfh5721_iltl_bit, (value & 0x00FF));
    ret |= Sfh5721SetBit(ctx, sfh5721_ilth_bit, (value >> 8));

    return ret;
}

/**
 * @brief   Set the high threshold of interrupt
 * 
 * @param ctx read / write interface definitions(ptr)
 * @param value 
 * @return int32_t 
 */
int32_t Sfh5721SetIntHighThr(osram_ctx_t *ctx, uint16_t value)
{
    uint32_t ret = 0;

    ret |= Sfh5721SetBit(ctx, sfh5721_ihtl_bit, (value & 0x00FF));
    ret |= Sfh5721SetBit(ctx, sfh5721_ihth_bit, (value >> 8));

    return ret;
}

/**
 * @brief Get the Interrupt Flag high side ALS Channel
 *          
 * @param ctx read / write interface definitions(ptr)
 * @param value     Readout ALS high side interrupt is triggered.
 *                  The interrupt is cleared when IFLAG (DATA1L*) register is read.
 * @return int32_t 
 */
int32_t Sfh5721GetIFHT_Als(osram_ctx_t *ctx, uint8_t *value)
{
    return Sfh5721GetBit(ctx, sfh5721_als_h_flg_bit, value);
}

/**
 * @brief Get the Interrupt Flag low side ALS Channel
 *          
 * @param ctx read / write interface definitions(ptr)
 * @param value     Readout ALS low side interrupt is triggered.
 *                  The interrupt is cleared when IFLAG (DATA1L*) register is read.
 * @return int32_t 
 */
int32_t Sfh5721GetIFLT_Als(osram_ctx_t *ctx, uint8_t *value)
{
    return Sfh5721GetBit(ctx, sfh5721_als_l_flg_bit, value);
}

/**
 * @brief Get the Interrupt Flag high side IR Channel
 *          
 * @param ctx read / write interface definitions(ptr)
 * @param value     Readout IR high side interrupt is triggered.
 *                  The interrupt is cleared when IFLAG (DATA1L*) register is read.
 * @return int32_t 
 */
int32_t Sfh5721GetIFHT_IR(osram_ctx_t *ctx, uint8_t *value)
{
    return Sfh5721GetBit(ctx, sfh5721_ir_h_flg_bit, value);
}

/**
 * @brief Get the Interrupt Flag low side IR Channel
 *          
 * @param ctx read / write interface definitions(ptr)
 * @param value     Readout IR low side interrupt is triggered.
 *                  The interrupt is cleared when IFLAG (DATA1L*) register is read.
 * @return int32_t 
 */
int32_t Sfh5721GetIFL_TR(osram_ctx_t *ctx, uint8_t *value)
{
    return Sfh5721GetBit(ctx, sfh5721_ir_l_flg_bit, value);
}

/**
 * @brief Get the Interrupt Flag high side Dark Channel
 *          
 * @param ctx read / write interface definitions(ptr)
 * @param value     Readout Dark high side interrupt is triggered.
 *                  The interrupt is cleared when IFLAG (DATA1L*) register is read.
 * @return int32_t 
 */
int32_t Sfh5721GetIFHT_Dark(osram_ctx_t *ctx, uint8_t *value)
{
    return Sfh5721GetBit(ctx, sfh5721_dark_h_flg_bit, value);
}

/**
 * @brief Get the Interrupt Flag low side Dark Channel
 *          
 * @param ctx read / write interface definitions(ptr)
 * @param value     Readout Dark low side interrupt is triggered.
 *                  The interrupt is cleared when IFLAG (DATA1L*) register is read.
 * @return int32_t 
 */
int32_t Sfh5721GetIFLT_Dark(osram_ctx_t *ctx, uint8_t *value)
{
    return Sfh5721GetBit(ctx, sfh5721_dark_l_flg_bit, value);
}

/**
 * @brief set the integration time of the measurements
 * 
 * @param ctx read / write interface definitions(ptr)
 * @param value 
 * @return int32_t 
 */
int32_t Sfh5721SetIT(osram_ctx_t *ctx, SFH5721_IT_E value)
{
    return Sfh5721SetBit(ctx, sfh5721_it_bit, value);
}

/**
 * @brief get the integration time of the measurements
 * 
 * @param ctx read / write interface definitions(ptr)
 * @param value 
 * @return int32_t 
 */
int32_t Sfh5721GetIT(osram_ctx_t *ctx, uint8_t *value)
{
    return Sfh5721GetBit(ctx, sfh5721_it_bit, value);
}

/**
 * @brief Set the analog gain
 * 
 * @param ctx read / write interface definitions(ptr)
 * @param value 
 * @return int32_t 
 */
int32_t Sfh5721SetA_Gain(osram_ctx_t *ctx, SFH5721_A_GAIN_E value)
{
    return Sfh5721SetBit(ctx, sfh5721_a_gain_bit, value);
}

/**
 * @brief Get the analog gain
 * 
 * @param ctx read / write interface definitions(ptr)
 * @param value 
 * @return int32_t 
 */
int32_t Sfh5721GetA_Gain(osram_ctx_t *ctx, uint8_t *value)
{
    return Sfh5721GetBit(ctx, sfh5721_a_gain_bit, value);
}

/**
 * @brief Set the digital gain
 * 
 * @param ctx read / write interface definitions(ptr)
 * @param value     the enumeration value of the digital gain
 * @return int32_t 
 */
int32_t Sfh5721SetD_Gain(osram_ctx_t *ctx, SFH5721_D_GAIN_E value)
{
    return Sfh5721SetBit(ctx, sfh5721_d_gain_bit, value);
}

/**
 * @brief Get the digital gain
 * 
 * @param ctx read / write interface definitions(ptr)
 * @param value     the pointer of d_gain value
 * @return int32_t 
 */
int32_t Sfh5721GetD_Gain(osram_ctx_t *ctx, uint8_t *value)
{
    return Sfh5721GetBit(ctx, sfh5721_d_gain_bit, value);
}

/**
 * @brief Set the Wait Time between The measurements
 * 
 * @param ctx read / write interface definitions(ptr)
 * @param value     the enumeration value of the wait time
 * @return int32_t 
 */
int32_t Sfh5721SetWait(osram_ctx_t *ctx, SFH5721_WAIT_E value)
{
    return Sfh5721SetBit(ctx, sfh5721_wait_bit, value);
}


int32_t Sfh5721EnSub(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_sub_bit, PROPERTY_ENABLE);
}
int32_t Sfh5721DiaSub(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_sub_bit, PROPERTY_DISABLE);
}

/**
 * @brief Set the depth of low pass filter
 * 
 * @param ctx read / write interface definitions(ptr)
 * @param value     the enumeration value of the low pass filter depth
 * @return int32_t 
 */
int32_t Sfh5721SetLpfDepth(osram_ctx_t *ctx, SFH5721_LPF_DEP_TH_E value)
{
    return Sfh5721SetBit(ctx, sfh5721_lpf_depth_th_bit, value);
}

/**
 * @brief Digital lowpass filtering of readout ALS data is enabled
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721EnLpfAls(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_lpf_als_bit, PROPERTY_ENABLE);
}

/**
 * @brief Digital lowpass filtering of readout ALS data is disabled 
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721DisLpfAls(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_lpf_als_bit, PROPERTY_DISABLE);
}

/**
 * @brief Digital lowpass filtering of readout IR data is enabled
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721EnLpfIR(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_lpf_ir_bit, PROPERTY_ENABLE);
}

/**
 * @brief Digital lowpass filtering of readout IR data is disabled
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721DisLpfIR(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_lpf_ir_bit, PROPERTY_DISABLE);
}

/**
 * @brief Digital lowpass filtering of readout Dark data is enabled
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721EnLpfDark(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_lpf_dark_bit, PROPERTY_ENABLE);
}

/**
 * @brief Digital lowpass filtering of readout Dark data is disabled
 * 
 * @param ctx read / write interface definitions(ptr)
 * @return int32_t 
 */
int32_t Sfh5721DisLpfDark(osram_ctx_t *ctx)
{
    return Sfh5721SetBit(ctx, sfh5721_lpf_dark_bit, PROPERTY_DISABLE);
}

/**
 * @brief Get Data Low Byte Dark Channel
 * 
 * @param ctx read / write interface definitions(ptr)
 * @param value pointer of value to store data
 * @return int32_t 
 */
int32_t Sfh5721GetDarkValL(osram_ctx_t *ctx, uint8_t *value)
{
    return Sfh5721GetBit(ctx, sfh5721_dark_data_l_bit, value);
}

/**
 * @brief Get Data High Byte Dark Channel
 * 
 * @param ctx read / write interface definitions(ptr)
 * @param value pointer of value to store data
 * @return int32_t 
 */
int32_t Sfh5721GetDarkValH(osram_ctx_t *ctx, uint8_t *value)
{
    return Sfh5721GetBit(ctx, sfh5721_dark_data_h_bit, value);
}

/**
 * @brief Get Data Low Byte IR Channel
 * 
 * @param ctx read / write interface definitions(ptr)
 * @param value pointer of value to store data
 * @return int32_t 
 */
int32_t Sfh5721GetIRValL(osram_ctx_t *ctx, uint8_t *value)
{
    return Sfh5721GetBit(ctx, sfh5721_ir_data_l_bit, value);
}

/**
 * @brief Get Data High Byte IR Channel
 * 
 * @param ctx read / write interface definitions(ptr)
 * @param value pointer of value to store data
 * @return int32_t 
 */
int32_t Sfh5721GetIRValH(osram_ctx_t *ctx, uint8_t *value)
{
    return Sfh5721GetBit(ctx, sfh5721_ir_data_h_bit, value);
}

/**
 * @brief Get Data Low Byte ALS Channel
 * 
 * @param ctx read / write interface definitions(ptr)
 * @param value pointer of value to store data
 * @return int32_t 
 */
int32_t Sfh5721GetAlsValL(osram_ctx_t *ctx, uint8_t *value)
{
    return Sfh5721GetBit(ctx, sfh5721_als_data_l_bit, value);
}
/**
 * @brief Get Data Hi Byte ALS Channel
 * 
 * @param ctx read / write interface definitions(ptr)
 * @param value pointer of value to store data
 * @return int32_t 
 */
int32_t Sfh5721GetAlsValH(osram_ctx_t *ctx, uint8_t *value)
{
    return Sfh5721GetBit(ctx, sfh5721_als_data_h_bit, value);
}