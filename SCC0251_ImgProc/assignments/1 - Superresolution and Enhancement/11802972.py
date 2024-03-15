"""
SCC0251 - Image Processing and Analysis (2024/1)

*** ASSIGNMENT 1 - SUPERRESOLUTION AND ENHANCEMENT ***

Author: André Zanardi Creppe
Nusp: 11802972
"""

import numpy as np
import imageio.v3 as imageio
# import matplotlib.pyplot as plt

# ==================== FUNCTIONS ====================

def histogram(img, no_levels):
    """ Calculates the intensity histogram of a given image.
    """ 
    hist = np.zeros(no_levels).astype(int)

    for i in range(no_levels):
        pixels_value_i = np.sum(img == i)
        hist[i] = pixels_value_i

    return hist

def cumultative_histogram(img, no_levels):
    """ Calculates the *cumultative* histogram of intensities from a given image.
    """ 
    hist = histogram(img, no_levels)

    histC = np.zeros(no_levels).astype(int)

    histC[0] = hist[0]
    for i in range(1, no_levels):
        histC[i] = hist[i] + histC[i-1]

    return histC

def single_histogram_equalization(img, no_levels):
    """ Enhancement tecnique that equalizes the histogram of a single image.
    """ 

    histC = cumultative_histogram(img, no_levels)

    N, M = img.shape
    img_eq = np.zeros([N, M]).astype(np.uint8)

    for z in range(no_levels):
        s = ((no_levels-1) / float(M * N)) * histC[z]
        img_eq[ np.where(img == z) ] = s

    return img_eq

def joint_histogram_equalization(img_list, no_levels):
    """ Enhancement tecnique that equalizes the histogram of a multiple images.
    One joint histogram is calculated and later used to equalize the images.
    """
    hist_sum = np.zeros(no_levels)
    for img in img_list:
        hist_sum += cumultative_histogram(img, no_levels)
    histC = hist_sum / int(len(img_list))

    # Enhancing each image using the joint histogram.
    enhanced_images = []
    for img in img_list:
        N, M = img.shape
        img_eq = np.zeros([N, M]).astype(np.uint8)

        for z in range(no_levels):
            s = ((no_levels-1) / float(M * N)) * histC[z]
            img_eq[ np.where(img == z) ] = s

        enhanced_images.append(img_eq)

    return enhanced_images

def gamma_correction(img, gamma):
    """ Calculates the pixel-wise enchancement using the gamma correction method.
    """ 
    img_hat = 255 * np.power(img / 255, 1/gamma)
    return img_hat

def super_resolution(images):
    """ Technique to increase the resolution of an image using 4 enchanced smaller images
    """
    
    # New resolution is twice as big.
    N = images[0].shape[0] * 2

    super_img = np.zeros((N, N))
    
    ## Old version left here to have a better idea of what the compact solution is 'doing'
    # for i in np.arange(0, N, 2):
    #     for j in np.arange(0, N, 2):
    #         for k in np.arange(0, 2):
    #             for m in np.arange(0, 2):
    #                 super_img[i + k][j + m] = images[k*2 + m][int(i/2)][int(j/2)]
    
    # Improved solution to avoid 'timeout' at RunCodes
    ## Solution inspired by: https://stackoverflow.com/questions/509211/how-slicing-in-python-works
    for k in range(2):
        for m in range(2):
            super_img[k:N:2, m:N:2] = images[k*2 + m]

    return super_img

def rmse(h, h_hat):
    """ Calculates the rooted mean square loss (RMSE) of two images.
    """ 
    squared_diff = np.square(np.subtract(h, h_hat))
    mse_loss = np.mean(squared_diff)
    rmse_loss = np.sqrt(mse_loss)
    return rmse_loss

# ==================== PROBLEM LOADING ====================

# >> Fixed Testing Data
# low_basename = './test_cases/04_low'
# high_filename = './test_cases/04_high.png'
# method = 2
# gamma = 1.0

low_basename = str(input().rstrip())
high_filename = str(input().rstrip())
method = int(input())
gamma = float(input())

lowimg_list = []
for i in range(4):
    lowimg_list.append(imageio.imread(low_basename + str(i) + '.png'))

highimg = imageio.imread(high_filename)

# ==================== IMAGE PROCESSING ====================

processed_imgs = []
levels = 256

# Case 0) No enhancement
if (method == 0):
    processed_imgs = lowimg_list

# Case 1) Single-image Cumulative Histogram
elif(method == 1):
    for lowimg in lowimg_list:
        eq_img = single_histogram_equalization(lowimg, levels)
        processed_imgs.append(eq_img)

# Case 2) Joint Cumulative Histogram
elif(method == 2):
    processed_imgs = joint_histogram_equalization(lowimg_list, levels)

# Case 3) Gamma Correction Function
elif(method == 3):
    for lowimg in lowimg_list:
        corr_img = gamma_correction(lowimg, gamma)
        processed_imgs.append(corr_img)

# ==================== SUPERRESOLUTION ====================

super_img = super_resolution(processed_imgs)

# ==================== REFERENCE COMPARISON ====================

loss = rmse(highimg, super_img)
print(round(loss, 4))

# plt.figure()
# plt.subplot(1,3,1)
# plt.imshow(highimg, cmap="gray", vmin=0, vmax=255)
# plt.title('ORIGINAL')
# plt.subplot(1,3,2)
# plt.imshow(super_img, cmap="gray", vmin=0, vmax=255)
# plt.title('SUPERIMAGE')
# plt.show()
