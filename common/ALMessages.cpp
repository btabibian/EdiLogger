#include "ALMessages.h"

locationMessage ALMessages::readLocationfromMemory(AL::ALValue ALLocation,std::string type)
{
    locationMessage k;
    if(type!="")
    {
        k.dataType=type;
    }
    const int startIndex=0;

    k.theta=ALLocation[startIndex];
    k.y=ALLocation[startIndex+1];
    k.x=ALLocation[startIndex+2];
    return k;
}
AL::ALValue ALMessages::writeLocationtoMemory(locationMessage msg)
{
    AL::ALValue res;
   res.arrayPush(msg.theta);
   res.arrayPush(msg.y);
   res.arrayPush(msg.x);
   return res;
}
movementMessage ALMessages::readMovementfromMemory(AL::ALValue ALLocation)
{
    const int startIndex=0;
    movementMessage k;
    k.dtheta=ALLocation[startIndex];
    k.distance=ALLocation[startIndex+1];
    k.angle=ALLocation[startIndex+2];
    return k;
}
AL::ALValue ALMessages::writeMovementtoMemory(movementMessage msg)
{
    AL::ALValue loc;
    loc.arrayPush(msg.dtheta);
    loc.arrayPush(msg.distance);
    loc.arrayPush(msg.angle);
    return loc;
}
AL::ALValue ALMessages::writeGeneraltoMemory(generalAlMessage msg)
{
    AL::ALValue loc;
    loc.unSerializeFromText(msg.messageText.c_str(),msg.length);
    //std::cout<<"rcvd data:"<<loc.serializeToText()<<"From "<<msg.messageText.c_str()<<std::endl;
    return loc;
}
generalAlMessage ALMessages::readgeneralfromMemory(AL::ALValue ALGeneralMsg,std::string type)
{
    generalAlMessage k(type);
    k.messageText=ALGeneralMsg.serializeToText();

    k.length=k.messageText.size();
    return k;
}
