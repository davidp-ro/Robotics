#define pwm_r 11 //Pin turatie motoare dreapta
#define fwd_r 13 //HIGH -> Merge in fata, celalalt pe LOW!
#define bkd_r 12 //HIGH -> Merge in spate, celalalt pe LOW!

#define pwm_l 10 //Pin turatie motoare stanga
#define fwd_l 8 //HIGH -> Merge in fata, celalalt pe LOW!
#define bkd_l 9 //HIGH -> Merge in spate, celalalt pe LOW!

#define wait_time_start 10000 //Cat sa se astepte la pornire

//Serial:
int state=0;
  
//****************************************************************************
//****************************************************************************
//****************************************************************************
//____________________________Diverse setari__________________________________
int timp_de_mers = 5000; //Cat sa mearga/comanda -- default: 5 sec
int putere = 255; // 1-min(100), 2-med(180), 3-max(255) -- default: max

void menu_setup(){
  delay(5000);
  
  Serial.println("Config:");
      //-----------Timp de mers:
      Serial.println("Timp de mers (0=1 sec, 9=10 sec:");
      delay(1000);
      if(Serial.available() > 0){
        state = Serial.read(); // Reads data
      }
      switch (state) {
        case '0':
          timp_de_mers = 1000;
          break;
        case '1':
          timp_de_mers = 2000;
          break;
        case '2':
          timp_de_mers = 3000;
          break;
        case '3':
          timp_de_mers = 4000;
          break;
        case '4':
          timp_de_mers = 5000;
          break;
        case '5':
          timp_de_mers = 6000;
          break;
        case '6':
          timp_de_mers = 7000;
          break;
        case '7':
          timp_de_mers = 8000;
          break;
        case '8':
          timp_de_mers = 9000;
          break;
        case '9':
          timp_de_mers = 10000;
          break;      
      }

     //-----------Turatii:
     Serial.println("Turatie (1=min, 2=med, 3=max):");
     delay(1000);
     if(Serial.available() > 0){
        state = Serial.read(); // Reads data
      }
     switch (state){
      case '1':
        putere = 100;
        break;
      case '2':
        putere = 180;
        break;
      case '3':
        putere = 255;
        break;
      }
     
     state = 0;
}
//****************************************************************************
//****************************************************************************
//****************************************************************************

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
void setup() {
  //Pini:
  pinMode(pwm_r, OUTPUT);
  pinMode(fwd_r, OUTPUT);
  pinMode(bkd_r, OUTPUT);
  pinMode(pwm_l, OUTPUT);
  pinMode(fwd_l, OUTPUT);
  pinMode(bkd_l, OUTPUT);

  //Serial:
  Serial.begin(9600);
  if(Serial.available() > 0){
        state = Serial.read(); // Reads data
     }

  //Setup:
  menu_setup(); 

  //Timp sa pregatesc roborul:
  //delay(wait_time_start);
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void mergiInFata(){ 
  //Turatii:
  analogWrite(pwm_r, putere);
  analogWrite(pwm_l, putere);

  //Miscarea in fata:
  digitalWrite(fwd_r, HIGH);
  digitalWrite(bkd_r, LOW);
  digitalWrite(fwd_l, HIGH);
  digitalWrite(bkd_l, LOW);
}

void mergiInSpate(){ 
  //Turatii:
  analogWrite(pwm_r, putere);
  analogWrite(pwm_l, putere);

  //Miscarea in spate:
  digitalWrite(fwd_r, LOW);
  digitalWrite(bkd_r, HIGH);
  digitalWrite(fwd_l, LOW);
  digitalWrite(bkd_l, HIGH);
}

void Stanga(){ 
  //Turatii:
  analogWrite(pwm_r, 255);
  analogWrite(pwm_l, 0);

  //Miscarea in fata:
  digitalWrite(fwd_r, HIGH);
  digitalWrite(bkd_r, LOW);
  digitalWrite(fwd_l, LOW);
  digitalWrite(bkd_l, LOW);
}

void Dreapta(){ 
  //Turatii:
  analogWrite(pwm_r, 0);
  analogWrite(pwm_l, 255);

  //Miscarea in fata:
  digitalWrite(fwd_r, LOW);
  digitalWrite(bkd_r, LOW);
  digitalWrite(fwd_l, HIGH);
  digitalWrite(bkd_l, LOW);
}


void Stop(){ 
  //Stop:
  digitalWrite(fwd_r, LOW);
  digitalWrite(bkd_r, LOW);
  digitalWrite(fwd_l, LOW);
  digitalWrite(bkd_l, LOW);
}


//--------------------------
//-----------LOOP-----------
//--------------------------
void loop() {  
  if(Serial.available() > 0){
        state = Serial.read(); // Reads data
     }
            
     //Miscare:
     if (state == 'f') {
      //Fata
      mergiInFata();
      Serial.println("^^^"); 
      delay(timp_de_mers);
      
      state = 0;
      Stop();
     }
     
     else if (state == 'b') {
      //Spate
      mergiInSpate();
      Serial.println("VVV");
      delay(timp_de_mers);
      
      state = 0;
      Stop();
     }
     
     else if (state == 's') {
      //Stanga
      Stanga();
      Serial.println("<<<"); 
      delay(1000);
      
      state = 0;
      Stop();
     }
     
     else if (state == 'd') {
      //Dreapta
      Dreapta();
      Serial.println(">>>");
      delay(1000);
      
      state = 0;
      Stop();
     } 
     
      
}
