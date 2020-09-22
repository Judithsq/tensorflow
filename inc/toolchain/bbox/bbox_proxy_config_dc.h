/**
 * Copyright 2019-2020 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef BBOX_PROXY_CONFIG_DC
#define BBOX_PROXY_CONFIG_DC

#include "bbox_proxy_config.h"
#include "device/bbox_pub.h"

/*
 * 说明：模块代理及异常注册
 * 各模块通过模板宏初始化 struct bbox_proxy_info 结构体，黑匣子引用该头文件并将初始化结构体实例化
 *
 * 示例：
 * 各模块通过BBOX_PROXY_MODULE_XXX宏定义初始化 struct bbox_proxy_module_info 结构体
 * #define BBOX_PROXY_MODULE_LPM { \
 *     .coreid = BBOX_LPM, \
 *     .flag = BBOX_PROXY_CAPACITY_REGISTER | BBOX_PROXY_CAPACITY_DUMP | BBOX_PROXY_CAPACITY_LOG, \
 *     .name = "lpm", \
 *     .log_addr = 0xA00000, \
 *     .log_len = 0x400000, \
 *     .wait_timeout = 20000, \ // wait timeout will be restricted <= 20s
 *     .e_count = 3, \
 * }
 * 各模块通过BBOX_PROXY_EXCEPTION_XXX宏定义初始化 struct bbox_proxy_exception_info 结构体
 * #define BBOX_PROXY_EXCEPTION_LPM { \
 *     {0xA819320F, BBOX_DEAD, BBOX_REBOOT_WAIT, LPM_EXCEPTION, BBOX_REENTRANT_DISALLOW,
 *          BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "tsensor error"}, \
 *     {0xA619FFFF, BBOX_ERR, BBOX_REBOOT_WAIT, LPM_EXCEPTION, BBOX_REENTRANT_DISALLOW,
 *          BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "lpm heartbeat lost"}, \
 *     {0xA819FFFF, BBOX_DEAD, BBOX_REBOOT_WAIT, LPM_EXCEPTION, BBOX_REENTRANT_DISALLOW,
 *          BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "lpm startup error"}, \
 * }
 * 各模块通过BBOX_PROXY_CTRL_XXX宏定义初始化 struct bbox_proxy_ctrl_info 结构体
 * #define BBOX_PROXY_CTRL_LPM { \
 *     .e_block_num = 2, \
 *     .block_info = { \
 *         {BLOCK_TYPE_STARTUP, CHECK_NONE, 0, 0x200000}, \
 *         {BLOCK_TYPE_NORMAL, CHECK_RUNTIME_EXCEPID | CHECK_RUNTIME_TMSTMP | CHECK_HEARTBEAT_EXCEPID, \
 *          0x200000, 0x200000}, \
 *     } \
 * }
 * 各模块通过修改DEFINE_BBOX_PROXY(x)宏定义增加自身模块在黑匣子代码中实例化 struct bbox_proxy_info 结构体
 * #define BBOX_PROXY_INITIALIZER(name) { \
 *     .module = BBOX_PROXY_MODULE_##name, \
 *     .exception = BBOX_PROXY_EXCEPTION_##name, \
 *     .ctrl = BBOX_PROXY_CTRL_##name, \
 * }
 * DEFINE_BBOX_PROXY(x) struct bbox_proxy_info x[] = { \
 *     BBOX_PROXY_INITIALIZER(TS), \
 *     BBOX_PROXY_INITIALIZER(LPM), \
 * }
 */
#define BBOX_PROXY_MODULE_TS { \
    .coreid = BBOX_TS, \
    .flag = BBOX_PROXY_CAPACITY_REGISTER | BBOX_PROXY_CAPACITY_DUMP_DDR | BBOX_PROXY_CAPACITY_TRANS_ID, \
    .name = "ts", \
    .log_addr = 0, \
    .log_len = 0, \
    .wait_timeout = 10000, \
    .e_count = 21, \
}

