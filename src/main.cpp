#include <Arduino.h>
#include <IRremote.hpp>

// Definování makra pro použití AVR timeru a pinu pro IR přijímač
#define IR_USE_AVR_TIMER 1
#define IR_RECEIVE_PIN 12
#define ENTER_CODE 4127850240 // Kód klávesy ENTER

// Definování pinů pro LED diody
#define RED_LED_PIN 6
#define GREEN_LED_PIN 5
#define BLUE_LED_PIN 9

// Pole kódů pro jednotlivé klávesy
const unsigned long irCodes[] = {
    3910598400, // 0
    4077715200, // 1
    3877175040, // 2
    2707357440, // 3
    4144561920, // 4
    3810328320, // 5
    2774204160, // 6
    3175284480, // 7
    2907897600, // 8
    3041591040, // 9
};

// Proměnná pro ukládání zadaného čísla jako řetězec
String inputNumber = "";
int activeLED = 0; // Proměnná pro sledování aktuální LED diody

// Velikost pole kódů
const int irCodesSize = sizeof(irCodes) / sizeof(irCodes[0]);

// Funkce pro převod IR kódu na číslo
String decodeIRCode(unsigned long irData) {
    for (int i = 0; i < irCodesSize; i++) {
        if (irData == irCodes[i]) {
            return String(i); // Návrat čísla jako řetězec
        }
    }
    return ""; // Pokud kód není nalezen, vrátí prázdný řetězec
}

// Funkce pro nastavení hodnoty LED diody
void adjustLED(int brightness) {
    switch (activeLED) {
        case 0:
            Serial.print("Nastavuji Červenou LED: ");
            analogWrite(RED_LED_PIN, brightness);
            activeLED = 1; // Přepnutí na další LED
            break;
        case 1:
            Serial.print("Nastavuji Zelenou LED: ");
            analogWrite(GREEN_LED_PIN, brightness);
            activeLED = 2; // Přepnutí na další LED
            break;
        case 2:
            Serial.print("Nastavuji Modrou LED: ");
            analogWrite(BLUE_LED_PIN, brightness);
            activeLED = 0; // Přepnutí zpět na první LED
            break;
    }
    Serial.println(brightness); // Výpis nastavené hodnoty
}

// Inicializace systému
void setup() {
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Inicializace IR přijímače
    Serial.begin(9600); // Inicializace sériové komunikace

    // Nastavení pinů pro LED diody jako výstupní
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);

    Serial.println("Setup dokončen");
}

// Hlavní smyčka programu
void loop() {
    if (IrReceiver.decode()) { // Pokud je přijato IR data
        unsigned long irData = IrReceiver.decodedIRData.decodedRawData; // Dekódování přijatých dat
        if (irData > 0) {
            if (irData == ENTER_CODE) { // Pokud je stisknuto ENTER
                int numValue = inputNumber.toInt(); // Převod řetězce na celé číslo
                if (numValue >= 0 && numValue <= 255) { // Kontrola platnosti rozsahu
                    adjustLED(numValue); // Nastavení LED
                    Serial.print("Nastavená hodnota: ");
                    Serial.println(numValue);
                } else {
                    Serial.println("Mimo rozsah"); // Výpis chyby rozsahu
                }
                inputNumber = ""; // Resetování řetězce
            } else {
                inputNumber += decodeIRCode(irData); // Přidání čísla do řetězce
                String ledColor = activeLED == 0 ? "Červená" :
                                  activeLED == 1 ? "Zelená" :
                                  "Modrá"; // Výběr názvu LED podle aktuálního stavu
                Serial.print("LED: ");
                Serial.print(ledColor);
                Serial.print(" Aktuální číslo: ");
                Serial.println(inputNumber);
            }
        }
        IrReceiver.resume(); // Obnovení přijímače pro další příjem dat
    }
}
