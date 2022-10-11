#define btn_pin 3
#define led_pin 11
#define click_time 50
#define pressed_time 500
#define button_delay 400

long timer = 0;
long last_click = 0;
int counter = 0;
int prev = 0;
bool state_led;
int brightness = 255;
bool way_brightness = false;

void setup()
{
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  state_led = false;
}

void loop()
{
  int value = !digitalRead(btn_pin);
  
  if (state_led && value && millis() - timer > pressed_time)
  {
      Serial.println(brightness);
      analogWrite(led_pin, state_led ? brightness : LOW);
      brightness = way_brightness ? brightness + 1 : brightness - 1;
      if (brightness == 0 || brightness == 255) { way_brightness = !way_brightness; }
      delay(3);
  }

  if (prev && !value && (millis() - timer > click_time) && (millis() - timer < pressed_time))
    {
      Serial.println("<click>");
      state_led = !state_led;
      analogWrite(led_pin, state_led ? 255 : LOW);
     delay(button_delay);
    }  

  if (value != prev)
  {
    timer = millis();
    delay(15);
  }
  
  prev = value;
}