#ifndef MOVEMENTMESSAGE_H_
#define MOVEMENTMESSAGE_H_
#include <iostream>
#include "LogData.h"
//!  movementMessage representing a movement of robot.
class movementMessage:public LogData
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
    //! constructur for movement messages.
    /*!
      \param type type of the message.
    */
    movementMessage(std::string type="movement"):LogData(){dataType=type;};
    //! copy constructur for movement messages.
    /*!
      \param obj message to be copied.
    */
    movementMessage(const movementMessage& obj): LogData()
    {
        this->dataType=obj.dataType;
        this->angle=obj.angle;
        this->distance=obj.distance;
        this->dtheta=obj.dtheta;
    };
    //! destrcutor for movementMessages.
    ~movementMessage(){};
    //! angle in which robot has moved to.
    float angle;
    //! distance which robot has traversed.
    float distance;
    //! change in robot angle.
    float dtheta;

private:
    std::string dataType;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & dataType;
        ar & angle;
        ar & distance;
        ar & dtheta;

    }
};
#endif
