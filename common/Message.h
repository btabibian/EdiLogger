#ifndef MESSAGE_H_
#define MESSAGE_H_
#include <iostream>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/time_serialize.hpp>
//! Message class container of all types of messages.
class Message
{
    friend class boost::serialization::access;
public:
    //! constructur for Message.
    /*!
      \param type type of the message.
    */
    Message(std::string sender="")
    {
        time=boost::posix_time::second_clock::universal_time();
        this->sender=sender;
    }
    //! returns type of message/
    /*!
      \returns type of the message.
    */
    std::string GetDataType()
    {
        return type;
    }
    //! Returns time stamp of the message.
    /*!
      \returns time in which the message was sent.
    */
    boost::posix_time::ptime GetTimeStamp()
    {
        return time;
    }
    //! returns sender of the message.
    /*!
      \returns name of the sender.
    */
    std::string getSender()
    {
        return sender;
    }
    //! This function sets the data that message delivers.
    /*!
      \param Mdata message data to send.
    */
    template<class T>
    void setData(T& Mdata)
    {
        type=Mdata.getType();
        std::stringstream ss("");
        boost::archive::text_oarchive ar(ss);
        ar << Mdata;
        data=ss.str();

    }
    //! This function returns data which this message contains.
    /*!
      \param dat reference to part of memory to write message..
    */
    template<class T>
    void getData(T& dat)
    {

        std::stringstream ss(data);
        boost::archive::text_iarchive ar(ss);
        ar >> dat;

    }
    std::string data;
private:
    std::string type;
    std::string sender;
    boost::posix_time::ptime time;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & type;
        ar & time;
        ar & sender;
        ar & data;
    }
};
#endif
