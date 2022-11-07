// s3_cote_lab4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

constexpr auto lab_num = 4;
constexpr auto description = "1) Подсчитать количество чисел, " \
"соответствующих определенному условию на некотором числовом промежутке." \
"2) Найти и вывести на экран двухсотое число или пару чисел соответствующих заданному условию." \
"Если таких чисел меньше двухсот, то вывести об этом сообщение на экран.\n" \
"Вариант 3: На промежутке от 1 до 100 000. " \
"Подсчитать количество таких чисел X, что(Х + X - 2) - делится на 3 без остатка.\n";


int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "lab #" << lab_num << endl;
    cout << description << endl;

    int number_of_matching_numbers = -1;
    int number_under_number_200 = -1;

    __asm {
        // EBX = 0 :счётчик
        mov EBX, 0
        // :temp
        push EBX

        // for: ECX = 1
        mov ECX, 1

        loop_start:

        // EAX = ECX
        mov EAX, ECX
    
        // [EDX, EAX] = EAX * 2
        mov EBX, 2
        imul EBX

        // [EDX, EAX] -= 2
        sub EAX, 2
        sbb EDX, 0 // assert EDX == 0,

        // [EDX, EAX] %/= 3
        mov EBX, 3
        idiv EBX

        // if EDX == 0
        cmp EDX, 0
        jne number_not_match

        // :счётчик
        pop EBX 

        // EBX += 1
        inc EBX 

        // if EBX == 200
        cmp EBX, 200
        jne number_no_200
        
        // 
        mov dword ptr number_under_number_200, ECX

        number_no_200:

        // : temp
        push EBX

        number_not_match:
    
        // for: ECX <= 100000
        cmp ECX, 100000
        je loop_end

        // for: ECX++
        inc ECX
        jmp loop_start

        loop_end:

        // : счётчик
        pop EBX
        mov dword ptr number_of_matching_numbers, EBX
    }

    printf("Количество подходящих чисел: %d 0x%04X\n", number_of_matching_numbers, number_of_matching_numbers);
    printf("Число под номером 200: ");
    if (number_under_number_200 != -1)
        printf("%d 0x%04X\n", number_under_number_200, number_under_number_200);
    else
        printf("чисел меньше 200\n");
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
