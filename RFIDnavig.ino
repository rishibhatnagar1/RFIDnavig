#include <SoftwareSerial.h>
SoftwareSerial RFID(2, 3); // RX and TX
 
int data1 = 0;
int ok = -1;
int yes = 13;
int no = 12;
 
// use first sketch in http://wp.me/p3LK05-3Gk to get your tag numbers
int tag1[10] = {48,52,49,53,52,51,57,53,13,10};
int tag2[10] = {48,52,49,53,52,52,48,56,13,10};
int tag3[10] = {48,52,49,53,52,51,57,50,13,10};
int tag4[10] = {48,52,49,53,52,51,57,56,13,10};
int tag5[10] = {48,52,49,51,54,53,52,49,13,10};
int tag6[10] = {48,52,49,53,52,52,49,48,13,10};
int tag7[10] = {48,52,49,54,51,49,49,54,13,10};
//int tag8[10] = {48,52,49,53,52,52,48,57,13,10};
//int tag9[10] = {48,52,49,53,52,51,57,51,13,10};
//int tag10[10] = {48,52,49,53,52,51,57,55,13,10};

int newtag[10] = { 0,0,0,0,0,0,0,0,0,0}; // used for read comparisons
 
void setup()
{
  RFID.begin(9600);    // start serial to RFID reader
  Serial.begin(9600);  // start serial to PC 
  pinMode(yes, OUTPUT); // for status LEDs
  pinMode(no, OUTPUT);
}
 
boolean comparetag(int aa[10], int bb[10])
{
  boolean ff = false;
  int fg = 0;
  for (int cc = 0 ; cc < 10 ; cc++)
  {
    if (aa[cc] == bb[cc])
    {
      fg++;
    }
  }
  if (fg == 10)
  {
    ff = true;
  }
  return ff;
}
 
void checkmytags() // compares each tag against the tag just read
{
  ok = 0; // this variable helps decision-making,
  // if it is 1 we have a match, zero is a read but no match,
  // -1 is no read attempt made
  if (comparetag(newtag, tag1) == true)
  {
    ok++;//ok=1
    Serial.println("Welcome to Sumeru");
    Serial.println(" Please move forward to enter or backwards to exit");
  }
  if (comparetag(newtag, tag2) == true)
  {
    ok++;
    Serial.println("In the front is the shoe rack");
    Serial.println("Please take a left turn for the hall and kitchen");
    Serial.println("Points 3,4 correspond to Hall and Kitchen Respectively");
    Serial.println("Please turn around to exit");
  }
  if (comparetag(newtag, tag3) == true)
  {
    ok++;
    Serial.println(" Welcome to checkpoint number 3");
    Serial.println(" This is the hall");
    Serial.println(" Towards your right is the way to washroom ");
    Serial.println("If you want to go to the kitchen please move forward");
    Serial.println("If you are returning from the washroom , you can move to the right for checkpoint number 4");
    delay(100);
  }
  if (comparetag(newtag, tag4) == true)
  {
    ok++;
    Serial.println("This is checkpoint 4");
    Serial.println("Towards your front is the kitchen");
    Serial.println("Towards your left is the temple. Please move forward to check point 5 for more information on the temple");
    Serial.println("Towards you right is Bhavana's room");
    Serial.println("Please move to checkpoint for the same");
    Serial.println("For exiting , please turn around. Checkpoint 7,8,9 will guide you outside");
  }
  if (comparetag(newtag, tag5) == true)
  {
    ok++;
    Serial.println("In front of you is the temple");
    Serial.println(" If you wish to exit , please go to check point 4");
    Serial.println("Checkpoints 7,8,9 will guide you outside");
    Serial.println("If you wish to check out Bhavana's room , please move forward to checkpoint 5");
  }
   if (comparetag(newtag, tag6) == true)
  {
    ok++;
    Serial.println("Welcome to Bhavana's room");
    Serial.println("This is the last check point");
    Serial.println("You may exit now");
    Serial.println("Points 7,8,9 will help you exit");
    
  }
   if (comparetag(newtag, tag7) == true)
  {
    ok++;
    Serial.println("You are now moving towards the exit");
  }
}
 
void readTags()
{
  ok = -1;
 
  if (RFID.available() > 0) 
  {
    // read tag numbers
    delay(100); // needed to allow time for the data to come in from the serial buffer.
 
    for (int z = 0 ; z < 10 ; z++) // read the rest of the tag
    {
      data1 = RFID.read();
      newtag[z] = data1;
    }
    RFID.flush(); // stops multiple reads
 
    // do the tags match up?
    checkmytags();
  }
 
  // now do something based on tag type
  if (ok > 0) // if we had a match
  {
    Serial.println("Accepted");
    digitalWrite(yes, HIGH);
    delay(1000);
    digitalWrite(yes, LOW);
 
    ok = -1;
  }
  else if (ok == 0) // if we didn't have a match
  {
    Serial.println("End of the steet , please take either a left or a right");
    digitalWrite(no, HIGH);
    delay(1000);
    digitalWrite(no, LOW);
    ok = -1;
  }
}
 
void loop()
{
  readTags();
}

