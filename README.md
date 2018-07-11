# Requirements
In order to use these examples:
- Make sure you have 
[MATRIX HAL](https://matrix-io.github.io/matrix-documentation/matrix-hal/overview/) installed on your MATRIX device

# Download Examples
The following commands download and compile all the examples:

```language-cpp
sudo apt-get install cmake g++ git
cd ~/
git clone https://github.com/matrix-io/matrix-hal-examples.git
cd matrix-hal-examples
mkdir build
cd build
cmake ..
make -j4
```
