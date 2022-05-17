#include <SoftwareSerial.h>
SoftwareSerial serial(2, 3);



String ConteudoESP = ""; //RECEBE DO ESP8266
String Conteudo = "";    //ENVIA PARA O ESP8266
String Conteudo2;

unsigned long Tempo2;
unsigned long Tempo;
unsigned long Tempo3;

boolean SerialAv;
boolean Control;
boolean Control2;
boolean Reading = false;

void setup() {
  
Serial.begin(9600);   //SERIAL DO ARDUINO
serial.begin(9600);   //SERIAL DO ESP8266

pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);

digitalWrite(11,HIGH);
    delay(100);
    digitalWrite(11,LOW);
    delay(100);
}

void loop() {
  
Conteudo = LeConteudo();
ConteudoESP = LeESP();
/*
if(ConteudoESP == "Server Online"){
  Reading = true;
  }
if(Conteudo == "Server Online"){
  Reading = true;
  }
  */

/*
if((Conteudo != "") && ((millis() - Tempo) > 20)){
  Serial.println(Conteudo);
  Conteudo.trim();
  if(Conteudo == "Server Online"){
  Reading = true;
  Serial.print("Parsing Enabled");
  }
  
  if((Reading)&&(Conteudo.indexOf(",") > 0)){
  Cmd(Conteudo);
  }
  Conteudo = "";}
*/

if((ConteudoESP != "") && ((millis() - Tempo2) > 20)){
  ConteudoESP.trim();
  Pisca(4);
  if(ConteudoESP == "Server Online"){
  digitalWrite(7,HIGH);
  Reading = true;
  }
  
  if((Reading)&&(ConteudoESP.indexOf(",") > 0)){
  Cmd(ConteudoESP);
  }

  ConteudoESP = "";
}
/*
if((millis() - Tempo3) > 400){
  serial.println("10");
  Pisca(8);
  Tempo3 = millis();
}
*/
}

String LeConteudo() {  //LE SERIAL DO PC FUNÇÃO

char caracter;
while(Serial.available()){
  caracter = Serial.read();
  Conteudo.concat(caracter);
  Tempo = millis(); 
  Control = 1; }
  SerialAv = (Serial.available()) ;
  
  if((Conteudo != "") && (SerialAv == 0) && (Control == 1)){
  serial.print(Conteudo);
  Control = 0;
  }
 return Conteudo;
 }


String LeESP()   {     //LE ESP8266
  
  char caracter;
  while(serial.available()){
    
  caracter = serial.read();
  ConteudoESP.concat(caracter);
  Tempo2 = millis();  

  }
  
  return ConteudoESP;
}

void Pisca(int led){
  digitalWrite(led,HIGH);
  delay(50);
  digitalWrite(led,LOW);
  }

void npisca(String ct){
  for(int i = 0;i < ct.toInt();i++){
    digitalWrite(10,HIGH);
    delay(100);
    digitalWrite(10,LOW);
    delay(100);
    }
    delay(2000);
  }

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void Cmd(String input){
  input.trim();
  //Serial.println("EXECUTE: " + input);
  
  String port = getValue(input,',',0);
  String state = getValue(input,',',1);
  //Serial.print("Port: "+port+" State: "+state); 
  digitalWrite(port.toInt(),parseState(state));
  }
  
boolean parseState(String st){
  if(st == "ON"){return true;}
  if(st == "OFF"){return false;}}
