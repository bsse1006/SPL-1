#include <iostream>
#include <math.h>
#include "stat.h"
#include <vector>
#include <map>

using namespace std;

double mean (vector <double> vec)
{
    double sum = 0;

    int num = 0;

    vector <double> :: iterator itr;

    for(itr=vec.begin();itr!=vec.end();itr++)
    {
        if(*itr<=100.0&&*itr>=0.0)
        {
            sum+=*itr;
            num++;
        }
    }

    double meanPercentage = sum / num;

    if(meanPercentage==0.0)
        return 1;
    else if(meanPercentage==100.0)
        return 99;

    return meanPercentage;
}

double variance (double mean,vector <double> vec)
{
    double squaredSumOfDifferences=0;

    int num = 0;

    vector <double> :: iterator itr;

    for(itr=vec.begin();itr!=vec.end();itr++)
    {
        if(*itr<=100.0&&*itr>=0.0)
        {
            squaredSumOfDifferences+=(*itr-mean)
            *(*itr-mean);
            num++;
        }
    }

    double variance = squaredSumOfDifferences/num;

    if(variance==0.0)
        return 1;

    return variance;
}

double alphaParameter (double mean, double variance)
{
    return (((1-(mean/100))/(variance/10000))
        -(1/(mean/100)))*
        ((mean/100)*(mean/100));
}

double betaParameter (double mean, double variance)
{
    return (alphaParameter(mean,variance))*((1/(mean/100))-1);
}

double betaFunction (double mean, double variance)
{
    double a = alphaParameter(mean,variance);
    double b = betaParameter(mean,variance);
    return ((pow(2*3.1416,0.5))*(pow(a,a-0.5)*pow(b,b-0.5)))/pow((a+b),a+b-0.5);
}

double normalDistribution (double mean, double variance, double tempMean)
{
    return (1/(sqrt(2*3.1416*variance/10000)))*exp(-((pow(tempMean/100-mean/100,2))/(2*variance/100)));
}

double betaDistribution (double mean, double variance, double tempMean)
{
    double a = alphaParameter(mean,variance);
    double b = betaParameter(mean,variance);
    double betaFunctionValue = betaFunction(mean,variance);

    if(isnan((pow(tempMean/100,a-1)*pow(1-(tempMean/100),b-1))/betaFunctionValue)
       ||isinf((pow(tempMean/100,a-1)*pow(1-(tempMean/100),b-1))/betaFunctionValue))
        return normalDistribution(mean,variance,tempMean);
    return (pow(tempMean/100,a-1)*pow(1-(tempMean/100),b-1))/betaFunctionValue;
}

int matchingRankSum (map <int,double> proMap)
{
    map <int,double> :: iterator mapItr;

    double maximum=0;
    int deAnoID=0;

    for(mapItr=proMap.begin();mapItr!=proMap.end();mapItr++)
    {
        if(mapItr->second>maximum)
        {
            maximum=mapItr->second;
            deAnoID=mapItr->first;
        }
    }

    return deAnoID;
}
