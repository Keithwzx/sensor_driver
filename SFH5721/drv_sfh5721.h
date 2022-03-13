#ifndef _SFH5721_DRV_H_
#define _SFH5721_DRV_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include <stdbool.h>

#define SFH5721_I2C_ADDR_H              0x27
#define SFH5721_I2C_ADDR_L              0x26
#define PROPERTY_DISABLE                (0U)
#define PROPERTY_ENABLE                 (1U)

typedef int32_t (*osram_write_ptr)(void *, uint8_t, const uint8_t *, uint16_t);
typedef int32_t (*osram_read_ptr)(void *, uint8_t, uint8_t *, uint16_t);

typedef struct osram_ctx
{
    osram_write_ptr write_reg;
    osram_read_ptr read_reg;
    void *i2c_handle;
}osram_ctx_t;

/**
 * @brief struct for bit with pos, len, msk, , reg
 * 
 */
typedef struct osram_reg_bit
{
    uint8_t pos;
    uint8_t len;
    uint8_t msk;
    uint8_t reg;
}osram_reg_bit_t;

typedef enum SFH5721_INT_PER
{
    SFH5721_INT_PER_0       =     0,
    SFH5721_INT_PER_1       =     1,
    SFH5721_INT_PER_2       =     2,
    SFH5721_INT_PER_3       =     3,
    SFH5721_INT_PER_4       =     4,
    SFH5721_INT_PER_5       =     5,
    SFH5721_INT_PER_6       =     6,
    SFH5721_INT_PER_7       =     7,
    SFH5721_INT_PER_8       =     8,
    SFH5721_INT_PER_9       =     9,
    SFH5721_INT_PER_10      =     10,
    SFH5721_INT_PER_11      =     11,
    SFH5721_INT_PER_12      =     12,
    SFH5721_INT_PER_13      =     13,
    SFH5721_INT_PER_14      =     14,
    SFH5721_INT_PER_15      =     15,
}SFH5721_INT_PER_E;

typedef enum SFH5721_A_GAIN
{
    SFH5721_A_GAIN_1    = 0,
    SFH5721_A_GAIN_4    = 1,
    SFH5721_A_GAIN_16   = 2,
    SFH5721_A_GAIN_128  = 3,
    SFH5721_A_GAIN_256  = 4,
}SFH5721_A_GAIN_E;
extern uint16_t g_a_gain_arr[];

typedef enum SFH5721_IT
{
    SFH5721_IT_200us  =     0,
    SFH5721_IT_400us  =     1,
    SFH5721_IT_800us  =     2,
    SFH5721_IT_1600us =     3,
    SFH5721_IT_3100us =     4,
    SFH5721_IT_6300us =     5,
    SFH5721_IT_12ms   =     6,
    SFH5721_IT_25ms   =     7,
    SFH5721_IT_50ms   =     8,
    SFH5721_IT_100ms  =     9,
    SFH5721_IT_200ms  =     10,
    SFH5721_IT_400ms  =     11,
    SFH5721_IT_800ms  =     12,
    SFH5721_IT_1600ms =     13,
}SFH5721_IT_E;
extern float g_it_arr[];

typedef enum SFH5721_D_GAIN
{
    SFH5721_D_GAIN_1  =     0,
    SFH5721_D_GAIN_2  =     1,
    SFH5721_D_GAIN_4  =     2,
    SFH5721_D_GAIN_8  =     3,
    SFH5721_D_GAIN_16 =     4,
}SFH5721_D_GAIN_E;
extern uint8_t g_d_gain_arr[];

typedef enum SFH5721_WAIT
{
    SFH5721_WAIT_0ms        =       0,
    SFH5721_WAIT_780us      =       1,
    SFH5721_WAIT_1560us     =       2,
    SFH5721_WAIT_3ms        =       3,
    SFH5721_WAIT_6ms        =       4,
    SFH5721_WAIT_12ms       =       5,
    SFH5721_WAIT_25ms       =       6,
    SFH5721_WAIT_50ms       =       7,
    SFH5721_WAIT_100ms      =       8,
    SFH5721_WAIT_200ms      =       9,
    SFH5721_WAIT_400ms      =       10,
    SFH5721_WAIT_800ms      =       11,
    SFH5721_WAIT_1600ms     =       12,
    SFH5721_WAIT_3s         =       13,
    SFH5721_WAIT_6s         =       14,
    SFH5721_WAIT_12s        =       15,
}SFH5721_WAIT_E;

typedef enum SFH5721_LPF_DEP_TH
{
    SFH5721_LPF_DEP_2 =     0,
    SFH5721_LPF_DEP_3 =     1,
    SFH5721_LPF_DEP_4 =     2,
    SFH5721_LPF_DEP_5 =     3,
}SFH5721_LPF_DEP_TH_E;


