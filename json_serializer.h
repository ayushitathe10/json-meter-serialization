#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include <stddef.h>

// Meter Reading Information 
typedef struct
{
    const char *timestamp;
    const char *meter_datetime;
    float total_m3;
    const char *status;
} data_point_t;


//  Meter Device Details
typedef struct
{
    const char *media;
    const char *meter;
    const char *deviceId;
    const char *unit;

    data_point_t *data_points;
    size_t data_point_count;

} device_reading_t;


//  All Device Measurements
typedef struct
{
    size_t device_count;
    device_reading_t *readings;
} values_t;


// Gateway Information
typedef struct
{
    const char *gatewayId;
    const char *date;
    const char *deviceType;
    int interval_minutes;
    int total_readings;

    values_t values;

} gateway_data_t;


// API Function 
int serialize_to_json(
    const gateway_data_t *data,
    char *output_buffer,
    size_t buffer_size
);

#endif 
