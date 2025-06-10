#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

// Definir pines para SPI
#define SD_MOSI 11
#define SD_MISO 12
#define SD_SCK 13
#define SD_CS 4

void listFiles(File dir, int numTabs);

void setup() {
    Serial.begin(115200);
    
    // Configurar bus SPI
    SPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
    
    if (!SD.begin(SD_CS)) {
        Serial.println("Error al inicializar la tarjeta SD");
        return;
    }
    Serial.println("Tarjeta SD inicializada correctamente");
    
    File root = SD.open("/");
    Serial.println("Contenido de la tarjeta SD:");
    listFiles(root, 0);
}

void loop() {
    // No es necesario código en loop para solo listar archivos
}

void listFiles(File dir, int numTabs) {
    while (true) {
        File entry = dir.openNextFile();
        if (!entry) {
            break;
        }
        for (int i = 0; i < numTabs; i++) {
            Serial.print("\t");
        }
        Serial.print(entry.name());
        if (entry.isDirectory()) {
            Serial.println("/");
            listFiles(entry, numTabs + 1);
        } else {
            Serial.print(" \tTamaño: ");
            Serial.println(entry.size());
        }
        entry.close();
    }
}