int32_t Sfh5721Reset(osram_ctx_t *ctx);
int32_t Sfh5721EnSyncMode(osram_ctx_t *ctx);
int32_t Sfh5721DisSyncMode(osram_ctx_t *ctx);
int32_t Sfh5721EnSingleMode(osram_ctx_t *ctx);
int32_t Sfh5721DisSingleMode(osram_ctx_t *ctx);
int32_t Sfh5721EnAlsCh(osram_ctx_t *ctx);
int32_t Sfh5721DisAlsCh(osram_ctx_t *ctx);
int32_t Sfh5721EnIRCh(osram_ctx_t *ctx);
int32_t Sfh5721DisIRCh(osram_ctx_t *ctx);
int32_t Sfh5721EnDarkCh(osram_ctx_t *ctx);
int32_t Sfh5721DisDarkCh(osram_ctx_t *ctx);
int32_t Sfh5721GetOtped(osram_ctx_t *ctx, uint8_t *flg);
int32_t Sfh5721GetOtpes(osram_ctx_t *ctx, uint8_t *flg);
int32_t Sfh5721GetDryAls(osram_ctx_t *ctx, uint8_t *flg);
int32_t Sfh5721GetDryIR(osram_ctx_t *ctx, uint8_t *flg);
int32_t Sfh5721GetDryDark(osram_ctx_t *ctx, uint8_t *flg);
int32_t Sfh5721EnIenAlsH(osram_ctx_t *ctx);
int32_t Sfh5721EnIenAlsL(osram_ctx_t *ctx);
int32_t Sfh5721EnIenIRH(osram_ctx_t *ctx);
int32_t Sfh5721EnIenIRL(osram_ctx_t *ctx);
int32_t Sfh5721EnIenDarkH(osram_ctx_t *ctx);
int32_t Sfh5721EnIenDarkL(osram_ctx_t *ctx);
int32_t Sfh5721DisIenAlsH(osram_ctx_t *ctx);
int32_t Sfh5721DisIenAlsL(osram_ctx_t *ctx);
int32_t Sfh5721DisIenIRH(osram_ctx_t *ctx);
int32_t Sfh5721DisIenIRL(osram_ctx_t *ctx);
int32_t Sfh5721DisIenDarkH(osram_ctx_t *ctx);
int32_t Sfh5721DisIenDarkL(osram_ctx_t *ctx);
int32_t Sfh5721SetICC(osram_ctx_t *ctx, uint8_t value);
int32_t Sfh5721SetIOA(osram_ctx_t *ctx, uint8_t value);
int32_t Sfh5721SetPersistence(osram_ctx_t *ctx, SFH5721_INT_PER_E value);
int32_t Sfh5721SetIntLowThr(osram_ctx_t *ctx, uint16_t value);
int32_t Sfh5721SetIntHighThr(osram_ctx_t *ctx, uint16_t value);
int32_t Sfh5721GetIFHT_Als(osram_ctx_t *ctx, uint8_t *value);
int32_t Sfh5721GetIFLT_Als(osram_ctx_t *ctx, uint8_t *value);
int32_t Sfh5721GetIFHT_IR(osram_ctx_t *ctx, uint8_t *value);
int32_t Sfh5721GetIFL_TR(osram_ctx_t *ctx, uint8_t *value);
int32_t Sfh5721GetIFHT_Dark(osram_ctx_t *ctx, uint8_t *value);
int32_t Sfh5721GetIFLT_Dark(osram_ctx_t *ctx, uint8_t *value);
int32_t Sfh5721SetIT(osram_ctx_t *ctx, SFH5721_IT_E value);
int32_t Sfh5721GetIT(osram_ctx_t *ctx, uint8_t *value);
int32_t Sfh5721SetA_Gain(osram_ctx_t *ctx, SFH5721_A_GAIN_E value);
int32_t Sfh5721GetA_Gain(osram_ctx_t *ctx, uint8_t *value);
int32_t Sfh5721SetD_Gain(osram_ctx_t *ctx, SFH5721_D_GAIN_E value);
int32_t Sfh5721GetD_Gain(osram_ctx_t *ctx, uint8_t *value);
int32_t Sfh5721SetWait(osram_ctx_t *ctx, SFH5721_WAIT_E value);
int32_t Sfh5721EnSub(osram_ctx_t *ctx);
int32_t Sfh5721DiaSub(osram_ctx_t *ctx);
int32_t Sfh5721SetLpfDepth(osram_ctx_t *ctx, SFH5721_LPF_DEP_TH_E value);
int32_t Sfh5721EnLpfAls(osram_ctx_t *ctx);
int32_t Sfh5721DisLpfAls(osram_ctx_t *ctx);
int32_t Sfh5721EnLpfIR(osram_ctx_t *ctx);
int32_t Sfh5721DisLpfIR(osram_ctx_t *ctx);
int32_t Sfh5721EnLpfDark(osram_ctx_t *ctx);
int32_t Sfh5721DisLpfDark(osram_ctx_t *ctx);
int32_t Sfh5721GetDarkValL(osram_ctx_t *ctx, uint8_t *value);
int32_t Sfh5721GetDarkValH(osram_ctx_t *ctx, uint8_t *value);
int32_t Sfh5721GetIRValL(osram_ctx_t *ctx, uint8_t *value);
int32_t Sfh5721GetIRValH(osram_ctx_t *ctx, uint8_t *value);
int32_t Sfh5721GetAlsValL(osram_ctx_t *ctx, uint8_t *value);
int32_t Sfh5721GetAlsValH(osram_ctx_t *ctx, uint8_t *value);

#endif // _SFH5721_DRV_H_