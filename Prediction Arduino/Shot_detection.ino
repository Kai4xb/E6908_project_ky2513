#include <Arduino.h>
#include <Arduino_LSM9DS1.h>
#include <TensorFlowLite.h>
#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/micro_error_reporter.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <tensorflow/lite/version.h>
#include "model.h" 

tflite::MicroInterpreter* interpreter = nullptr;

constexpr int tensor_arena_size = 2 * 1024;
uint8_t tensor_arena[tensor_arena_size];

void setup() {
  Serial.begin(9600);
  
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  static tflite::MicroErrorReporter micro_error_reporter;
  tflite::ErrorReporter* error_reporter = &micro_error_reporter;
  const tflite::Model* gesture_model = tflite::GetModel(model);

  
  static tflite::AllOpsResolver micro_op_resolver;
  interpreter = new tflite::MicroInterpreter(gesture_model, micro_op_resolver, tensor_arena, tensor_arena_size, error_reporter);
  interpreter->AllocateTensors();

  TfLiteTensor* input = interpreter->input(0);
  TfLiteTensor* output = interpreter->output(0);
}

void loop() {

  float ax, ay, az, gx, gy, gz;
  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
    IMU.readAcceleration(ax, ay, az);
    IMU.readGyroscope(gx, gy, gz);
  }


  float input_data[6] = {ax, ay, az, gx, gy, gz};
  memcpy(interpreter->input(0)->data.f, input_data, sizeof(input_data));

  interpreter->Invoke();

  float output_data = interpreter->output(0)->data.f[0];

  if (output_data > 0.6) {
  Serial.println("Correct shot");
  Serial.write((uint8_t)1);

} else {
  Serial.println("Incorrect shot");
  Serial.write((uint8_t)0);
}

  
  delay(2000);
}