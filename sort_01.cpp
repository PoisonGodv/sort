/**
 * 使用随机数生成一个随机数列，使用两种排序，比较两种排序时间性能
 * 随机生成的序列直接用数组存储
 */

#include <iostream>
#include <windows.h>
#include <algorithm>


using namespace std;

/**
 * 选择枢轴，使用int返回
 * 用简单排序后选择中间的数
 * @param num
 * @return
 */
int EssentialSort(int *num, int left, int right) {//简单选择排序
    int swap, min;
    for (int j = left; j < right - 1; ++j) {
        min = j;
        for (int i = j + 1; i < right; ++i) {
            if (num[min] > num[i]) {
                min = i;
            }
        }
        swap = num[j];
        num[j] = num[min];
        num[min] = swap;

    }
    return 1;
}

/**
 * 选择中位数
 * 将枢轴放到最右边减一，可以使得排序判断次数少一
 * @return
 */
int SelectMid(int *num, int left, int right) {
    int center = (left + right) / 2, save;
    if (num[left] > num[center]) {
        save = num[center];
        num[center] = num[left];
        num[left] = save;
    }
    if (num[left] > num[right]) {
        save = num[right];
        num[right] = num[left];
        num[left] = save;
    }
    if (num[center] > num[right]) {
        save = num[center];
        num[center] = num[right];
        num[right] = save;
    }
    save = num[center];
    num[center] = num[right - 1];
    num[right - 1] = save;
    return num[right - 1];
}

/**
 * 递归每一次缩小范围，选择枢轴元素，双指针进行比对
 * 双指针相等时
 * 将该元素放入
 * @param num
 * @param left
 * @param right
 * @return
 */
void QuickSort(int *num, int left, int right) {

    //选择枢轴
    int mid, low, high, swap, cutoff = 10;
    if (cutoff <= right - left) {

        mid = SelectMid(num, left, right);
        low = left;
        high = right - 1;
        //left and right为两个指针，从right - 2和left + 1开始走
        //左边和右边分别与中枢比较，先将中枢储存起来，左右指针相等时，赋值退出循环
        while (true) {
            while (num[++low] < mid);
            while (num[--high] > mid);
            if (low < high) {
                swap = num[low];
                num[low] = num[high];
                num[high] = swap;
            } else
                break;
        }
        swap = num[low];
        num[low] = num[right - 1];
        num[right - 1] = swap;
        //分别递归左边或右边
        //先递归左边，左边下标从left开始，右边下标从righ开始
        QuickSort(num, left, low - 1);
        //递归右边，左边从left+1开始，右边从一开始的right下标开始，为数组长度-1
        QuickSort(num, low + 1, right);
    } else {
        //return;
        EssentialSort(num,left,right);
    }
}


int main() {
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    QueryPerformanceFrequency(&nFreq);

    srand(1);
    int question[1000];
    int question1[1000];
    int question2[1000];
    for (int i = 0; i < 1000; ++i) {
        //循环录入数组
        question[i] = rand() % 100;//随机生成0-100随机数进行排序
    }
    for (int i = 0; i < 1000; ++i) {
        question1[i] = question[i];
    }
    for (int i = 0; i < 1000; ++i) {
        question2[i] = question[i];
    }
    //输出随机数组
    for (int i = 0; i < 1000; ++i) {
        cout << question[i] << " ";
    }
    cout << endl;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);
    //排序后输出
    for (int i = 0; i < 10000; ++i) {
        EssentialSort(question, 0, 1000);
    }
    /*for (int i = 0; i < 1000; ++i) {
        cout << question[i] << " ";
    }*/
    QueryPerformanceCounter(&nEndTime);
    cout << "选择排序程序执行时间" << ((double) (nEndTime.QuadPart - nBeginTime.QuadPart) / (double) nFreq.QuadPart) * 1000 << endl;
    QueryPerformanceCounter(&nBeginTime);
    for (int i = 0; i < 10000; ++i) {
        QuickSort(question1, 0, 999);
    }
    //排序后输出
    /*for (int i = 0; i < 1000; ++i) {
        cout << question1[i] << " ";
    }*/
    QueryPerformanceCounter(&nEndTime);
    cout << "快速排序程序执行时间" << ((double) (nEndTime.QuadPart - nBeginTime.QuadPart) / (double) nFreq.QuadPart) * 1000 << endl;


    QueryPerformanceCounter(&nBeginTime);
    for (int i = 0; i < 10000; ++i) {
        sort(question2,question2+1000);
    }//排序后输出
    /*for (int i = 0; i < 1000; ++i) {
        cout << question1[i] << " ";
    }*/
    QueryPerformanceCounter(&nEndTime);
    cout << "系统排序程序执行时间" << ((double) (nEndTime.QuadPart - nBeginTime.QuadPart) / (double) nFreq.QuadPart) * 1000 << endl;
    return 0;
}


