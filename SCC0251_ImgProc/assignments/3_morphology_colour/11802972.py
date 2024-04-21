"""
SCC0251 - Image Processing and Analysis (2024/1)

*** ASSIGNMENT 3 - COLOR & SEGMENTATION & MORPHOLOGY ***

Author: André Zanardi Creppe
Nusp: 11802972
"""

# =================================================
# ==================== IMPORTS ====================
# =================================================

import numpy as np
import imageio.v3 as imageio
# import matplotlib.pyplot as plt

# ============================================================
# ==================== FUNCTIONS: GENERAL ====================
# ============================================================

def to_grayscale(img):
  """ Converts a given RGB image to grayscale. If the image is already one-channel, just returns it.
  """
  if len(img.shape) > 2: # If image is RGB
    img = np.dot(img, [0.2989, 0.5870, 0.1140]).astype(np.int64)
    
  return img

def rmse_score(img, ref_img):
  """ Calculates the rooted mean square loss (RMSE) of two images.
  """ 
  squared_diff = np.square(np.subtract(img, ref_img))
  mse_loss = np.mean(squared_diff)
  rmse_loss = np.sqrt(mse_loss)
  return rmse_loss

def rmse_rgb_score(rgb_img, ref_img):
  """ Calculates the rooted mean square loss (RMSE) for two RGB images.
  """
  error_R = rmse_score(rgb_img[:,:,0], ref_img[:,:,0])
  error_G = rmse_score(rgb_img[:,:,1], ref_img[:,:,1])
  error_B = rmse_score(rgb_img[:,:,2], ref_img[:,:,2])
  
  error = (error_R + error_G + error_B)/3
  return error

# ==================================================================
# ==================== FUNCTIONS: LIMIARIZATION ====================
# ==================================================================

def otsu_threshold(img, th_max=256):
  """ Apply the Otsu's binarization technique to an image.
  """
  total_pixels = img.size

  best_th = None
  min_sigma = np.inf
  
  for th in range(1, th_max):
    # Create the thresholded image
    thresholded_im = np.zeros_like(img)
    thresholded_im[img >= th] = 1
    
    # Compute weights
    count_pixels_1 = np.count_nonzero(thresholded_im)
    w_b = count_pixels_1 / total_pixels
    w_a = 1 - w_b

    # If one of the classes is empty >> threshold not considered
    if (w_b == 0) or (w_a == 0):
      continue

    # Find all pixels belonging to each class
    class_0_pixels = img[thresholded_im == 0]
    class_1_pixels = img[thresholded_im == 1]

    # Variance of each class
    sig_a = np.var(class_0_pixels) if len(class_0_pixels) > 0 else 0 # if to avoid warnings and errors
    sig_b = np.var(class_1_pixels) if len(class_1_pixels) > 0 else 0

    # Calculate Otsu sigma
    sigma = ((w_a * sig_a) + (w_b * sig_b))

    if sigma < min_sigma:
      min_sigma = sigma
      best_th = th

  # Binarize the image based on the best threshold
  binary_img = np.where(img > best_th, 255, 0)

  return binary_img

# ===============================================================
# ==================== FUNCTIONS: MORPHOLOGY ====================
# ===============================================================

def erosion(img):
  """ Execute the erosion operation into an image using a square 3x3 kernel.
  """
  kernel = np.ones((3,3)) # square(3)
  
  M, N = img.shape
  img_ers = np.zeros((M,N))
  
  img_pad = np.pad(img, pad_width=1)

  for y in range(1, M-1):
    for x in range(1, N-1):
      neighborhood = img_pad[y-1:y+2, x-1:x+2]
                  
      img_ers[y, x] = np.min(neighborhood * kernel)
  
  return img_ers

def dilation(img):
  """ Execute the dilation operation into an image using a square 3x3 kernel.
  """
  kernel = np.ones((3,3)) # square(3)
  
  M, N = img.shape
  img_dil = np.zeros((M,N))
  
  img_pad = np.pad(img, pad_width=1)

  for y in range(1, M-1):
    for x in range(1, N-1):
      neighborhood = img_pad[y-1:y+2, x-1:x+2]
                  
      img_dil[y, x] = np.max(neighborhood * kernel)
  
  return img_dil

# ============================================================
# ==================== FUNCTIONS: HEATMAP ====================
# ============================================================

def filter_gaussian(P, Q):
  s1 = P
  s2 = Q

  D = np.zeros([P, Q]) # Compute Distances
  for u in range(P):
    for v in range(Q):
      x = (u-(P/2))**2/(2*s1**2) + (v-(Q/2))**2/(2*s2**2)
      D[u, v] = np.exp(-x)
      
  return D

