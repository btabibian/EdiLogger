/**
 * @author Behzad Tabibian
 *
 * Version : $Id$
 * This file was generated by Aldebaran Robotics ModuleGenerator
 */

#include <alcommon/alproxy.h>
#include <alvalue/alvalue.h>
#include <alcore/alptr.h>
#include <alcommon/albroker.h>
#include <alcommon/almodule.h>
#include "comclient.h"
#include "ALMessages.h"

//______________________________________________
// constructor
//______________________________________________
comClient::comClient(AL::ALPtr<AL::ALBroker> broker, const std::string& name ): AL::ALModule(broker, name )
{
    try
    {
        setModuleDescription( "This module connects to ther robots and recieves information from them" );
    }
    catch(std::exception ex)
    {
        std::cout<<"Error happened in Communication"<<std::endl;
    }
}
void comClient::init()
{
    try
    {
        WorkerThread=new boost::thread(boost::bind(&comClient::Observer,this));
    }
    catch(std::exception ex)
    {
        std::cout<<"Error happened in Communication"<<std::endl;
    }

}
void comClient::Observer()
{
    loadConfig();
    service.run();
}

bool comClient::loadConfig()
{

    std::ifstream configFile("/home/nao/data/Comm_Config.txt");

    if(!configFile)
    {
        std::cout<<"Error loading config file";
        return false;
    }
    std::cout<<"Loading cofiguration variables"<<std::endl;
    std::set<std::string> options;
    options.insert("*");
    AL::ALValue peers;
    std::string port="";
    try
    {
        for (pod::config_file_iterator i(configFile,options),ex;i!=ex;++i)
        {

            if (std::strcmp(i->string_key.c_str(),"Comm_Config.IP")==0)
            {
                std::string IP=i->value[0];
                AL::ALValue name=IP;
                peers.arrayPush(name);
                std::cout<<"Connecting to:"<<IP<<":"<<port<<std::endl;
                CommChannel::CommChannel_ptr channel=CommChannel::CommChannel_ptr(new CommChannel(service,IP,port,this->getParentBroker()->getMemoryProxy()));
                channels.push_back(channel);
                continue;

            }
            if (std::strcmp(i->string_key.c_str(),"Comm_Config.Port")==0)
            {


                port=i->value[0];
                continue;

            }
        }
        std::cout<<"end of loading cofiguration variables"<<std::endl;
    }
    catch(std::exception& ex)
    {
        std::cout<<"Something went wrong while loading config file:"<<ex.what()<<std::endl;
        configFile.close();
    }
    configFile.close();
    this->getParentBroker()->getMemoryProxy()->insertData("Peers",peers);
    return true;


}
CommChannel::CommChannel(boost::asio::io_service& serv,std::string ip,std::string port,AL::ALPtr<AL::ALMemoryProxy> memoryPtr)
{
    this->srv=&serv;
    this->ip=ip;
    this->port=port;
    this->memoryProPtr=memoryPtr;
    conn=tcp_connection_serialized::connection_serialized_ptr(new tcp_connection_serialized(serv));
    networklayer(serv);
}
void CommChannel::reconnect(int count,boost::asio::io_service* service=0)
{
    if (!count)
    {
        std::cout<<"Unable to reconnect. drop!"<<std::endl;
        return;
    }
    try
    {
        if(!service)
            service=srv;
        std::cout << "reConnecting to"<<ip<< std::endl;
        boost::asio::ip::tcp::resolver resolver(*service);
        boost::asio::ip::tcp::resolver::query Q(boost::asio::ip::tcp::v4(),ip,port);
        boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(Q);
        boost::asio::ip::tcp::resolver::iterator end;
        boost::system::error_code error = boost::asio::error::host_not_found;
        while (error && endpoint_iterator != end)
        {
            //tcpClient.close();
            conn->socket().close();
            conn->socket().connect(*endpoint_iterator++);
            conn->async_read(data,boost::bind(&CommChannel::handle_read,(this),
                                              boost::asio::placeholders::error));
            std::cout<<"Connected to"<<ip<<std::endl;
        }
    }
    catch(std::exception& ex)
    {
        std::cout<<ex.what();
        std::cout<<"Unable to reconnect Wait..."<<std::endl;
        sleep(2);
        boost::this_thread::interruption_point();
        reconnect(count-1);

    }
}

void CommChannel::networklayer(boost::asio::io_service& service)
{
    try
    {

        std::cout << "Connecting" << std::endl;
        boost::asio::ip::tcp::resolver resolver(service);
        boost::asio::ip::tcp::resolver::query Q(boost::asio::ip::tcp::v4(),ip,port);
        boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(Q);
        boost::asio::ip::tcp::resolver::iterator end;
        boost::asio::ip::tcp::socket tcpClient(service);
        boost::system::error_code error = boost::asio::error::host_not_found;
        while (error && endpoint_iterator != end)
        {
            tcpClient.close();
            conn->socket().connect(*endpoint_iterator++);
            conn->async_read(data,boost::bind(&CommChannel::handle_read,(this),
                                              boost::asio::placeholders::error));

        }
    }
    catch(std::exception& ex)
    {
        std::cout<<"Unable to find host or connect"<<std::endl;
        reconnect(20);

    }
}
void CommChannel::handle_read(const boost::system::error_code& e)
{
    if (!e)
    {

        std::string str=(data.data);

        bool done=false;
        AL::ALValue val;

        if(data.GetDataType()=="movement")
        {
            done=true;
            movementMessage msg;
            data.getData(msg);

            val=ALMessages::writeMovementtoMemory(msg);
            val.arrayPush(data.getSender());
            val.arrayPush(boost::posix_time::to_simple_string(data.GetTimeStamp()));

        }
        if(data.GetDataType()=="location")
        {
            done=true;
            locationMessage msg;
            data.getData(msg);

            val=ALMessages::writeLocationtoMemory(msg);
      }

      if(!done)
      {
          std::cout<<"rcvd general data "<<str<<std::endl;
          generalAlMessage msg;
          data.getData(msg);
          val=ALMessages::writeGeneraltoMemory(msg);
            done=true;
        }
        if(done)
        {

            if(data.getSender()=="local")
            {
                memoryProPtr->insertData(data.GetDataType(),val);
            }
            else
            {
                memoryProPtr->insertData(data.getSender()+"\\"+data.GetDataType(),val);
            }
        }
        try
        {
           conn->async_read(data,boost::bind(&CommChannel::handle_read, this,
                  boost::asio::placeholders::error));
        }
        catch(std::exception ex)
        {
            reconnect(20,this->srv);
        }
          }
          else
          {
            std::cout << e.message() << std::endl;
            std::cout<<"reconnecting"<<std::endl;
            reconnect(20);

          }

}
//______________________________________________
// destructor
//______________________________________________
comClient::~comClient()
{

}
CommChannel::~CommChannel()
{

}



