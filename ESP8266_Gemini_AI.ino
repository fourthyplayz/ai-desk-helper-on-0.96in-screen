/**
 * ESP8266 Gemini AI Client
 * Architecture: Hexagonal (Ports and Adapters)
 * Description: Communicates with Google Gemini API using a decoupled structure.
 */

#include <ESP8266WiFi.h>
#include "ESP8266AIGemini.h"
#include "GeminiValidator.h" 
#include "ApiGatewayESP8266.h"
#include "GeminiJsonParser.h"

// --- Configuration ---
const char* WIFI_SSID      = "YOUR_WIFI_SSID";
const char* WIFI_PASS      = "YOUR_WIFI_PASSWORD";
const char* GEMINI_API_KEY = "YOUR_GEMINI_API_KEY";

// --- Domain & Infrastructure Setup ---
GeminiValidator realValidator; 
ApiGatewayESP8266 apiGateway;
GeminiJsonParser jsonParser;

// Dependency Injection: Injecting adapters into the core logic
ESP8266AIGemini gemini(GEMINI_API_KEY, 
                     &realValidator, 
                     &apiGateway, 
                     &jsonParser);

String userPrompt = "";

void setup() {
    Serial.begin(115200);
    delay(100);
    
    Serial.println("\n--- Starting ESP8266 Gemini AI (Hexagonal Architecture) ---");

    // Connect to WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("\nConnected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    Serial.println("\n=======================================");
    Serial.println("Ready! Type your question and press Enter:");
    Serial.println("=======================================");
    Serial.print("Your question >> ");
}

void loop() {
    while (Serial.available()) {
        char incomingChar = Serial.read();

        // Check for Newline or Carriage Return (Enter key)
        if (incomingChar == '\n' || incomingChar == '\r') {
            
            if (userPrompt.length() > 0) {
                userPrompt.trim(); 
                
                Serial.println("\n-> Sending prompt to Gemini...");
                Serial.print("Final Prompt: ");
                Serial.println(userPrompt);

                // Execute the core AI logic
                String response = gemini.generateContent(userPrompt);

                Serial.println("<- Gemini Response:");
                Serial.println("---------------------------------------");
                Serial.println(response);
                Serial.println("---------------------------------------");
                
                // Clear the buffer and prepare for next input
                userPrompt = "";
                Serial.println("\n=======================================");
                Serial.println("Response complete! Ask another question:");
                Serial.println("=======================================");
                Serial.print("Your question >> ");
            }
        } else {
            userPrompt += incomingChar;
        }
    }

    // Small delay to ensure the WiFi stack stays stable
    delay(10);
}
