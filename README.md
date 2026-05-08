# ESP8266 Gemini AI Client (Hexagonal Architecture)

A robust, decoupled implementation of the Google Gemini LLM API for the ESP8266 microcontroller. This project utilizes **Hexagonal Architecture (Ports and Adapters)** to ensure that the core AI logic remains independent of hardware-specific libraries and external dependencies.

## 🚀 Features
* **Clean Architecture:** Core logic is separated from WiFi and JSON handling via dependency injection.
* **Real-time Interaction:** Use the Arduino Serial Monitor to chat with Google Gemini.
* **Memory Optimized:** Designed with the ESP8266's RAM constraints in mind.
* **Easy Portability:** Swap the `ApiGateway` adapter to move from ESP8266 to ESP32 without touching the core AI logic.

## 🏗️ Architecture Overview

The project follows the **Ports and Adapters** pattern:
* **Core (`ESP8266AIGemini`):** The "Brain." It doesn't know about WiFi; it only knows how to build requests.
* **Adapters:**
    * `ApiGatewayESP8266`: Handles the physical HTTPS requests.
    * `GeminiJsonParser`: Handles the extraction of text from the Google API response.
    * `GeminiValidator`: Validates inputs and API keys.

## 🛠️ Requirements
* **Hardware:** ESP8266 (NodeMCU, Wemos D1 Mini, etc.)
* **API Key:** Get one for free at [Google AI Studio](https://ai.google.dev/)
* **Libraries:** * `ESP8266WiFi` (Standard)
    * `ArduinoJson` (Used internally by the parser)

## ⚙️ Setup
1. Clone this repository.
2. Open `ESP8266_Gemini_AI.ino` in the Arduino IDE.
3. Replace the placeholders in the config section:
   ```cpp
   const char* WIFI_SSID      = "YOUR_WIFI_SSID";
   const char* WIFI_PASS      = "YOUR_WIFI_PASSWORD";
   const char* GEMINI_API_KEY = "YOUR_API_KEY";

Set your Serial Monitor to 115200 Baud.

Upload and start chatting!

⚠️ Important Notes
SSL/TLS: Ensure your ApiGateway is configured to handle HTTPS, as Google's API requires a secure connection.

Memory: Large responses from the LLM can exceed the ESP8266's heap memory. For production use, consider streaming the response
