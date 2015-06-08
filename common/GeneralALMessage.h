#ifndef GENERALALMESSAGE_H_
#define GENERALALMESSAGE_H_
#include <iostream>
#include "LogData.h"
//!  generalAlMessage representing a generic message.
class generalAlMessage:public LogData
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
    //! constructur for generic messages.
    /*!
      \param type type of the message.
    */
    generalAlMessage(std::string type="GeneralData"):LogData(){dataType=type;};
    //! copy constructur for generic messages.
    /*!
      \param obj message to be copied.
    */
    generalAlMessage(const generalAlMessage& obj): LogData()
    {
        this->dataType=obj.dataType;
        this->messageText=obj.messageText;
        this->length=obj.length;
    };
    //! destrcutor generic messages.
    ~generalAlMessage(){};
    //! message Text.
    std::string messageText;
    //! message Length.
    int length;
    //! message Type.
    std::string dataType;
private:

    template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & dataType;
        ar & messageText;
        ar & length;

    }
};
#endif
