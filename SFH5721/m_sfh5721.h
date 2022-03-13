#include "drv_sfh5721.h"

/* set the macro to 1 when variable is enabled */
#define EN_SINGLE_MODE      0
#define EN_SYNC_MODE        0
#define EN_ALS_CH           1
#define EN_IR_CH            1
#define EN_DRK_CH           1

#define EN_ALS_INT          0
#define EN_IR_INT           0
#define EN_DRK_INT          0

#define EN_LPF_ALS          0
#define EN_LPF_IR           0
#define EN_LPF_DRK          0

/* set the formula variable */
#define ANALOG_GAIN         SFH5721_A_GAIN_1
#define IT_TIME             SFH5721_IT_50ms
#define DIGITAL_GAIN        SFH5721_D_GAIN_1
#define WAIT_TIME           SFH5721_WAIT_0ms

/* set the threshold value */
#define LOW_INT_THR         0x0000
#define HIGH_INT_THR        0x0000

/* set the depth of low pass filter */
#define LPF_DEP_THR         0

#define RTK_ALS_SUPPORT     0


typedef struct osram_all_data
{
    uint16_t als_data;
    uint16_t ir_data;
    uint16_t dark_data;
}osram_all_data_t;

extern osram_ctx_t g_osram_ctx;
extern bool g_single_mode_flg;
extern bool g_en_als_ch;
extern bool g_en_ir_ch;
extern bool g_en_dark_ch;

/* declare functions */
int32_t Sfh5721SensorInit(void);
int32_t Sfh5721GetLux(osram_ctx_t *ctx, float *lux);
int32_t Sfh5721GetIrradiance(osram_ctx_t *ctx, float *irradians);
int32_t Sfh5721GetAllData(osram_ctx_t *ctx, osram_all_data_t *all_data, uint8_t *all_data_arr);
int32_t Sfh5721ReadVal(osram_ctx_t *ctx, uint16_t *value, uint8_t ch);