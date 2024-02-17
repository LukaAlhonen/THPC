
def unroll_loop(degree: int) -> str:
    retval = ""
    if degree == 0:
        retval += f'a[i] = i;\n'
    else:
        retval += unroll_loop(degree - 1)
        if degree != 1:
            retval += f'\t\ta[i + {degree - 1}] = i + {degree - 1};\n'
    return retval
    
def create_programs() -> None:    
    i = 1
    while(i <= 32):
        program = \
f"""
#include <iostream>
#include <cstdint>
#include <chrono>

double unrolled_loop_{i}(int32_t *a, int size)
{{
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i += {i}) {{
        {unroll_loop(i)[:-1]}
    }}
    auto finnish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finnish - start;

    return elapsed.count();
}}

int main()
{{
    int size = 1048576;
    int32_t a[size];

    double duration = unrolled_loop_{i}(a, size);
    std::cout << duration << std::endl;

    return 0;
}}
"""        
        print('Creating program ...')
        print(f'Writing program to p03_{i}.cpp ...')
        with open(f'p03_{i}.cpp', 'w') as f:
            f.write(program)
        print('Done')
        
        i = i*2

def main() -> None:
    create_programs()

if __name__ == '__main__':
    main()