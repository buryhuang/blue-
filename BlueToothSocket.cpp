#include "stdafx.h"
#include "BlueToothSocket.h"

BOOL CBlueToothSocket::Create(BOOL authenticate, BOOL encrypt) {
//    debug(("socket"));
	// create socket

	SOCKET s = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);

	if (s == INVALID_SOCKET) {
		//throwIOExceptionWinGetLastError(env, "Failed to create socket");
		Utils::ShowError(TEXT("socket"));
		return FALSE;
	}

	// set socket options

	if (authenticate) {
		ULONG ul = TRUE;

		if (setsockopt(s, SOL_RFCOMM, SO_BTH_AUTHENTICATE, (char *)&ul, sizeof(ULONG))) {
			closesocket(s);
			//throwIOExceptionWinGetLastError(env, "Failed to set authentication option");
			Utils::ShowError(TEXT("socket"));
			return FALSE;
		}
	}

	if (encrypt) {

		ULONG ul = TRUE;

		if (setsockopt(s, SOL_RFCOMM, SO_BTH_ENCRYPT, (char *)&ul, sizeof(ul))) {
			closesocket(s);
			//throwIOExceptionWinGetLastError(env, "Failed to set encryption option");
			Utils::ShowError(TEXT("socket"));
			return FALSE;
		}
	}
	//debug(("socket[%u] opened", (int)s));
	m_socket = s;
	return TRUE;
}




