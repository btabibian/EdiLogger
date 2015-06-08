#ifndef LOGDATA_H_
#define LOGDATA_H_
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
//!  super class of all message classes.
class LogData
{
    friend class boost::serialization::access;

public:
    //! returns type of the message.
    virtual std::string getType()=0;
    //! destrcutor for all messages.
    virtual ~LogData() {};
private:
} ;
#endif
