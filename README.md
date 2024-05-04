# ShaderTestFrameworkExamples

Example projects that show how to use [Shader Test Framework](https://github.com/KStocky/ShaderTestFramework)

## What is Shader Test Framework

An automation testing framework for testing shader code. Based on Catch2. It uses D3D12 and requires HLSL 2021

It is a framework that is intended to be used with another testing framework such as [Catch2](https://github.com/catchorg/Catch2/tree/devel) to add shader testing capabilities to your already existing test suite. It is currently very experimental, meaning that every merge to main will likely break all old code. The purpose of this project is to explore how we can write unit tests in HLSL.

## Getting Started

This should be enough to grab the repo and build everything provided you have a recent install of Visual Studio 2022 and CMake.
```
$ git clone https://github.com/KStocky/ShaderTestFrameworkExamples
$ cd ShaderTestFrameworkExamples
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```

From there you can run the example project and having a look through the CMakeLists.txt to see how you might make use of [Shader Test Framework](https://github.com/KStocky/ShaderTestFramework) in your own projects.

There is also a much more in depth [tutorial](https://github.com/KStocky/ShaderTestFramework/blob/main/docs/Tutorial.md). This describes the requirements in detail, then takes you through how to include the framework in your project, and then how to write tests for your shader code.
