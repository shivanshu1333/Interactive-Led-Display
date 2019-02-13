#include <Adafruit_GFX.h>
#include <gfxfont.h>

#include <gamma.h>
#include <RGBmatrixPanel.h>


#define CLK 11
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);
int base =0;
int object=31;
int times=5;
int height = 6;
int jump=0;
int ancor = 3;
int game_over = 0;
int pushButton = 10;
float t1=100;
int t2=100;
int t4=millis();
int randNumber=20;
int m=15;
int start_time=0;
boolean object_base[32];



void draw_object(){
  if(digitalRead(pushButton)){
      jump = digitalRead(pushButton);
    }
   while(millis()>t4)
   { 
     if(t1>70)
     {
       t1=(50+(t1-50.0)*(0.95)); 
       t4=t4+1000;
     }
     else if(t1>30)
     {
        t1=(30+(t1-30.0)*(0.95)); 
        t4=t4+1000;
     }
   }
    display_score();
//shift objects to the left
  object_base[32]=LOW;
  for(int i=0;i<32;i++)
  {
   object_base[i]=object_base[i+1]; 
  } 
//If that base is high draw the object
  for(int i=0;i<32;i++)
  {
   if(object_base[i]==HIGH)
   {
     matrix.fillRect(i, 14, 1, 2, matrix.Color333(7, 0, 0));
     
   }
  }

    for(int i=0;i<32;i++)
  {
   if(object_base[i]==HIGH)
   {
     test_game_over(i);
   }
  }

  
  delay(t1);

   matrix.fillRect(0, 14, 32, 2, matrix.Color333(0, 0, 0));

   matrix.fillRect(1,15,3 ,1 , matrix.Color333(0, 7,0 ));
   matrix.fillRect(2,14,1 ,2 , matrix.Color333(0, 7,0 ));
  
  if(times==-5){
    times=5;
    jump=0;
  }
//  test_game_over();
  if(game_over==1){
      return;
    }
//  if(object>0){
//    draw_object();
//    }
//   else {
//    object=31;
//    draw_object();
//   }
   randNumber--;
   if(randNumber==0)
   {
       randNumber = random(10, 20);
       object_base[31]=HIGH;
   }
    draw_object();
}
void del_object(){
    matrix.fillRect(object, 14, 1, 2, matrix.Color333(0, 0, 0));
  }


void jump_rex() {
  if(jump==1){
      if(times>0){
          delete_rex(m);
          base++;
          m--;
          draw_rex(m);
          times--;
          delay(t2);
          matrix.fillRect(0, 14, 32, 2, matrix.Color333(0, 0, 0));
          draw_object();
        }
        else if(times>=-4){
            delete_rex(m);
            base--;
            m++;
            draw_rex(m);
            times--;
            delay(t2);
            matrix.fillRect(0, 14, 32, 2, matrix.Color333(0, 0, 0));
            draw_object();
          }
      
    }
}

void test_game_over(int j){
  
  if((ancor==j+2 || ancor == j || ancor == j+1) && base<=1){
    //display game over
    game_over=1;
   return ;
  }
  if(jump==
  1){
    jump_rex();
  }
 
}

void setup() {
  // put your setup code here, to run once:
    start_time=millis();
     for(int i=0;i<32;i++)
    {
     
     object_base[i]=LOW;
    } 
    object_base[31]=HIGH;
    matrix.begin();
    draw_rex(15);
    draw_object();
    pinMode(pushButton, INPUT);
    Serial.begin(9600);
    
}
void display_game_over() {
  matrix.fillRect(0, 0, 32, 16, matrix.Color333(0, 0, 0));
  matrix.setCursor(5, 0); 
  matrix.setTextSize(1);
  
  matrix.setTextColor(matrix.Color333(7,0,0));
  matrix.print('G');
  matrix.print('A');
  matrix.print('M');
  matrix.print('E');
  matrix.setCursor(5, 9);
  matrix.print('O');
  matrix.print('V');
  matrix.print('E');
  matrix.print('R');
  delay(60000);
}

void name()
{

  matrix.fillRect(0, 0, 32, 16, matrix.Color333(0, 0, 0));
  matrix.setCursor(1, 0); 
  matrix.setTextSize(1);
  
  matrix.setTextColor(matrix.Color333(7,0,0));
  matrix.print('Y');
  matrix.print('U');
  matrix.print('G');
  matrix.print('A');
  matrix.print('L');
  matrix.setCursor(1, 9);
  matrix.print('G');
  matrix.print('U');
  matrix.print('P');
  matrix.print('T');
  matrix.print('A');
  delay(60000);

}

void display_score(){
  matrix.setCursor(10, 1); 
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(7,0,0));
  matrix.fillRect(10, 1, 20, 8, matrix.Color333(0, 0, 0));
  matrix.print((millis()-start_time)/100);
//int speed=t1;
//matrix.print(speed);
}
void loop() {
//   put your main code here, to run repeatedly:
    display_game_over();
    
}
void draw_rex(int m) {
 // matrix.fillRect(ancor, 16-height-base, ancor-1, height, matrix.Color333(0, 7, 0));
matrix.fillRect(1,m,3 ,1 , matrix.Color333(0, 7,0 ));
matrix.fillRect(1,m-2,3 ,1 , matrix.Color333(0, 7,0 ));
matrix.fillRect(2,m-3,1 ,4 , matrix.Color333(0, 7,0 ));
  
}
void delete_rex(int m) {
  
  
matrix.fillRect(1,m,3 ,1 , matrix.Color333(0, 0,0 ));
matrix.fillRect(1,m-2,3 ,1 , matrix.Color333(0, 0,0 ));
matrix.fillRect(2,m-3,1 ,4 , matrix.Color333(0, 0,0 ));
}
