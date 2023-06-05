////////////////////////////////// INCLUDE //////////////////////////////////
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>

////////////////////////////////// DEFINE ///////////////////////////////////

#define rxPin 11 //Broche 11 en tant que RX, � raccorder sur TX du HC-05
#define txPin 10 //Broche 10 en tant que TX, � raccorder sur RX du HC-05
SoftwareSerial HC05(rxPin ,txPin); //D�finition du software serial

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 4     // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C

//Parameters Sensor
#define Vcc 5.0
#define R1 100000.0
#define R2 1000.0
#define R3 100000.0
#define R5 10000.0

//Parameters for game
#define DINO_WIDTH 25
#define DINO_HEIGHT 26
#define DINO_INIT_X 10 // Dino initial spawn location
#define DINO_INIT_Y 10 // Dino initial spawn location

#define BASE_LINE_X 0
#define BASE_LINE_Y 10
#define BASE_LINE_X1 127
#define BASE_LINE_Y1 10

#define TREE1_WIDTH 11
#define TREE1_HEIGHT 23

#define TREE2_WIDTH 22
#define TREE2_HEIGHT 23

#define TREE_Y 10

#define JUMP_PIXEL 22 // Number of pixel dino will jump

Adafruit_SSD1306 display(OLED_RESET);
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);




///////////////////////////////// VARIABLES /////////////////////////////////
// Encoder
int encoderDT = 4;  
int encoderCLK = 3;
int encoderSW = 2;
volatile int lastEncoded = 0;
volatile long encoderValue = 0;
// Menu
bool screenOn = false;
int click = 0 ; 
int lastMSB = 0;
int lastLSB = 0;
int selected= 0;
int numMenu = 3;      
String menuItems[] = {"1- Easy Mode", "2- Gettin Tough", "3- Good Luck lol"};
String initial[] = {"PLAY","TEST", "OFF"} ;
String endgame[] = {"PLAY AGAIN","MAIN MENU", "OFF"} ;

/***************************************/
// Jump
float resistance ; 
float min = 100000.0 ; 
float max = -100000.0 ; 
float range ; 
float middle ; 
int i=0 ; 

/***************************************/
//Parameters for game
bool collision = false ; 

static const unsigned char PROGMEM dino1[]={
  // 'dino', 25x26px
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x00, 0x00, 0x06, 0xff, 0x00, 0x00, 0x0e, 0xff, 0x00, 
0x00, 0x0f, 0xff, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x00, 0x0f, 0xc0, 0x00, 
0x00, 0x0f, 0xfc, 0x00, 0x40, 0x0f, 0xc0, 0x00, 0x40, 0x1f, 0x80, 0x00, 0x40, 0x7f, 0x80, 0x00, 
0x60, 0xff, 0xe0, 0x00, 0x71, 0xff, 0xa0, 0x00, 0x7f, 0xff, 0x80, 0x00, 0x7f, 0xff, 0x80, 0x00, 
0x7f, 0xff, 0x80, 0x00, 0x3f, 0xff, 0x00, 0x00, 0x1f, 0xff, 0x00, 0x00, 0x0f, 0xfe, 0x00, 0x00, 
0x03, 0xfc, 0x00, 0x00, 0x01, 0xdc, 0x00, 0x00, 0x01, 0x8c, 0x00, 0x00, 0x01, 0x8c, 0x00, 0x00, 
0x01, 0x0c, 0x00, 0x00, 0x01, 0x8e, 0x00, 0x00
};

static const unsigned char PROGMEM tree1[]={
  // 'tree1', 11x23px
0x1e, 0x00, 0x1f, 0x00, 0x1f, 0x40, 0x1f, 0xe0, 0x1f, 0xe0, 0xdf, 0xe0, 0xff, 0xe0, 0xff, 0xe0, 
0xff, 0xe0, 0xff, 0xe0, 0xff, 0xe0, 0xff, 0xe0, 0xff, 0xc0, 0xff, 0x00, 0xff, 0x00, 0x7f, 0x00, 
0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00
};

static const unsigned char PROGMEM tree2[]={
  // 'tree2', 22x23px
0x1e, 0x01, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 0x4f, 0xe8, 0x1f, 0xff, 0xfc, 0x1f, 0xff, 0xfc, 0xdf, 
0xff, 0xfc, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xfc, 0xff, 0xff, 
0xfc, 0xff, 0xef, 0xfc, 0xff, 0x83, 0xfc, 0xff, 0x03, 0xfc, 0xff, 0x03, 0xf8, 0x7f, 0x03, 0xe0, 
0x1f, 0x03, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 
0x03, 0xe0, 0x1f, 0x03, 0xe0
};




