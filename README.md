# Example of vector addition with normal scalar and SIMD with avx2

### Compile 

```bash 
gcc -mavx2 simd.c -o runner
```

### Run

```bash
./runner <array size>
```

## Comparison

![alt text](./time_comparrison.png "SIMD vs. Scalar")


