// Wire the components as per the accompanying circuit diagram.
// Turn on your serial monitor after you have uploaded the code to see the effect of this code.

unsigned long lastPeriodStart;
const int onDuration=1000;
const int periodDuration=2000;
const int buzzerPin = 9;    // connect the buzzer to pin 9
const int songLength = 4;  // sets the number of notes of the song

// Notes is an array of text characters corresponding to the notes
// in your song. A space represents a rest (no tone)

char notes[songLength] = {'c', ' ', 'c', 'a'}; 

// beats[] is an array of values for each note. A "1" represents a quarter-note, 
// "2" a half-note, and "4" a quarter-note.
// Don't forget that the rests (spaces) need a length as well.

int beats[songLength] = {1, 1,1,4 };

int tempo = 113;  // The tempo is how fast to play the song (beats per second).
int buttonPinA = 3; // Button A to Arduino Pin (Digital)
int buttonPinB = 2; // Button B to Arduino Pin (Digital)
int potPin = A0; // Potentiometer to Arduino Pin (Analog)

const int RED_PIN = 8;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;





int buttonAVal = 1; // set button A value to 1;
int buttonBVal = 1; // set button B value to 1;
int oldButtonAVal = 1; // set old button A value to 1;
int oldButtonBVal = 1; // set old button B value to 1;
int potVal = 0; // set potentiometer value to 0;

long minTime = 5000; // minimum timer time in milliseconds
long maxTime = 10000; // maximum timer time in milliseconds
long timeCheck = 0; // time stamp variable, value set to arbitrary zero
long timerTime = 0; // timer timer, value set to arbitrary zero

boolean timing = false; // is it timing? true or false value

void setup() {
   if (buttonBVal != oldButtonBVal && buttonBVal == 1) { // this statement literally reads: "if button B's current value is not equal to button B's old value, and, button B's value is 1". Essentially, it detects a "click event", when the user presses the button and releases it.
      timing = false; // stop timing and set timing value to false
    }
  pinMode(buttonPinA, INPUT_PULLUP); // rather than use "INPUT" we will use "INPUT_PULLUP" which makes use of the internal resistors in the Arduino board. This removes the need for pullup resistors connected to the button. See accompanying circuit diagram.
  pinMode(buttonPinB, INPUT_PULLUP); // One thing to note about INPUT_PULLUP: HIGH or 1 = button not pressed, LOW or 0 = button pressed.
  Serial.begin(9600); // begin the serial monitor for debugging purposes
 
  //lights
  pinMode(7, OUTPUT); // light 2min,  water
  pinMode(6, OUTPUT); // light 3min, light
  pinMode(5, OUTPUT); // light 4min, medium
  pinMode(4, OUTPUT); // light 5min, dark

  //RGB
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  //buzzer
  pinMode(buzzerPin, OUTPUT);  // sets the  buzzer pin as an OUTPUT
}