////////////////////////////// CONFIGURATION ////////////////////////////////
void setup() {
  Serial.begin(9600) ; 
  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);
  HC05.begin(9600);
 
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();  //Clear the buffer
  display.display();
  /***************************************/
  pinMode(encoderDT, INPUT_PULLUP);
  pinMode(encoderCLK, INPUT_PULLUP); 
  pinMode(encoderSW, INPUT_PULLUP); 

  attachInterrupt(digitalPinToInterrupt(encoderDT), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderCLK), updateEncoder, CHANGE);
  /***************************************/
  Wire.begin();
  //display.clearDisplay();
}


////////////////////////////////// FUNCTIONS ////////////////////////////////

///////////////// INTRO MESSAGE /////////////////
void introMessage(){
  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10,4);
  display.println("Dino Game");
  display.display();
}

/////////////////// MOVE DINO ///////////////////
void moveDino(int16_t *y, int type=0){
  display.drawBitmap(DINO_INIT_X, *y, dino1, DINO_WIDTH, DINO_HEIGHT, SSD1306_WHITE);
}

/////////////////// MOVE TREE /////////////////// 
void moveTree(int16_t *x, int type=0){
  if(type==0){
    display.drawBitmap(*x, TREE_Y, tree1, TREE1_WIDTH, TREE1_HEIGHT, SSD1306_WHITE);
  }
  else if(type==1){
    display.drawBitmap(*x, TREE_Y, tree2, TREE2_WIDTH, TREE2_HEIGHT, SSD1306_WHITE);
  }
  
}

///////// GAME OVER DISPLAY WITH SCORE //////////
void gameOver(){
  display.clearDisplay();
  
  display.setTextSize(2);             
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15,0);
  display.println("Game Over");
  
  display.setTextSize(1);
  display.setCursor(10,20);
  display.println(endgame[selected]) ;

  display.display();
}

////////////// MAIN PLAY FUNCTION ///////////////
bool play(){
  bool collision = false ;  
  int16_t tree_x=127;
  int16_t tree1_x=195;
  int tree_type = random(0,2);
  int tree_type1 = random(0,2);
  int16_t dino_y = DINO_INIT_Y;
  int input_command;
  int jump=0;
  int score=0;
    
  for(;;){
    display.clearDisplay();   
      
    if(GetSensor()*4 >= middle){
      if(jump==0){
        jump=1;
      }
    }

    if(jump==1){
      dino_y--;
      if(dino_y== (DINO_INIT_Y-JUMP_PIXEL)){
        jump=2;
        score++;
      }
    } else if(jump==2){
      dino_y++;
      if(dino_y== DINO_INIT_Y){
        jump=0; 
      }
    }

    if(tree_x<= (DINO_INIT_X+DINO_WIDTH) && tree_x>= (DINO_INIT_X+(DINO_WIDTH/2))){
    // Serial.println("Might be Collision Happend");
      if(dino_y>=(DINO_INIT_Y-3)){
        // Collision Happened
        Serial.println("Collision Happend");
        collision = true ; 
        break;
      }    
    }

    if(tree1_x<= (DINO_INIT_X+DINO_WIDTH) && tree1_x>= (DINO_INIT_X+(DINO_WIDTH/2))){
    // Serial.println("Might be Collision Happend");
      if(dino_y>=(DINO_INIT_Y-3)){
        // Collision Happened
        Serial.println("Collision Happend");
        collision = true ; 
        break;
      }    
    }

    displayScore(score);
    moveTree(&tree_x,tree_type);
    moveTree(&tree1_x,tree_type1);
    moveDino(&dino_y);
    display.drawLine(0, 54, 127, 54, SSD1306_WHITE);

    tree_x--;
    tree1_x--;
    if(tree_x==0) {
      tree_x = 127;
      tree_type = random(0,1);
    }

    if(tree1_x==0) {
      tree1_x = 195;
      tree_type1 = random(0,1);
    }
   display.display();
  }
  Serial.println("Game Over");
  return collision ; 
}

//////// DISPLAY SCORE WHILE GAME RUNNING ///////
void displayScore(int score){
  display.setTextSize(1);
  display.setCursor(64,2);
  display.print("Score: ");
  display.print(score);
}

///////////////// RENDER SCENE //////////////////
void renderScene(int16_t i=0){
  display.drawBitmap(10, 29, dino1, 25, 26, SSD1306_WHITE);
  display.drawBitmap(50, TREE_Y, tree1, 11, 23, SSD1306_WHITE);
  display.drawBitmap(100, TREE_Y, tree2, 22, 23, SSD1306_WHITE);
  display.drawLine(0, 54, 127, 54, SSD1306_WHITE);
  display.drawPixel(i, 60, SSD1306_WHITE);
}

