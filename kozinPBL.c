#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include "led-matrix-c.h"
#include "mnb_bmp.h"

int main(int argc, char const **argv)
{
    struct RGBLedMatrixOptions options;
    struct RGBLedMatrix *matrix;
    struct LedCanvas *offscreen_canvas;
    char rgb_sequence[] = "GBR";

    memset(&options, 0, sizeof(options));
    options.rows = options.cols = 64;
    options.led_rgb_sequence = rgb_sequence;
    matrix = led_matrix_create_from_options(&options, &argc, (char***)&argv);
    if (matrix == NULL) return 1;
    offscreen_canvas = led_matrix_create_offscreen_canvas(matrix);

    pthread_t recthread;
    if(pthread_create(&recthread, NULL, (void*)takeTimelapse, NULL)) {
        return -1;
    }

    int width, height;
    led_canvas_get_size(offscreen_canvas, &width, &height);



//あらかじめ宣言されいて使用可能な変数は，以下の4つ
//  int width, heigh; //width=64, height=64です
//  struct RGBLedMatrix *matrix; //LEDディスプレイパネルを表す変数
//  struct LedCanvas *offscreen_canvas; //バッファ
//LEDディスプレイパネルを光らせるのに使用する特別な関数は以下の4つのみ
//  void led_canvas_clear(struct LedCanvas *canvas); //LEDディスプレイパネル前面を黒にする
//  void led_canvas_set_pixel(struct LedCanvas *canvas, int x, int y,
//                            uint8_t r, uint8_t g, uint8_t b); //canvasのx,yにr,g,bの色を出す
//  struct LedCanvas *led_matrix_swap_on_vsync(struct RGBLedMatrix *matrix,
//                                             struct LedCanvas *canvas); //canvasの内容をLEDパネルに転送
//  int usleep(useconds_t usec); //usecマイクロ秒待機する．usecは1000000（1秒）まで

   #include<math.h>
    int i,j,k;
    double x,y;

     for(i=1;i<121;++i){
       // led_canvas_clear(offscreen_canvas); //canvasをクリア
       y=-31*sin(4*i*M_PI/180+M_PI/6)+31;
       x=-31*sin(3*i*M_PI/180)+31;
       for(j=1;j<4;++j){
         for(k=1;k<4;++k){
          led_canvas_set_pixel(offscreen_canvas, x-1+j, y-1+k, 2*i, 200, 4*i); //(i,i)に赤点を打つ
         }
       }   
       led_canvas_set_pixel(offscreen_canvas, x, y, 2*i, 200, 4*i); //(i,i)に赤点を打つ
       led_matrix_swap_on_vsync(matrix, offscreen_canvas); //canvasの内容をLEDパネルに転送
       usleep(20000);//100ミリ秒待機
     }
      for(i=121;i>0;--i){
       // led_canvas_clear(offscreen_canvas); //canvasをクリア
       y=-11*sin(4*i*M_PI/180+M_PI/6)+35;
       x=-10*sin(3*i*M_PI/180)+33;
       for(j=1;j<3;++j){
	   led_canvas_set_pixel(offscreen_canvas, x-1+j, y-1, 240-i, 150-i, 200-i); //(i,i)に赤点を打つ
       }
       led_canvas_set_pixel(offscreen_canvas, x, y, 240-i, 150-i, 200-i); //(i,i)に赤点を打つ
       led_matrix_swap_on_vsync(matrix, offscreen_canvas); //canvasの内容をLEDパネルに転送
       usleep(20000);//100ミリ秒待機
       }
      return 0;
}
