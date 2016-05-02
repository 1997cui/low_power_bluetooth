
#ifndef _ARCH_MAIN_H_
#define _ARCH_MAIN_H_

#include "da1458x_scatter_config.h"
#include "arch.h"
#include "arch_api.h"
#include <stdlib.h>
#include <stddef.h>     // standard definitions
#include <stdint.h>     // standard integer definition
#include <stdbool.h>    // boolean definition
#include "boot.h"       // boot definition
#include "rwip.h"       // BLE initialization
#include "syscntl.h"    // System control initialization
#include "emi.h"        // EMI initialization
#include "intc.h"       // Interrupt initialization
#include "em_map_ble.h"
#include "ke_mem.h"
#include "ke_event.h"
#include "user_periph_setup.h"

#include "uart.h"   // UART initialization
#include "nvds.h"   // NVDS initialization
#include "rf.h"     // RF initialization
#include "app.h"    // application functions
#include "dbg.h"    // For dbg_warning function

#include "global_io.h"

#include "datasheet.h"

#include "em_map_ble_user.h"
#include "em_map_ble.h"

#include "lld_sleep.h"
#include "rwble.h"
#include "rf_580.h"
#include "gpio.h"

#include "lld_evt.h"
#include "arch_console.h"

#include "arch_system.h"

#include "arch_patch.h"

// external function declarations
void patch_llm_task(void);
void patch_gtl_task(void);

#if (BLE_MEM_LEAK_PATCH)
    void patch_llc_task(void);
#endif


#include "arch_wdg.h"
//#include "app_stream_queue.h"

#include "user_callback_config.h"

void otp_prepare(uint32 code_size);
bool ble_is_powered ( void );
void ble_turn_radio_off( void );
void schedule_while_ble_on( void );
sleep_mode_t ble_validate_sleep_mode(sleep_mode_t current_sleep_mode);
void arch_turn_peripherals_off (sleep_mode_t current_sleep_mode);
void arch_goto_sleep (sleep_mode_t current_sleep_mode);
void arch_switch_clock_goto_sleep (sleep_mode_t current_sleep_mode);
void arch_resume_from_sleep ( void );
sleep_mode_t rwip_power_down ( void );
bool app_asynch_trm(void);
bool app_asynch_proc(void);
void app_asynch_sleep_proc(void);
void app_sleep_prepare_proc(sleep_mode_t *sleep_mode);
void app_sleep_exit_proc( void );
void app_sleep_entry_proc(sleep_mode_t sleep_mode);

#endif
