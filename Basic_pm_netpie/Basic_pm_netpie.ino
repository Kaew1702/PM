/*  NETPIE ESP32 basic sample                            */
/*  More information visit : https://netpie.io             */
#include <PMS.h>
#include <WiFi.h>
#include <MicroGear.h>

const char* ssid = "iPhone";
const char* password = "Kaew170246";

#define APPID "pmpcc"
#define KEY "bCUwRmwVERY6RSY"
#define SECRET "yQsxGKtPFPEsu43pVFketstMt"
#define ALIAS "piepm"
#define FEEDID "pmpcshs"
//********************************************************************************************************************************************************************************************************************************

WiFiClient client;

int timer = 0;
MicroGear microgear(client);

/* If a new message arrives, do this */
void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
    Serial.print("Incoming message --> ");
    msg[msglen] = '\0';
    Serial.println((char *)msg);
}

void onFoundgear(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.print("Found new member --> ");
    for (int i=0; i<msglen; i++)
        Serial.print((char)msg[i]);
    Serial.println();  
}

void onLostgear(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.print("Lost member --> ");
    for (int i=0; i<msglen; i++)
        Serial.print((char)msg[i]);
    Serial.println();
}

/* When a microgear is connected, do this */
void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.println("Connected to NETPIE...");
    /* Set the alias of this microgear ALIAS */
    microgear.setAlias(ALIAS);
}


void setup() {
    /* Add Event listeners */

    /* Call onMsghandler() when new message arraives */
    microgear.on(MESSAGE,onMsghandler);

    /* Call onFoundgear() when new gear appear */
    microgear.on(PRESENT,onFoundgear);

    /* Call onLostgear() when some gear goes offline */
    microgear.on(ABSENT,onLostgear);

    /* Call onConnected() when NETPIE connection is established */
    microgear.on(CONNECTED,onConnected);

    Serial.begin(9600);
    Serial.println("Starting...");

    /* Initial WIFI, this is just a basic method to configure WIFI on ESP8266.                       */
    /* You may want to use other method that is more complicated, but provide better user experience */
    if (WiFi.begin(ssid, password)) {
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
    }

    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    /* Initial with KEY, SECRET and also set the ALIAS here */
    microgear.init(KEY,SECRET,ALIAS);

    /* connect to NETPIE to a specific APPID */
    microgear.connect(APPID);
}
//**************************************************************************************************************************************************************************************************************************************************************************
void loop() 
{
    /* To check if the microgear is still connected */
    if (microgear.connected()) 
    {
        Serial.println("connected");
    //}
        /* Call this method regularly otherwise the connection may be lost */
        microgear.loop();
    
//********************************************************************************************************************************************************************************************************************************************************************************
  if((pms.read(data))&&(timer >= 1000))
        {
             
               
               pm1 = data.PM_AE_UG_1_0;
    
               pm25 = data.PM_AE_UG_2_5;
               
               pm10 = data.PM_AE_UG_10_0;
             
               sprintf(str,"%d,%d,%d",pm1,pm25,pm10);
               Serial.println(str);
               Serial.print("Sending -->");
               microgear.publish("/pms",str);
               timer = 0;
        } 
else timer += 100;
    }
     {
        Serial.println("connection lost, reconnect...");
        if (timer >= 5000) {
            microgear.connect(APPID);
            timer = 0;
        }
        else timer += 100;
    }
    delay(100);
}
