#include "pch.h" 
#include "CppUnitTest.h" 
#include <vector>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

// ������� ��� ���������� �������� ����������� �� ����
vector<int> sortIndexes(int N, vector<int>& A) {
    vector<int> indexes(N);
    for (int i = 0; i < N; ++i) {
        indexes[i] = i;
    }
    sort(indexes.begin(), indexes.end(), [&](int a, int b) {
        return A[a] < A[b];
        });
    return indexes;
}

// ������� ��� ������� �����������
pair<int, vector<int>> buyCars(int N, int S, vector<int>& A) {
    vector<int> indexes = sortIndexes(N, A);
    int boughtCars = 0;
    vector<int> boughtIndexes;
    for (int i = 0; i < N; ++i) {
        if (A[indexes[i]] <= S && A[indexes[i]] >= 0) { // �������� �� ������������� ����
            S -= A[indexes[i]];
            ++boughtCars;
            boughtIndexes.push_back(indexes[i]);
        }
        else {
            break;
        }
    }
    return make_pair(boughtCars, boughtIndexes);
}

// �������� ����� ��� ������� ���������� ��������
TEST_CLASS(SortIndexesTest) {
public:

    // ���� 1: �������� ���������� � ������� �����������
    TEST_METHOD(TestSortIndexesAscending) {
        vector<int> A1 = { 15, 5, 11, 10, 12 };
        vector<int> expected_result1 = { 1, 3, 2, 4, 0 };
        Assert::IsTrue(sortIndexes(A1.size(), A1) == expected_result1);
    }

    // ���� 2: �������� ���������� � ������ ����������
    TEST_METHOD(TestSortIndexesDuplicates) {
        vector<int> A2 = { 5, 5, 10, 1, 2, 1, 20 };
        vector<int> expected_result2 = { 3, 5, 4, 0, 1, 2, 6 };
        Assert::IsTrue(sortIndexes(A2.size(), A2) == expected_result2);
    }

    // ������ ����� ����� �������� ����������� �������
};

// �������� ����� ��� ������� ������� �����������
TEST_CLASS(BuyCarsTest) {
public:

    // ���� 1: ������ �� ������� ������
    TEST_METHOD(TestBuyCarsExample) {
        vector<int> A1 = { 15, 5, 11, 10, 12 };
        int S1 = 30;
        auto result1 = buyCars(A1.size(), S1, A1);
        Assert::AreEqual(result1.first, 3);
        vector<int> expected_indexes1 = { 1, 3, 2 };
        Assert::IsTrue(result1.second == expected_indexes1);
    }

    // ���� 2: �������������� ���� � ������� �������
    TEST_METHOD(TestBuyCarsAdditional) {
        vector<int> A2 = { 5, 10, 1, 2, 1, 20 };
        int S2 = 18;
        auto result2 = buyCars(A2.size(), S2, A2);
        Assert::AreEqual(result2.first, 4);
        vector<int> expected_indexes2 = { 2, 4, 0, 3 }; // ����� ��������� ������� ��������
        sort(expected_indexes2.begin(), expected_indexes2.end()); // ���������� ��������� ��������
        sort(result2.second.begin(), result2.second.end()); // ���������� ����������� ��������
        Assert::IsTrue(result2.second == expected_indexes2);
    }

    // ���� 3: �������� �� ������������� ����
    TEST_METHOD(TestBuyCarsNegativePrices) {
        vector<int> A3 = { -1, -2, -3, -4, -5 };
        int S3 = 10;
        auto result3 = buyCars(A3.size(), S3, A3);
        Assert::AreEqual(result3.first, 0); // �������, ��� ������ �� ����� �������
        vector<int> expected_indexes3 = {};
        Assert::IsTrue(result3.second == expected_indexes3);
    }

    // ���� 4: �������� �� ������������� ������
    TEST_METHOD(TestBuyCarsNegativeBudget) {
        vector<int> A4 = { 1, 2, 3, 4, 5 };
        int S4 = -10;
        auto result4 = buyCars(A4.size(), S4, A4);
        Assert::AreEqual(result4.first, 0); // �������, ��� ������ �� ����� �������
        vector<int> expected_indexes4 = {};
        Assert::IsTrue(result4.second == expected_indexes4);
    }

    // ���� 5: �������� ������� ������ �����������
    TEST_METHOD(TestBuyCarsEmptyList) {
        vector<int> A5 = {}; // ������ ������ �����������
        int S5 = 100;
        auto result5 = buyCars(A5.size(), S5, A5);
        Assert::AreEqual(result5.first, 0); // �������, ��� ������ �� ����� �������
        vector<int> expected_indexes5 = {};
        Assert::IsTrue(result5.second == expected_indexes5);
    }

};
