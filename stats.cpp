#include "stats.h"


Statistics::Stats Statistics::ComputeStatistics(const std::vector<double>& container ) {
   Statistics::Stats obj;
   if (!container.empty()) {
       auto iter1 = std::max_element(container.begin(), container.end());
       obj.max = *iter1;
       auto iter2 = std::min_element(container.begin(), container.end());
       obj.min = *iter2;
       obj.average = getAverage(container);
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
void Alert::EmailAlert::alert(const std::vector<double>& container)
{
    auto itr = max_element(container.begin(), container.end());
    if (*itr > maxThreshold)
    {
        emailSent = true;
    }

}

void Alert::EmailAlert::setThreshold(double thresoldValue)
{
    maxThreshold = thresoldValue;
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

void Alert::LEDAlert::setThreshold(double thresoldValue)
{
    maxThreshold = thresoldValue;
}

Alert::StatsAlerter::StatsAlerter()
{
    alerters = { nullptr };
}

Alert::StatsAlerter::StatsAlerter(double thresold, std::vector<IAlerter*> alertersVar)
{
    this->alerters = alertersVar;
    for (auto itr = alerters.begin();itr != alerters.end();itr++)
    {
        (*itr)->setThreshold(thresold);
    }
}

void Alert::StatsAlerter::checkAndAlert(const std::vector<double>& Container)
{
    for (auto itr = alerters.begin();itr != alerters.end();itr++)
    {
        (*itr)->alert(Container);
    }
}

Alert::StatsAlerter::~StatsAlerter()
{
    alerters.clear();
}