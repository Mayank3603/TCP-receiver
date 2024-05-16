#include "tcp_receiver.hh"

#include <algorithm>


using namespace std;

void TCPReceiver::segment_received(const TCPSegment &seg) {
    const TCPHeader head = seg.header();


    if(head.fin){
        _finReceived=true;
    }
    if(head.syn){
        _isn=head.seqno;
        _synReceived=true;
        
    }
    
    // ...

    // --- Hint ------
        // convert the seqno into absolute seqno
    uint64_t checkpoint = _reassembler.ack_index();
    uint64_t abs_seqno = unwrap(head.seqno, _isn, checkpoint);
    uint64_t stream_idx = abs_seqno - _synReceived;
    // --- Hint ------  

    // ... 
    string data_to_send = seg.payload().copy();
    _reassembler.push_substring(data_to_send,stream_idx,head.fin);
}

optional<WrappingInt32> TCPReceiver::ackno() const {

   if(!_synReceived){
        return nullopt;
   }
   
    uint64_t value=_reassembler.ack_index()+1;
    if(_finReceived) value+=1;
    return wrap(value,_isn);

   
}

size_t TCPReceiver::window_size() const { 
    return stream_out().remaining_capacity(); 
    }
