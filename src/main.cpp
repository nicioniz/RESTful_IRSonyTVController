extern "C" {
  #include "user_interface.h"
}
#ifndef _ARDUINO
#include <Arduino.h>
#define _ARDUINO
#endif

#include "mainPage.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "ESP8266WebServer.h"
#include <ESP8266mDNS.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRutils.h>
#include <EEPROM.h>

#define COMMAND unsigned int

#define DEBUG

#define IR_SEND_PIN 4
#define HTTP_PORT 80

#define MAX_RESTARTS_BEFORE_AP_MODE 3
//We save the tries counter in the last address of the eeprom
#define COUNTER_EEPROM_ADDRESS 511

#define STRING_IN_EEPROM_MAX_LENGTH 50
#define STA_SSID_POSITION 0
#define STA_PWD_POSITION 1

//At first boot it doesn't find anything in the eeprom, so it tries to connect to anything
char* staSsid;
char* staPwd;

IPAddress ip(192,168,1,200), gw(192,168,1,1), mask(255,255,255,0);

char apSsid[] = "Tv Remote";
char apPwd[] = "TV_REMOTE";

ESP8266WebServer server(HTTP_PORT);
IRsend irsend(IR_SEND_PIN);

String jsonCommandsList = "{\"commands\": [\"onoff\", \"0\", \"1\", \"2\", \"3\", \"4\", \"5\", \"6\", \"7\", \"8\", \"9\", \"volup\", \"voldown\", \"chup\", \"chdown\", \"mute\", \"input\", \"sync\", \"andig\", \"audio\", \"sync\", \"text\", \"sub\", \"guide\", \"info\", \"enter\", \"return\", \"options\", \"up\", \"down\", \"left\", \"right\", \"home\", \"prev\", \"next\", \"play\", \"titlelist\", \"rec\", \"pause\", \"stop\", \"red\", \"green\", \"yellow\", \"blue\"]}";

int lastIndexOf(String s, char ch) {
  for(int i = s.length(); i >= 0; i--)
    if(s[i] == ch)
      return i;
}

COMMAND parseCommand(String arg) {
  if(arg == "onoff")
    return 0xA90;
  if(arg == "0")
      return 0x910;
  if(arg == "1")
    return 0x010;
  if(arg == "2")
    return 0x810;
  if(arg == "3")
    return 0x410;
  if(arg == "4")
    return 0xC10;
  if(arg == "5")
    return 0x210;
  if(arg == "6")
    return 0xA10;
  if(arg == "7")
    return 0x610;
  if(arg == "8")
    return 0xE10;
  if(arg == "9")
    return 0x110;
  if(arg == "volup")
    return 0x490;
  if(arg == "voldown")
    return 0xC90;
  if(arg == "chup")
    return 0x090;
  if(arg == "chdown")
    return 0x890;
  if(arg == "mute")
    return 0x290;
  if(arg == "input")
    return 0xA50;
  if(arg == "sync")
    return 0xD58;
  if(arg == "andig")
    return 0xD58;
  if(arg == "audio")
    return 0xE90;
  if(arg == "sync")
    return 0xD58;
  if(arg == "text")
    return 0xFD0;
  if(arg == "sub")
    return 0xAE9;
  if(arg == "guide")
    return 0x6D25;
  if(arg == "info")
    return 0x5D0;
  if(arg == "enter")
    return 0xA70;
  if(arg == "return")
    return 0x62E9;
  if(arg == "options")
    return 0x36E9;
  if(arg == "up")
    return 0x2F0;
  if(arg == "down")
    return 0xAF0;
  if(arg == "left")
    return 0x2D0;
  if(arg == "right")
    return 0xCD0;
  if(arg == "home")
    return 0x70;
  if(arg == "prev")
    return 0x6CE9;
  if(arg == "next")
    return 0x1CE9;
  if(arg == "play")
    return 0x2CE9;
  if(arg == "titlelist")
    return 0x5358;
  if(arg == "rec")
    return 0x2E9;
  if(arg == "pause")
    return 0x4CE9;
  if(arg == "stop")
    return 0xCE9;
  if(arg == "red")
    return 0x52E9;
  if(arg == "green")
    return 0x32E9;
  if(arg == "yellow")
    return 0x72E9;
  if(arg == "blue")
    return 0x12E9;
  return 0;
}

