/*
  Listing 4.10
  Handling multiple connections from a single thread using promises
*/

#include <deque>
#include <future>

using payload_type = char *;

struct data_packet {
  int id;
  payload_type payload;
};

struct outgoing_packet : data_packet {
  std::promise<bool> promise;
};

struct connection {
  bool has_incoming_data();
  bool has_outgoing_data();
  data_packet incoming();
  std::promise<payload_type> &get_promise(int);
  outgoing_packet top_of_outgoing_queue();
  void send(payload_type);
};

using connection_set = std::deque<connection>;

bool done(connection_set);

void process_connections(connection_set &connections) {
  while (!done(connections)) {
    for (auto connection : connections) {
      if (connection.has_incoming_data()) {
        data_packet data{connection.incoming()};
        std::promise<payload_type> &p{connection.get_promise(data.id)};
        p.set_value(data.payload);
      }
      if (connection.has_outgoing_data()) {
        outgoing_packet data{connection.top_of_outgoing_queue()};
        connection.send(data.payload);
        data.promise.set_value(true);
      }
    }
  }
}
