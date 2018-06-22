volatile int state = LOW;   //Чтобы зуммер не пищал постоянно при включении ардуино
int val;
int lvl1 = analogRead(A1); //Указываем аналоговый пин к которому подключен микрофон
int Zpin = 13;    //Указываем пин к которому подключена пищалка  (зуммер)
int porog = 510;    //Указываем минимальный порог при котором будет включатся зуммер
int b;
int k1=millis();
int k2=millis();
int len=100;
int i=0;

void setup()  //Процедура setup
{
  Serial.begin(9600);
  pinMode(Zpin,OUTPUT);

}


void vkl()  //Процедура включения зуммера
  {
    tone(Zpin,500,300);
  }


void vykl() //Процедура выключения зуммера
  {
    noTone(Zpin);
  }

void vkl2() //Процедура выключения зуммера
  {
    if (k1-k2<500)
      if (len<1500)
        len = len + 100;
      else
        len=len;
    else
      len=100;
   tone(Zpin,len,1500);
   delay(1000);
   k2=millis();
  }


void loop()
  {
    lvl1 = analogRead(A1);  //Считываем сигнал
    k1=millis();
    if (lvl1<porog) //Включаем зиммер, если сигнал полученный с микрофона ниже допустимого
        vkl2();
    
    if (Serial.available())
      {
        val = Serial.read();
        //переменная val принимается из консоли, например на телефоне через bluetooth
        // При символе отлисном от 0  включаем звук на частоте val
        // При символе "0" выключаем светодиод
        if ( val == '0')
            vykl();
        if ( val == '1')
            vkl();
       }
    //Продолжение работы зуммера до ввода "0"
    if (val=='1')
      {
        vkl();
      }
   }

