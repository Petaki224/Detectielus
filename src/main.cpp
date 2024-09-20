#include <Arduino.h>

// Gebruik #define of const voor fixed values
//gebruik juiste pin benamingen!!!
//gebruik functies!!!
//gebruik juiste datatypes!!!
// Duidelijke en voldoende hoeveelheid Comments toevoegen!!!!

void display_counter();
void button_state();
void vehicle_passed();
void init_pins();


int main(void){
  //main() conform ontwerp
  init_pins();
  display_counter();

  return 0;
}


void display_counter(){
  //functie display_counter() met juiste oneliner om aantal gepasseerde voertuigen weer te geven.
  PORTC = 00001111;
}

void button_state(){
  //functie button_state() waarin debouncing wordt gedaan
}

void vehicle_passed(){
  //functie vehicle_passed() geeft de juiste boolean waarde
}

void init_pins(){
  //functie init_pins() initialiseert de pinnen juist
  DDRC = 00001111;
}