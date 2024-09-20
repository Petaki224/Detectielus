#include <Arduino.h>

#define DEBOUNCE_DELAY 50 //debounce tijd in ms
unsigned long previousTime = 0;
uint8_t counter = 0;  //teller voor voertuigen

enum bstate { pressed, released };
enum bstate lastState = released;  //houdt de laatste status bij

//declareer functies die na de main() komen.
void display_counter(uint8_t counter);
enum bstate button_state(void);
bool vehicle_passed(void);
void init_pins();

int main(void) {
  init_pins();
  
  // Start de seriële communicatie
  Serial.begin(9600);  

  while (1) {
    // Check of auto is langsgereden/knop losgelaten
    if (vehicle_passed()) {
      counter++;  //verhoogt de teller
      if (counter > 15) {  // reset naar 0 bij overflow
        counter = 0;
      }
      display_counter(counter);  // laat de teller binair zien op ledjes
    }
  }

  return 0;  // door infinite loop kom je nooit bij deze return
}

// Functie om de teller te laten zien op de leds
void display_counter(uint8_t counter) {
  PORTC = (PORTC & 0xF0) | (counter & 0x0F);  // laat linker 4 bit op 0 zodat rechter 4 bit worden laten zien op leds.
}

// debounce en laat status van leds zien.
enum bstate button_state(void) {
  static enum bstate currentState = released;
  unsigned long currentTime = millis();
  
  //debounce logica
  if (currentTime - previousTime >= DEBOUNCE_DELAY) {
    if (!(PIND & (1 << PD2))) {  // Controleert of de knop ingedrukt (0) is
      currentState = pressed; 
    } else {
      currentState = released;
    }
    previousTime = currentTime;
  }
  return currentState;
}

//voertuig is gepasseerd? / knop losgelaten?
bool vehicle_passed(void) {
  enum bstate currentState = button_state();
  
  // Kijk of de knop van ingedrukt naar losgelaten is gegaan
  if (lastState == pressed && currentState == released) {
    lastState = currentState;  // Update de vorige status
    return true;  // Voertuig langs gekomen
  }

  lastState = currentState;  //update vorige status
  return false;  // Geen voertuig langs gekomen.
}

// Initialiseer de pinnen
void init_pins() {
  DDRC = 0x0F; //stel de eerste vier pinnen van Port C in als output (PC0-PC3)
  DDRD &= ~(1 << PD2); //stel Pin D2 in als input
  PORTD |= (1 << PD2); // zet de interne pull-up weerstand van Pin D2 aan
}
