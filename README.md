# TCP Protocol Implementation

This assignment focuses on implementing essential components of TCP (Transmission Control Protocol) for reliable communication over a network. TCP ensures that data sent from one point to another is received accurately and in order, despite the unreliable nature of the underlying network.

## PART 1: Building ByteStream

In this part of the assignment, you will construct a ByteStream class responsible for storing and managing a collection of bytes in a reliable byte stream fashion. The ByteStream class is designed with specific properties to handle the transmission and reception of data efficiently:

- **Writing and Reading Bytes:** Bytes are written on the input side and read out from the output side of the ByteStream.
- **Finite Stream:** The byte stream has a finite length, meaning that once the writer ends the input, no more bytes can be written.
- **End of File (EOF):** When the reader reaches the end of the stream, it encounters EOF, indicating no more bytes are available to read.
- **Capacity Limit:** The byte stream is initialized with a capacity limit, restricting the total amount of bytes that can be held in memory at once.
- **Writer Constraints:** The writer is restricted from writing into the byte stream if it exceeds the storage capacity.
- **Dynamic Capacity:** As the reader consumes bytes from the stream, the writer is allowed to write more.
- **Single-Threaded Context:** The ByteStream operates in a single-threaded context, eliminating concerns about race conditions.

## PART 2: Building a Reassembler

In this segment of the assignment, you will develop a Reassembler class responsible for reassembling substrings of bytes received from the sender and arranging them into a contiguous byte stream. The Reassembler class addresses challenges posed by the unreliable nature of the network, where datagrams may arrive out of order, be dropped, or duplicated.

### Key components of the Reassembler:

- **Insert Method:** Informs the Reassembler about a new excerpt of the byte stream and its position within the larger stream.
- **Handling Categories of Knowledge:**
  - Next bytes in the stream.
  - Buffered bytes that fit within the stream’s capacity but can't be written yet.
  - Bytes beyond the stream’s capacity, which are discarded.

The Reassembler aims to optimize memory usage by limiting the storage of bytes in both the reassembled ByteStream and internally within the Reassembler.

## PART 3: Building the TCP Receiver

The final part of the assignment involves implementing an actual TCP receiver that integrates the ByteStream and Reassembler components to correctly receive and write bytes into the byte stream. Additionally, the TCP Receiver generates receiver messages back to the sender, indicating:

- **Acknowledgement Number (ackno):** Index of the first unassembled byte.
- **Window Size:** Available capacity in the output ByteStream.

### Key considerations include:

- **TCP Sequence Numbers:** Handling 32-bit integers wrapping around, random initial sequence numbers, and reliable transmission of the beginning and end of the byte stream.
- **Conversion Routines:** Implementing conversion routines for WrappingInt32 to manage sequence number representations.
