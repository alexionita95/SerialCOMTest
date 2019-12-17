void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("Ready");
pinMode(9,OUTPUT);
}
int count=1;
String data;
void set(char val)
{
  val -='0';
  if(val!=0)
  digitalWrite(9,HIGH);
  else
   digitalWrite(9,LOW);
  
}
void loop() {
  while(Serial.available())
  {
    if(Serial.available() > 0)
    {
      char d = Serial.read();
      if(d != '\n')
      {
        data +=d;
      }
      else
      {
        if(data[0]=='c')
        {
          set(data[1]);
        }
        Serial.println(data);
        data = "";
      }
    }
  }
  // put your main code here, to run repeatedly:

}
