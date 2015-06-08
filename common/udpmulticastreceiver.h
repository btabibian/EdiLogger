#ifndef UDPMULTICASTRECEIVER_H
#define UDPMULTICASTRECEIVER_H

#include "boost/system/error_code.hpp"
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/function.hpp"

class UdpMultiCastReceiver
{
public:
  UdpMultiCastReceiver(boost::asio::io_service& io_service,
      const boost::asio::ip::address& listen_address,
      const boost::asio::ip::address& multicast_address,
      const short multicast_port,
      boost::function<void (const char *data, int len)> callback);

  void handle_receive_from(const boost::system::error_code& error,
      size_t bytes_recvd);

private:
  boost::asio::ip::udp::socket socket_;
  boost::asio::ip::udp::endpoint sender_endpoint_;
  enum { max_length = 1024 };
  char data_[max_length];

  boost::function<void (const char *data, int len)> callback;



};


#endif // UDPMULTICASTRECEIVER_H
