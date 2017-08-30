# Repository name: libecg-test
A Command Line Interface (CLI) prototype for libecg repo to measure signal compression performance and distortion.

## Repo Description
The prototype application is a test scenario to examine the integrity of the hybrid compression algorithm proposed by _libecg_. It compresses and then decompresses given signal based on given Threshold and Aperture as inputs to measure __Compression Ratio__, __Percent Root-Mean-Square Difference__, and __Quality Score__. Next, it utilizes ChartDirector library to create a line chart of the overlapping signals (original and reconstructed) to visually demonstrate the signal distortion.

Lastly, the prototype attempts to compress the signal again, but this time within a limited range of threshold and aperture (which means compressing it multiple times) in order to reveal the affect of different input factors.

## Dependencies
1. libecg (v >= 1.1.0.3)
2. ChartDirector © 2015 Advanced Software Engineering Limited. All rights reserved. (Extract the file _libchartdir.so_ from _chartdir_cpp_linux_64.tar.gz_ and place into _ChartDirector/lib_)

## Sample Output
`Received parameters:`
`- ECG signal dataset: ECGs/samples100.txt`
`- Dataset length: 3600`
`- Threshold: 7`
`- Aperture: 15`
`Initialising Encoder...`
`Reading data...`
`Encoder object initialised by 3600 samples.`
`Further analysis:`
`- Samples ranging from 895 to 1216. Hence, 11 bits per sample needed.`
`- The total number of 39600 bits required to represent the entire dataset.`
`Compressing...`
`Phase 1: Lossless Compression (3671 items)`
`Phase 2-1: Lossy Compression Filter (3671 items)`
`Phase 2-2: Redundant Error Eliminator (525 items)`
`Phase 2-3: Error Count Controller (529 items)`
`Phase 3: Sample Scale Down (530 items)`
`Embedding additional data...`
`Translating 534 decimal items into bits...`
`Translated into 3874 bits.`
`Compression is done.`
`CR: 10.221992`
`Initialising Decoder...`
`Translating 3874 bits...`
`Translated into 534 decimal numbers.`
`Decoder object initialised.`
`Decompressing...`
`Reading embedded data...`
`Phase 1: Sample Scale Up (530 items)`
`Phase 2: Redundant Error Recovery (3671 items)`
`Phase 3: Decompression (3600 items)`
`Decompression is done.`
`PRD: 0.615284`
`QS: 16.613459`
