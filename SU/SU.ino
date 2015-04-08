#include <HT.h>
//#include <IRD.h>
#include <LED.h>
#include <Pin.h>
//#include <Dust.h>
#include <HCHO.h>
//#include <Light.h>
//#include <Button.h>
#include <Controller.h>
//#include <SoilMoisture.h>
//#include <Pyroelectric.h>

Controller ctrl = Controller();

//----------------------------------------------------//
// Add your code:
//----------------------------------------------------//
HT ht0 = HT(PIN_HT0);
//IRD ird0 = IRD(PIN_IRD0);
LED led0 = LED(PIN_LED0);
HCHO hcho0 = HCHO(PIN_HCHO0);
//Dust dust0 = Dust(PIN_DUST0);
//Button btn0 = Button(PIN_BTN0);
//Light light0 = Light(PIN_LIGHT0);
//Pyroelectric pe0 = Pyroelectric(PIN_PE0);
//SoilMoisture sm0 = SoilMoisture(PIN_SM0);

void create() {
  //----------------------------------------------------//
  // Add your code:
  //----------------------------------------------------//
  ctrl.add(&ht0);
  ctrl.add(&hcho0);
  //ctrl.add(&sm0);
  //ctrl.add(&pe0);
  //ctrl.add(&btn0);
  //ctrl.add(&ird0);
  //ctrl.add(&dust0);
  //ctrl.add(&light0);
}

void setup() {
  create();
  ctrl.setup();
  setNotifier(&led0);
}

void loop() {
  ctrl.proc();
}
