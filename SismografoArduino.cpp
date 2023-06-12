

#include <Wire.h> //Incluimos Libreria

const int MPU = 0x68;   //Dirección predeterminada de I2C para MPU 6050
int16_t AcX, AcY, AcZ, JK, JJ, JI;

int buz1 = 7;

void setup() {
  Wire.begin();                   // Inicialización de la biblioteca
  Wire.beginTransmission(MPU);    // Comenzar transmisión a MPU
  Wire.write(0x6B);               // registro PWR_MGMT_1
  Wire.write(0);                  // MPU-6050 al modo de inicio
  Wire.endTransmission(true);
  Serial.begin(9600);

//Configara el pin en modo entrada-salida

  pinMode(buz1, OUTPUT);
  
}

void loop() {
  Wire.beginTransmission(MPU);      // Iniciar Transferencia
  Wire.write(0x3B);                 // registra 0x3B (ACCEL_XOUT_H), registra datos en cola.
  Wire.endTransmission(false);      // mantener la conexión
  Wire.requestFrom(MPU, 14, true);  // Solicitar datos a MPU
  //Lee byte a byte
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  //Inicializamos nuestra variable
  JI=AcX;
  //Condicion para encender led1 y buzzer
if( JI>=550){

    digitalWrite(buz1, HIGH);
} 

//Inicializamos nuestra variable
 JJ=AcY;
 //Condicion para encender led2 y buzzer
if( JJ<=-550){
    
    digitalWrite(buz1, HIGH);
}

//Inicializamos nuestra variable
JK=AcZ;
//Condicion para encender led3 y buzzer
if( JK>=18000){
  
    digitalWrite(buz1, HIGH);
}

  //Imprimimos valores en el serial
  Serial.print(AcX);
  Serial.print(","); 
  Serial.print(AcY);
  Serial.print(","); 
  Serial.println(AcZ);
  
  delay(20);
  //Se apagan leds y buzzer

digitalWrite(buz1, LOW);
}
