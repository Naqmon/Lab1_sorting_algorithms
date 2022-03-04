import sys
import time
import random
import array as arr
def swap_array(array):
    n = array.buffer_info()[1]
    for i in range(0, n):
        array[i] = i
    for i in range(0, n // 20):
        a = random.randint(0, n - 1)
        b = random.randint(0, n - 1)
        array[a], array[b] = array[b], array[a]

def quick_sort(array, left, right):
    if (left >= right): return
    i, j = left, right
    pivot = array[(j + i) >> 1]
    while i <= j:
        while array[i] < pivot: i += 1
        while array[j] > pivot: j -= 1
        if i <= j:
            array[i], array[j] = array[j], array[i]
            i, j = i + 1, j - 1
    quick_sort(array, left, j)
    quick_sort(array, i, right)

def radix_sort(array):
    n = array.buffer_info()[1]
    buffer = arr.array('L', [random.randint(0, 10**9) for _ in range (n)])
    basis = 256;
    for shift in range(0, 32, 8):
        rem = arr.array('L', [i for i in range(256)])
        for i in range(0, n):
            rem[(array[i] >> shift) & basis - 1] += 1;
        for i in range(1, basis):
            rem[i] += rem[i - 1];
        for i in range(n - 1, 0, -1):
            rem[(array[i] >> shift) & (basis - 1)] -= 1
            buffer[rem[(array[i] >> shift) & (basis - 1)]] = array[i];
        buffer, array = array, buffer

if(__name__ == "__main__"):
    random.seed(int(sys.argv[1]))
    array = arr.array('L', [random.randint(0, 10**9) for _ in range (int(sys.argv[1]))])
    #swap_array(array)
    n = array.buffer_info()[1]
    start = time.time()
    radix_sort(array)
    stop = time.time()
    print(stop - start)
