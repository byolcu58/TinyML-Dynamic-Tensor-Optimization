#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

// Eski tip Enum (Hemen her derleyici destekler)
enum DataType {
    TYPE_FLOAT32,
    TYPE_FLOAT16,
    TYPE_INT8
};

struct Tensor {
    DataType type;
    size_t size;
    float scale;      
    int zero_point;   

    union DataPtr {
        float* f32;
        unsigned short* f16; // uint16_t yerine unsigned short
        signed char* i8;     // int8_t yerine signed char
    } data;

    Tensor(size_t s, DataType t) : size(s), type(t), scale(1.0f), zero_point(0) {
        if (type == TYPE_FLOAT32) data.f32 = new float[size];
        else if (type == TYPE_FLOAT16) data.f16 = new unsigned short[size];
        else if (type == TYPE_INT8) data.i8 = new signed char[size];
    }
};

void quantize(float* input, signed char* output, size_t size, float scale, int zero_point) {
    for (size_t i = 0; i < size; ++i) {
        float val = floor((input[i] / scale) + zero_point + 0.5f); // round yerine manuel yuvarlama
        if (val > 127) val = 127;
        if (val < -128) val = -128;
        output[i] = (signed char)val;
    }
}

int main() {
    std::cout << "--- TinyML Dinamik Tensor Uygulamasi ---" << std::endl;
    const size_t element_count = 5;
    float raw_data[5] = {0.85f, -0.42f, 1.1f, -0.95f, 0.22f};

    Tensor f32_tensor(element_count, TYPE_FLOAT32);
    for(size_t i=0; i<element_count; i++) f32_tensor.data.f32[i] = raw_data[i];

    Tensor i8_tensor(element_count, TYPE_INT8);
    i8_tensor.scale = 0.01f; 
    i8_tensor.zero_point = 0;

    quantize(f32_tensor.data.f32, i8_tensor.data.i8, element_count, i8_tensor.scale, i8_tensor.zero_point);

    for (size_t i = 0; i < element_count; ++i) {
        std::cout << "F32: " << f32_tensor.data.f32[i] 
                  << "  =>  Int8: " << (int)i8_tensor.data.i8[i] << std::endl;
    }
    return 0;
}
