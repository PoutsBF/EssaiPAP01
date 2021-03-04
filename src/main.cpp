#include <Arduino.h>

const int pasParTour = 200;        // change this to fit the number of steps per revolution

unsigned long tempoPas = 10;      // 10ms entre chaque pas

// initialize the stepper library

uint8_t brakeA = 8;
uint8_t enableA = 11;
uint8_t directionA = 13;

uint8_t enableB = 3;
uint8_t brakeB = 9;
uint8_t directionB = 12;

void setup() 
{
    Serial.begin(115200);

    // Configure les sorties freins et les active (état haut)
    pinMode(brakeA, OUTPUT); digitalWrite(brakeA, HIGH);
    pinMode(brakeB, OUTPUT); digitalWrite(brakeB, HIGH);

  // Configure des deux sorties de direction par défaut à 0
    pinMode(directionA, OUTPUT); digitalWrite(directionA, LOW);
    pinMode(directionB, OUTPUT); digitalWrite(directionB, LOW);

  // Configure les sorties "enable" pour valider le moteur PAP ou le laisser en roue libre
    pinMode(enableA, OUTPUT); digitalWrite(enableA, HIGH);
    pinMode(enableB, OUTPUT); digitalWrite(enableB, HIGH);

    Serial.println("début...");
}

void loop() 
{
    static unsigned long ptempoPas = 0;       // délai entre deux pas
    static unsigned long ptempoImpuls = 0;    // délai de maintien du contrôle
    static uint8_t active = 0;                  // indique si les sorties sont actives


// non fonctionnel : 
    if(active)
    {
        ptempoImpuls = millis();
        active = 0;
    } 
    else
    {
        if ((millis() - ptempoImpuls) > 5)   // pour débug, tempo de 5 ms
            {
                // met les freins
                digitalWrite(brakeA, HIGH);
                digitalWrite(brakeB, HIGH);
            }
    }

    if((millis() - ptempoPas) > tempoPas)
    {
        static uint8_t position = 0;

        ptempoPas = millis();
        active = 1;             // indique qu'on a activé la sortie, 
                                // et qu'il faudra remettre les freins

        switch (position)
        {
            case 0 :
            {
                // choisis la direction
                digitalWrite(directionA, LOW); digitalWrite(directionB, HIGH);
                // retire les freins
                digitalWrite(brakeA, LOW);         digitalWrite(brakeB, LOW);
            }
            break;
            case 1 :
            {
                // choisis la direction
                digitalWrite(directionA, HIGH); digitalWrite(directionB, HIGH);
                // retire les freins
                digitalWrite(brakeA, LOW);         digitalWrite(brakeB, LOW);
            } break;
            case 2 :
            {
                // choisis la direction
                digitalWrite(directionA, HIGH); digitalWrite(directionB, LOW);
                // retire les freins
                digitalWrite(brakeA, LOW);         digitalWrite(brakeB, LOW);

            } break;
            case 3 :
            {
                // choisis la direction
                digitalWrite(directionA, LOW); digitalWrite(directionB, LOW);
                // retire les freins
                digitalWrite(brakeA, LOW);         digitalWrite(brakeB, LOW);

            } break;
        }
        (position == 3) ? position = 0 : position++;
        Serial.print(position); Serial.print(" ");
    }
}