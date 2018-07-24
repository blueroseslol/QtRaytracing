#include "sampler.h"
#include <QDebug>
Sampler::Sampler():count(0),numSamples(1),numSets(1),jump(0)
{

}

Sampler::Sampler(const int &_numSamples):numSamples(_numSamples),count(0),numSets(1),jump(0)
{

}

Sampler::Sampler(const int &_numSamples,const int& _numSets):numSamples(_numSamples),count(0),numSets(_numSets),jump(0)
{

}


int Sampler::getNumSamples() const
{
    return numSamples;
}

Point2D Sampler::sampleUnitSquare(){
    if(count%numSamples==0){
        //TODO:qrand()是个伪随机函数，先测试效果，如果不行再换
        jump=(qrand()%numSets)*numSamples;
    }
    return samples[jump+count++%(numSamples)];
//    return (samples[count++%(numSamples*numSets)]);
}