void loop() {

  buttonAVal = digitalRead(buttonPinA); // read new button A value
  buttonBVal = digitalRead(buttonPinB); // read new button B value
  timerTime = map(potVal, 0, 1023, minTime, maxTime);

  // lights are on to indicate coffee brew setting
  if (timerTime > 6000 & timerTime < 7000){
      digitalWrite(7,HIGH);
      digitalWrite(6,LOW);
      digitalWrite(5, LOW);
      digitalWrite(4,LOW);
      
      
   
     
    }
     if (timerTime > 7000 & timerTime < 8000){
      digitalWrite(7,HIGH);
      digitalWrite(6,HIGH);
      digitalWrite(5, LOW);
      digitalWrite(4,LOW);
      
       
    }
      if (timerTime > 8000 & timerTime < 9000){
       digitalWrite(7,HIGH);
      digitalWrite(6,HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(4,LOW);
      
       
    }
      if (timerTime > 9000){
       digitalWrite(7,HIGH);
      digitalWrite(6,HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(4,HIGH);
      
      
    }  

  if (timing) {
      //light is red
     digitalWrite(RED_PIN, HIGH);
     digitalWrite(GREEN_PIN, LOW);
     digitalWrite(BLUE_PIN, LOW);
     
     
         // Red, Green, Blue, Yellow, Cyan, Purple, White
     if (buttonBVal != oldButtonBVal && buttonBVal == 1) { // this statement literally reads: "if button B's current value is not equal to button B's old value, and, button B's value is 1". Essentially, it detects a "click event", when the user presses the button and releases it.
      timing = false; // stop timing and set timing value to false
    }
    //when timer is timing
    long delta = millis() - timeCheck; // time difference between time elapsed and timeCheck. This gives you the amount of time since the timer started
     //make timer end
     if( buttonBVal == 0){
      delta = timerTime +1;
      }
    if (delta < timerTime) { // if time is not up

      // YOUR CODE FOR INDICATING TIME ELAPSED HERE

      Serial.print("time elapsed: ");
      Serial.print(delta); // print time elapsed
      Serial.print("  |  time left: ");
      Serial.print(timerTime - delta); // print time left
      Serial.println(); // print a line break;
    }
    else { // if time is up
            //light is green for ready!
           digitalWrite(RED_PIN, LOW);
           digitalWrite(GREEN_PIN, HIGH);
           digitalWrite(BLUE_PIN, LOW);

            digitalWrite(7,LOW);
            digitalWrite(6,LOW);
            digitalWrite(5, LOW);
            digitalWrite(4,LOW);
           
          //tone(9, 500);
          if (millis()-lastPeriodStart>=periodDuration)
  {
    lastPeriodStart+=periodDuration;
    tone(9,550, onDuration); // play 550 Hz tone in background for 'onDuration'
  }
          
            
      // YOUR CODE FOR TIME'S UP HERE
  if (buttonBVal != oldButtonBVal && buttonBVal == 1) { // this statement literally reads: "if button B's current value is not equal to button B's old value, and, button B's value is 1". Essentially, it detects a "click event", when the user presses the button and releases it.
      timing = false; // stop timing and set timing value to false
    }
      Serial.println("TIME IS UP!");
    }

   
  }
  else {
    //when timer is not timing
           noTone(9);
           digitalWrite(RED_PIN, LOW);
           digitalWrite(GREEN_PIN, LOW);
           digitalWrite(BLUE_PIN, LOW);

    // YOUR CODE FOR WAITING HERE
    
    potVal = analogRead(potPin); // read the potentiometer value
   ; // maps the pot value to the time between minimum and maximum
    Serial.print("...waiting... ");
    Serial.print("potVal: ");
    Serial.print(potVal);
    Serial.print("  |  mapped time: ");
    Serial.print(timerTime);
    Serial.println();
    if (buttonAVal != oldButtonAVal && buttonAVal == 1) { // this statement literally reads: "if button A's current value is not equal to button A's old value, and, button A's value is 1". Essentially, it detects a "click event", when the user presses the button and releases it.
      timeCheck = millis(); // store the time since the start of the arduino sketch
      timing = true;
    }
  }

  oldButtonAVal = buttonAVal; // set old button A value to current button A value
  oldButtonBVal = buttonBVal; // set old button B value to current button B value

  //delay(50); //just a short delay. This is just to make the Serial monitor more readable
}



void mainColors()
{
  
  // Red
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
   delay(1000);
   digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, HIGH);
   
  
}
void showSpectrum()
{
  for (int x = 0; x <= 767; x++)
  {
    RGB(x);      // Increment x and call RGB() to progress through colors.
    delay(10);   // Delay for 10 ms (1/100th of a second) - to help the "smoothing"
  }
}

/******************************************************************
 * void RGB(int color)
 * 
 * RGB(###) displays a single color on the RGB LED.
 * Call RGB(###) with the number of a color you want
 * to display. For example, RGB(0) displays pure RED, RGB(255) 
 * displays pure green.
 * 
 * This function translates a number between 0 and 767 into a
 * specific color on the RGB LED. If you have this number count
 * through the whole range (0 to 767), the LED will smoothly
 * change color through the entire spectrum.
 * 
 * The "base" numbers are:
 * 0   = pure red
 * 255 = pure green
 * 511 = pure blue
 * 767 = pure red (again)
 * 
 * Numbers between the above colors will create blends. For
 * example, 640 is midway between 512 (pure blue) and 767
 * (pure red). It will give you a 50/50 mix of blue and red,
 * resulting in purple.
/*****************************************************************/
void RGB(int color)
{
  int redIntensity;
  int greenIntensity;
  int blueIntensity;

  color = constrain(color, 0, 767); // constrain the input value to a range of values from 0 to 767

    // if statement breaks down the "color" into three ranges:
  if (color <= 255)       // RANGE 1 (0 - 255) - red to green
  {
    redIntensity = 255 - color;    // red goes from on to off
    greenIntensity = color;        // green goes from off to on
    blueIntensity = 0;             // blue is always off
  }
  else if (color <= 511)  // RANGE 2 (256 - 511) - green to blue
  {
    redIntensity = 0;                     // red is always off
    greenIntensity = 511 - color;         // green on to off
    blueIntensity = color - 256;          // blue off to on
  }
  else                    // RANGE 3 ( >= 512)- blue to red
  {
    redIntensity = color - 512;         // red off to on
    greenIntensity = 0;                 // green is always off
    blueIntensity = 767 - color;        // blue on to off
  }

  // "send" intensity values to the Red, Green, Blue Pins using analogWrite()
  analogWrite(RED_PIN, redIntensity);
  analogWrite(GREEN_PIN, greenIntensity);
  analogWrite(BLUE_PIN, blueIntensity);
}


int frequency(char note) 
{
  int i;
  const int numNotes = 8;  // number of notes we're storing
  char names[numNotes] = { 
    'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'    };
  int frequencies[numNotes] = {
    262, 294, 330, 349, 392, 440, 494, 523    };

  // Now we'll search through the letters in the array, and if
  // we find it, we'll return the frequency for that note.

  for (i = 0; i < numNotes; i++)  // Step through the notes
  {
    if (names[i] == note)         // Is this the one?
    {
      return(frequencies[i]);     // Yes! Return the frequency and exit function.
    }
  }
  return(0);  // We looked through everything and didn't find it,
  // but we still need to return a value, so return 0.
}
