#!/bin/bash
cmake -H. -Bbuild/linux-intermediate && cmake --build ./build/linux-intermediate -- -j5 && cd build/Release-LinuxTests && ./Vic2ToHoi4ConverterTests && cd ..