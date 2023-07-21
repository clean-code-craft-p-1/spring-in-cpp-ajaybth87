#include<iostream>
#include <vector>
#include<algorithm>
#include <numeric>
#include <limits>
#define NAN (std::numeric_limits<double>::quiet_NaN())

namespace Statistics {
    struct Stats
    {
       double average;
       double max;
       double min;
    };

    Stats ComputeStatistics(const std::vector<double>& );

    template<typename T>
    double getAverage(std::vector<T> const& data) {
        if (data.empty()) {
            return 0;
        }
        return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
    }
}


namespace Alert
{
    class IAlerter
    {
    public:
        IAlerter() :maxThreshold{ 0 } {}
        virtual void setThreshold(double) = 0;
        virtual void alert(const std::vector<double>&) = 0;
    protected:
        double maxThreshold;   
        virtual ~IAlerter() {};
    };

    class EmailAlert :public IAlerter
    {
    public:
        bool emailSent;
    public:
        EmailAlert();
        void alert(const std::vector<double>& Container) override;
        void setThreshold(double Thresold) override;
        ~EmailAlert();
    };

    class LEDAlert :public IAlerter
    {
    public:
        bool ledGlows;
    public:
        LEDAlert();
        void alert(const std::vector<double>& Container) override;
        void setThreshold(double Thresold) override;
        ~LEDAlert();
    };


    class StatsAlerter
    {
        std::vector<IAlerter*> alerters;
    public:
        StatsAlerter();
        StatsAlerter(double, std::vector<IAlerter*>);
        void checkAndAlert(const std::vector<double>& Container);
        ~StatsAlerter();
    };
}