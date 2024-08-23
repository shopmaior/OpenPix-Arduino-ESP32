# OpenPix-Arduino-ESP32
This library is a simple and efficient library for OpenPix (https://openpix.com.br) payment. This use the REST API of OpenPix to make payments.

## Installation
To install this library, you can use the Arduino Library Manager or download the library and import it to your Arduino IDE.

## Usage
To use this library, you need to include it in your sketch. You can do this by adding the following line at the beginning of your sketch:
```cpp
#include <OpenPix.h>
```

## Example
Here is an example of how to use this library:
```cpp
#include <ArduinoJson.h>
#include <OpenPix.h>

#define BUTTON_PIN 5

OpenPix Pix = OpenPix(OPENPIX_APPID);

void buttonsWatcher() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    String pixResponse = Pix.pixCreateChargeInsecure(198); // Create a charge of R$ 1.98

    if (pixResponse == "") {
      Serial.println("Error creating charge");
      return;
    }

    JsonDocument responseDoc;
    DeserializationError error = deserializeJson(responseDoc, pixResponse);
    if (error) {
      Serial.println("Error parsing JSON");
      return;
    }

    if (responseDoc.containsKey("errors")) {
      String errorMsg = responseDoc["errors"][0]["message"].as<String>();
      Serial.println("Error: " + errorMsg);
      return;
    }

    String correlationID = responseDoc["charge"]["correlationID"].as<String>();
    // String pixQRCode = responseDoc["charge"]["pixQRCode"].as<String>();

    Serial.println("Correlation ID: " + correlationID);
    // Serial.println("Pix QR Code: " + pixQRCode);
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  buttonsWatcher();
}
```
