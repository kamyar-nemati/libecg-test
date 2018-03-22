# Repository name: libecg-test
A Command Line Interface (CLI) prototype for libecg repo to measure signal compression performance and distortion.

## Repo Description
The prototype application is a test scenario to examine the integrity of the hybrid compression algorithm proposed by _libecg_. It compresses and then decompresses given signal based on given Threshold and Aperture as inputs to measure __Compression Ratio__, __Percent Root-Mean-Square Difference__, and __Quality Score__. Next, it utilizes ChartDirector library to create a line chart of the overlapping signals (original and reconstructed) to visually demonstrate the signal distortion.

Lastly, the prototype attempts to compress the signal again, but this time within a limited range of threshold and aperture (which means compressing it multiple times) in order to reveal the affect of different input factors.

## Dependencies
1. [libecg](https://github.com/kamyar-nemati/libecg) (v >= 1.1.0.3)

> To get _libecg_ sub-project, run the following commands:
>> `git submodule init`
>>
>> `git submodule update`

2. ChartDirector © 2015 Advanced Software Engineering Limited. All rights reserved. (Extract the file _libchartdir.so_ from _chartdir_cpp_linux_64.tar.gz_ and place into _ChartDirector/lib_)

## Sample Output
![Signal Compression](https://user-images.githubusercontent.com/29518086/29853685-f23153b2-8d73-11e7-946f-dd8fa9c2256e.png "Signal Compression")
