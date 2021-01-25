// This code creates the image to the right >>
//
// (c) 2020 Mike Field <hamster@snap.net.nz>

#include <stdio.h>
#include <math.h>

int width  = 4660;
int height = 4660;

void make_ball(int ball_x, int ball_y, FILE *file){
      int i;
   for(i = 0; i < width; i++ ) {
      int j;
      for(j = 0; j < height; j++) {
         //Where center of ball y (0,0)
         int y = i - ball_x;
         int x = j - ball_y;

         if(x*x+ y*y < (width/16.0)*(width/16.0)) {
            double dx = x/(width/4.0);
            double dy = y/(width/4.0);
            double dz = sqrt(1.0 - dx*dx - dy*dy);
            int light = (dx*0.57-dy*0.57+dz*0.57)*255;

            if(light < 0) {
               putc(0, file);  // Red
               putc(0, file);  // Green
               putc(0, file);  // Blue
            } 
            else {
               putc(1, file);
               putc(1, file);
               putc(1, file);
            }
         } 
         else {
            putc(128, file);
            putc(128, file);
            putc(128, file);
         }
      }
   }
}

int main(int argc, char *argv[])
{
   FILE *file;

   if(argc != 2) {
      printf("You need to supply the file name\n");
      return -1;
   }

   printf("Creating file %s\n", argv[1]);
 
   file = fopen(argv[1],"w");
   if(file == NULL) {
      printf("Unable to open output image file\n");
      return -1;
   }

   fprintf(file, "P6\n");
   fprintf(file, "%i %i\n",width, height);
   fprintf(file, "255\n");

   make_ball(width/2, width-600, file);
   make_ball(0, 0, file);

   fclose(file);
   return 0;
}
