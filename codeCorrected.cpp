#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// Функция для сортировки индексов по ценам
vector<int> sortIndexes(const vector<int>& prices)
{
    vector<int> indexes(prices.size());
    for (int i = 0; i < prices.size(); ++i)
    {
        indexes[i] = i;
    }
    sort(indexes.begin(), indexes.end(), [&](int i, int j) { return prices[i] < prices[j]; });
    return indexes;
}

// Функция для покупки автомобилей
pair<int, vector<int>> buyCars(int N, int S, const vector<int>& prices)
{
    vector<int> sortedIndexes = sortIndexes(prices);
    int boughtCars = 0;
    vector<int> boughtIndexes;
    // Проверка на пустой список автомобилей
    if (N == 0) {
        return { 0, boughtIndexes };
    }

    for (int i : sortedIndexes)
    {
        if (prices[i] <= S && prices[i] >= 0)  // Проверка на отрицательные цены
        {
            S -= prices[i];
            boughtCars++;
            boughtIndexes.push_back(i + 1); // +1 для корректного отображения номеров автомобилей
        }
        else
        {
            break;
        }
    }
    return { boughtCars, boughtIndexes };
}

int main()
{
    setlocale(LC_ALL, "ru");

    int N, S;
    cout << "Введите количество автомобилей и общий бюджет: ";
    while (!(cin >> N >> S) || N < 1 || N > 100 || S < 1 || S > 1000000000)
    {
        cout << "Ошибка ввода! Значения должны быть в диапазоне 1 <= N <= 100 и 1 <= S <= 10^9.\n";
        cin.clear();
    }

    vector<int> prices(N);
    cout << "Введите стоимость каждого автомобиля: ";
    for (int& price : prices)
    {
        while (!(cin >> price))
        {
            cout << "Ошибка ввода! Пожалуйста, введите числовое значение стоимости.\n";
            cin.clear();
        }
        if (price < 0) {
            cout << "Ошибка ввода: цена автомобиля не может быть отрицательной.\n";
            return 1; // Завершаем программу с ошибкой
        }
    }

    auto result = buyCars(N, S, prices);

    cout << "\nКоличество купленных автомобилей: " << result.first << "\n";
    cout << "Номера купленных автомобилей:  ";
    for (int index : result.second)
    {
        cout << "   " << index;
    }

    cout << "\n\nСписок купленных автомобилей с ценами:\n";
    for (int index : result.second)
    {
        cout << "Автомобиль #" << " " << index << "   - Цена: " << "   " << prices[index - 1] << " млн. руб.\n";
    }
    cout << endl;

    return 0;
}