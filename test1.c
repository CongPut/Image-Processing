//Convert image format
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
    //Input the dataset
    unsigned char *img=stbi_load("dataset-cover.jpg",&width,&height,&channels,0);

    if(img==NULL){
        printf("No image found !\n");
        exit(1);
    } else {
        printf("Image is %dpx width, %dpx height, and %d channel\n",width,height,channels);
    }
    
    //convert to png
    stbi_write_png("dataset.png",width,height,channels,img,width*channels);
    //convert to jpg
    //stbi_write_jpg("dataset.jpg",width,height,channels,img,100);

    stbi_image_free(img);

    return 0;
}
