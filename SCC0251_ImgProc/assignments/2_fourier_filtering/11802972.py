"""
SCC0251 - Image Processing and Analysis (2024/1)

*** ASSIGNMENT 2 - FOURIER TRANSFORM AND FILTERING IN FREQUENCY DOMAIN ***

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

def filter_image(F, H, P, Q):
  """ Function that applies the filter to the frequency domain,
  uses the IFFT to get the inverse FFT of the image,
  and returns it back to the spatial domain h.
  """
  # Apply the filter.
  F = F * H

  # Get the inverse FFT of the image to return it back to the spatial domain h.
  new_img = np.fft.ifft2(np.fft.ifftshift(F))
  new_img = np.real(new_img / np.sqrt(P * Q))

  # Normalize the image back to [0 - 255]
  min_value = np.min(new_img)
  max_value = np.max(new_img)
  new_img = (new_img - min_value) * (255 / (max_value - min_value))

  return new_img

def rmse_score(rest_img, ref_img):
  """ Calculates the rooted mean square loss (RMSE) of two images.
  """ 
  squared_diff = np.square(np.subtract(rest_img, ref_img))
  mse_loss = np.mean(squared_diff)
  rmse_loss = np.sqrt(mse_loss)
  return rmse_loss

# ==================================================================
# ==================== FUNCTIONS: IDEAL FILTERS ====================
# ==================================================================

def ideal_filter(P, Q):
  """ Calculates the base range for ideal filters.
  """
  filter = np.zeros((P, Q), dtype=np.float32)
  for u in range(P):
    for v in range(Q):
      filter[u, v] = np.sqrt((u - P // 2) ** 2 + (v - Q // 2) ** 2) # "//" -> floor division

  return filter

def ideal_low_pass(input_img, r):
  """ Ideal low-pass filter root function.
  """
  F = np.fft.fftshift(np.fft.fft2(input_img))
  P, Q = F.shape

  dist = ideal_filter(P, Q)
  H = np.where(dist <= r, 1, 0) # Low-pass filtering
  
  filtered_img = filter_image(F, H, P, Q)

  return filtered_img, H, F

def ideal_high_pass(input_img, r):
  """ Ideal high-pass filter root function.
  """
  F = np.fft.fftshift(np.fft.fft2(input_img))
  P, Q = F.shape

  dist = ideal_filter(P, Q)
  H = np.where(dist <= r, 0, 1) # High-pass filtering

  filtered_img = filter_image(F, H, P, Q) 

  return filtered_img, H, F

def ideal_band_stop(input_img, r1, r2):
  """ Ideal band-stop filter root function
  """
  F = np.fft.fftshift(np.fft.fft2(input_img))
  P, Q = F.shape

  dist1 = ideal_filter(P, Q)
  dist2 = ideal_filter(P, Q)

  # Band-stop filtering
  filter1 = np.where(dist1 <= r1, 1, 0)
  filter2 = np.where(dist2 <= r2, 0, 1)

  H = np.abs(filter1 - filter2)

  filtered_img = filter_image(F, H, P, Q)

  return filtered_img, H, F

# ==============================================================
# ==================== FUNCTIONS: LAPLACIAN ====================
# ==============================================================

def laplacian_high_pass_filter(P, Q):
  """ Calculates the laplacian high-pass filter.
  """
  filter = np.zeros((P, Q), dtype=np.float32)
  for u in range(P):
    for v in range(Q):
      filter[u, v] = -4 * np.pi**2 * ((u - P // 2) ** 2 + (v - Q // 2) ** 2)

  return filter

def laplacian_high_pass(input_img):
  """ Laplacian high-pass filter root function
  """
  F = np.fft.fftshift(np.fft.fft2(input_img))
  P, Q = F.shape

  H = laplacian_high_pass_filter(P, Q)

  filtered_img = filter_image(F, H, P, Q)

  return filtered_img, H, F

# =============================================================
# ==================== FUNCTIONS: GAUSSIAN ====================
# =============================================================

def gaussian_low_pass_filter(P, Q, sigma1, sigma2):
  """ Calculates the gaussian low-pass filter.
  """
  filter = np.zeros((P, Q), dtype=np.float32)
  for u in range(P):
    for v in range(Q):
      filter[u, v] = np.exp(-(((u - P // 2) ** 2) / (2 * sigma1**2)) - (((v - Q // 2) ** 2) / (2 * sigma2**2)))

  return filter

def gaussian_low_pass(input_img, sigma1, sigma2):
  """ Gaussian low pass filter root function
  """
  F = np.fft.fftshift(np.fft.fft2(input_img))
  P, Q = F.shape

  H = gaussian_low_pass_filter(P, Q, sigma1, sigma2)

  filtered_img = filter_image(F, H, P, Q)

  return filtered_img, H, F

# ================================================
# ==================== "MAIN" ====================
# ================================================

# -------------------- TEST INPUTS --------------------

# >> Fixed Testing Data
# input_filename = './images/apollo17.png'
# ref_filename = './images/apollo17_ref-case7.png'
# filter_index = 3
# r = 0
# r1 = 0
# r2 = 0
# sigma_1 = 0
# sigma_2 = 0

# -------------------- READING INPUTS --------------------

input_filename = str(input().rstrip())
ref_filename = str(input().rstrip())
filter_index = int(input())

input_img = imageio.imread(input_filename)
ref_img = imageio.imread(ref_filename)

# -------------------- SELECTING FILTER --------------------

# 0. Ideal Low-Pass >> with radius r
if (filter_index == 0):
  r = float(input())
  restored_img, filter, fft_img = ideal_low_pass(input_img, r)

# 1. Ideal High-Pass >> with radius r
elif (filter_index == 1):
  r = float(input())
  restored_img, filter, fft_img = ideal_high_pass(input_img, r)

# 2. Ideal Band-Stop >> with radius r1 and r2
elif (filter_index == 2):
  r1 = float(input())
  r2 = float(input())
  restored_img, filter, fft_img = ideal_band_stop(input_img, r1, r2)

# 3. Laplacian high-pass
elif (filter_index == 3):
  restored_img, filter, fft_img = laplacian_high_pass(input_img)

# 4. Gaussian Low-Pass >> with sigma_1 and sigma_2
elif filter_index == 4:
  sigma_1 = float(input())
  sigma_2 = float(input())
  restored_img, filter, fft_img = gaussian_low_pass(input_img, sigma_1, sigma_2)
    
# -------------------- RESULTS --------------------

loss = rmse_score(restored_img, ref_img)
print(round(loss, 4))

# plt.figure()
# plt.subplot(1,4,1)
# plt.imshow(input_img, cmap="gray", vmin=0, vmax=255)
# plt.title('input_img')
# plt.subplot(1,4,2)
# plt.imshow(np.log(1 + np.fft.fftshift(np.abs(fft_img))), cmap="gray")
# plt.title('fft_img')
# plt.subplot(1,4,3)
# plt.imshow(filter, cmap="gray")
# plt.title('filter')
# plt.subplot(1,4,4)
# plt.imshow(restored_img, cmap="gray", vmin=0, vmax=255)
# plt.title('restored_img')
# plt.show()