#define BBOX_PROXY_EXCEPTION_TS { \
    {0xA6060FFF, BBOX_MAJOR, BBOX_REBOOT_WAIT, HEARTBEAT_EXCEPTION, BBOX_REENTRANT_DISALLOW,  \
        BBOX_COREID_MASK(BBOX_TS), BBOX_COREID_MASK(BBOX_TS), "ts heartbeat lost"}, \
    {0xA8060FFF, BBOX_CRITICAL, BBOX_REBOOT_WAIT, STARTUP_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_TS), BBOX_COREID_MASK(BBOX_TS), "ts startup error"}, \
    {0xA6060000, BBOX_MAJOR, BBOX_REBOOT_WAIT, TS_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_TS), BBOX_COREID_MASK(BBOX_TS), "data abort"}, \
    {0xA6060001, BBOX_MAJOR, BBOX_REBOOT_WAIT, TS_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_TS), BBOX_COREID_MASK(BBOX_TS), "instr abort"}, \
    {0xA6060002, BBOX_MAJOR, BBOX_REBOOT_WAIT, TS_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_TS), BBOX_COREID_MASK(BBOX_TS), "pc align fault"}, \
    {0xA6060003, BBOX_MAJOR, BBOX_REBOOT_WAIT, TS_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_TS), BBOX_COREID_MASK(BBOX_TS), "sp align fault"}, \
    {0xA6060004, BBOX_MAJOR, BBOX_REBOOT_WAIT, TS_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_TS), BBOX_COREID_MASK(BBOX_TS), "infinite loop"}, \
    {0xA6060005, BBOX_MAJOR, BBOX_REBOOT_WAIT, TS_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_TS), BBOX_COREID_MASK(BBOX_TS), "unknow exception"}, \
    {0xB4060006, BBOX_MINOR, BBOX_REBOOT_NO, TS_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_TS), BBOX_COREID_MASK(BBOX_TS), "aicore exception"}, \
    {0xB4060007, BBOX_MINOR, BBOX_REBOOT_NO, TS_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_TS), BBOX_COREID_MASK(BBOX_TS), "aicore timeout"}, \
    {0xB6060008, BBOX_MAJOR, BBOX_REBOOT_NO, TS_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_TS), BBOX_COREID_MASK(BBOX_TS), "sdma init fault"}, \
    {0xB4060009, BBOX_MINOR, BBOX_REBOOT_NO, TS_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_TS), BBOX_COREID_MASK(BBOX_TS), "sdma timeout"}, \
    {0xA606000A, BBOX_MAJOR, BBOX_REBOOT_WAIT, TS_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_TS), BBOX_COREID_MASK(BBOX_TS), "hwts bus error"}, \
    {0xA606000B, BBOX_MAJOR, BBOX_REBOOT_WAIT, TS_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_TS), BBOX_COREID_MASK(BBOX_TS), "hwts sqe error"}, \
    {0xA606000C, BBOX_MAJOR, BBOX_REBOOT_WAIT, TS_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_TS), BBOX_COREID_MASK(BBOX_TS), "hwts ecc error"}, \
    {0xA406000D, BBOX_MINOR, BBOX_REBOOT_WAIT, TS_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_TS), BBOX_COREID_MASK(BBOX_TS), "ts aicpu exception"}, \
    {0xA406000E, BBOX_MINOR, BBOX_REBOOT_WAIT, TS_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_TS), BBOX_COREID_MASK(BBOX_TS), "ts npu exception"}, \
    {0xA606000F, BBOX_MAJOR, BBOX_REBOOT_WAIT, TS_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_TS), BBOX_COREID_MASK(BBOX_TS), "aicore reset timeout"}, \
    {0xA4060010, BBOX_MINOR, BBOX_REBOOT_WAIT, TS_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_TS), BBOX_COREID_MASK(BBOX_TS), "ts aiv exception"}, \
    {0xA4060011, BBOX_MINOR, BBOX_REBOOT_WAIT, TS_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_TS), BBOX_COREID_MASK(BBOX_TS), "ts aiv timeout"}, \
    {0xA4060014, BBOX_MINOR, BBOX_REBOOT_WAIT, TS_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_TS), BBOX_COREID_MASK(BBOX_TS), "ts aicpu timeout"}, \
}

#define BBOX_PROXY_CTRL_TS { \
    .e_block_num = 2, \
    .padding = {0}, \
    .block_info = { \
        {BLOCK_TYPE_STARTUP, CHECK_NONE, \
            0x200,    0x19000}, \
        {BLOCK_TYPE_NORMAL,  CHECK_RUNTIME_EXCEPID | CHECK_RUNTIME_TMSTMP | CHECK_HEARTBEAT_EXCEPID, \
            0x19200,  0x1E6E00}, \
    } \
}

#define BBOX_PROXY_MODULE_LPM { \
    .coreid = BBOX_LPM, \
    .flag = BBOX_PROXY_CAPACITY_REGISTER | BBOX_PROXY_CAPACITY_DUMP_DDR | BBOX_PROXY_CAPACITY_DUMP_LOG, \
    .name = "lpm", \
    .log_addr = 0xA00000, \
    .log_len = 0x20000, \
    .wait_timeout = 10000, \
    .e_count = 24, \
}

