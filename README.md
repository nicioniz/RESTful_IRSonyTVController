# RESTful IR Sony TV remote

This is a RESTful server made on Wemos D1 mini board for controlling via IR led a Sony TV.

## Description

The systems acts like a RESTful server that expose api. Every command can be sent using a `PUT` request.
The `GET` at the uri `/remotes` return, in json format, all the commands available.
The `PUT` at every uri like `/remotes/COMMAND` (COMMAND is one of the commands retrive by the `GET` at `/remotes`) make the send of ir command

Every time it boots it search the SSID and the password of the WiFi network to which connect in the EEPROM.
In the case of first boot it doesn't find anything (at the same mode everytime it doesn't find the saved network), so it make a self network, named "Tv remote" and with the password "TV_REMOTE". It can be used in this way (without a internet or WiFi connection), or it can be possibile to upload the new parameter for the WiFi connection (check the end of the main page).
When it connects to a WiFi network it takes the static IP "192.168.1.200", with the netmask "255.255.255.0" (the same as /24) and the gateway "192.168.1.1". It can be possible to edit these configuration in the source.

## Prerequisites

In order to use correctly this project the `ESP8266WebServer` library need some mods.
The library is located, in case of using PlatformIO IDE through Atom.io, under the folder `HOME:/.platformio/packages/framework-arduinoespressif8266/libraries/ESP8266WebServer`

The file to be modified is `src/detail/RequestHandlerImpl.h`

- We had to add the private method that implements a comparation between Strings based on wildcards (? and *).
  We use the method found here https://www.codeproject.com/Articles/1088/Wildcard-string-compare-globbing, thanks to Jack Handy

  After
```c++
      protected:
        ESP8266WebServer::THandlerFunction _fn;
        ESP8266WebServer::THandlerFunction _ufn;
        String _uri;
        HTTPMethod _method;
```
  Add the method in the page as `private`.

- Change the simple equality with the comparision made with that method. In order to not overhead the system in case of not wildcard, is used the old method.
  Comment this part:
```c++
      if (requestUri != _uri)
        return false;
```

  And add:
```c++
      if(_uri.indexOf('*') == -1 && _uri.indexOf('?') == -1) {
        if(requestUri != _uri)
          return false;
        }
          else {
            return wildcmp(&(_uri[0]), &(requestUri[0]));
        }
```

## License

This project is licensed under the GPLv3 License - see the [LICENSE](LICENSE) file for details
