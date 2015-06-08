#ifndef LOCATIONMESSAGE_H_
#define LOCATIONMESSAGE_H_
#include <iostream>
#include "LogData.h"
//!  locationMessage representing a location messages.
class locationMessage:public LogData
{
    friend class boost::serialization::access;
public:

    //! returns type of the message.
    /*!
      \returns type of the message.
     */
    std::string getType()
    {
        return dataType;
    }
    //! constructur for location messages.
    /*!
      \param type type of the message.
    */
    locationMessage(std::string type="MotionData"):LogData(){dataType=type;};
    //! copy constructur for location messages.
    /*!
      \param obj message to be copied.
    */
    locationMessage(const locationMessage& obj): LogData()
    {
        this->dataType=obj.dataType;
        this->x=obj.x;
        this->y=obj.y;
        this->theta=obj.theta;
        this->conf=obj.conf;
        this->spread=obj.spread;
    };
    //! destrcutor for locationMessages.
    ~locationMessage(){};
    //! X location.
    float x;
    //! Y location.
    float y;
    //! Theta
    float theta;
    float conf;
    float spread;
    //! Type.
    std::string dataType;


private:

    template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & dataType;
        ar & x;
        ar & y;
        ar & theta;
        ar & conf;
        ar & spread;
        //std::cout<<"Serializing Motion "<<x<<std::endl;
    }
};
#endif