#define BBOX_PROXY_EXCEPTION_LPM { \
    {0xa819320f, BBOX_CRITICAL, BBOX_REBOOT_NO, LPM_EXCEPTION, BBOX_REENTRANT_ALLOW, \
        BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "tsensor error"}, \
    {0xa6192d15, BBOX_MAJOR, BBOX_REBOOT_WAIT, HEARTBEAT_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "lpm heart error"}, \
    {0xa6193206, BBOX_MAJOR, BBOX_REBOOT_WAIT, LPM_EXCEPTION, BBOX_REENTRANT_ALLOW, \
        BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "headfault error"}, \
    {0xa4193216, BBOX_MINOR, BBOX_REBOOT_NO, LPM_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "edp error"}, \
    {0xa4193217, BBOX_MINOR, BBOX_REBOOT_WAIT, LPM_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "ipc timeout error"}, \
    {0xa4193218, BBOX_MINOR, BBOX_REBOOT_WAIT, LPM_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "ipc queue error"}, \
    {0xa6193215, BBOX_MAJOR, BBOX_REBOOT_WAIT, LPM_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "os heart error"}, \
    {0xa8193234,BBOX_CRITICAL, BBOX_REBOOT_WAIT, LPM_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "ddr tmon low error"}, \
    {0xa8193235, BBOX_CRITICAL, BBOX_REBOOT_WAIT, LPM_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "ddr tmon high error"}, \
    {0xa6193236, BBOX_MAJOR, BBOX_REBOOT_WAIT, LPM_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "ddr gate error"}, \
    {0xa619323f, BBOX_MAJOR, BBOX_REBOOT_WAIT, LPM_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "ddr aref error"}, \
    {0xa6193240, BBOX_MAJOR, BBOX_REBOOT_WAIT, LPM_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "ddr rdtimeout error"}, \
    {0xa6193241, BBOX_MAJOR, BBOX_REBOOT_WAIT, LPM_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "ddr pll unlock error"}, \
    {0xa6193242, BBOX_MAJOR, BBOX_REBOOT_WAIT, LPM_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "ddr retrain error"}, \
    {0xa6193243, BBOX_MAJOR, BBOX_REBOOT_WAIT, LPM_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "ddr tmon error"}, \
    {0xa6193244, BBOX_MAJOR, BBOX_REBOOT_WAIT, LPM_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "ddr dfs error"}, \
    {0xa6193245, BBOX_MAJOR, BBOX_REBOOT_WAIT, LPM_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "ddr dvalid error"}, \
    {0xa6193246, BBOX_MAJOR, BBOX_REBOOT_WAIT, LPM_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "ddr dfi sel error"}, \
    {0xa6193247, BBOX_MAJOR, BBOX_REBOOT_WAIT, LPM_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "ddr pll unlock lp error"}, \
    {0xa6193248, BBOX_MAJOR, BBOX_REBOOT_NO, LPM_EXCEPTION, BBOX_REENTRANT_ALLOW, \
        BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "ddr iecc uerr error"}, \
    {0xa419324a, BBOX_MAJOR, BBOX_REBOOT_WAIT, LPM_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "ddr unkonwn error"}, \
    {0xa4193250, BBOX_MINOR, BBOX_REBOOT_NO, LPM_EXCEPTION, BBOX_REENTRANT_ALLOW, \
        BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "ddr iecc cerr error"}, \
    {0xa4192c1a, BBOX_MINOR, BBOX_REBOOT_WAIT, STARTUP_EXCEPTION, BBOX_REENTRANT_ALLOW, \
        BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "lp startup error"}, \
    {0xa419321b, BBOX_MINOR, BBOX_REBOOT_NO, LPM_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_LPM), BBOX_COREID_MASK(BBOX_LPM), "lp tmonitor error"}, \
}

#define BBOX_PROXY_CTRL_LPM { \
    .e_block_num = 6, \
    .padding = {0}, \
    .block_info = { \
        {BLOCK_TYPE_STARTUP, CHECK_NONE, 0x0400, 0x12C00}, \
        {BLOCK_TYPE_NORMAL, CHECK_RUNTIME_EXCEPID | CHECK_RUNTIME_TMSTMP | CHECK_HEARTBEAT_EXCEPID, 0x13000, 0x19000}, \
        {BLOCK_TYPE_NORMAL, CHECK_RUNTIME_EXCEPID | CHECK_RUNTIME_TMSTMP | CHECK_HEARTBEAT_EXCEPID, 0x2C000, 0x19000}, \
        {BLOCK_TYPE_NORMAL, CHECK_RUNTIME_EXCEPID | CHECK_RUNTIME_TMSTMP | CHECK_HEARTBEAT_EXCEPID, 0x45000, 0x19000}, \
        {BLOCK_TYPE_NORMAL, CHECK_RUNTIME_EXCEPID | CHECK_RUNTIME_TMSTMP | CHECK_HEARTBEAT_EXCEPID, 0x5E000, 0x19000}, \
        {BLOCK_TYPE_NORMAL, CHECK_RUNTIME_EXCEPID | CHECK_RUNTIME_TMSTMP | CHECK_HEARTBEAT_EXCEPID, 0x77000, 0x19000}, \
    } \
}

