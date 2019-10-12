#define RFD_SERIAL Serial1
#define RFD_BAUD 38400  // This is the baud all of our RFDs communicate at. They can be changed to something else, but you have to make sure these always match up.

char receive_packet[100]; // Make sure the size of this array is larger than your largest data string will be. In this case, 100 characters is the max.
char transmit_packet[100];
String read_packet;

void setup() {
  Serial.begin(9600);
  RFD_SERIAL.begin(RFD_BAUD);
}

void loop() {
  if(RFD_SERIAL.available()>0){                   // Checks for any incoming bytes
    delay(10);                                    // Bytes will be received one at a time unless you add a small delay so the buffer fills with your message
    int incomingBytes = RFD_SERIAL.available();   // Checks number of total bytes to be read
    Serial.println(incomingBytes);                // Just for testing to see if delay is sufficient to receive all bytes.
    for(int i=0; i<incomingBytes; i++)
    {
      receive_packet[i] = RFD_SERIAL.read();      // Reads bytes one at a time and stores them in a character array.
    }

    Serial.println(receive_packet);               // prints whole character array

    for(int k=0; k<sizeof(receive_packet); k++)
    {
      receive_packet[k] = '\0';                   // Clear the bytes
    }

  }

  if(Serial.available()>0) {
    delay(30);
    int serialBytes = Serial.available();
    read_packet = "";                             // Empty the string that reads to the serial terminal
    for(int j=0; j<serialBytes; j++)
    {
        transmit_packet[j] = Serial.read();           // Reads bytes one at a time and stores them in a character array.
        if(transmit_packet[j] != '\n') {
          read_packet += transmit_packet[j];
        }
    }
    RFD_SERIAL.print(transmit_packet);
    Serial.println("You are sending: " + read_packet);
    for(int k=0; k<sizeof(transmit_packet); k++)
    {
      transmit_packet[k] = '\0';                      // Clear the bytes
    }
    
  }
  
}
