"""
SCC0251 - Image Processing and Analysis (2024/1)

*** ASSIGNMENT 0 - HOW TO DO ASSIGNMENTS ***

Author: André Zanardi Creppe
Nusp: 11802972
"""

import imageio.v3 as imageio

filename = input()
xpos = int(input())
ypos = int(input())

# filename = 'C:\\Users\\andre\\Documents\\Programming\\CompCodes\\SCC0251_ImgProc\\imageprocessing_course_icmc-master\\images\\dog.png'
# xpos = 0
# ypos = 0

img = imageio.imread(filename.rstrip())

r, g, b = img[xpos][ypos]
print(f'{r} {g} {b}')
