## Introduction

This is small collection of bindings to a few ArrayFire functions
for Octave and MATLAB. These bindnings where mainly created to speed
up convolutions when using the DREAM Toolbox available here:

https://github.com/frli8848/DREAM

## Build Instructions

1. Install the ArrayFire library https://arrayfire.com
2. Build the Octave and/or MATLAB bindnings using:
```
$ git clone https://github.com/frli8848/af_octave.git
$ cd af_octave
$ mkdir build
$ cmake ..
$ make -j8
```

### Octave Bindings

Set the path to the `build/oct` folder in your `.octaverc` file using, for example,
```matlab
addpath('/home/<USER>/af_octave/build/oct')
```
if you have cloned `af_octave` in your home folder (replace `<USER>` with the true user name).

### MATLAB Bindings

Set the path to the `build/mex` folder in your `starup.m` file using, for example,

```matlab
addpath('/home/<USER>/af_octave/build/mex')
```
if you have cloned `af_octave` in your home folder (replace `<USER>` with the true user name).
