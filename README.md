# PXD_cubemap_sampling
Trying to make the cubemap sampling less branched as possible mainly for GPU implementations but tested in CPU.
- The implementation is taken from [Oyun-Teknolojileri/textureUtil.shader](https://github.com/Oyun-Teknolojileri/ToolKit/blob/Engine/Resources/Engine/Shaders/textureUtil.shader)

## Usage
- Clone the repository with ```git clone --recursive https://github.com/alpertunga-bile/PXD_cubemap_sampling.git``` command
- Run the CMake with the CMakeLists.txt file
- The project will create two executables which are named **pxd-cubesample-test** and **pxd-cubesample-benchmark**. As the names suggest, test executable is checking the correctness of the refactored function and benchmark executable is checking the performance of the refactored function
