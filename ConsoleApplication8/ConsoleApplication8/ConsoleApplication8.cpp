// ConsoleApplication8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include <chrono>
#include <random>

class monte_carlo
{
public:
    double stock_price;
    double strike_price;
    double volatility;
    double time_to_maturity;
    double risk_free_rate;

    double euro_call(int sims) 
    {
        unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
        std::default_random_engine e(seed);
        std::normal_distribution<double> rand_norm(0, 1);
        double sum = 0;
        for (size_t i = 0; i < sims; i++)
        {
            sum += std::max(0.0,(stock_price * std::exp(((risk_free_rate - (0.5 * volatility * volatility)) * time_to_maturity)
                + (volatility*std::sqrt(time_to_maturity)*rand_norm(e))))-strike_price);
        }
        return std::exp(-1 * risk_free_rate * time_to_maturity) * (sum / sims);
    }

    double euro_put(int sims)
    {
        unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
        std::default_random_engine e(seed);
        std::normal_distribution<double> rand_norm(0, 1);
        double sum = 0;
        for (size_t i = 0; i < sims; i++)
        {
            sum += std::max(0.0,strike_price-
                (stock_price * std::exp(((risk_free_rate - (0.5 * volatility * volatility)) * time_to_maturity)
                + (volatility * std::sqrt(time_to_maturity) * rand_norm(e)))));
        }
        return std::exp(-1 * risk_free_rate * time_to_maturity) * (sum/sims);
    }


};


int main()
{
    monte_carlo m;
    m.risk_free_rate = 0.03;
    m.stock_price = 300;
    m.strike_price = 250;
    m.time_to_maturity = 1;
    m.volatility = 0.15;
    std::cout << m.euro_call(100000000);
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
