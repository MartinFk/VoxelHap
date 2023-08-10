/*
This code works based on painless mesh. 

1. It connects to the master and Master acknowledges back with "Connected " from master.
2. Once it is connected to master( i.e. connection_flag=1 and light tuirn on cyan) , it sends the capacitance touch values to master. 
3. Every time there is a change in the capacitance touch, sends data to Master touched -1, relesed -0.
 -- Touch_status[12] saves the staus of each capacitance value.
 --  Here touch values 0,1,6,9,7,11 are mapped to the sides of the cubes to detect touch by the user and rest are mapped to see whether there is connection plate. 
4. We also send Cube_id to identify which cube is connected. For example now cub_id is 1 for cube 1. For example Base_Cube 1, doc["12"]=1; Base_Cube 2 doc["12"] = 2;


*/


#include <Wire.h>
#include "Adafruit_MPR121.h"
#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif


#include "namedMesh.h"
#define   MESH_SSID       "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555
#include <ArduinoJson.h>



#include <FastLED.h>

#define NUM_LEDS        6
#define LED_TYPE      NEOPIXEL
#define COLOR_ORDER     GRB
#define DATA_PIN        13
#define BRIGHTNESS      255

CRGB leds[NUM_LEDS];


// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();



// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

// to control your personal task
Scheduler     userScheduler; 
namedMesh  mesh;
String msg =  String("hi");
String to = "Master";


// Name needs to be unique
// also change the cube_id,  value of variable doc[12].
 
String nodeName = "Base_Cube";
int cube_id =1;

void sendMessage() ;
Task taskSendMessage( TASK_SECOND * 0.3 , TASK_FOREVER, &sendMessage );

// indicates whether it is connected to master or not
int connection_flag=0;


bool a[12];
int t_flag=0;
const size_t CAPACITY = JSON_ARRAY_SIZE(3);
 
// allocate the memory for the document
StaticJsonDocument<CAPACITY> doc;

// create an empty array
JsonArray array = doc.to<JsonArray>();



// To store all capacitance touch values
int Touch_status[12]= {0,0,0,0,0,0,0,0,0,0,0,0};


void sendMessage() 
{   
  
  
  if(connection_flag==1)
    {
      DynamicJsonDocument doc(1024) ;
      currtouched = cap.touched();
	  
	  
      for (uint8_t i=0; i<12; i++) 
      {
        msg="";
        t_flag=0;
		
        // it if *is* touched and *wasnt* touched before, alert!
        if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) 
        {
            Touch_status[i]=1;
            a[i]= true;
            t_flag=1;
          
        }
		
        // if it *was* touched and now *isnt*, alert!
        if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) 
        {
            Touch_status[i]=0;
            a[i]=false;
            t_flag=1;
           
        }
        // Flag to see is any change in the touch status 
        if(t_flag==1)
        {  
            for (uint8_t i=0; i<12; i++)
            doc[String(i)]=Touch_status[i];
            doc["12"]= cube_id;;
            serializeJson(doc,msg);
            mesh.sendSingle(to,msg);
            Serial.println(msg);
        }
    
      }
  
      lasttouched = currtouched;
       
    } 
  };

void setup() {
  
      Serial.begin(115200);
	  
      if (!cap.begin(0x5A)) 
      {
        Serial.println("MPR121 not found, check wiring?");
        while (1);
      }
	  
	  // Fast LED setup
      FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
      FastLED.setBrightness(BRIGHTNESS);
	  
	  // Mesh initialisation, for more plesae named mesh example from painlessmesh 
	  
      mesh.init(MESH_SSID, MESH_PASSWORD, &userScheduler, MESH_PORT);
      mesh.setName(nodeName);                                                    // This needs to be an unique name! 
      mesh.onReceive([](uint32_t from, String &msg) { });

        mesh.onReceive([](String &from, String &msg) 
        {
            Serial.printf("Received message by name from: %s, %s\n", from.c_str(), msg.c_str());
            if(String(msg.c_str())=="Connected")
            {
            
            leds[4] = (CRGB::Cyan);
            FastLED.show(); 
            connection_flag=1;
			
         }
            
         });
          
          userScheduler.addTask(taskSendMessage);
          taskSendMessage.enable();

          
    }

void loop() 
{
  mesh.update();
}
