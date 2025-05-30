#include <iostream>
#include <vector>
#include <algorithm>

int partition(std::vector<int> &arr, int low, int high)
{
   int i = low - 1;
   int pivot = arr[high];
   for (int j = low; j < high; j++)
   {
      if (arr[j] <= pivot)
      {
         i++;
         std::swap(arr[i], arr[j]);
      }
   }
   std::swap(arr[i + 1], arr[high]);
   return i + 1;
}

void quickSort(std::vector<int> &arr, int low, int high)
{
   if (low < high)
   {
      int pi = partition(arr, low, high);
      quickSort(arr, low, pi - 1);
      quickSort(arr, pi + 1, high);
   }
}