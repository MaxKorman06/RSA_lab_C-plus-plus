#include <iostream>
#include <math.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

bool Prime_num(long int); // Перевірка на просте число
long int calculate_d(long int); // Обирається випадкове число d, взаємно просте с m;
long int Great_Com_Div(long int, long int); // Найбільший спільний дільник
long int calculate_e(long int, long int); // Визначається таке число e, для якого є істинним вираз : (e ⋅ d) mod(m) = 1
long int encrypt(long int, long int, long int); // Шифрування
long int decrypt(long int, long int, long int); // Розшифрування

int main()
{
    setlocale(LC_ALL, "Russian");//Робимо можливим вивід кирилиці на екран консолі

    long int p, q, n, m, d, e;
    bool f;
    string message;

    long int enc_text[255];
    memset(enc_text, 0, sizeof(enc_text)); // Заповнюєм усю память масиву нулями

    long int dec_text[255];
    memset(dec_text, 0, sizeof(dec_text));

    cout << "Ласкаво просимо до програми RCA\n\nВи можете використовувати будь-яку пару простих чисел наприклад 3 та 17" << endl << endl;

    do // 1. Обираються два великі прості числа p и q
    {
        cout << "Введiть просте число p:" << endl;
        cin >> p;
        f = Prime_num(p);

        if (f == false)
        {
            cout << "\nНЕПРАВИЛЬНИЙ ВВIД (Це число не є простим. Просте число — це натуральне число, бiльше 1, яке не має додатних дiльникiв, крім 1 i самого себе\n" << endl;
        }
    } while (f == false);


    do // 1. Обираються два великі прості числа p и q
    {
        cout << "Введiть просте число q:" << endl;
        cin >> q;
        f = Prime_num(q);

        if (f == false)
        {
            cout << "\nНЕПРАВИЛЬНИЙ ВВIД (Це число не є простим. Просте число — це натуральне число, більше 1, яке не має додатних дiльникiв, крім 1 i самого себе\n" << endl;
        }
    } while (f == false);

    
    n = p * q; // 2.1 Обчислюється: n = p ⋅ q 
    cout << "\nРезультат обчислень n = p*q = " << n << endl;

    m = (p - 1) * (q - 1); // 2.2 Обчислюється: m = (p – 1) ⋅ (q – 1)
    cout << "Результат обчислення функцiї Ейлера: t = " << m << endl;

    d = calculate_d(m); // 3. Обирається випадкове число d, взаємно просте с m;

    e = calculate_e(d, m); // 4. Визначається таке число e, для якого є істинним вираз: (e ⋅ d) mod (m) = 1

    cout << "\nВiдкритий ключ RSA це (n = " << n << ", d = " << d << ")" << endl; // 5.1 Числа e та n – це відкритий ключ

    cout << "Закритий ключ RSA це (n = " << n << ", e = " << e << ")" << endl; // 5.2 Числа d и n – це закритий ключ

    cout << "\nВведiть повiдомлення, яке потрiбно зашифрувати\n\nВАЖЛИВО!!! використовути лише латинськi лiтери, iнакше програмf може працювати некорректно" << endl;

  
    cin.ignore(); // У вхідному потоці залишився символ нового рядка, тому ми використовуємо ignore()

    getline(std::cin, message);

    cout << "\nПовiдомлення це: " << message << endl;

    for (long int i = 0; i < message.length(); i++) // Шифрування
    {
        enc_text[i] = encrypt(message[i], d, n);
    }

    cout << "\nЗашивповане повiдомлення це:" << endl;

    for (long int i = 0; i < message.length(); i++)
    {
        cout << (char)enc_text[i];
    }

    for (long int i = 0; i < message.length(); i++) // Розшифрування
    {
        dec_text[i] = decrypt(enc_text[i], e, n);
    }

    cout << "\n\nРозшивповане повiдомлення це:" << endl;

    for (long int i = 0; i < message.length(); i++)
    {
        cout << (char)dec_text[i];
    }

    cout << endl;

    return 0;
}

bool Prime_num(long int prime) // Перевірка на просте число
{
    long int i, j;

    j = (long int)sqrt((long double)prime);

    for (i = 2; i <= j; i++)
    {
        if (prime % i == 0)
        {
            return false;
        }
    }

    return true;
}

long int calculate_d(long int m) // Обирається випадкове число d, взаємно просте с m;
{
    long int d;

    for (d = 2; d < m; d++)
    {
        if (Great_Com_Div(d, m) == 1)
        {
            return d;
        }
    }

    return -1;
}

long int Great_Com_Div(long int d, long int m) // Найбільший спільний дільник
{
    while (d > 0)
    {
        long int myTemp;

        myTemp = d;
        d = m % d;
        m = myTemp;
    }

    return m;
}

long int calculate_e(long int d, long int m) // Визначається таке число e, для якого є істинним вираз : (e ⋅ d) mod(m) = 1
{
    long int e;
    long int k = 1;

    while (1)
    {
        k = k + m;

        if (k % d == 0)
        {
            e = (k / d);
            return e;
        }
    }
}

long int encrypt(long int i, long int d, long int n) // Шифрування
{
    long int current, result;

    current = i - 100;
    result = 1;

    for (long int j = 0; j < d; j++)
    {
        result = result * current;
        result = result % n;
    }

    return result;
}

long int decrypt(long int i, long int d, long int n) // Розшифрування
{
    long int current, result;

    current = i;
    result = 1;

    for (long int j = 0; j < d; j++)
    {
        result = result * current;
        result = result % n;
    }

    return result + 100;
}