BOOL CBlueToothSocket::Connect(long socket, long address, int channel, int retryUnreachable) {
    //debug(("socket[%u] connect", (int)socket));

	SOCKADDR_BTH addr;

	memset(&addr, 0, sizeof(SOCKADDR_BTH));

	addr.addressFamily = AF_BTH;
	addr.btAddr = address;
	addr.port = channel;

	int retyCount = 0;
connectRety:
	if (connect((SOCKET)socket, (sockaddr *)&addr, sizeof(SOCKADDR_BTH))) {
		retyCount ++;
		int last_error = WSAGetLastError();
		//10051 - A socket operation was attempted to an unreachable network. / Error other than time-out at L2CAP or Bluetooth radio level.
		if (last_error == WSAENETUNREACH) {
			if ((retyCount < retryUnreachable) && (retryUnreachable > 0)) {
//			    if (isCurrentThreadInterrupted(env, peer, "connect")) {
 //                   return;
//                }
				//debug(("connectRety %i", retyCount));
				goto connectRety;
			}
		}
		if (last_error == WSAEACCES) {
			//throwBluetoothConnectionException(env, BT_CONNECTION_ERROR_SECURITY_BLOCK, "Connecting application requested authentication, but authentication failed [10013] .");
			Utils::ShowError(TEXT("Connect"));
			return FALSE;
		} else if (last_error == WSAETIMEDOUT) {
			//throwBluetoothConnectionException(env, BT_CONNECTION_ERROR_TIMEOUT, "Connection timeout; [%lu] %S", last_error, getWinErrorMessage(last_error));
			Utils::ShowError(TEXT("Connect"));
			return FALSE;
		} else {
			//throwBluetoothConnectionException(env, BT_CONNECTION_ERROR_FAILED_NOINFO, "Failed to connect; [%lu] %S", last_error, getWinErrorMessage(last_error));
			Utils::ShowError(TEXT("Connect"));
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CBlueToothSocket::Bind(long socket) {
	// bind socket
//	debug(("socket[%u] bind", (int)socket));

	SOCKADDR_BTH addr;
	memset(&addr, 0, sizeof(addr));
	addr.addressFamily = AF_BTH;

	addr.port = BT_PORT_ANY;

	if (bind((SOCKET)socket, (SOCKADDR *)&addr, sizeof(addr))) {
		closesocket((SOCKET)socket);
		//throwIOExceptionWSAGetLastError(env, "Failed to bind socket");
		Utils::ShowError(TEXT("Bind"));
		return FALSE;
	}
	return TRUE;
}

BOOL CBlueToothSocket::Listen(long socket) {
    //debug(("socket[%u] listen", (int)socket));
	if (listen((SOCKET)socket, 10)) {
		//throwIOExceptionWSAGetLastError(env, "Failed to listen socket");
		Utils::ShowError(TEXT("Listen"));
		return FALSE;
	}
	return TRUE;
}

SOCKET CBlueToothSocket::Accept(long socket) {
	//debug(("socket[%u] accept", (int)socket));
	SOCKADDR_BTH addr;

	int size = sizeof(SOCKADDR_BTH);

	SOCKET s = accept((SOCKET)socket, (sockaddr *)&addr, &size);

	if (s == INVALID_SOCKET) {
		//throwIOException(env, "Failed to listen socket");
		Utils::ShowError(TEXT("Accept"));
		return 0;
	}

	//debug(("connection accepted"));

	return s;
}

int CBlueToothSocket::RecveiveAvailable(long socket) {
	unsigned long arg = 0;
	if (ioctlsocket((SOCKET)socket, FIONREAD, &arg) != 0) {
		//throwIOExceptionWSAGetLastError(env, "Failed to read available");
		Utils::ShowError(TEXT("recvAvailable"));
		return 0;
	}
	return (int)arg;
}

void CBlueToothSocket::Close(long socket) {
	//debug(("socket[%u] close", (int)socket));
	if (shutdown((SOCKET)socket, SD_BOTH) != 0) {
	    int last_error = WSAGetLastError();
	    if (last_error != WSAENOTCONN) {
	        //debug(("shutdown error [%i] %S", last_error, getWinErrorMessage(last_error)));
	    }
		Utils::ShowError(TEXT("close"));

	}
	if (closesocket((SOCKET)socket)) {
		//throwIOExceptionWSAGetLastError(env, "Failed to close socket");
		Utils::ShowError(TEXT("close"));
	}
}

int CBlueToothSocket::Recveive(long socket) {
	//debug(("socket[%u] recv()", (int)socket));
	// Use non blocking functions to see if we have one byte
	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 500 * 1000; //microseconds
    while (TRUE) {
        fd_set readfds;
        fd_set exceptfds;
        FD_ZERO(&readfds);
        FD_SET((SOCKET)socket, &readfds);
        FD_ZERO(&exceptfds);
        FD_SET((SOCKET)socket, &exceptfds);
        int ready_count = select(FD_SETSIZE, &readfds, NULL, &exceptfds, &timeout);
        if (ready_count == SOCKET_ERROR) {
	        //throwIOExceptionWSAGetLastError(env, "Failed to read(int)/select");
			Utils::ShowError(TEXT("Receive"));
	        return -1;
	    } else if (ready_count > 0) {
            break;
        }
    }
    // Read the data when available
	unsigned char c;
	int rc = recv((SOCKET)socket, (char *)&c, 1, 0);
	if (rc == SOCKET_ERROR) {
		//throwIOExceptionWSAGetLastError(env, "Failed to read(int)");
		Utils::ShowError(TEXT("Receive"));
		return 0;
	} else if (rc == 0) {
		//debug(("Connection closed"));
		// See InputStream.read();
		return -1;
	}
	return (int)c;
}

size_t CBlueToothSocket::Recveive(long socket, BYTEBUFFER buff) {
	//debug(("socket[%u] recv (byte[],int,int=%i)", (int)socket, len));
	BYTEBUFFER tmpbuff;
	int BUFFSIZE = 5000;
	size_t len= RecveiveAvailable(socket);

	if(len<=0){
		return -1;
	}

	buff.clear();
	buff.reserve(len);

	// Use non blocking functions to see if we have one byte
    struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 500 * 1000; //microseconds
    while (TRUE) {
        fd_set readfds;
        fd_set exceptfds;
        FD_ZERO(&readfds);
        FD_SET((SOCKET)socket, &readfds);
        FD_ZERO(&exceptfds);
        FD_SET((SOCKET)socket, &exceptfds);
        int ready_count = select(FD_SETSIZE, &readfds, NULL, &exceptfds, &timeout);
        if (ready_count == SOCKET_ERROR) {
	        //throwIOExceptionWSAGetLastError(env, "Failed to read(byte[])/select");
			Utils::ShowError(TEXT("Receive"));
	        return -1;
	    } else if (ready_count > 0) {
            break;
        }
    }
    // Read the data when available
    size_t done = 0;
	while(done < len) {
		tmpbuff.clear();
		tmpbuff.resize(BUFFSIZE);
		size_t count = recv((SOCKET)socket, &tmpbuff[0], static_cast<int>(tmpbuff.size()), 0);

		if (count == SOCKET_ERROR) {
			//throwIOExceptionWSAGetLastError(env, "Failed to read(byte[])");
			Utils::ShowError(TEXT("Receive"));
			done = -1;
			break;
		} else if (count == 0) {
			//debug(("Connection closed"));
			if (done == 0) {
				// See InputStream.read();
				done = -1;
			    break;
			} else {
				break;
			}
		}
		ASSERT(count>=0);
		tmpbuff.resize(count);
		buff.insert(buff.end(),tmpbuff.begin(),tmpbuff.end());		

		done += count;
		if (done != 0) {
            unsigned long available = 0;
	        if (ioctlsocket((SOCKET)socket, FIONREAD, &available) != 0) {
	            // error;
	            break;
	        } else if (available == 0) {
	            break;
	        }
		}
	}

	return done;
}

size_t CBlueToothSocket::Send(long socket, BYTEBUFFER buff)
{
	//debug(("socket[%u] send(byte[],int,int=%i)", (int)socket, len));

	//jbyte *bytes = env->GetByteArrayElements(b, 0);
	size_t done = 0;
	size_t len = buff.size();
	while (done < buff.size()) {
		size_t count = send((SOCKET)socket, &buff[0], static_cast<int>(len - done), 0);
		if (count <= 0) {
			//throwIOExceptionWSAGetLastError(env, "Failed to write");
			Utils::ShowError(TEXT("Send"));
			break;
		}
		done += count;
	}
	return done;

}
