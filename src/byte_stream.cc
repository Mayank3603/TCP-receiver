#include "byte_stream.hh"

#include <algorithm>

// You will need to add private members to the class declaration in `byte_stream.hh`

/* Replace all the dummy definitions inside the methods in this file. */


using namespace std;

ByteStream::ByteStream(const size_t capa)
{
          input_full=false;
          capacity=capa;
          total_popped=0;
          total_writes=0;
          _error=false;
}

size_t ByteStream::write(const string &data) {
  if(dq.size()>=capacity || input_full==true) {
    return 0;
  }
  size_t data_len=data.size();
  size_t accepted_in_stream= (data_len<this->remaining_capacity())?data_len: this->remaining_capacity();

  for(size_t i=0;i<accepted_in_stream;i++){
    dq.push_back(data[i]);
    total_writes++;
  }
  return accepted_in_stream;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
  string str="";
 
  size_t peek_most=(len>this->buffer_size())? this->buffer_size() : len;
  
  for(size_t i=0;i<peek_most;i++){
    str+=dq[i];
  }
  return str;
}


//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
   
    if(len>this->buffer_size()) {
      set_error();
      return ;
    }
    //size_t removed_from_stream=(len<this->buffer_size()) ? len: this->buffer_size();
    else{
      for(size_t i=0;i<len;i++){
      dq.pop_front();
      total_popped++;
    }
    }
    
}
    
//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
  if(len>this->buffer_size()) {
      set_error();
      return "";
    }
  else{
    string copied_str=peek_output(len);
    pop_output(len);
    return copied_str;
  }
 
}

void ByteStream::end_input() {  input_full=true; }

bool ByteStream::input_ended() const { 
  return input_full;
  }


size_t ByteStream::buffer_size() const {return dq.size(); }

bool ByteStream::buffer_empty() const {return dq.empty(); }

bool ByteStream::eof() const { 
  return (input_ended() && buffer_empty()); }


size_t ByteStream::remaining_capacity() const { return capacity-this->buffer_size() ;}
size_t ByteStream::bytes_written() const { return total_writes; }
size_t ByteStream::bytes_read() const { return total_popped;  }