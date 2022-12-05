// s3_cote_lab5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
using namespace std;

constexpr auto lab_num = 5;
constexpr auto description = "dsa";

using byte = __int8;

constexpr auto header_size = 54;
constexpr auto bpp = 4;

void task_cpp(ifstream& input, ofstream& output)
{
    cout << "Решение на C++" << endl;

    // header
    byte* header = new byte[header_size];
    input.read(header, header_size);

    unsigned int width;
    constexpr auto width_offset = 18;
    memcpy(
        &width,
        header + width_offset,
        sizeof(width)
    );

    unsigned int height;
    constexpr auto height_offset = width_offset + sizeof(width);
    memcpy(
        &height,
        header + height_offset,
        sizeof(height)
    );


    output.write(header, header_size);
    delete[] header;
    //

    // body
    unsigned int body_size = bpp * width * height;
    byte* body = new byte[body_size];
    input.read(body, body_size);

    byte* color;
    for (unsigned int i = 0; i < width; ++i)
    {
        for (unsigned int j = height - height*i/width; j < height; ++j)
        {
            color = body + bpp * (i + j * width) + 0;
            *color = min((*color) * 2, 255);
        }
    }

    output.write(body, body_size);
    delete[] body;
    //
}

void task_asm(ifstream& input, ofstream& output)
{
    cout << "Решение на C++" << endl;

    // header
    byte* header = new byte[header_size];
    input.read(header, header_size);

    unsigned int width;
    constexpr auto width_offset = 18;
    memcpy(
        &width,
        header + width_offset,
        sizeof(width)
    );

    unsigned int height;
    constexpr auto height_offset = width_offset + sizeof(width);
    memcpy(
        &height,
        header + height_offset,
        sizeof(height)
    );


    output.write(header, header_size);
    delete[] header;
    //

    // body
    unsigned int body_size = bpp * width * height;
    byte* body = new byte[body_size];
    input.read(body, body_size);

    _asm {
        // EAX ~ i = 0
        mov EAX, 0
        //

        // for i in [0, width)
        loop_i:

        // EBX ~ j = height - height * i / width
        push EAX

        mul DWORD PTR height
        div DWORD PTR width
        mov EBX, DWORD PTR height
        sub EBX, EAX
        dec EBX

        pop EAX
        //

        // for j in [J, height)
        loop_j:

        // EDX ~ color = body + bpp * (i + j * width) + 0;
        push EAX 
        push EBX

        xchg EAX, EBX // EAX~j, EBX~i

        mul DWORD PTR width // EAX *= width
        add EAX, EBX // EAX += i
        mov EBX, 4
        mul EBX // EAX *= 4
        mov EDX, DWORD PTR body // EDX = body
        add EDX, EAX // EDX += EAX

        pop EBX
        pop EAX
        //

        // change color

        cmp [EDX], 200
        jna if_else
        
        mov [EDX], 255
        jmp if_end
        if_else:

        add [EDX], 55
        if_end:

        //

        // loops
        inc EBX // ++j

        cmp EBX, DWORD PTR height // j != height
        jne loop_j // => loop

        mov EBX, 0 // j = 0
        inc EAX // ++i

        cmp EAX, DWORD PTR width // i != width
        jne loop_i // => loop
        //
    }

    output.write(body, body_size);
    delete[] body;
    //
}



int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "lab #" << lab_num << endl;
    cout << description << endl;

    ifstream input("input.bmp", ios::binary);
    ofstream output("output.bmp", ios::binary);

    task_asm(input, output);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.