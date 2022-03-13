#ifndef _STK_DRV_H_
#define _STK_DRV_H_
#include "m_i2c.h"

// #define STK2236_I2C_ADDR        0x57
#define STK2236_DEV_ID          0x5B

#define STK2236_STATE_REG       0x00
#define STK2236_ALSCTRL1_REG    0x02
#define STK2236_INTCTRL1_REG    0x04
#define STK2236_WAIT_REG1       0x05
#define STK2236_THDH1_ALS_REG   0x0A
#define STK2236_THDH2_ALS_REG   0x0B
#define STK2236_THDL1_ALS_REG   0x0C
#define STK2236_THDL2_ALS_REG   0x0D
#define STK2236_FLAG_REG        0x10
#define STK2236_DATA1_ALS_REG   0x13
#define STK2236_DATA2_ALS_REG   0x14
#define STK2236_DATA1_C_REG     0x1B
#define STK2236_DATA2_C_REG     0x1C
#define STK2236_PDT_ID_REG      0x3E
#define STK2236_ALSCTRL2_REG    0x4E
#define STK2236_SOFT_RESET_REG  0x80
#define STK2236_INTCTRL2_REG    0xA5
#define STK2236_AGCTRL_REG      0xDB




/****************************************************
**\name  BITSLICE FUNCTIONS     
***************************************************/
#define STK2236_GET_BITSLICE(regvar, bitname)\
((regvar & bitname##_MSK) >> bitname##_POS)


#define STK2236_SET_BITSLICE(regvar, bitname, val)\
((regvar & ~bitname##_MSK) | ((val<<bitname##_POS)&bitname##_MSK))

/************************************************
 * State register
 * 
***********************************************/
#define STK2236_EN_ALS_POS 1
#define STK2236_EN_ALS_LEN 1
#define STK2236_EN_ALS_MSK 0x02
#define STK2236_EN_ALS_REG STK2236_STATE_REG

#define STK2236_EN_WAIT_POS 2
#define STK2236_EN_WAIT_LEN 1
#define STK2236_EN_WAIT_MSK 0x04
#define STK2236_EN_WAIT_REG STK2236_STATE_REG

/************************************************
 * ALSCTRL1 Register
***********************************************/
#define STK2236_IT_ALS_POS 0
#define STK2236_IT_ALS_LEN 4
#define STK2236_IT_ALS_MSK 0x0F
#define STK2236_IT_ALS_REG STK2236_ALSCTRL1_REG

#define STK2236_GAIN_ALS_POS 4
#define STK2236_GAIN_ALS_LEN 2
#define STK2236_GAIN_ALS_MSK 0x30
#define STK2236_GAIN_ALS_REG STK2236_ALSCTRL1_REG

#define STK2236_PRST_ALS_POS 6
#define STK2236_PRST_ALS_LEN 2
#define STK2236_PRST_ALS_MSK 0xC0
#define STK2236_PRST_ALS_REG STK2236_ALSCTRL1_REG

/************************************************
 * INTCTRL1 Register
***********************************************/
#define STK2236_EN_ALS_INT_POS 3
#define STK2236_EN_ALS_INT_LEN 1
#define STK2236_EN_ALS_INT_MSK 0x08
#define STK2236_EN_ALS_INT_REG STK2236_INTCTRL1_REG

#define STK2236_INT_CTRL_POS 7
#define STK2236_INT_CTRL_LEN 1
#define STK2236_INT_CTRL_MSK 0x80
#define STK2236_INT_CTRL_REG STK2236_INTCTRL1_REG

/************************************************
 * WAIT Register direct read and write by i2c cmd operations
***********************************************/
#define STK2236_WAIT_POS 0
#define STK2236_WAIT_LEN 7
#define STK2236_WAIT_MSK 0xFF
#define STK2236_WAIT_REG STK2236_WAIT_REG1

/************************************************
 * FLAG Register
***********************************************/
#define STK2236_FLG_ALS_SAT_POS 2
#define STK2236_FLG_ALS_SAT_LEN 1
#define STK2236_FLG_ALS_SAT_MSK 0x04
#define STK2236_FLG_ALS_SAT_REG STK2236_FLAG_REG

#define STK2236_FLG_ALS_INT_POS 5
#define STK2236_FLG_ALS_INT_LEN 1
#define STK2236_FLG_ALS_INT_MSK 0x20
#define STK2236_FLG_ALS_INT_REG STK2236_FLAG_REG

#define STK2236_FLG_ALS_DR_POS 7
#define STK2236_FLG_ALS_DR_LEN 1
#define STK2236_FLG_ALS_DR_MSK 0x80
#define STK2236_FLG_ALS_DR_REG STK2236_FLAG_REG

/************************************************
 * ALSCTRL2 Register
***********************************************/
#define STK2236_GAIN_C_POS 4
#define STK2236_GAIN_C_LEN 2
#define STK2236_GAIN_C_MSK 0x30
#define STK2236_GAIN_C_REG STK2236_ALSCTRL2_REG

/************************************************
 * INTCTRL2 Register
***********************************************/
#define STK2236_EN_ALS_DR_INT_POS 1
#define STK2236_EN_ALS_DR_INT_LEN 1
#define STK2236_EN_ALS_DR_INT_MSK 0x02
#define STK2236_EN_ALS_DR_INT_REG STK2236_INTCTRL2_REG

/************************************************
 * INTCTRL2 Register
***********************************************/
#define STK2236_CLEAR_CI_POS 4
#define STK2236_CLEAR_CI_LEN 2
#define STK2236_CLEAR_CI_MSK 0x30
#define STK2236_CLEAR_CI_REG STK2236_AGCTRL_REG

#define STK2236_ALS_CI_POS 2
#define STK2236_ALS_CI_LEN 2
#define STK2236_ALS_CI_MSK 0x0C
#define STK2236_ALS_CI_REG STK2236_AGCTRL_REG



typedef enum STK2236_ERR_CODE
{
    // STK2236_ERR = -1,
    STK2236_OK                      = 0,
    STK2236_I2C_R_FAIL              = 1,
    STK2236_I2C_W_FAIL              = 2,
    STK2236_EN_ALS_FAIL             = 3,
    STK2236_EN_WAIT_FAIL            = 4,
    STK2236_GET_IT_FAIL             = 5,            
    STK2236_SET_IT_FAIL             = 6,
    STK2236_SET_GAIN_ALS_FAIL       = 7,
    STK2236_SET_PRST_ALS_FAIL       = 8,  
    STK2236_GET_FLG_ALS_SAT_FAIL    = 9,
    STK2236_GET_FLG_ALS_INT_FAIL    = 10,
    STK2236_GET_FLG_ALS_DR_FAIL     = 11,
    STK2236_EN_ALS_INT_FAIL         = 12,
    STK2236_GET_ALS_H_FAIL          = 13,
    STK2236_GET_ALS_L_FAIL          = 14,
    STK2236_GET_DATA_FAIL           = 15,
    STK2236_GET_C_DATA_H_FAIL       = 16,
    STK2236_GET_C_DATA_L_FAIL       = 17,
    STK2236_GET_C_DATA_FAIL         = 18,
    STK2236_GET_DEV_ID_FAIL         = 19,
    STK2236_SFT_RST_FAIL            = 20,
    STK2236_INIT_FAIL               = 21,
    STK2236_SET_WAIT_FAIL           = 22,
    
}STK2236_ERR_CODE_E;

#define Log_info0(fmt)                  APP_PRINT_INFO0(fmt)
#define Log_info1(fmt, arg0)            APP_PRINT_INFO1(fmt, arg0)
#define Log_info2(fmt, arg0, arg1)      APP_PRINT_INFO2(fmt, arg0, arg1)

/**
 * declare function
*/
uint8_t Stk2236WriteReg(uint8_t reg_addr, uint8_t *data, uint16_t data_len);
uint8_t Stk2236ReadReg(uint8_t reg_addr, uint8_t *data, uint16_t data_len);
STK2236_ERR_CODE_E Stk2236EnableAls(uint8_t option_val);
STK2236_ERR_CODE_E Stk2236EnableWait(uint8_t option_val);
STK2236_ERR_CODE_E Stk2236SetIntegrationTime(uint8_t option_val);
STK2236_ERR_CODE_E Stk2236SetGainAls(uint8_t option_val);
STK2236_ERR_CODE_E Stk2236SetPRSTAls(uint8_t option_val);
STK2236_ERR_CODE_E Stk2236EnableAlsInt(uint8_t option_val);
STK2236_ERR_CODE_E Stk2236SetIntCtrl(uint8_t option_val);
STK2236_ERR_CODE_E Stk2236GetFlgAlsSat(uint8_t *flg_als_sat);
STK2236_ERR_CODE_E Stk2236GetFlgAlsInt(uint8_t *flg_als_int);
STK2236_ERR_CODE_E Stk2236GetFlgAlsDr(uint8_t *flg_als_dr);
STK2236_ERR_CODE_E Stk2236GetAlsDataH(uint8_t *als_data_h);
STK2236_ERR_CODE_E Stk2236GetAlsDataL(uint8_t *als_data_l);
STK2236_ERR_CODE_E Stk2236GetAlsData(uint16_t *als_data);
STK2236_ERR_CODE_E Stk2236GetCDataH(uint8_t *c_data_h);
STK2236_ERR_CODE_E Stk2236GetCDataL(uint8_t *c_data_l);
STK2236_ERR_CODE_E Stk2236GetCData(uint16_t *c_data);
STK2236_ERR_CODE_E Stk2236GetDevID(uint8_t *dev_id);
STK2236_ERR_CODE_E Stk2236SoftRst(void);
STK2236_ERR_CODE_E Stk2236SetWait(uint8_t value);
STK2236_ERR_CODE_E Stk2236SetGainClear(uint8_t option_val);
/**
 * need to add set and get threshold functions 
*/
#endif //_STK_DRV_H_