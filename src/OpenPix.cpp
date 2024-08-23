#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "OpenPix.h"

#define host "https://api.openpix.com.br/api/v1"

OpenPix::OpenPix(char *appID, char *rootCA)
{
    _openPixAppID = appID;
    _rootCA = rootCA;
}

String OpenPix::generateUniqueID()
{
    String macAddress = String(ESP.getEfuseMac(), HEX);
    macAddress.toUpperCase();
    String uniqueID = macAddress + "-" + String(millis());
    return uniqueID;
}

String OpenPix::pixCreateChargeInsecure(int value)
{
    HTTPClient http;

    // Cria o objeto JSON
    JsonDocument doc;
    doc["correlationID"] = generateUniqueID();
    doc["value"] = value; // Valor em centavos

    // Serializa o objeto JSON para uma string
    String payload;
    serializeJson(doc, payload);

    http.begin(String(host) + "/charge");
    http.addHeader("Authorization", String(_openPixAppID));
    http.addHeader("Accept", "application/json");
    http.addHeader("Content-Type", "application/json");
    http.addHeader("User-Agent", "ESP32");

    int httpCode = http.POST(payload);

    String response = http.getString();
    http.end();

    return String(response);
}

String OpenPix::pixPaymentStatusInsecure(String correlationID)
{
    HTTPClient http;

    http.begin(String(host) + "/charge/" + correlationID);
    http.addHeader("Authorization", String(_openPixAppID));
    http.addHeader("Accept", "application/json");
    http.addHeader("Content-Type", "application/json");
    http.addHeader("User-Agent", "ESP32");

    int httpCode = http.GET();
    String payload = http.getString();
    http.end();

    return String(payload);
}
