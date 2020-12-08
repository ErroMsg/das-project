#ifndef PARAMSTRUCT_H
#define PARAMSTRUCT_H
#include <time.h>
#include <stdint.h>

//1.用户登录
typedef struct userinfo
{
    char username[64];
    char password[64];
    uint8_t userType;
}USER;

typedef struct metatype
{
    uint32_t type_code;
    char     username[255];
}META_TYPE;


//操作日志
typedef struct operate
{
    time_t          time;
    char            username[64];
    uint64_t        operate_type;
    int             reserve[8];
}OP_LOG;

//报警日志

typedef struct alarm
{
    time_t          time;
    uint8_t         chan;
    uint32_t        part;
    uint64_t        pos;
    uint8_t         reson;
    uint64_t        alarm_value;
    uint8_t         state;
    int             reserve[4];
}ALARM_LOG;

//故障日志

typedef struct err
{
    time_t          time;
    uint64_t        type;
    uint8_t         state;
    union{
         struct{
            uint8_t  chan;
            uint32_t position;
         };
        uint8_t     fault_id;	//故障描述
    }Desc;
    int             reserve[4];
}ERR_LOG;


//分区参数
typedef struct part_para
{
    uint8_t         chan_id;
    uint32_t        part_id;
    char            part_name[64];
    uint32_t        part_start;
    uint32_t        part_end;
    uint8_t         alarm_algo;

    uint32_t        alarm_value_1;
    uint32_t        alarm_value_2;
    uint32_t        alarm_value_3;

    uint8_t         alarm_level;

    uint8_t         alarm_enable;

    int   reserve[10];
} T_SYS_PARA;


//通道参数
typedef struct channel_para
{
    uint8_t         chan_id;
    char            chan_name[64];
    uint32_t        part_count;
    uint32_t        sample;
    uint32_t        base_start;
    uint32_t        base_end;
    uint32_t        zero_start;
    uint32_t        zero_end;

    uint8_t         algo;
    uint8_t         Refractive;//折射
    uint32_t        time_count;
    uint32_t        freq_count;
    uint8_t         enable; /* 0->disable, 1->enable */

    uint32_t        reserve[15];

} T_CHANNEL_PARA;


//系统参数
typedef struct syscfg
{
    uint32_t        chan_time;
    uint8_t         alarm_enable;
    uint8_t         dev_factory;
    uint16_t          dev_num;
    char            dev_name[50];

    uint8_t         dev_type;
    uint8_t         apply_type;

    uint8_t         dual_chan_enable;

    int             pulse[2]; //脉冲衰减
    float           EOM_V;
    float           EOM_R;
    float           AOM;
    uint32_t        step;
    uint8_t         chan_num;
    uint8_t      reserve[8];
}SYS_CFG;


#endif // PARAMSTRUCT_H
