#include "json_serializer.h"
#include <stdio.h>

int serialize_to_json(const gateway_data_t *data,
                      char *buffer,
                      size_t buffer_size)
{
    int len = 0;

    if (data == NULL || buffer == NULL)
        return -1;

    /* Start JSON array */
    len += snprintf(buffer + len, buffer_size - len, "[{");

    /* Gateway information */
    len += snprintf(buffer + len, buffer_size - len,
                    "\"gatewayId\":\"%s\",", data->gatewayId);
    len += snprintf(buffer + len, buffer_size - len,
                    "\"date\":\"%s\",", data->date);
    len += snprintf(buffer + len, buffer_size - len,
                    "\"deviceType\":\"%s\",", data->deviceType);
    len += snprintf(buffer + len, buffer_size - len,
                    "\"interval_minutes\":%d,", data->interval_minutes);
    len += snprintf(buffer + len, buffer_size - len,
                    "\"total_readings\":%d,", data->total_readings);

    /* Values section */
    len += snprintf(buffer + len, buffer_size - len,
                    "\"values\":{");
    len += snprintf(buffer + len, buffer_size - len,
                    "\"device_count\":%d,", (int)data->values.device_count);
    len += snprintf(buffer + len, buffer_size - len,
                    "\"readings\":[");

    /* Device loop */
    for (size_t i = 0; i < data->values.device_count; i++)
    {
        device_reading_t *dev = &data->values.readings[i];

        len += snprintf(buffer + len, buffer_size - len, "{");
        len += snprintf(buffer + len, buffer_size - len,
                        "\"media\":\"%s\",", dev->media);
        len += snprintf(buffer + len, buffer_size - len,
                        "\"meter\":\"%s\",", dev->meter);
        len += snprintf(buffer + len, buffer_size - len,
                        "\"deviceId\":\"%s\",", dev->deviceId);
        len += snprintf(buffer + len, buffer_size - len,
                        "\"unit\":\"%s\",", dev->unit);

        /* Data points */
        len += snprintf(buffer + len, buffer_size - len,
                        "\"data\":[");

        for (size_t j = 0; j < dev->data_point_count; j++)
        {
            data_point_t *dp = &dev->data_points[j];

            len += snprintf(buffer + len, buffer_size - len, "{");
            len += snprintf(buffer + len, buffer_size - len,
                            "\"timestamp\":\"%s\",", dp->timestamp);
            len += snprintf(buffer + len, buffer_size - len,
                            "\"meter_datetime\":\"%s\",", dp->meter_datetime);
            len += snprintf(buffer + len, buffer_size - len,
                            "\"total_m3\":%.3f,", dp->total_m3);
            len += snprintf(buffer + len, buffer_size - len,
                            "\"status\":\"%s\"", dp->status);
            len += snprintf(buffer + len, buffer_size - len, "}");

            if (j < dev->data_point_count - 1)
                len += snprintf(buffer + len, buffer_size - len, ",");
        }

        len += snprintf(buffer + len, buffer_size - len, "]}");

        if (i < data->values.device_count - 1)
            len += snprintf(buffer + len, buffer_size - len, ",");
    }

    /* Close JSON */
    len += snprintf(buffer + len, buffer_size - len, "]}");
    len += snprintf(buffer + len, buffer_size - len, "}]");

    if (len >= (int)buffer_size)
        return -2;

    return 0;
}
