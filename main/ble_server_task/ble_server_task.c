#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>
#include "freertos/queue.h"

#include "gat_server/gat_server.h"

static uint8_t ble_data_tx[5] = {0x03, 0x02, 0x00, 0x00, 0x33};

QueueHandle_t blt_rx_queue;

extern bool is_real;
static void bluetooth_server_task(void *arg)
{
  ble_server_init();
  while (1)
  {
      send_data(ble_data_tx, sizeof(ble_data_tx));
      uint8_t buffer[10];
      uint8_t len = 10;
      memset(buffer, 0,len);
      if(receive_data(buffer, &len))
      {
        for (int i=0;i < len;i++)
         {
        printf("len %d, buffer[%d] = %d\n",len,i, buffer[i]);
         }
      }
      vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void bluetooth_client_task_init(void)
{
  blt_rx_queue = xQueueCreate(QUEUE_BLE_SIZE, sizeof(server_data));
  xTaskCreate(bluetooth_server_task, "bluetooth_server_task_init", 1024 * 3, NULL, 12, NULL);
}