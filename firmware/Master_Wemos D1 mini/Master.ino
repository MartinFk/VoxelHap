//************************************************************
// This is a simple example that uses the painlessMesh library
// 
// This the master which recieves and sends information to the base cubes.
// Whenver a new cube connects it sends message to the cube and also write on serial port to communicate with Unity. 
// Comminicate the capacitance touch values sent by Base cube to unity 
// Every cube has a physical id and it is unique
// Physical id of the base Cube 3194200704  

//************************************************************


#include "namedMesh.h"
#define   MESH_SSID       "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555


Scheduler     userScheduler; // to control your personal task
namedMesh  mesh;
SimpleList<uint32_t> nodes;
String nodeName = "Master"; // Name needs to be unique
void newConnectionCallback(uint32_t nodeId);


uint32_t flag=0;
uint32_t connecetd_flag=0;
int j=0;
String a;

/*  Physical id of the base Cube 3194200704  */

Task taskSendMessage( TASK_SECOND, TASK_FOREVER, []() {
	
           // Serial.printf("--> startHere: New Connection, nodeId = %u\n", flag);
           String x = "";
		   
		   
		   
           if(flag !=0)
           {
                //Serial.printf("--> startHere: New Connection, nodeId = %u\n", flag);
                if (int(flag-3194200704) ==0)
                x = " Base_Cube";
                Serial.println(x);
				
				// Send message to the base cube acknowledging the connection
                String msg = String("Connected");
                String to = x;
                mesh.sendSingle(to, msg);
                flag= 0; 
				
           }
      
              
  }); 



void setup() 

{
  
      Serial.begin(115200);
      mesh.init(MESH_SSID, MESH_PASSWORD, &userScheduler, MESH_PORT);
      mesh.setName(nodeName); // This needs to be an unique name! 
  
  
  
     // Recieving the trouch values from the cubes after the connection is established 
      mesh.onReceive([](String &from, String &msg) 
      {
          DynamicJsonDocument doc(1024) ;
          deserializeJson(doc,msg.c_str());
		  
		  // Sending capacitance touch values to Unity
          for (uint8_t i=0; i<12; i++)
          {
            
			j = doc[String(i)];
            Serial.print(j);Serial.print(",");
          }
		  
          j = doc[String(12)];
          Serial.print(j);
          Serial.println();
      });
      
      // Detecting the base cube connection
      mesh.onChangedConnections([]() 
      {
          nodes = mesh.getNodeList();
          SimpleList<uint32_t>::iterator node = nodes.begin();
          while (node != nodes.end()) 
          {
             
             flag= *node;
             node++;
          }
           
       });
        
       userScheduler.addTask(taskSendMessage);
       taskSendMessage.enable();

}

void loop() 
{
  
    mesh.update();
     
}
