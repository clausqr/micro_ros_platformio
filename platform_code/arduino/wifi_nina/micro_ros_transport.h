#include <SPI.h>
#include <WiFiNINA.h>
#include <WiFiUdp.h>

struct micro_ros_agent_locator {
    IPAddress address;
    int port;
};

static inline void set_microros_wifi_transports(char * ssid, char * pass, IPAddress agent_ip, uint16_t agent_port){

    // if ssid is empty, skip wifi configuration and reuse the current connection
    if (strlen(ssid) != 0) {
    while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
      delay(500);
    }
}
    
    static struct micro_ros_agent_locator locator;
    locator.address = agent_ip;
    locator.port = agent_port;

    rmw_uros_set_custom_transport(
        false,
        (void *) &locator,
        platformio_transport_open,
        platformio_transport_close,
        platformio_transport_write,
        platformio_transport_read
    );
}