package com.karumi.nativeimagefilter;

import android.graphics.Bitmap;

/**
 * This is the contract that all filters must implement.
 */
public interface ImageFilter {
    public Bitmap apply(Bitmap bitmap);
}
