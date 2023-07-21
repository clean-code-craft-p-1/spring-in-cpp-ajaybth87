#include "stats.h"


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

Alert::EmailAlert::EmailAlert()
{
    maxThreshold = 0;
    emailSent = false;
}

Alert::EmailAlert::~EmailAlert()
{
    // Do nothing
}
void Alert::EmailAlert::alert(const std::vector<double>& Container)
{
    auto itr = max_element(Container.begin(), Container.end());
    if (*itr > maxThreshold)
    {
        emailSent = true;
    }

}

void Alert::EmailAlert::setThreshold(double Thresold)
{
    maxThreshold = Thresold;
}


Alert::LEDAlert::LEDAlert()
{
    maxThreshold = 0;
    ledGlows = false;
}

Alert::LEDAlert::~LEDAlert()
{
    //Do nothing
}

void Alert::LEDAlert::alert(const std::vector<double>& Container)
{
    auto itr = max_element(Container.begin(), Container.end());
        if (*itr > maxThreshold)
        {
            ledGlows = true;  
        }
}

void Alert::LEDAlert::setThreshold(double Thresold)
{
    maxThreshold = Thresold;
}

Alert::StatsAlerter::StatsAlerter()
{
    alerts = { nullptr };
}

Alert::StatsAlerter::StatsAlerter(double thresold, std::vector<IAlerter*> container)
{
    alerts = container;
    for (auto itr = alerts.begin();itr != alerts.end();itr++)
    {
        (*itr)->setThreshold(thresold);
    }
}

void Alert::StatsAlerter::checkAndAlert(const std::vector<double>& Container)
{
    for (auto itr = alerts.begin();itr != alerts.end();itr++)
    {
        (*itr)->alert(Container);
    }
}