def map_value_to_color(value, min_val, max_val, colormap):
  # Scale the value to the range [0, len(colormap) - 1]
  scaled_value = (value - min_val) / (max_val - min_val) * (len(colormap) - 1)
  # Determine the two closest colors in the colormap
  idx1 = int(scaled_value)
  idx2 = min(idx1 + 1, len(colormap) - 1)
  # Interpolate between the two colors based on the fractional part
  frac = scaled_value - idx1
  color = [
    (1 - frac) * colormap[idx1][0] + frac * colormap[idx2][0],
    (1 - frac) * colormap[idx1][1] + frac * colormap[idx2][1],
    (1 - frac) * colormap[idx1][2] + frac * colormap[idx2][2]
  ]
  
  return color

def generate_heatmap(mask_img, heatmap_colors):
  M, N = mask_img.shape
  
  color_distribution = filter_gaussian(M, N)
  min_val = np.min(np.array(color_distribution))
  max_val = np.max(np.array(color_distribution))

  heatmap_image = np.zeros([M, N, 3]) # Imagem RGB vazia
  for i in range(M):
    for j in range(N):
      heatmap_image[i, j] = map_value_to_color(color_distribution[i, j], min_val, max_val, heatmap_colors)

  return heatmap_image

def generate_color_mask(mask_img, heatmap_img):
  M, N = mask_img.shape
  
  img_color = np.ones([M, N, 3]) # Imagem RGB vazia
  indexes = np.where(mask_img==0)
  img_color[indexes] = heatmap_img[indexes]
  
  return img_color

def combine_images(gray_img, color_img, alpha):
  """ Combines two images by an alpha ratio
  """
  gray_image_normalized = gray_img / np.max(gray_img)

  # Mix the grayscale image and heatmap using alpha compositing
  mixed_image = ((1 - alpha) * np.expand_dims(gray_image_normalized, axis=-1)) + ((alpha) * color_img)
  
  return mixed_image

# ================================================
# ==================== "MAIN" ====================
# ================================================

# -------------------- TEST INPUTS --------------------

# >> Fixed Testing Data
# cd C:\Users\andre\Documents\Programming\CompCodes\SCC0251_ImgProc\assignments\3_morphology_color
# input_filename = './images/chest_xray_1.png'
# ref_filename = './images/references/chest_xray_1_ref-case1.png'
# operation_array = '2 2 2 2 2 2 2 2 2 1 1 1'.split(' ')

# -------------------- READING INPUTS --------------------

input_filename = str(input().rstrip())
ref_filename = str(input().rstrip())
operation_array = str(input().rstrip()).split(' ')

input_img = imageio.imread(input_filename)
ref_img = imageio.imread(ref_filename)

# -------------------- IMAGE PROCESSING --------------------

# 1. Conversion to Grayscale
img_grey = to_grayscale(input_img)

# 2. Adaptive Limiarization (Otsu) to binarize the image
img_otsu = otsu_threshold(img_grey)

# 3. Create the binary mask by applying the sequence of Erosions and Dilations
img_mask = img_otsu.copy()

for op in operation_array:
  if op == '1':
    img_mask = erosion(img_mask)
  elif op == '2':
    img_mask = dilation(img_mask)
    
# 4. Create the heatmap using the given implementation.
heatmap_colors = [
  [1, 0, 1],  # Pink
  [0, 0, 1],  # Blue
  [0, 1, 0],  # Green
  [1, 1, 0],  # Yellow
  [1, 0, 0]   # Red
]
heatmap_img = generate_heatmap(img_mask, heatmap_colors)

# 5. Create the colored mask as a combination of the heatmap and the binary mask.
color_img = generate_color_mask(img_mask, heatmap_img)

# 6. Create the image ( G ) combining the image ( I ) with the colored mask.
alpha = 0.30
combined_img = combine_images(img_grey, color_img, alpha)

# -------------------- RESULTS COMPARISON --------------------

ref_img_norm = ref_img / np.max(ref_img)

loss = rmse_score(combined_img, ref_img_norm)
print(round(loss, 4))

# -------------------- Testing Area --------------------

# show_img = [input_img, img_grey, img_otsu, img_mask]
# show_img = [heatmap_img, color_img, combined_img]
# col = len(show_img)

# for index, img in enumerate(show_img):
#   plt.subplot(1, col, index+1)
#   plt.imshow(img, cmap='grey')
# plt.show()
