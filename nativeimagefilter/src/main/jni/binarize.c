#include <jni.h>
#include <time.h>
#include <android/log.h>
#include <android/bitmap.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define  LOG_TAG    "libimageprocessing"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


static void binarize(AndroidBitmapInfo* info, void* pixels){
    int xx, yy, red, green, blue;
    int threshold = 127;
    uint32_t* line;

    for(yy = 0; yy < info->height; yy++){
        line = (uint32_t*)pixels;
        for(xx =0; xx < info->width; xx++){

        //extract the RGB values from the pixel
            red = (int) ((line[xx] & 0x00FF0000) >> 16);
            green = (int)((line[xx] & 0x0000FF00) >> 8);
            blue = (int) (line[xx] & 0x00000FF );

            int gray = (int) (red * 0.3 + green * 0.59 + blue * 0.11);

            //get binary value
            if (gray < threshold) {
                line[xx] = 0x000000;
            } else {
                line[xx] = 0xffffff;
            }
        }

        pixels = (char*)pixels + info->stride;
    }
}


JNIEXPORT void JNICALL Java_com_karumi_nativeimagefilter_filter_BinarizeImageFilter_binarize
(JNIEnv * env, jobject  obj, jobject bitmap)
{

    AndroidBitmapInfo  info;
    int ret;
    void* pixels;

    if ((ret = AndroidBitmap_getInfo(env, bitmap, &info)) < 0) {
            LOGE("AndroidBitmap_getInfo() failed ! error=%d", ret);
            return;
        }
    if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        LOGE("Bitmap format is not RGBA_8888 !");
        return;
    }

    if ((ret = AndroidBitmap_lockPixels(env, bitmap, &pixels)) < 0) {
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
    }

    binarize(&info,pixels);

    AndroidBitmap_unlockPixels(env, bitmap);
}