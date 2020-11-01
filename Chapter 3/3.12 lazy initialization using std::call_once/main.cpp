/*
  Listing 3.12
  Thread-safe lazy initialization of a class member using std::call_once
*/

#include <mutex>

struct connection_info {};

struct data_packet {};

struct connection_handle {
  void send_data(data_packet);
  data_packet receive_data();
};

struct connection {
  connection_handle open(connection_info);
};

connection connection_manager;

class X {
private:
  connection_info connection_details_;
  connection_handle conn;
  std::once_flag connection_init_flag;
  void open_connection() {
    conn = connection_manager.open(connection_details_);
  }

public:
  X(connection_info const &connection_details)
      : connection_details_{connection_details} {}
  void send_data(data_packet const &data) {
    std::call_once(connection_init_flag, &X::open_connection, this);
    conn.send_data(data);
  }
  data_packet receive_data() {
    std::call_once(connection_init_flag, &X::open_connection, this);
    return conn.receive_data();
  }
};

/*
  This can be used as an alternative to std::call_once for those cases where a
  single global instance is required.
*/

class my_class {};

/*
  Multiple threads can then call get_my_class_instance safely, without having
  to worry about race conditions on the initialization.
*/
my_class &get_my_class_instance() {
  static my_class instance; // Initialization guaranteed to be thread-safe
  return instance;
}
