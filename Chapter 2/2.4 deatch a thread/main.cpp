/*
  Listing 2.4
  Detaching a thread to handle other documents
*/

#include <string>
#include <thread>

enum cmd_type { open_new_document };

struct user_command {
  cmd_type type;
  user_command(cmd_type t) : type{t} {}
};

void open_document_and_display_gui(std::string const &);
bool done_editing();
cmd_type get_user_input();
std::string get_filename_from_user();
void process_user_input(user_command);

void edit_document(std::string const &filename) {
  open_document_and_display_gui(filename);
  while (!done_editing()) {
    user_command cmd{get_user_input()};
    if (cmd.type == open_new_document) {
      std::string const new_name{get_filename_from_user()};
      std::thread t(edit_document, new_name);
      t.detach();
    } else {
      process_user_input(cmd);
    }
  }
}
