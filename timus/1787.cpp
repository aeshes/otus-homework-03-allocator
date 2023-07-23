#include <iostream>
#include <algorithm>
#include <vector>

int main(int argc, char **argv)
{
    auto cars_per_minute = 0;
    auto time_in_minutes = 0;
    auto cars_in_traffic_jam = 0;

    std::cin >> cars_per_minute;
    std::cin >> time_in_minutes;

    std::vector<int> cars_per_minute_array;

    for (int i = 0; i < time_in_minutes; i++)
    {
        auto t = 0;

        std::cin >> t;

        cars_per_minute_array.push_back(t);
    }

    for (auto cars : cars_per_minute_array)
    {
        cars_in_traffic_jam += cars;

        if (cars_in_traffic_jam >= cars_per_minute)
            cars_in_traffic_jam -= cars_per_minute;
        else
            cars_in_traffic_jam = 0;
    }

    std::cout << cars_in_traffic_jam << std::endl;
}
