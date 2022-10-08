#include <iostream>
#include <vector>

/******************************************************************************
 * Given two vectors of non-negative integers which are equal in length, return
 * a vector which has the element `A[0]` repeated `R[0]` times, then element
 * `A[1]` repeated `R[1]` times, and so on.
 *
 * @param A
 * @param R
 * @param size Number of elements in `A`, which is also the number of elements
 *     in `R`.
 *
 * @return Vector with repeated values.
 *****************************************************************************/
std::vector<int> helper(std::vector<int> const& A, std::vector<int> const& R, int size)
{
    std::vector<int> result;
    for(int i = 0; i < size; ++i)
    {
        result.resize(result.size() + R[i], A[i]);
    }
    return result;
}

/******************************************************************************
 * https://codegolf.stackexchange.com/questions/252442
 *****************************************************************************/
int main(void)
{
    int size;
    std::cin >> size;

    std::vector<int> A(size);
    std::vector<int> R(size);
    for(int i = 0; i < size; ++i)
    {
        std::cin >> A[i];
    }
    for(int i = 0; i < size; ++i)
    {
        std::cin >> R[i];
    }
    std::vector<int> result = helper(A, R, size);
    for(auto const& r: result)
    {
        std::cout << r << " ";
    }
    std::cout << "\n";
}
