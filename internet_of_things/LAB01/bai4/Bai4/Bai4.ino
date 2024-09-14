// C++ code
//
int LED[]={2,3,4,5,6,7,8,9,10,11,12};//11(led0->led8)
int state=0;
void setup()
{
  
  for (int i=0; i<sizeof(LED); i++)
       {
         pinMode(LED[i], OUTPUT);
       }
  digitalWrite(LED[7], 0);  
}

void loop()
{
  //g f com a b 
  //e d com c dp
  
  //led6 led5 -- led4 led3
  //led2 led1 -- led0 led7
  
  
  //|	a	|
  //f		b
  //	g
  //e		c
  //|	d	|
  if (state==0){
    led_high(LED[8]);
  	number9();
    delay(1000);
    number8();
    delay(1000);
    number7();
    delay(1000);
    number6();
    delay(1000);
    number5();
    delay(1000);
    number4();
    delay(1000);
    number3();
    delay(1000);
    number2();
    delay(1000);
    number1();
    delay(1000);
    number0();
    delay(1000);
    state++;//xanh
    led_low(LED[8]);
  } else if (state==1){
    led_high(LED[9]);
  	number2();
    delay(1000);
    number1();
    delay(1000);
    number0();
    delay(1000);
    state++;
    led_low(LED[9]);
  } else{
    led_high(LED[10]);
    number6();
    delay(1000);
    number5();
    delay(1000);
    number4();
    delay(1000);
    number3();
    delay(1000);
    number2();
    delay(1000);
    number1();
    delay(1000);
    number0();
    delay(1000);
    state=0;
    led_low(LED[10]);
  }
  reload();
  
}
void number0()
{
  digitalWrite(LED[0], 1);
  digitalWrite(LED[1], 1);
  digitalWrite(LED[2], 1);
  digitalWrite(LED[3], 1);
  digitalWrite(LED[4], 1);
  digitalWrite(LED[5], 1);
  digitalWrite(LED[6], 0);
}
void number1()
{
  digitalWrite(LED[0], 1);
  digitalWrite(LED[1], 0);
  digitalWrite(LED[2], 0);
  digitalWrite(LED[3], 1);
  digitalWrite(LED[4], 0);
  digitalWrite(LED[5], 0);
  digitalWrite(LED[6], 0);
}
void number2()
{
  digitalWrite(LED[0], 0);
  digitalWrite(LED[1], 1);
  digitalWrite(LED[2], 1);
  digitalWrite(LED[3], 1);
  digitalWrite(LED[4], 1);
  digitalWrite(LED[5], 0);
  digitalWrite(LED[6], 1);
}
void number3()
{
  digitalWrite(LED[0], 1);
  digitalWrite(LED[1], 1);
  digitalWrite(LED[2], 0);
  digitalWrite(LED[3], 1);
  digitalWrite(LED[4], 1);
  digitalWrite(LED[5], 0);
  digitalWrite(LED[6], 1);
}
void number4()
{
  digitalWrite(LED[0], 1);
  digitalWrite(LED[1], 0);
  digitalWrite(LED[2], 0);
  digitalWrite(LED[3], 1);
  digitalWrite(LED[4], 0);
  digitalWrite(LED[5], 1);
  digitalWrite(LED[6], 1);
}
void number5()
{
  digitalWrite(LED[0], 1);
  digitalWrite(LED[1], 1);
  digitalWrite(LED[2], 0);
  digitalWrite(LED[3], 0);
  digitalWrite(LED[4], 1);
  digitalWrite(LED[5], 1);
  digitalWrite(LED[6], 1);
}
void number6()
{
  digitalWrite(LED[0], 1);
  digitalWrite(LED[1], 1);
  digitalWrite(LED[2], 1);
  digitalWrite(LED[3], 0);
  digitalWrite(LED[4], 1);
  digitalWrite(LED[5], 1);
  digitalWrite(LED[6], 1);
}
void number7()
{
  digitalWrite(LED[0], 1);
  digitalWrite(LED[1], 0);
  digitalWrite(LED[2], 0);
  digitalWrite(LED[3], 1);
  digitalWrite(LED[4], 1);
  digitalWrite(LED[5], 0);
  digitalWrite(LED[6], 0);
}
void number8()
{
  digitalWrite(LED[0], 1);
  digitalWrite(LED[1], 1);
  digitalWrite(LED[2], 1);
  digitalWrite(LED[3], 1);
  digitalWrite(LED[4], 1);
  digitalWrite(LED[5], 1);
  digitalWrite(LED[6], 1);
}
void number9()
{
  digitalWrite(LED[0], 1);
  digitalWrite(LED[1], 1);
  digitalWrite(LED[2], 0);
  digitalWrite(LED[3], 1);
  digitalWrite(LED[4], 1);
  digitalWrite(LED[5], 1);
  digitalWrite(LED[6], 1);
}
void reload()
{
  digitalWrite(LED[0], 0);
  digitalWrite(LED[1], 0);
  digitalWrite(LED[2], 0);
  digitalWrite(LED[3], 0);
  digitalWrite(LED[4], 0);
  digitalWrite(LED[5], 0);
  digitalWrite(LED[6], 0);
}
void led_high(int led)
{
  digitalWrite(led, HIGH);
}
void led_low(int led)
{
  digitalWrite(led, LOW);
}
