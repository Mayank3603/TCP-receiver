#include "stream_reassembler.hh"
#include <iostream>
// You will need to add private members to the class declaration in `stream_reassembler.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

StreamReassembler::StreamReassembler(const size_t capacity)
    :_output(capacity) {
        acknowledgement=0;
        index_at_end=-1;
        window_buffer_capacity=capacity;

}

//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.
void StreamReassembler::push_substring(const string &data, const size_t index, const bool eof) {
    if(data.size() == 0 && eof == 1){
            _output.end_input();
            return;
         }
  
    if(data.size()==0 || index >=(window_buffer_capacity+ acknowledgement)) return ;
    
    
    if(eof == 1){
        index_at_end = index+data.size();
    }
    int indexx=index;
    for(auto it : data)
        {
        if(indexx<acknowledgement){
            indexx++;
            continue;
        }
        if((indexx)>=(acknowledgement+window_buffer_capacity)){
            break;
        }
        if(mp_unassembled.find(indexx)==mp_unassembled.end()){
            mp_unassembled[indexx]=it;     
        }
        indexx++;
            
    }
    size_t val=acknowledgement;
    string add_to_buffer;
    
    vector<int> visited;

    for(auto it : mp_unassembled){
        
        if(val==it.first){
            visited.push_back(it.first);
            val++;
            add_to_buffer+=it.second;
        }
        else {
            break;
        }
    } 
    for(auto it : visited){      
        mp_unassembled.erase(it);
   
    }
    size_t accepted_in_stream= (add_to_buffer.size()<=_output.remaining_capacity() )? add_to_buffer.size(): _output.remaining_capacity();
    acknowledgement+=accepted_in_stream;
    string to_buffer= add_to_buffer.substr(0,accepted_in_stream);
    _output.write(to_buffer);
    
    if(acknowledgement == index_at_end){
        _output.end_input();
    }

}

size_t StreamReassembler::unassembled_bytes() const {
   return mp_unassembled.size();
}
bool StreamReassembler::empty() const { 
    return  (_output.buffer_empty() && mp_unassembled.empty()) ? true : false;
    }

size_t StreamReassembler::ack_index() const { 
    return acknowledgement;
    
 }