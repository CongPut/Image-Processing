//manipulaion image
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main(void){
    int width; 
    int height;
    int channels;
    //Input dataset
    unsigned char *img=stbi_load("dataset.png",&width,&height,&channels,0);

    if(img==NULL){
        printf("No image found !\n");
        exit(1);
    } else {
        printf("Image is %dpx width, %dpx height, and %d channel\n",width,height,channels);
    }

    // Convert image to bnw
    size_t img_size = width * height * channels;
    int gray_channels = channels == 4 ? 2 : 1;
    size_t gray_img_size = width * height * gray_channels;

    //declare that the bnw image will be the same size as the original image
    unsigned char *gray_img = malloc(gray_img_size); //allocate
    if(gray_img == NULL) {
        printf("Unable to allocate memory for the gray image.\n");
        exit(1);
    }

    for(unsigned char *ip = img, *op = gray_img; ip != img + img_size; ip += channels, op += gray_channels) {
        *op = (uint8_t)((*ip + *(ip + 1) + *(ip + 2))/3.0); //rgb in 8 byte
        if(channels == 4) {
            *(op + 1) = *(ip + 3);
        }
    }

    stbi_write_png("dataset_bnw.png", width, height, gray_channels, gray_img, width * gray_channels);

    // // Convert image to sepia (manipulation of lights)
    unsigned char *sepia_img = malloc(img_size);
    if(sepia_img == NULL) {
        printf("Unable to allocate memory for the sepia image.\n");
        exit(1);
    }

    //outputRed = (inputRed * .393) + (inputGreen *.769) + (inputBlue * .189)
    //outputGreen = (inputRed * .349) + (inputGreen *.686) + (inputBlue * .168)
    //outputBlue = (inputRed * .272) + (inputGreen *.534) + (inputBlue * .131)

    for(unsigned char *ip = img, *op = sepia_img; ip != img + img_size; ip += channels, op += channels) {
        *op       = (uint8_t)fmin(0.393 * *ip + 0.769 * *(ip + 1) + 0.189 * *(ip + 2), 255.0);         // red
        *(op + 1) = (uint8_t)fmin(0.349 * *ip + 0.686 * *(ip + 1) + 0.168 * *(ip + 2), 255.0);         // green
        *(op + 2) = (uint8_t)fmin(0.272 * *ip + 0.534 * *(ip + 1) + 0.131 * *(ip + 2), 255.0);         // blue        
        if(channels == 4) {
            *(op + 3) = *(ip + 3);
        }
    }

    stbi_write_png("dataset_sepia.png", width, height, channels, sepia_img, width * channels);

    stbi_image_free(img);
    free(gray_img);
    free(sepia_img);
}
