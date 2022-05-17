
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
 
//ESP Web Server Library to host a web page
#include <ESP8266WebServer.h>

#define LED 2  
#define Hdr 0

const String Solenoide = "4,";
const String Hidromassagem = "5,";
const String Jardim_Arecas = "6,";
const String AreaGourmet_Luz1 = "7,";

String Solenoide_estado = "ON";
String Hidro_estado = "ON";
String Arecas_estado = "ON";
String AGLuz1_estado = "ON";

String cont = "i";

unsigned long Tempo;
unsigned long Tempo2 = millis();

String Conteudo = "";

String LeConteudo() {  //LE SERIAL DO PC FUNÇÃO

char caracter;
while(Serial.available()){
  caracter = Serial.read()  ;
  Conteudo.concat(caracter) ;
  Tempo = millis()          ;  }
  return Conteudo           ;
}


void pisca(int times,int dly){
  for(int i = 0;i < times;i++){
    digitalWrite(LED,LOW);
    delay(dly);
    digitalWrite(LED,HIGH);
    delay(dly);
    }
  }
//---------------------------------------------------------------

String render_Main(String Sln_st,String Hdr_st,String Arc_st,String AGLuz1_st){
  return "<!DOCTYPE html> <html> <header> <link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css\"> <link rel=\"stylesheet\" href=\"https://www.w3schools.com/w3css/4/w3.css\"> <meta charset=\"UTF-8\"> <style> .mybtn{width:200px; height:35px; margin-top:12px; } .sector{ background-color:#f6f6f6; border-radius:30px; height:500px; margin-top:50px; margin-left:40px; padding-left:40px; margin-right:40px; padding-right:40px; } </style> </header> <body> <div class=\"row\"> <div class= \"col-sm-6\"> <div class=\"sector\"> <center> <h1>Jardim e Piscina</h1><br> </center> <center><h3>Irrigação</h3></center> <div class=\"row\"> <div class=\"col-sm-6\"> <a class=\"btn btn-primary mybtn\" href=\"solenoid_on\" >Liga</a><br> <a class=\"btn btn-dark mybtn\" href=\"solenoid_off\" >Desliga</a><br> </div> <div class=\"col-sm-6\"> Estado: "+Sln_st+" </div> </div> <hr> <center><h3>Hidromassagem</h3></center> <div class=\"row\"> <div class=\"col-sm-6\"> <a class=\"btn btn-primary mybtn\" href=\"hidro_on\" >Liga</a><br> <a class=\"btn btn-dark mybtn\" href=\"hidro_off\" >Desliga</a><br> </div> <div class=\"col-sm-6\"> Estado: "+Hdr_st+" </div> </div> </div> </div> <div class= \"col-sm-6\"> <div class=\"sector\"> <center> <h1>Area Gourmet</h1><br> </center> <center><h3>Arecas</h3></center> <div class=\"row\"> <div class=\"col-sm-6\"> <a class=\"btn btn-primary mybtn\" href=\"arecas_on\" >Liga</a><br> <a class=\"btn btn-dark mybtn\" href=\"arecas_off\" >Desliga</a><br> </div> <div class=\"col-sm-6\"> Estado: "+Arc_st+" </div> </div> <hr> <center><h3>Bancada</h3></center> <div class=\"row\"> <div class=\"col-sm-6\"> <a class=\"btn btn-primary mybtn\" href=\"AGLuz1_on\" >Liga</a><br> <a class=\"btn btn-dark mybtn\" href=\"AGLuz1_off\" >Desliga</a><br> </div> <div class=\"col-sm-6\"> Estado: "+AGLuz1_st+" </div> </div> </div> </div> </div> </body> </html>";
 }


//---------------------------------------------------------------






//SSID and Password of your WiFi router
const char* ssid = "TP-LINK_4914";
const char* password = "52349812";
 
//Declare a global object variable from the ESP8266WebServer class.
ESP8266WebServer server(80); //Server on port 80
 
//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String MAIN_page = render_Main(Solenoide_estado,Hidro_estado,Arecas_estado,AGLuz1_estado);
 server.send(200, "text/html", MAIN_page); //Send web page
}
 
