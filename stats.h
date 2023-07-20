
#include<iostream>
#include <vector>
#include<algorithm>
#include <numeric>


namespace Statistics {
    struct Stats
    {
       double average;
       double max;
       double min;
    };

    Stats ComputeStatistics(const std::vector<double>& );

    template<typename T>
    double getAverage(std::vector<T> const& v) {
        if (v.empty()) {
            return 0;
        }
        return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
    }
}

class IAlerter
{
public:
    double maxThreshold;
public:
    virtual void checkAndAlert(const std::vector<double>&) = 0;
    virtual void setThreshold(double) = 0;
};

class EmailAlert :public IAlerter
{
public:
    bool emailSent;
    public:
        EmailAlert();
        void checkAndAlert(const std::vector<double>& Container) override;
        void setThreshold(double Thresold) override;
};

class LEDAlert :public IAlerter
{
public:
    bool ledGlows;
public:
    LEDAlert();
    void checkAndAlert(const std::vector<double>& Container) override;
    void setThreshold(double Thresold) override;
};


class StatsAlerter
{
    std::vector<IAlerter*> alerts;
public:
    StatsAlerter();
    StatsAlerter(double, std::vector<IAlerter*>);
    void checkAndAlert(const std::vector<double>& Container);
};