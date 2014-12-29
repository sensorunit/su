#include <SM.h>
#include <TH.h>
#include <LED.h>
#include <Pin.h>
#include <Com.h>
#include <HCHO.h>
#include <Dust.h>
#include <Unit.h>
#include <Pump.h>
#include <Controller.h>

//#include <CO.h>
//#include <TV.h>
//#include <IRD.h>
//#include <Lux.h>
//#include <USD.h>
//#include <Reset.h>
//#include <Light.h>
//#include <Relay.h>
//#include <Button.h>
//#include <Pyroelectric.h>

Com com = Com();
Unit unit = Unit();
Controller ctrl = Controller();

//----------------------------------------------------//
// Add your code:
//----------------------------------------------------//
SM sm0 = SM(PIN_SM0);
TH th0 = TH(PIN_TH0);
LED led0 = LED(PIN_LED0);
Pump pump0 = Pump(PIN_PUMP0);
HCHO hcho0 = HCHO(PIN_HCHO0);
Dust dust0 = Dust(PIN_DUST0);

//CO co0 = CO(PIN_CO0);
//TV tv0 = TV(PIN_TV0);
//IRD ird0 = IRD(PIN_IRD0);
//Lux lux0 = Lux(PIN_LUX0);
//Reset reset0 = Reset(PIN_RESET0);
//Button btn0 = Button(PIN_BTN0);
//Light light0 = Light(PIN_LIGHT0);
//Relay relay0 = Relay(PIN_RELAY0);
//USD usd0 = USD(PIN_USD_TRIG0, PIN_USD_ECHO0);
//Pyroelectric pe0 = Pyroelectric(PIN_PYROELECTRIC0);

void create() {
  //----------------------------------------------------//
  // Add your code:
  //----------------------------------------------------//
  unit.add(&sm0);
  unit.add(&th0);
  unit.add(&led0);
  unit.add(&pump0);
  unit.add(&hcho0);
  unit.add(&dust0);
  
  //unit.add(&pe0);
  //unit.add(&tv0);
  //unit.add(&lux0);
  //unit.add(&btn0);
  //unit.add(&usd0);
  //unit.add(&ird0);
  //unit.add(&reset0);
  //unit.add(&relay0);
  //unit.add(&light0);
}

void setup() {
  create();
  com.setup();
  unit.setup();
  setNotifier(&led0);
}

void loop() {
  ctrl.process(&com, &unit);
}

