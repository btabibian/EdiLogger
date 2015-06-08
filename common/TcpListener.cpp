#include "TcpListener.h"
#include "Message.h"

namespace tcplib =boost::asio;

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}


  tcp_connection::tcp_connection_pointer tcp_connection::create(boost::asio::io_service& io_service)
  {
    return tcp_connection_pointer(new tcp_connection(io_service));
  }

  tcplib::ip::tcp::socket& tcp_connection::socket()
  {
    return socket_;
  }

  template <typename T>
  void tcp_server::sendData(const T& data)
  {
      listLock.lock();
      try
      {

          std::vector<tcp_connection_serialized::connection_serialized_ptr>::iterator it;
          it=activeConnections.begin();
          while (it<activeConnections.end())
          {

              if (it->get()->socket().is_open())
              {
                 tcp_connection_serialized::connection_serialized_ptr con=*it;
                 it->get()->async_write(data,boost::bind(&tcp_server::handle_write, this, boost::asio::placeholders::error,con));


              }
              else
              {

                  it=activeConnections.erase(it);

              }
              it++;
          }
          listLock.unlock();
      }
      catch (std::exception& ex)
      {

          listLock.unlock();
      }
  }

  template void tcp_server::sendData<Message>(Message const&);
  
  bool tcp_connection::write(std::string& str)
  {
    try
    {
      
    socket_.write_some(boost::asio::buffer(str));
    return true;
    }
    catch(std::exception& ex)
    {
      return false;
    }
     /*boost::asio::write(socket_, boost::asio::buffer(str),
	  boost::bind(&tcp_connection::handle_write, shared_from_this(),
	    boost::asio::placeholders::error,
	    boost::asio::placeholders::bytes_transferred));*/
  }


  tcp_connection::tcp_connection(boost::asio::io_service& io_service)
    : socket_(io_service)
  {
  }

  void tcp_connection::handle_write(const boost::system::error_code& /*error*/,
      size_t /*bytes_transferred*/)
  {
    
  }
  tcp_server::tcp_server(int port): acceptor_(service, tcplib::ip::tcp::endpoint(tcplib::ip::tcp::v4(), port))
  {
       
    start_accept();

    
  }
  tcp_server::tcp_server(int port,boost::asio::io_service& nservice):acceptor_(nservice, tcplib::ip::tcp::endpoint(tcplib::ip::tcp::v4(), port))
  {
    
    start_accept();
  }
void tcp_server::start_accept()
{

tcp_connection_serialized::connection_serialized_ptr new_connection =tcp_connection_serialized::connection_serialized_ptr(new tcp_connection_serialized::tcp_connection_serialized(acceptor_.io_service()));
    acceptor_.async_accept(new_connection->socket(),
        boost::bind(&tcp_server::handle_accept, this, new_connection,
          boost::asio::placeholders::error));
}
void tcp_server::handle_accept(tcp_connection_serialized::connection_serialized_ptr new_connection,
      const boost::system::error_code& error)
      {
    std::cout<<"Incomming connection ..."<<std::endl;
        if(error.value())
            return;
	  listLock.lock();
	    activeConnections.push_back(new_connection);
	    
	   listLock.unlock();
	   std::cout<<"New connection added"<<activeConnections.size()<<std::endl;
           start_accept();
	
      }
void tcp_server::start()
{
  std::cout<<"strating service"<<std::endl;
service.run();
}
void tcp_server::startasync()
{
 boost::thread a(boost::bind(&tcp_server::start,this));
 
}

void tcp_server::handle_write(const boost::system::error_code& e, tcp_connection_serialized::connection_serialized_ptr conn)
{

  if(e.value())
    conn->socket().close();
  
}

