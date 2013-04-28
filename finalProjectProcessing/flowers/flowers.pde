float cx, cy, diam;
float counter1, counter2;
float vel, acel;
boolean petal;


void setup () {
 
 size (500, 500);
 background (255);
 cx = 250;
 cy = 250;
 counter1 = 0;
 vel = 0.1;
 acel = 0.005;
 petal = true;
  
}

void draw () {
  
  if (petal) {
  
  diam = (sin (counter1)) * 100;
  ellipse (cx,cy, diam, diam);
  counter1 += 0.03;
  counter2 += 0.05;
  cx = 250 + sin(counter1) * 100;
  vel += acel;
  cy -= vel;
  
  }
  
  if (diam < 0) petal = false;
  
}
