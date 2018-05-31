#include "connection.h"
#include <assert.h>

namespace beam {

Connection::Connection(ProtocolBase& protocol, uint64_t peerId, Connection::Direction d, size_t defaultMsgSize, io::TcpStream::Ptr&& stream) :
    _protocol(protocol),
    _peerId(peerId),
    _msgReader(protocol, peerId, defaultMsgSize),
    _stream(std::move(stream)),
    _direction(d)
{
    assert(_stream);
    _stream->enable_read([this](io::ErrorCode what, void* data, size_t size){ on_recv(what, data, size); });
}

Connection::~Connection()
{}

io::Result Connection::write_msg(const std::vector<io::SharedBuffer>& fragments) {
    return _stream->write(fragments);
}

io::Result Connection::write_msg(const io::SharedBuffer& msg) {
    return _stream->write(msg);
}

void Connection::shutdown() {
    _stream->shutdown();
}

void Connection::on_recv(io::ErrorCode what, const void* data, size_t size) {
    if (what == 0) {
        assert(data && size);
        _msgReader.new_data_from_stream(data, size);
    } else {
        // stream error
        _protocol.on_connection_error(_peerId, what);
    }
}

/// Returns socket address (non-null if connected)
io::Address Connection::address() const {
    return _stream->address();
}

/// Returns peer address (non-null if connected)
io::Address Connection::peer_address() const {
    return _stream->peer_address();
}

} //namespace