boolean connectToWifi(char* ssid, char* pwd, int n_try){
	WiFi.disconnect();
  WiFi.softAPdisconnect();
	WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pwd);
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    #ifdef DEBUG
      Serial.print(".");
    #endif
    i++;
    if (i > n_try) {
      #ifdef DEBUG
        Serial.println("\n\nConnections problems\nToo many time");
      #endif
      return false;
    }
  }

  WiFi.config(ip,gw,mask);

  #ifdef DEBUG
    Serial.println();
    Serial.print("Connected to ");
    Serial.println(staSsid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  #endif

  return true;
}

boolean createAPWifi(char* ssid, char* pwd) {
  WiFi.disconnect();
  WiFi.softAPdisconnect();
	WiFi.mode(WIFI_AP);

  WiFi.softAPConfig(gw, gw, mask);

	WiFi.softAP(ssid, pwd);

  IPAddress myIP = WiFi.softAPIP();
  #ifdef DEBUG
  	Serial.print("AP IP address: ");
    Serial.println(myIP);
  #endif

  return true;
}

boolean launchAP() {
  uint8_t precTries = EEPROM.read(COUNTER_EEPROM_ADDRESS);
  #ifdef DEBUG
    Serial.printf("We tried to connect before %d times.\n", precTries);
  #endif
  if(precTries < MAX_RESTARTS_BEFORE_AP_MODE){
    precTries++;
    EEPROM.write(COUNTER_EEPROM_ADDRESS, precTries);
    EEPROM.commit();
    #ifdef DEBUG
      Serial.println("Writed to EEPROM");
    #endif
    return false;
  }
  EEPROM.write(COUNTER_EEPROM_ADDRESS, 0);
  EEPROM.commit();
  #ifdef DEBUG
    Serial.println("We pass the tries. Need to launch AP Mode.");
  #endif
  return true;
}

boolean writeStringToEeprom(char* buf, uint8_t position) {
  if(strlen(buf) > STRING_IN_EEPROM_MAX_LENGTH)
    return false;
  uint8_t startPos = position * (1 + STRING_IN_EEPROM_MAX_LENGTH);
  uint8_t dim = (strlen(buf));
  EEPROM.write(startPos++, dim);
  for(uint8_t i = 0; i < dim; i++)
    EEPROM.write(startPos++, buf[i]);
  EEPROM.commit();
  return true;
}

char* readStringFromEeprom(uint8_t position) {
  uint8_t startPos = position * (1 + STRING_IN_EEPROM_MAX_LENGTH);
  uint8_t dim = EEPROM.read(startPos++);
  if(dim > STRING_IN_EEPROM_MAX_LENGTH)
    dim = STRING_IN_EEPROM_MAX_LENGTH;
  char res[STRING_IN_EEPROM_MAX_LENGTH + 1];
  uint8_t i = 0;
  for(;i < dim; i++)
    res[i] = EEPROM.read(startPos++);
  //A string ends with a \0
  res[i] = '\0';
  return &(res[0]);
}

void handleRoot() {
	server.send(200, "text/html", mainPage);
}

void handleNotFound() {
	String message = "File Not Found\n\n";
	message += "URI: ";
	message += server.uri();
	message += "\nMethod: ";
	message += server.method();
	message += "\nArguments: ";
	message += server.args();
	message += "\n";
	for (uint8_t i = 0; i < server.args(); i++)
		message += " " + server.argName(i) + ": " + server.arg (i) + "\n";
	server.send(404, "text/plain", message);
}

void handleCommands() {
  #ifdef DEBUG
    Serial.println("Received a command:");
  #endif

  if(server.method() != HTTP_PUT) {
    server.send(405, "text/plain", "ERROR, Not good method\n");
    #ifdef DEBUG
      Serial.println("\tNot good method");
    #endif
    return;
  }
  String str_command = server.uri().substring(lastIndexOf(server.uri(), '/') + 1);
  #ifdef DEBUG
    Serial.print("The string of the command is: ");
    Serial.println(str_command);
  #endif
  COMMAND command = parseCommand(str_command);
  if(command == 0) {
    server.send(404, "text/plain", "ERROR, Command not found\n");
    #ifdef DEBUG
      Serial.println("\tCommand not found");
    #endif
    return;
  }

  #ifdef DEBUG
    Serial.print("\tGood command: ");
    Serial.println(command, HEX);
    Serial.println();
  #endif
  irsend.sendSony(command, 12);
  server.send(200, "text/html", "OK");
}

