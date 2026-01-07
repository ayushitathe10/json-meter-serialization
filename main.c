#include <stdio.h>
#include "json_serializer.h" 

int main(void)
{
    /* Create one data point */
    data_point_t data_point = {
        .timestamp = "1970-01-01 00:00",
        .meter_datetime = "1970-01-01 00:00",
        .total_m3 = 107.752f,
        .status = "OK"
    };

    // Create one device 
    device_reading_t device = {
        .media = "water",
        .meter = "waterstarm",
        .deviceId = "stromleser_50898527",
        .unit = "m3",
        .data_points = &data_point,
        .data_point_count = 1
    };

    // Values section
    values_t values = {
        .device_count = 1,
        .readings = &device
    };

    // Gateway data 
    gateway_data_t gateway = {
        .gatewayId = "gateway_1234",
        .date = "1970-01-01",
        .deviceType = "stromleser",
        .interval_minutes = 15,
        .total_readings = 1,
        .values = values
    };

    // Output buffer
    char json_buffer[1024];

    // Serialize to JSON 
    int result = serialize_to_json(&gateway, json_buffer, sizeof(json_buffer));

    if (result == 0)
    {
        printf("JSON Output:\n%s\n", json_buffer);
    }
    else
    {
        printf("Error generating JSON\n");
    }

    return 0;
}
