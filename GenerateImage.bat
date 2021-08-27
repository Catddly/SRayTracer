@ECHO OFF
TITLE ImageGenerator
:: generate
cd x64\Debug\
SRayTracer.exe > image.ppm
ECHO Generate image successfully!
PAUSE