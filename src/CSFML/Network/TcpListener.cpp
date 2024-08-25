////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2023 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <CSFML/Network/TcpListener.h>
#include <CSFML/Network/TcpListenerStruct.hpp>
#include <CSFML/Network/TcpSocketStruct.hpp>
#include <CSFML/Internal.hpp>


////////////////////////////////////////////////////////////
sfTcpListener* sfTcpListener_create()
{
    return new sfTcpListener;
}


////////////////////////////////////////////////////////////
void sfTcpListener_destroy(sfTcpListener* listener)
{
    delete listener;
}


////////////////////////////////////////////////////////////
void sfTcpListener_setBlocking(sfTcpListener* listener, bool blocking)
{
    CSFML_CALL(listener, setBlocking(blocking));
}


////////////////////////////////////////////////////////////
bool sfTcpListener_isBlocking(const sfTcpListener* listener)
{
    CSFML_CALL_RETURN(listener, isBlocking(), false);
}


////////////////////////////////////////////////////////////
unsigned short sfTcpListener_getLocalPort(const sfTcpListener* listener)
{
    CSFML_CALL_RETURN(listener, getLocalPort(), 0);
}


////////////////////////////////////////////////////////////
sfSocketStatus sfTcpListener_listen(sfTcpListener* listener, unsigned short port, sfIpAddress address)
{
    CSFML_CHECK_RETURN(listener, sfSocketError);

    std::optional<sf::IpAddress> sfmlAddress = sf::IpAddress::resolve(address.address);

    if (!sfmlAddress)
    {
        return sfSocketError;
    }

    return static_cast<sfSocketStatus>(listener->This.listen(port, *sfmlAddress));
}


////////////////////////////////////////////////////////////
sfSocketStatus sfTcpListener_accept(sfTcpListener* listener, sfTcpSocket** connected)
{
    CSFML_CHECK_RETURN(listener, sfSocketError);
    CSFML_CHECK_RETURN(connected, sfSocketError);

    *connected = new sfTcpSocket;
    sfSocketStatus status = static_cast<sfSocketStatus>(listener->This.accept((*connected)->This));

    if (status != sfSocketDone)
    {
        delete *connected;
        *connected = nullptr;
    }

    return status;
}