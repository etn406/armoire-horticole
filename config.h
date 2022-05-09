#ifndef ARMOIRE_HORTI_CONFIG_H
#define ARMOIRE_HORTI_CONFIG_H

// Nom du point d'accès et mot de passe pour y accéder
#define AH_WIFI_PORTAL_SSID "Armoire_horticole"
#define AH_WIFI_PORTAL_PASS "X5nsdQ7J"

// Pins des capteurs de température et d'humidité
#define AH_DHT1_PIN 13
#define AH_DHT2_PIN 12
#define AH_DHT3_PIN 14

// Intervalle entre chaque rafraichissement
// des capteurs de température et d'humidité
#define AH_SENSORS_REFRESH_INTERVAL 3000
#define AH_SENSORS_COUNT 3

// Pins des relais
#define AH_RELAYS_COUNT 4
#define AH_RELAY_1_PIN 0
#define AH_RELAY_2_PIN 1
#define AH_RELAY_3_PIN 2
#define AH_RELAY_4_PIN 3

// Bouton ON/OFF des LEDS
#define AH_BUTTON_ONOFF 16

// Temps d'affichage des informations WiFi
#define AH_DISPLAY_TIME_OF_WIFI_INFOS 10000

#endif