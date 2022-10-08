#include <algorithm>
#include <iostream>
#include <string>

/******************************************************************************
 * Generate parity bits for the given binary string.
 *
 * @param message Binary string.
 * @param num_of_bits Number of parity bits.
 *
 * @return Message with parity bits appended.
 *****************************************************************************/
std::string helper(std::string const& message, int unsigned num_of_bits)
{
    int unsigned rem = std::count(message.begin(), message.end(), '1') % (1 << num_of_bits);
    std::string appendee;
    while(rem > 0)
    {
        if((rem & 1) == 1)
        {
            appendee.push_back('1');
        }
        else
        {
            appendee.push_back('0');
        }
        rem >>= 1;
    }
    while(appendee.size() < num_of_bits)
    {
        appendee.push_back('0');
    }
    std::reverse(appendee.begin(), appendee.end());
    return message + appendee;
}

/******************************************************************************
 * https://codegolf.stackexchange.com/questions/252491
 *****************************************************************************/
int main(void)
{
    std::string message;
    std::cin >> message;
    int unsigned num_of_bits;
    std::cin >> num_of_bits;
    std::string result = helper(message, num_of_bits);
    std::cout << result << "\n";
}
