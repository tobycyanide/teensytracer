/***************************************************
  This is our GFX example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651
  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
  NOTE: This version is the same of the ILI9340_t3 library
  here just for testing...
 ****************************************************/

#include "arduinomacrofix.h"
#include <SPI.h>
#include <ILI9341_t3.h>
#include "include/tuple.h"
#include "include/color.h"
#include "include/shapes.h"
#include "include/light.h"
#include "include/matrix_helper.h"
#include "include/world.h"
#include "include/camera.h"
#include <Eigen/Dense>
#include <memory>


// For the Adafruit shield, these are the default.
#define TFT_DC  9
#define TFT_CS 10
#define TFT_RST 15
#define TFT_MOSI 11
#define TFT_CLK 13
#define TFT_MISO 12


uint8_t errorCode = 0;


ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_CLK, TFT_MISO);


int x_width = 320;
int y_height = 240;



void setup() {
    tft.begin();
    tft.setRotation( 3 );
    tft.fillScreen(ILI9341_BLACK);

    // Serial
    if(true) {
        Serial.begin(9600);
        tft.setTextColor(ILI9341_YELLOW);
        tft.setCursor(98, 42);
        tft.print("waiting for");
        tft.setCursor(100, 80);
        tft.print("Arduino");
        tft.setCursor(60, 120);
        tft.print("Serial Monitor");
        tft.setTextColor(ILI9341_GREEN);
        while (!Serial && millis() < 8000) { // wait for Arduino Serial Monitor
            tft.fillRect(118, 182, 42, 18, ILI9341_BLACK);
            tft.setCursor(118, 182);
            tft.print((8000.0 - (float)millis()) / 1000.0, 1);
            tft.print(" sec");
        }
    }

//    pinMode(6, OUTPUT);
//    digitalWriteFast(6, LOW);
//    tft.begin();
//    Serial.begin(38400);
//    delay(5000);
//    Serial.println("Begin");
//    Serial.println("Begin");
//    tft.fillScreen(ILI9341_BLACK);
//    Serial.println("Screen filled");
//    digitalWriteFast(6, HIGH);


    delay(1000);
    Serial.println("Beginning");
    delay(1000);
    World w;
    Serial.println("Created world");
    delay(1000);
    w.light = PointLight(Point(-10, 10, -10), Color(1, 1, 1));
    Serial.println("Set Light");
    delay(1000);
    std::unique_ptr<Shape> floor_sphere = std::make_unique<Sphere>();
    Serial.println("Created Material");
    delay(1000);
    floor_sphere->set_transform(Scaling(10, .01, 10));
    floor_sphere->material = Material();
    floor_sphere->material.color = Color(1, 0.9, 0.9);
    floor_sphere->material.specular = 0;
    Serial.println("Set Material");
    delay(1000);
    w.addObject(std::move(floor_sphere));
    Serial.println("Adding to world");
    delay(1000);

    //CODE GETS TO HERE

    std::unique_ptr<Shape> left_wall = std::make_unique<Sphere>();
    Serial.println("Created left");
    delay(1000);
    left_wall->transform = Translation(0, 0, 5) *
                           Rotation_Y(-M_PI / 4) * Rotation_X(M_PI / 2) *
                           Scaling(10, 0.01, 10);
    left_wall->material = w.objects[0]->material;
    Serial.println("Set transform");
    delay(1000);
    w.addObject(std::move(left_wall));


    std::unique_ptr<Shape> right_wall = std::make_unique<Sphere>();
    right_wall->transform = Translation(0, 0, 5) *
                            Rotation_Y(M_PI / 4) * Rotation_X(M_PI / 2) *
                            Scaling(10, 0.01, 10);
    right_wall->material = w.objects[0]->material;
    w.addObject(std::move(right_wall));

    std::unique_ptr<Shape> middle = std::make_unique<Sphere>();
    middle->transform = Translation(-0.5, 1, 0.5);
    middle->material = Material();
    middle->material.color = Color(0.1, 1, 0.5);
    middle->material.diffuse = 0.7;
    middle->material.specular = 0.3;
    w.addObject(std::move(middle));

    std::unique_ptr<Shape> right = std::make_unique<Sphere>();
    right->transform = Translation(1.5, 0.5, -0.5) * Scaling(0.5, 0.5, 0.5);
    right->material = Material();
    right->material.color = Color(0.5, 1, 0.1);
    right->material.diffuse = 0.7;
    right->material.specular = 0.3;
    w.addObject(std::move(right));


    std::unique_ptr<Shape> left = std::make_unique<Sphere>();
    left->transform = Translation(-1.5, 0.33, -0.75) * Scaling(0.33, 0.33, 0.33);
    left->material = Material();
    left->material.color = Color(1, 0.8, 0.1);
    left->material.diffuse = 0.7;
    left->material.specular = 0.3;
    w.addObject(std::move(left));

    Camera c = Camera(x_width, y_height, M_PI / 3);
    c.transform = ViewTransform(Point(0, 1.5, -5), Point(0, 1, 0), Vector(0, 1, 0));

    for (int y = 0; y < y_height; y++) {
        for (int x = 0; x < x_width; x++) {
            Serial.println(w.objects.size());
            Ray ray = c.ray_for_pixel(x, y);
            Color c_unclamped = w.color_at(ray);
            Color c = c_unclamped.to_clamped_rgb();
            tft.drawPixel(y, 320 - x, tft.color565(c.red(), c.green(), c.blue()));
        }
    }
}

void loop(void) {

}