void handleSettings() {
  String ssid = server.arg("ssid");
  String pwd = server.arg("pwd");
  server.send(200, "text/html",
  "<!doctype html>\
  <html>\
  <head>\
    <meta name=\"author\" content=\"nicioniz\">\
    <meta name=\"description\" content=\"A simple page that controls a Wemos D1 Mini with an IR transmitter\">\
    <title>Telecomando</title>\
  </head>\
  <body>\
    OK. Now the system restarts. You can find me in the WLAN " + ssid + " at the address <a href=\"http://192.168.1.200\">192.168.1.200</a>\
  </body>\
  </html>");

  #ifdef DEBUG
    Serial.println("Arrived new settings:");
    Serial.println("\tssid:\t" + ssid);
    Serial.println("\tpwd:\t" + pwd);
    Serial.println("Now save and restart");
  #endif
  delay(100);

  writeStringToEeprom(&(ssid[0]), STA_SSID_POSITION);
  writeStringToEeprom(&(pwd[0]), STA_PWD_POSITION);
  system_restart();
}

void handleGenericCommand() {

  //TODO
  server.send(404, "text/html", "<!doctype html><body>Not implemented yet. It's under TODO.<br/>If you want to contribute go to <a href=\"https://github.com/nicioniz/RESTful_IRSonyTVController\"> my github page</a>.</body>");
  return;

  if(server.method() != HTTP_PUT) {
    server.send(405, "text/plain", "ERROR, Not good method\n");
    #ifdef DEBUG
      Serial.println("\tNot good method");
    #endif
    return;
  }

  //Extract the producer and the specific command from the uri. The uri is in the form: /genericcommand/PRODUCER/COMMAND
  String producer = "";
  String command = "";
  #ifdef DEBUG
    Serial.println("Received a GENERIC command:");
    Serial.println(producer + ": 0x" + command);
    Serial.println();
  #endif


  //call the requested function with the requested data
  server.send(200, "text/plain", "OK\n");
}

void handleRemotes() {
  if(server.method() != HTTP_GET) {
    server.send(405, "text/plain", "ERROR, Not good method\n");
    #ifdef DEBUG
      Serial.println("\tNot good method");
    #endif
    return;
  }

  //According to RESTful implementetion a GET to the list elements return the json representation of the list, in this case the list of acceptable commands (listed in handleCommand())
  server.send(200, "application/json", jsonCommandsList);
}

void setup() {
  #ifdef DEBUG
	   pinMode(BUILTIN_LED, OUTPUT);
     digitalWrite(BUILTIN_LED, HIGH);  //high lo spegne
  #endif

  EEPROM.begin(512);

	Serial.begin(115200);

  staSsid = readStringFromEeprom(STA_SSID_POSITION);
  staPwd = readStringFromEeprom(STA_PWD_POSITION);

  #ifdef DEBUG
      Serial.println();
    	Serial.printf("Trying to connect to %s\n", staSsid);
  #endif
	// Wait for connection
	if(!connectToWifi(staSsid, staPwd, 30)){
    if(launchAP())
      createAPWifi(apSsid, apPwd);
    else {
      system_restart();
      return;
    }
  }

	if(MDNS.begin("tvremote")) {
    #ifdef DEBUG
		    Serial.println("MDNS responder started");
    #endif
	}

	server.on("/", handleRoot);
  server.on("/remotes", handleRemotes);
	server.on("/remotes/?*", handleCommands); //using the wildcard /remotes/?* because after the slash must be at least 1 char (?) the * says 0 or more.
  server.on("/restart", system_restart);
  server.on("/settings", handleSettings);
  server.on("/genericcommand", handleGenericCommand);
	server.onNotFound(handleNotFound);
	server.begin();
  #ifdef DEBUG
	   Serial.println("HTTP server started");
  #endif
  irsend.begin();
  #ifdef DEBUG
      Serial.println("IRSend begin");
  #endif
}

void loop() {
  server.handleClient();
}
