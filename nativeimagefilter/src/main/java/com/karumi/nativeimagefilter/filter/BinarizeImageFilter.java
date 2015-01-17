package com.karumi.nativeimagefilter.filter;

import android.graphics.Bitmap;

import com.karumi.nativeimagefilter.ImageFilter;

/**
 * This is a binarizeImageFilter, this filter take an image and transform on black and white
 * image, the threshold value to take the decision between black and white is 127.
 */
public class BinarizeImageFilter implements ImageFilter{

    static {
        System.loadLibrary("binarize");
    }

    @Override
    public Bitmap apply(Bitmap bitmap) {
        if (!bitmap.isMutable()){
            throw new IllegalArgumentException("the bitmap is inmutable.");
        }

        if(bitmap.isRecycled()){
            throw new IllegalArgumentException("this bitmap is recycle.");
        }

        binarize(bitmap);

        return bitmap;
    }

    public native void binarize(Bitmap bmp);
}
