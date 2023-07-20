#include "stats.h"

using namespace std;


Statistics::Stats Statistics::ComputeStatistics(const std::vector<double>& Container ) {
   Statistics::Stats obj;
   if (!Container.empty()) {
       auto iter1 = std::max_element(Container.begin(), Container.end());
       obj.max = *iter1;
       auto iter2 = std::min_element(Container.begin(), Container.end());
       obj.min = *iter2;
       obj.average = getAverage(Container);
   }
   else
   {
       obj.max = NAN;
       obj.min = NAN;
       obj.average = NAN;
   }
   return obj;
}

EmailAlert::EmailAlert()
{
    maxThreshold = 0;
    emailSent = false;
}

void EmailAlert::checkAndAlert(const std::vector<double>& Container) 
{
    for (auto itr = Container.begin();itr != Container.end();itr++)
    {
        if (*itr > maxThreshold) {
            emailSent = true;
            break;
        }
    }

}

void EmailAlert::setThreshold(double Thresold)
{
    maxThreshold = Thresold;
}


LEDAlert::LEDAlert()
{
    maxThreshold = 0;
    ledGlows = false;
}

void LEDAlert::checkAndAlert(const std::vector<double>& Container)
{
    for (auto itr = Container.begin();itr != Container.end();itr++)
    {
        if (*itr > maxThreshold) {
            ledGlows = true;
            break;
        }
    }
}

void LEDAlert::setThreshold(double Thresold)
{
    maxThreshold = Thresold;
}

StatsAlerter::StatsAlerter()
{
    alerts = { nullptr };
}

StatsAlerter::StatsAlerter(double thresold, std::vector<IAlerter*> container)
{
    alerts = container;
    for (auto itr = alerts.begin();itr != alerts.end();itr++)
    {
        (*itr)->setThreshold(thresold);
    }
}

void StatsAlerter::checkAndAlert(const std::vector<double>& Container)
{
    for (auto itr = alerts.begin();itr != alerts.end();itr++)
    {
        (*itr)->checkAndAlert(Container);
    }
}