#define BBOX_PROXY_MODULE_HSM { \
    .coreid = BBOX_HSM, \
    .flag = BBOX_PROXY_CAPACITY_REGISTER | BBOX_PROXY_CAPACITY_DUMP_DDR | BBOX_PROXY_CAPACITY_DUMP_LOG, \
    .name = "hsm", \
    .log_addr = 0x3E00000, \
    .log_len = 0x100000, \
    .wait_timeout = 10000, \
    .e_count = 3, \
}

#define BBOX_PROXY_EXCEPTION_HSM { \
    {0xa6360000, BBOX_MAJOR, BBOX_REBOOT_WAIT, STARTUP_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_HSM), BBOX_COREID_MASK(BBOX_HSM), "HSM startup exception"}, \
    {0xa6361000, BBOX_MAJOR, BBOX_REBOOT_WAIT, HEARTBEAT_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_HSM), BBOX_COREID_MASK(BBOX_HSM), "HSM heartbeat exception"}, \
    {0xa6362000, BBOX_MAJOR, BBOX_REBOOT_NO, HSM_EXCEPTION, BBOX_REENTRANT_ALLOW, \
        BBOX_COREID_MASK(BBOX_HSM), BBOX_COREID_MASK(BBOX_HSM), "HSM resource shortage exception"}, \
}

#define BBOX_PROXY_CTRL_HSM { \
    .e_block_num = 5, \
    .padding = {0}, \
    .block_info = { \
        {BLOCK_TYPE_STARTUP, CHECK_NONE, 0x200,  0x1000}, \
        {BLOCK_TYPE_NORMAL,  CHECK_RUNTIME_EXCEPID | CHECK_RUNTIME_TMSTMP | CHECK_HEARTBEAT_EXCEPID, 0x1200, 0x1000}, \
        {BLOCK_TYPE_NORMAL,  CHECK_RUNTIME_EXCEPID | CHECK_RUNTIME_TMSTMP | CHECK_HEARTBEAT_EXCEPID, 0x2200, 0x1000}, \
        {BLOCK_TYPE_NORMAL,  CHECK_RUNTIME_EXCEPID | CHECK_RUNTIME_TMSTMP | CHECK_HEARTBEAT_EXCEPID, 0x3200, 0x1000}, \
        {BLOCK_TYPE_NORMAL,  CHECK_RUNTIME_EXCEPID | CHECK_RUNTIME_TMSTMP | CHECK_HEARTBEAT_EXCEPID, 0x4200, 0x1000}, \
    } \
}

#define BBOX_PROXY_MODULE_ATF { \
    .coreid = BBOX_TF, \
    .flag = BBOX_PROXY_CAPACITY_REGISTER, \
    .name = "atf", \
    .log_addr = 0x0, \
    .log_len = 0x0, \
    .wait_timeout = 10000, \
    .e_count = 1, \
}

#define BBOX_PROXY_EXCEPTION_ATF { \
    {0xA8340000, BBOX_CRITICAL, BBOX_REBOOT_WAIT, ATF_EXCEPTION, BBOX_REENTRANT_DISALLOW, \
        BBOX_COREID_MASK(BBOX_TF), BBOX_COREID_MASK(BBOX_TF), "atf panic exception"}, \
}

#define BBOX_PROXY_CTRL_ATF { \
    .e_block_num = 1, \
    .padding = {0}, \
    .block_info = { \
        {BLOCK_TYPE_STARTUP, CHECK_NONE, 0x400, 0xF800}, \
    } \
}

#define DEFINE_BBOX_PROXY(x) struct bbox_proxy_info x[] = { \
    BBOX_PROXY_INITIALIZER(TS), \
    BBOX_PROXY_INITIALIZER(LPM), \
    BBOX_PROXY_INITIALIZER(HSM), \
    BBOX_PROXY_INITIALIZER(ATF), \
}

#endif // BBOX_PROXY_CONFIG_DC
