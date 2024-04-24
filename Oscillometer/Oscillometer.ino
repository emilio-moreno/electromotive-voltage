// To determine frequency of oscillations we'll
// first find the period by considering the
// time difference of an event that happens once every
// cycle: Voltage going from below a given bound_voltage
// to above it.

// bound_voltage must be selected so that the event
// described before happens once every cycle.
const float bound_voltage = 3;
const int pin = A0; // measuring pin
float V; // measured voltage

void setup() {
    Serial.begin(9600);
    pinMode(pin, INPUT);
}

bool above = false;
// An average can be taken of num_avg time differences.
int num_avg = 4;
// Period average.
float period_avg; // ms
void loop() {
  	
  	// Sum for average.
    float period_sum = 0; // ms
  
  	// Time of first voltage measurement above ground for past cycle.
  	float past_time_above = 0;
  	// And for current cycle.
  	float current_time_above;
  
  	int n = 0;
    while (n <= num_avg) {
      V = float(analogRead(pin)) * 5 / 1023; // measured voltage
      Serial.println(V);

      // Voltage crosses bound.
      if ((above != true) && (V > bound_voltage)) {
        above = true;

        // If past_time is zero, this is the first measurement above bound.
        // As there's no past time to compare it to, we simply define this
        // measurement as the first past_time on the while loop.
        if (past_time_above == 0) {
          past_time_above = millis();
        }
        
        else {
          current_time_above = millis();
          period_sum = period_sum + (current_time_above - past_time_above);
          past_time_above = current_time_above;
        }
      }

      // Voltage is now under bound.
      if (above && (V < bound_voltage)) {
        above = false;
        n ++;
      }
    }

    period_avg = period_sum / num_avg; // ms
	float frequency = 1000 / period_avg; // Hz
  	
    Serial.println(frequency);
}