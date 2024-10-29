#include <WiFi.h>

bool state;
bool energy;
bool _speed;

AsyncWebServer server(80);

const char* ssid = "nomeDaRede";
const char* password = "senhaDaRede";

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

void handleRoot();
void handleEnergy();
void handleState();
void handleOptions(int option);
void handleSpeedDropdown(int speed);

void setup() {
  Serial.begin(115200);

  state = false;
  energy = false;

  // Initialize SPIFFS
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();

  // Route definitions
  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("Request for root page received");
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route to set GPIO to HIGH
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("Request to turn ON received");
    handleState(1);  
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to set GPIO to LOW
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("Request to turn OFF received");
    handleState(0);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route to handle optionsDropdown
  server.on("/peca1", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("Request to handle PECA 1 received");
    handleOptions(1);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.on("/peca2", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("Request to handle PECA 2 received");
    handleOptions(2);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route to handle speedDropdown
  server.on("/lento", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("Request to handle LENTO received");
    handleSpeedDropdown(1);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.on("/medio", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("Request to handle MEDIO received");
    handleSpeedDropdown(2);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.on("/rapido", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("Request to handle RAPIDO received");
    handleSpeedDropdown(3);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
}

void loop(){
  server.handleClient();
}

// endpoints functions
void handleEnergy() {
  Serial.println("Handling energy endpoint");
  // Handle energy button press here
  server.send(200, "text/plain", "Energy button pressed");
  energy != energy;
}

void handleState(int newState) {
  Serial.println("Handling state endpoint");
  // Handle state button press here
  if(newState == 1) {
    Serial.println("Turning ON");
  } else {
    Serial.println("Turning OFF");
  }
  state = newState;
}

void handleOptions(int option) {
  Serial.println("Handling dropdown selection endpoint");
  Serial.print("Option selected: ");
  Serial.println(option);
}

void handleSpeedDropdown(int speed){
  Serial.println("Handling speed dropdown endpoint");
  Serial.print("Speed selected: ");
  Serial.println(speed);
}
