#include <Wire.h>
#include <math.h>

#Переменные для ускорений a
float aX, aY, aZ, a; 
int16_t x, y, z; // 16-битные данные от датчика

#Адрес датчика на I2C-шине
#define SENSOR_ADDRESS 0x18 

void setup() {
  Wire.begin();
  Serial.begin(9600); 
 Инициализация датчика
  Wire.beginTransmission(SENSOR_ADDRESS); #Функция Wire.beginTransmission(SENSOR_ADDRESS) используется для начала
  передачи данных на устройство, подключенное к I2C-шине, по заданному адресу. В данном случае, SENSOR_ADDRESS это адрес датчика LIS331HH  (0x18)
  Wire.write(0x20);  #CTRL_REG1: Адрес регистра управления
  Wire.write(0x27);  Включение датчика (частота 100 Hz, тогда все оси активны)
  Wire.endTransmission();
}

void loop() {
 #Чтение данных с датчика
  readSensorData();

  #Преобразуем необработанные данные в ускорение в единицах g
  aX = x * 0.00305; 
  aY = y * 0.00305;
  aZ = z * 0.00305;

 #Вычисление результирующего ускорения
  a = sqrt(aX * aX + aY * aY + aZ * aZ);

#Проверка порогового значения ускорения a (если оно больше 20)
  if (a > 20) {
    sendSOS();
  }

  delay(100); #Короткий перерыв
}

#Функция для чтения данных с датчика!!!
void readSensorData() {
  Wire.beginTransmission(SENSOR_ADDRESS);
  Wire.write(0x28 | 0x80); // Адрес регистра X_L, включен автоматический инкремент
  Wire.endTransmission();
  Wire.requestFrom(SENSOR_ADDRESS, 6); Запрос 6 байт данных (X, Y, Z)

  if (Wire.available() == 6) {
    x = Wire.read() | (Wire.read() << 8); 
    y = Wire.read() | (Wire.read() << 8); 
    z = Wire.read() | (Wire.read() << 8); 
  }
}

#Функция для отправки SOS-сигнала
void sendSOS() {
  Serial.println("ВНИМАНИЕ! Обнаружено столкновение!"); #на сербском (Upozorenje! Otkriven je sudar!)
#здесь будет код для отправки оповещения на определенный номер или email
}
