from PIL import Image
import scipy.fftpack as fp
import matplotlib.pylab as pylab
import numpy as np
import numpy.fft

# Source Image FT
imsrc = np.array(Image.open('../images/rhino.jpg').convert('L'))

freqsrc = fp.fft2(imsrc)
ftsrc =20*np.log10( 0.01 + np.abs(fp.fftshift(freqsrc)))
ftsrcinv = fp.ifft2(freqsrc).real

# add noise
imcpy = np.copy(imsrc)
ly, lx = imcpy.shape

for y in range(0, ly, 10): 
    imcpy[y, :] = 0
    
freqcpy = fp.fft2(imcpy)
ftcpy =20*np.log10( 0.01 + np.abs(fp.fftshift(freqcpy)))
ftcpyinv = fp.ifft2(freqcpy).real

# filtering
ftcpyshift = fp.fftshift(freqcpy)
for y in range(34, ly, 34): 
    if y != 170 : 
        ftcpyshift[y-10:y+10,230:270] = 0
        
ftadj = 20*np.log10( 0.01 + np.abs(ftcpyshift))
ftadjinv = fp.ifft2(fp.ifftshift(ftcpyshift)).real

pylab.figure(figsize=(25,20))

pylab.subplot(3,3,1), pylab.imshow(imsrc, cmap='gray'), pylab.title("Source")
pylab.subplot(3,3,2), pylab.imshow(ftsrc, cmap='gray'), pylab.title("Source FT")
pylab.subplot(3,3,3), pylab.imshow(ftsrcinv, cmap='gray'), pylab.title("Source InvFT")

pylab.subplot(3,3,4), pylab.imshow(imcpy, cmap='gray'), pylab.title("Noise")
pylab.subplot(3,3,5), pylab.imshow(ftcpy, cmap='gray'), pylab.title("Noise FT")
pylab.subplot(3,3,6), pylab.imshow(ftcpyinv, cmap='gray'), pylab.title("Noise InvFT")

pylab.subplot(3,3,7), pylab.imshow(ftadj, cmap='gray'), pylab.title("Filtered")
pylab.subplot(3,3,8), pylab.imshow(ftadjinv, cmap='gray'), pylab.title("Filtered Image")
pylab.subplot(3,3,9), pylab.imshow(imsrc, cmap='gray'), pylab.title("Source")