void handleSLDoff() { 
 digitalWrite(LED,LOW); 
 Solenoide_estado = "OFF";
 Serial.println(Solenoide+"OFF");
 
 String MAIN_page = render_Main(Solenoide_estado,Hidro_estado,Arecas_estado,AGLuz1_estado);
 server.send(200, "text/html",MAIN_page); 
}
 
void handleSLDon() { 
 Solenoide_estado = "ON";
 digitalWrite(LED,HIGH); 
 Serial.println(Solenoide+"ON");
 String MAIN_page = render_Main(Solenoide_estado,Hidro_estado,Arecas_estado,AGLuz1_estado);
 server.send(200, "text/html",MAIN_page); 
}

void handleHidroOn() { 
 Hidro_estado = "ON";
 digitalWrite(Hdr,HIGH); 
 Serial.println(Hidromassagem+"ON");

 String MAIN_page = render_Main(Solenoide_estado,Hidro_estado,Arecas_estado,AGLuz1_estado);
 server.send(200, "text/html",MAIN_page); 
}

void handleHidroOff() { 
 Hidro_estado = "OFF";
 digitalWrite(Hdr,LOW); 
 Serial.println(Hidromassagem+"OFF");
 
 String MAIN_page = render_Main(Solenoide_estado,Hidro_estado,Arecas_estado,AGLuz1_estado);
 server.send(200, "text/html",MAIN_page); 
}

void handleArecasOn() { 
 Arecas_estado = "ON";
 digitalWrite(Hdr,HIGH); 
 Serial.println(Jardim_Arecas+"ON");
 
 String MAIN_page = render_Main(Solenoide_estado,Hidro_estado,Arecas_estado,AGLuz1_estado);
 server.send(200, "text/html",MAIN_page); 
}

void handleArecasOff() { 
 Arecas_estado = "OFF";
 digitalWrite(Hdr,LOW); 
 Serial.println(Jardim_Arecas+"OFF");
 
 String MAIN_page = render_Main(Solenoide_estado,Hidro_estado,Arecas_estado,AGLuz1_estado);
 server.send(200, "text/html",MAIN_page); 
}

void handleAGLuz1On() { 
 AGLuz1_estado = "ON";
 digitalWrite(Hdr,HIGH); 
 Serial.println(AreaGourmet_Luz1+"ON");
 
 String MAIN_page = render_Main(Solenoide_estado,Hidro_estado,Arecas_estado,AGLuz1_estado);
 server.send(200, "text/html",MAIN_page); 
}

void handleAGLuz1Off() { 
 AGLuz1_estado = "OFF";
 digitalWrite(Hdr,LOW); 
 Serial.println(AreaGourmet_Luz1+"OFF");
 
 String MAIN_page = render_Main(Solenoide_estado,Hidro_estado,Arecas_estado,AGLuz1_estado);
 server.send(200, "text/html",MAIN_page); 
}
//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  Serial.begin(9600);
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
 
  //Onboard LED port Direction output
  pinMode(LED,OUTPUT); 
  pinMode(Hdr,OUTPUT);

  digitalWrite(LED,HIGH);
  digitalWrite(Hdr,HIGH);
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/solenoid_on", handleSLDon); //as Per  <a href="ledOn">, Subroutine to be called
  server.on("/solenoid_off", handleSLDoff);
  server.on("/hidro_off", handleHidroOff);
  server.on("/hidro_on", handleHidroOn);
  server.on("/arecas_on",handleArecasOn);
  server.on("/arecas_off",handleArecasOff);
  server.on("/AGLuz1_on",handleAGLuz1On);
  server.on("/AGLuz1_off",handleAGLuz1Off);
  
 
  server.begin();                  //Start server
  
  pisca(4,150);
  pisca(7,50);
  Serial.print("Server Online");
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
Conteudo = LeConteudo();
if((Conteudo != "") && ((millis() - Tempo)> 2)){      //INICIA
  Serial.println(Conteudo);
  Conteudo = "";
  Tempo = millis();
}                                                     //FINALIZA

  server.handleClient();          //Handle client requests
}
