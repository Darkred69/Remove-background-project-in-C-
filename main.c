#include <math.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "./stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./stb_image_write.h"

unsigned char *subtract(unsigned char *image1, unsigned char *image2, unsigned char *image3, int width, int height, int channel, int rate)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int change = 0;
            for (int k = 0; k < channel; k++)
            {
                 if (abs(image1[i * width * channel + j * channel + k] - image2[i * width * channel + j * channel + k]) < rate)
                 {
                     change+=1;
                 }
            }
            if(change != 3) {
                for (int k = 0; k < channel; k++)
                {
                    image3[i * width * channel + j * channel + k] = image2[i * width * channel + j * channel + k];
                }
            }
        }
    }
    return image3;
}






int main()
{

    int width, height, channel;
    int threshold = 80;
    char back_path[] = "./background.jpg";
    char weather_path[] = "./new_background.jpg";
    char woman_path[] = "./foreground.jpg";
    char save_path[] = "./new_res.jpg";

    // read image data
    unsigned char *back_img = stbi_load(back_path, &width, &height, &channel, 0);
    unsigned char *weather_img = stbi_load(weather_path, &width, &height, &channel, 0);
    unsigned char *woman_img = stbi_load(woman_path, &width, &height, &channel, 0);


    unsigned char *result_img = subtract(back_img, woman_img, weather_img, width, height, channel, threshold);
    stbi_write_jpg(save_path, width, height, channel, result_img, width * channel);

}
