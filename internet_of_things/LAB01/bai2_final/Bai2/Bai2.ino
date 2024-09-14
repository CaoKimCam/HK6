// C++ code
//
int led[]={2,3,4};
// int input_led=3;
void setup()
{
  Serial.begin(115200);
  for (int i=0; i<3; i++)
  {
  	  pinMode(led[i], OUTPUT);
  }
  pinMode(A0, INPUT);
}

void loop()
{
  
  int t;
  int read_il=analogRead(A0);
  Serial.println(read_il);
  if (read_il<300)
  	t=1500;
  else if (read_il<700)
    t=500;
  else t = 200;
  for (int i=0; i<3; i++)
  {
  	high(led[i]);
    delay(t);
  }
  for (int i=0; i<3; i++)
  {
  	low(led[i]);
  }
  for (int i=3; i>=0; i--)
  {
  	high(led[i]);
    delay(t);
  }
  for (int i=0; i<3; i++)
  {
  	low(led[i]);
  }
  delay(300);
  
}

void high(int led){
	digitalWrite(led, HIGH);
}

void low(int led){
	digitalWrite(led, LOW);
}