/////////////// GET SENSOR VALUES ///////////////
int8_t GetSensor() {
  int sensorValue = analogRead(A0);
  float voltage = (float)sensorValue * (5.0 / 1023.0); // Convert the analog reading (0 - 1023) to a volt (0 - 5V):
  int8_t resistance = (0.000001*((R1*(R2+R3)/R2)*(Vcc/voltage)-R5-R1))/4; //Voltage to MOhm
  //Serial.println(resistance);  // print out the value you read
  //delay(100); 
  return resistance ; 
}


////////////////////////////////// PLAY /////////////////////////////////////
void loop() { 
  //Click conditions****************************************/
  if (digitalRead(encoderSW)==LOW && click==0)  {
    click = 1 ; 
  } else if (digitalRead(encoderSW)==LOW && click ==1 && initial[selected]=="PLAY"){
    click = 2 ; 
  } else if (digitalRead(encoderSW)==LOW && click ==1 && initial[selected]=="TEST"){
    click = 4 ; 
  } else if (digitalRead(encoderSW)==LOW && click ==1 && initial[selected]=="OFF"){
    click = 0 ; 
  } else if (digitalRead(encoderSW)==LOW && click ==4){
    click = 1 ; 
  } else if (digitalRead(encoderSW)==LOW && click ==2){
    click = 3 ; 
  } else if (i>=100 && click==3){
    click = 5 ; 
  } else if (digitalRead(encoderSW)==LOW && click ==7 && endgame[selected]=="OFF"){
    click = 0 ; 
  } else if (digitalRead(encoderSW)==LOW && click ==7 && endgame[selected]=="PLAY AGAIN"){
    collision = false ;
    click = 3 ; 
  } else if (digitalRead(encoderSW)==LOW && click ==7 && endgame[selected]=="MAIN MENU"){
    click = 1 ; 
  } 

  Serial.println(click) ; 

  /////// SCREEN OFF ////////
  if (click==0){
    display.clearDisplay();
    display.display();
  /*********************************************************/

  //////// MAIN MENU ////////
  } else if (click==1) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(50,0);
    display.println("Hi :)");
    display.setCursor(20,10);
    display.println("select a mode");
    display.setCursor(50, 20);
    display.println(initial[selected]) ;
    display.display();
  /*********************************************************/

  //////// DIFFICULTY ///////
  } else if (click ==2) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(30,0);
    display.println("Difficulty");
    display.setCursor(0, 12);
    display.println(menuItems[selected]);
    display.display();
  /*********************************************************/

  /////// SENSOR VAL ////////
  } else if (click == 4) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(20,0);
    display.println("Sensor values");
    display.setCursor(50,13) ; 
    display.println(GetSensor()*4) ;
    HC05.write(GetSensor());
    display.setCursor(20,25);
    display.println("click to EXIT");
    display.display();
  /*********************************************************/

  /////// CALIBRATION ///////
  } else if (click == 3) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(30,5);
    display.println("CALIBRATION");
    display.setCursor(10,15);
    display.println("please move sensor") ; 
    display.display();
    /*Calibration on 9000 values*****************/
    while (i<=1000){
     float resistance_nb = GetSensor()* 4 ; 
      Serial.println(resistance_nb) ; 
      if (resistance_nb>max){
        max = resistance_nb ;
      } else if (resistance_nb < min){
        min = resistance_nb ; 
      }
      i++ ;
    }

  } else if (click==5) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(17,5);
    display.println("CALIBRATION DONE");
    display.display();
    i=0 ;

    /*Intervals calculation**********************/
    range = max+min ; 
    middle = range/2; 
    delay(1500) ; 
    click = 6 ; 

  } else if (click ==6) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,5);
    display.print("No jump ");
    display.print(min) ; 
    display.print("-");
    display.print(middle) ; 
    display.setCursor(5,15);
    display.print("Jump ");
    display.print(middle) ; 
    display.print("-");
    display.print(max) ; 
    display.display();
    delay(2000) ; 
    display.clearDisplay();
    introMessage();
    delay(1000) ;

    click =  7;   
  /*********************************************************/

  ////////// GAME ///////////
  } else if (click==7) {
    if (collision==false){
      collision=play() ; 
    } else {
      gameOver();
    }
  }
}
  
void updateEncoder() {
  int MSB = digitalRead(encoderCLK);
  int LSB = digitalRead(encoderDT);

  int encoded = (MSB << 1) | LSB;
  int sum = (lastEncoded << 2) | encoded;

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    encoderValue++;
  } else if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    encoderValue--;
  }

  lastEncoded = encoded;

  if (encoderValue < 0) {
    encoderValue = 0;
  } else if (encoderValue >= numMenu) {
    encoderValue = numMenu - 1;
  }
  
  selected = encoderValue;
}
