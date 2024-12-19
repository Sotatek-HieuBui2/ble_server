#ifndef GAT_SERVER_H
#define GAT_SERVER_H

#include <stdio.h>
#include "sdkconfig.h"

#define GATTS_TAG "GATTS_DEMO"

#define GATTS_SERVICE_UUID_TEST_A   0x00FF
#define GATTS_CHAR_UUID_TEST_A      0xFF01
#define GATTS_DESCR_UUID_TEST_A     0x3333
#define GATTS_NUM_HANDLE_TEST_A     4

#define TEST_DEVICE_NAME            "ESP_GATTS_DEMO"
#define TEST_MANUFACTURER_DATA_LEN  17

#define GATTS_DEMO_CHAR_VAL_LEN_MAX 0x40

#define PREPARE_BUF_MAX_SIZE 1024

#define adv_config_flag      (1 << 0)
#define scan_rsp_config_flag (1 << 1)

#define PROFILE_NUM 1
#define PROFILE_A_APP_ID 0

#define QUEUE_BLE_SIZE 5
#define CONTROL_GPIO 10
#define HUMAN_DISTANCE 200
#define IS_SAFE 0

typedef struct {
    uint8_t *value;
    uint8_t len;
}server_data;

struct gatts_profile_inst {
    esp_gatts_cb_t gatts_cb;
    uint16_t gatts_if;
    uint16_t app_id;
    uint16_t conn_id;
    uint16_t service_handle;
    esp_gatt_srvc_id_t service_id;
    uint16_t char_handle;
    esp_bt_uuid_t char_uuid;
    esp_gatt_perm_t perm;
    esp_gatt_char_prop_t property;
    uint16_t descr_handle;
    esp_bt_uuid_t descr_uuid;
};

/* One gatt-based profile one app_id and one gatts_if, this array will store the gatts_if returned by ESP_GATTS_REG_EVT */

typedef struct {
    uint8_t                 *prepare_buf;
    int                     prepare_len;
} prepare_type_env_t;


/**
 * @brief Init ble config for esp32 communication
 * This function configures and initializes the ble interfaces for esp32 server.
 */

void ble_server_init();

/**
 * @brief Send data frame to server
 *
 * @param data is the data that want to send
 * @param len is the length of data
 * @return ESP_OK if send successfully, ESP_FAIL if not
 */
esp_err_t send_data(uint8_t *data, uint8_t len);

/**
 * @brief take receive data from queue_receive into *data_receive pointer
 *
 * @param buffer pointer take data
 * @param buffer_size is length of buffer
 * @return true if take data success
 * @return false if take data fail
 */
bool receive_data(uint8_t *buffer, uint8_t *buffer_size);

/**
 * @brief this function control GPIO pin to turn on or off machine base on distance to human
 * 
 * @param human_distance is smallest distance from people around to machine
 */
void control_gpio(uint8_t human_distance);


#endif