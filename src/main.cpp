#include <Arduino.h>

// Gebruik #define of const voor fixed values
//gebruik juiste pin benamingen!!!
//gebruik functies!!!
//gebruik juiste datatypes!!!
// Duidelijke en voldoende hoeveelheid Comments toevoegen!!!!


#define DEBOUNCE_DELAY 50 // Debounce-tijd in ms

void display_counter(uint8_t counter);
void button_state();
void vehicle_passed();
void init_pins();


int main(void){
  //main() conform ontwerp
  init_pins();
  display_counter(10);
  return 0;
}


void display_counter(uint8_t counter){
  //functie display_counter() met juiste oneliner om aantal gepasseerde voertuigen weer te geven.
  PORTC = counter;
}

void button_state(uint8_t currentButtonState) {
  static unsigned long lastDebounceTime = 0;
  static uint8_t buttonState = 1; // 1 staat voor knop losgelaten

  // Debounce 
  if (currentButtonState != buttonState) {
    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) { 
      buttonState = currentButtonState;

      // Doe iets wanneer de knop wordt losgelaten.
      if (buttonState == 1) {
        // hier de code om ledjes te gaan veranderen!!!
      }
    }
  }
  lastDebounceTime = millis();
}

bool vehicle_passed(void){
  //functie vehicle_passed() geeft de juiste boolean waarde
  return false;
}

// Initialiseert alle pinnen op arduino
void init_pins(){
  DDRC = 0x0F;             // Stel de eerste vier pinnen van Port C in als output
  DDRD &= ~(1 << PD2);     // Stel Pin D2 in als input
  PORTD |= (1 << PORTD2);  // Zet de interne pull-up weerstand van Pin D2 aan

}